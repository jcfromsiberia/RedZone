from libcpp cimport bool
from libcpp.map cimport map
from libcpp.vector cimport vector
from libcpp.string cimport string


# class mapping


cdef extern from "<Context/json11.hpp>" namespace "json11":

    cdef cppclass CJson "json11::Json":
        CJson()
        CJson( CJson & )
        CJson( double value )
        CJson( int value )
        CJson( bool value )
        CJson( string & value )
        CJson( char * value )
        CJson( vector[ CJson ] value )
        CJson( map[ string, CJson ] value)

        string dump()

        bool is_number()
        bool is_bool()
        bool is_object()
        bool is_string()
        bool is_array()

        double number_value()
        int int_value()
        bool bool_value()
        string string_value()
        vector[ CJson ] array_items()
        map[ string, CJson ] object_items()


cdef extern from "<Context/json11.hpp>" namespace "json11::Json":
    CJson parse( char *, string & )


cdef extern from "<Context/Context.h>" namespace "RedZone":
    cdef cppclass CContext "RedZone::Context":
        CContext( string & json )

        CContext( CJson & json ) except +

        CJson json()
        void setJson( CJson & json ) except +
        CJson resolve( string & name ) except +


cdef extern from "<IO/Reader.h>" namespace "RedZone":
    cdef cppclass CReader "RedZone::Reader":
        string read( size_t nBytes )
        string readAll()


cdef extern from "<IO/FileReader.h>" namespace "RedZone":
    cdef cppclass CFileReader "RedZone::FileReader" ( CReader ):
        CFileReader( string fileName ) except +
        string read( size_t nBytes )
        string readAll()


cdef extern from "<IO/StringReader.h>" namespace "RedZone":
    cdef cppclass CStringReader "RedZone::StringReader" ( CReader ):
        CStringReader( string & dataString )
        string read( size_t nBytes )
        string readAll()


cdef extern from "<IO/Writer.h>" namespace "RedZone":
    cdef cppclass CWriter "RedZone::Writer":
        void write( string & data )
        void flush()


cdef extern from "<IO/FileWriter.h>" namespace "RedZone":
    cdef cppclass CFileWriter "RedZone::FileWriter" ( CWriter ):
        CFileWriter( string & fileName ) except +
        void write( string & data )
        void flush()


cdef extern from "<IO/StringWriter.h>" namespace "RedZone":
    cdef cppclass CStringWriter "RedZone::StringWriter" ( CWriter ):
        CStringWriter( string & dataString ) except +
        void write( string & data )
        void flush()


cdef extern from "<Template/Template.h>" namespace "RedZone":
    cdef cppclass CTemplate "RedZone::Template":
        void renderToStream( CWriter * stream, CContext * context ) except +
        string render( CContext * context ) except +


cdef extern from "<Template/FileTemplate.h>" namespace "RedZone":
    cdef cppclass CFileTemplate "RedZone::FileTemplate" ( CTemplate ):
        CFileTemplate( string fileName )


# class wrapping


cdef class Context:
    cdef CContext * thisptr

    def __cinit__( self, dict json ):
        strJson = str( json )
        strJson = strJson.replace("'", '"')\
            .replace( "True", "true" )\
            .replace( "False", "false" )\
            .replace( "None", "null" )
        cdef string err
        cdef CJson cjson = parse( strJson, err )
        if err.length():
            raise RuntimeError( "Cannot parse json: " + err )
        self.thisptr = new CContext( cjson )


    property data:
        """
        Context data property, must always be dict.
        """
        def __get__( self ):
            jsonStr = self.thisptr.json().dump()
            jsonStr = jsonStr.replace( "true", "True" )\
                .replace( "false", "False" )\
                .replace( "null", "None" )
            return eval( jsonStr )  # FIXME: doesn't seem so good

        def __set__( self, dict json ):
            strJson = str( json )
            strJson = strJson.replace("'", '"')\
                .replace( "True", "true" )\
                .replace( "False", "false" )\
                .replace( "None", "null" )
            cdef string err
            cdef CJson cjson = parse( strJson, err )
            if err.length():
                raise RuntimeError( "Cannot parse json: " + err )
            self.thisptr.setJson( parse( strJson, err ) )


cdef class Writer:
    cdef CWriter * thisptr

    def write( self, string data ):
        self.thisptr.write( data )

    def flush( self ):
        self.thisptr.flush()


cdef class FileWriter(Writer):
    def __cinit__( self, string fileName ):
        self.thisptr = new CFileWriter( fileName )


cdef class StringWriter(Writer):
    def __cinit__( self, string & data ):
        self.thisptr = new CStringWriter( data )


cdef class Template:
    cdef CTemplate * thisptr

    def renderToStream( self, Writer stream, Context context ):
        self.thisptr.renderToStream( stream.thisptr, context.thisptr )

    def render( self, Context context ):
        return self.thisptr.render( context.thisptr )

cdef class FileTemplate( Template ):
    def __cinit__( self, string fileName ):
        self.thisptr = new CFileTemplate( fileName )