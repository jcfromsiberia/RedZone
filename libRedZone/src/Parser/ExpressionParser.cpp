/*
 * ExpressionParser.cpp
 *
 *      Author: jc
 */
#include "ExpressionParser.h"

#include <algorithm>
#include <ctype.h>
#include <math.h>
#include <regex>
#include <set>
#include <vector>

#include <Context/Context.h>
#include <Exception/ExpressionException.h>
#include <Exception/TemplateContextError.h>

#define MIN_PRIORITY 0
#define MAX_PRIORITY 3
#define ARGS_SIZE_CHECK(SIZE) if( args.size() != SIZE ) { \
   throw Exception( "Got " + std::to_string( args.size() ) + \
                    " arguments, expected " + std::to_string( SIZE ) ); \
   }

using namespace json11;

namespace RedZone
{


// A lot of copy-paste spaghetti code :-( Will refactor?

// Initializing operators

std::vector< std::tuple< std::string, int,
   std::function< Json( Json const &, Json const & ) > > >
   const ExpressionParser::s_binaryOperations {
   std::make_tuple( "+", 2, []( Json const & lhs, Json const & rhs ) -> Json {
      static std::map< std::tuple< Json::Type, Json::Type >,
         std::function< Json( Json const &, Json const & ) > > const possibleOperations {
         { std::make_tuple( Json::NUMBER, Json::NUMBER ),
            []( Json const & lhs, Json const & rhs ) -> Json {
            // Yes-yes, I know about implicit constructors feature
            // but I'd rather to call explicit instead
            return Json( lhs.number_value() + rhs.number_value() );
         }
         },
         { std::make_tuple( Json::STRING, Json::STRING ),
            []( Json const & lhs, Json const & rhs ) -> Json {
            return Json( lhs.string_value() + rhs.string_value() );
         }
         },
         { std::make_tuple( Json::NUMBER, Json::STRING ),
            []( Json const & lhs, Json const & rhs ) -> Json {
            return Json( std::to_string( lhs.number_value() ) + rhs.string_value() );
         }
         },
         { std::make_tuple( Json::STRING, Json::NUMBER ),
            []( Json const & lhs, Json const & rhs ) -> Json {
            return Json( lhs.string_value() + std::to_string( rhs.number_value() ) );
         }
         }
      };
      decltype( possibleOperations )::const_iterator foundOperation;
      if( ( foundOperation = possibleOperations.find( std::make_tuple( lhs.type(), rhs.type() ) ) ) == possibleOperations.end() ) {
         throw Exception( "Type mismatch: can not add " + lhs.dump() + " to " + rhs.dump() );
      }
      return foundOperation->second( lhs, rhs );
   } ),

   std::make_tuple( "-", 2, []( Json const & lhs, Json const & rhs ) -> Json {
      static std::map< std::tuple< Json::Type, Json::Type >,
         std::function< Json( Json const &, Json const & ) > > const possibleOperations {
         { std::make_tuple( Json::NUMBER, Json::NUMBER ),
            []( Json const & lhs, Json const & rhs ) -> Json {
            return Json( lhs.number_value() - rhs.number_value() );
         }
         }
      };
      decltype( possibleOperations )::const_iterator foundOperation;
      if( ( foundOperation = possibleOperations.find( std::make_tuple( lhs.type(), rhs.type() ) ) ) == possibleOperations.end() ) {
         throw Exception( "Type mismatch: can not subtract " + lhs.dump() + " from " + rhs.dump() );
      }
      return foundOperation->second( lhs, rhs );
   } ),

   std::make_tuple( "*", 3, []( Json const & lhs, Json const & rhs ) -> Json {
      static std::map< std::tuple< Json::Type, Json::Type >,
         std::function< Json( Json const &, Json const & ) > > const possibleOperations {
         { std::make_tuple( Json::NUMBER, Json::NUMBER ),
            []( Json const & lhs, Json const & rhs ) -> Json {
            return Json( lhs.number_value() * rhs.number_value() );
         }
         },
         { std::make_tuple( Json::STRING, Json::NUMBER ),
            []( Json const & lhs, Json const & rhs ) -> Json {
            std::string repeated;
            if( rhs.number_value() < 0.f ) {
               throw Exception( "String multiplier is negative" );
            }
            for( auto i = 0; i < rhs.number_value(); ++i ) {
               repeated += lhs.string_value();
            }
            return Json( repeated );
         }
         },
      };

      decltype( possibleOperations )::const_iterator foundOperation;
      if( ( foundOperation = possibleOperations.find( std::make_tuple( lhs.type(), rhs.type() ) ) ) == possibleOperations.end() ) {
         throw Exception( "Type mismatch: can not multiply " + lhs.dump() + " and " + rhs.dump() );
      }
      return foundOperation->second( lhs, rhs );
   } ),
   std::make_tuple( "/", 3, []( Json const & lhs, Json const & rhs ) -> Json {
      static std::map< std::tuple< Json::Type, Json::Type >,
         std::function< Json( Json const &, Json const & ) > > const possibleOperations {
         { std::make_tuple( Json::NUMBER, Json::NUMBER ),
            []( Json const & lhs, Json const & rhs ) -> Json {
            return Json( lhs.number_value() / rhs.number_value() );
         }
         }
      };
      decltype( possibleOperations )::const_iterator foundOperation;
      if( ( foundOperation = possibleOperations.find( std::make_tuple( lhs.type(), rhs.type() ) ) ) == possibleOperations.end() ) {
         throw Exception( "Type mismatch: can not divide " + lhs.dump() + " by " + rhs.dump() );
      }
      return foundOperation->second( lhs, rhs );
   } ),
   std::make_tuple( ">", 1, []( Json const & lhs, Json const & rhs ) -> Json {
      return lhs > rhs;
   } ),
   std::make_tuple( "<", 1, []( Json const & lhs, Json const & rhs ) -> Json {
      return lhs < rhs;
   } ),
   std::make_tuple( "==", 1, []( Json const & lhs, Json const & rhs ) -> Json {
      return lhs == rhs;
   } ),
   std::make_tuple( "!=", 1, []( Json const & lhs, Json const & rhs ) -> Json {
      return lhs != rhs;
   } ),
   std::make_tuple( "<=", 1, []( Json const & lhs, Json const & rhs ) -> Json {
      return lhs <= rhs;
   } ),
   std::make_tuple( ">=", 1, []( Json const & lhs, Json const & rhs ) -> Json {
      return lhs >= rhs;
   } ),
   std::make_tuple( "&&", 0, []( Json const & lhs, Json const & rhs ) -> Json {
      return lhs.bool_value() && rhs.bool_value();
   } ),
   std::make_tuple( "||", 0, []( Json const & lhs, Json const & rhs ) -> Json {
      return lhs.bool_value() || rhs.bool_value();
   } )
   // we need more gol... operators!
};

// /Initializing operators

// Initializing functions

std::map< std::string,
   std::function< Json( std::vector< Json > const & ) > > const ExpressionParser::s_functions {
   { "sin", []( std::vector< Json > const & args ) -> Json {
      ARGS_SIZE_CHECK( 1 );
      if( !args[ 0 ].is_number() ) {
         throw Exception( "Function accepts only numeric arguments" );
      }
      return Json( ::sin( args[ 0 ].number_value() ) );
   } },
   { "cos", []( std::vector< Json > const & args ) -> Json {
      ARGS_SIZE_CHECK( 1 );
      if( !args[ 0 ].is_number() ) {
         throw Exception( "Function accepts only numeric arguments" );
      }
      return Json( ::cos( args[ 0 ].number_value() ) );
   } },
   { "length", []( std::vector< Json > const & args ) -> Json {
      ARGS_SIZE_CHECK( 1 );
      Json arg = args[ 0 ];
      if( arg.is_array() ) {
         return Json( int( arg.array_items().size() ) );
      } else if( arg.is_object() ) {
         return Json( int( arg.object_items().size() ) );
      } else if( arg.is_string() ) {
         return Json( int( arg.string_value().size() ) );
      } else {
         throw Exception( "Can not calculate length of non-iterable object: " + arg.dump() );
      }
   } },
   { "not", []( std::vector< Json > const & args ) -> Json {
      ARGS_SIZE_CHECK( 1 );
      return Json( !args[ 0 ].bool_value() );
   } },
   { "get", []( std::vector< Json > const & args ) -> Json {
      ARGS_SIZE_CHECK( 2 );
      Json container = args[ 0 ];
      Json key = args[ 1 ];
      Json result;
      if( container.is_array() ) {
         if( !key.is_number() ) {
            throw Exception( "Key must be number, got " + key.dump() );
         }
         return container[ static_cast< size_t >( key.number_value() ) ];
      } else if( container.is_object() ) {
         if( !key.is_string() ) {
            throw Exception( "Key must be string, got " + key.dump() );
         }
         return container[ key.string_value() ];
      } else if( container.is_string() ) {
         if( !key.is_number() ) {
            throw Exception( "Key must be number, got " + key.dump() );
         }
         return Json(
            std::string( 1, container.string_value()[ static_cast< size_t >( key.number_value() ) ] ) );
      }
      throw Exception( "Can not get anything from " + container.dump() );
   } },
   { "lower", []( std::vector< Json > const & args ) -> Json {
      ARGS_SIZE_CHECK( 1 );
      if( !args[ 0 ].is_string() ) {
         throw Exception( "Can not make lower non-string objects" );
      }
      std::string arg = args[ 0 ].string_value();
      std::string result;
      std::transform( arg.begin(), arg.end(), std::back_inserter( result ), ::tolower );
      return Json( result );
   } },
   { "upper", []( std::vector< Json > const & args ) -> Json {
      ARGS_SIZE_CHECK( 1 );
      if( !args[ 0 ].is_string() ) {
         throw Exception( "Can not make upper non-string objects" );
      }
      std::string arg = args[ 0 ].string_value();
      std::string result;
      std::transform( arg.begin(), arg.end(), std::back_inserter( result ), ::toupper );
      return Json( result );
   } }

   // ... and functions as well
};

// /Initializing functions

ExpressionParser::ExpressionParser( Context const * context )
   : m_context( context )
{
}

Json ExpressionParser::parse( std::string expression ) const {
   // removing spaces
//   expression.erase( std::remove_if( expression.begin(), expression.end(), ::isspace ), expression.end() );

   {
      // validating
      // FIXME: do not count brackets between quotes
      static std::vector< std::tuple< std::string, char, char > > const validationData {
         std::make_tuple( "Parentheses mismatch", '(', ')' ),
         std::make_tuple( "Square brackets mismatch", '[', ']' ),
         std::make_tuple( "Braces mismatch", '{', '}' ),
         std::make_tuple( "Quotes mismatch", '"', '"' ),
      };
      for( auto data: validationData ) {
         if( std::count( expression.begin(), expression.end(), std::get< 1 >( data ) ) !=
             std::count( expression.begin(), expression.end(), std::get< 2 >( data ) ) ) {
            throw ExpressionException( expression, std::get< 0 >( data ) );
         }
      }
   }
   Json result;
   try {
      result = parseRecursive( expression );
   }
   catch( Exception const & ex ) {
      throw ExpressionException( expression, std::string( " occurred an exception " ) + ex.what() );
   }
   return result;
}

Json ExpressionParser::parseRecursive( std::string expression ) const {

   std::string err;

   // trying to convert the expression to json
   Json result = Json::parse( expression, err );
   if( !err.length() ) {
      return result;
   }

   // trimming expression
   expression.erase( expression.begin(), std::find_if( expression.begin(), expression.end(),
           std::not1( std::ptr_fun< int, int >( std::isspace ) ) ) );
   expression.erase( std::find_if( expression.rbegin(), expression.rend(),
           std::not1( std::ptr_fun< int, int >( std::isspace ) ) ).base(), expression.end() );

   // perhaps that's a variable
   try {
      result = m_context->resolve( expression );
      return result;
   }
   catch ( TemplateContextError & ) {
      // FFFFUUUUU~!
   }

   // ok... then that's a complex expression, have to parse it... damn! I hate this
   if( expression.front() == '(' && expression.back() == ')' ) {
      // Ok... we might omit parentheses around this expression
      // but something like "(1 + 2) + (3 + 4)" breaks everything!
      // Checking for this sh#t
      bool skip = false;
      int pcount = 0;
      for( auto i = expression.begin(); i != expression.end() ; ++i ) {
         if( *i == '(' ) {
            pcount++;
         } else if ( *i == ')' ) {
            pcount--;
         }
         if( !pcount && i + 1 != expression.end() ) {
            skip = true;
            break;
         }
      }
      if( !skip ) {
         return parseRecursive( expression.substr( 1, expression.length() - 2 ) );
      }
   }

   // if the expression is a function call
   static std::regex const funcRegex( R"(^(\w+)\s*\((.+)\)$)" );
   std::smatch funcMatch;
   if( std::regex_match( expression, funcMatch, funcRegex ) ) {
      std::string funcName = funcMatch[ 1 ];
      decltype( s_functions )::const_iterator foundFunc;
      if( ( foundFunc = s_functions.find( funcName ) ) == s_functions.end() ) {
         throw ExpressionException( expression, "No such function: " + funcName );
      }
      std::string argsString = funcMatch[ 2 ];
      std::vector< Json > args;
      int pcount = 0, qbcount = 0, bcount = 0;
      bool inQuotes = false;
      decltype( argsString )::const_iterator start = argsString.begin(), current = argsString.begin();
      for( ; current != argsString.end(); ++current ) {
         if( *current == '"' ) {
            inQuotes = !inQuotes;
         }
         if( inQuotes ) {
            continue;
         }
         if( *current == '(' ) {
            pcount++;
         }
         else if( *current == ')' ) {
            pcount--;
         }
         if( *current == '[' ) {
            qbcount++;
         }
         else if( *current == ']' ) {
            qbcount--;
         }
         if( *current == '{' ) {
            bcount++;
         }
         else if( *current == '}' ) {
            bcount--;
         }
         // monkeycoding... hate this!
         bool isInBrackets = pcount != 0 || qbcount != 0 || bcount != 0;
         bool nextIsEnd = current + 1 == argsString.end();
         if( !isInBrackets && ( *current == ',' || nextIsEnd ) ) {
            std::string argExpr;
            std::copy( start, current + ( nextIsEnd ? 1 : 0 ), std::back_inserter( argExpr ) );
            args.push_back( parseRecursive( argExpr ) );
            start = current + 1; // FIXME: oops, it's dangerous
         }
      }
      try {
         result = foundFunc->second( args );
      }
      catch( Exception const & ex ) {
         throw ExpressionException( expression, foundFunc->first + " raised exception: " + ex.what() );
      }
      return result;
   }

   typedef std::set< char > charset;
   static charset operatorChars;
   if( !operatorChars.size() ) {
      for( auto i = s_binaryOperations.begin(); i != s_binaryOperations.end(); ++i ) {
         std::string opString = std::get< 0 >( *i );
         std::for_each( opString.begin(), opString.end(),
            std::bind(
               static_cast< std::pair< charset::iterator, bool > ( charset::* )( const charset::value_type & ) >(
                  &std::set< char >::insert ), &operatorChars, std::placeholders::_1 ) );
      }
   }

   // it the expression is an expression exactly...
   for( int priority = MIN_PRIORITY; priority <= MAX_PRIORITY; ++priority ) {
      int len = expression.length(), i = 0, pcount = 0;
      bool inQuotes = false;
      std::string lhs, rhs;
      i = len - 1;
      while( i >= 0 ) {
         if( expression[ i ] == '"' ) {
            inQuotes = !inQuotes;
         }
         if( inQuotes ) {
            i--;
            continue;
         }
         if( expression[ i ] == ')' ) {
            pcount++;
         }
         else if( expression[ i ] == '(' ) {
            pcount--;
         }
         auto finder = [&]( std::tuple< std::string, int,
            std::function< json11::Json( json11::Json const &, json11::Json const & ) > > const & opData ) {
            if( priority != std::get< 1 >( opData ) )
               return false;
            std::string op = std::get< 0 >( opData );
            std::string possibleOp;
            int sensor = i;
            for( ;
               sensor < expression.length() && operatorChars.find( expression[ sensor ] ) != operatorChars.end();
               ++sensor ) {
               possibleOp.push_back( expression[ sensor ] );
            }
            return op == possibleOp;
         };
         decltype( s_binaryOperations )::const_iterator opIter;
         if( !pcount && operatorChars.find( expression[ i ] ) != operatorChars.end() &&
            ( opIter = std::find_if( s_binaryOperations.begin(), s_binaryOperations.end(), finder ) ) != s_binaryOperations.end() ) {
            rhs = expression.substr( i + std::get< 0 >( *opIter ).length() );
            lhs = expression.substr( 0, i );
            try {
               result = std::get< 2 >( *opIter )( parseRecursive( lhs ), parseRecursive( rhs ) );
            }
            catch( Exception const & ex ) {
               throw ExpressionException( expression, "operator " + std::get< 0 >( *opIter ) + " raised exception: " + ex.what() );
            }
            return result;
         }
         i--;
      }
   }

   // else
   throw ExpressionException( expression, "Wrong syntax or undefined variable" );
}

ExpressionParser::~ExpressionParser()
{
}

} /* namespace RedZone */
