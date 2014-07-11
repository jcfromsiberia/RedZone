cmake_minimum_required (VERSION 2.6)

project(RedZone)

# turn on C++11 features
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

set(RZ_SOURCES
    src/Common.cpp
    src/Context/Context.cpp
    src/Context/json11.cpp
    src/Exception/Exception.cpp
    src/Exception/ExpressionException.cpp
    src/Exception/IOError.cpp
    src/Exception/JsonError.cpp
    src/Exception/TemplateContextError.cpp
    src/Exception/TemplateSyntaxError.cpp
    src/IO/FileReader.cpp
    src/IO/FileWriter.cpp
    src/IO/Reader.cpp
    src/IO/StringReader.cpp
    src/IO/StringWriter.cpp
    src/IO/Writer.cpp
    src/Node/IfNode.cpp
    src/Node/IncludeNode.cpp
    src/Node/EachNode.cpp
    src/Node/ElseNode.cpp
    src/Node/Node.cpp
    src/Node/Root.cpp
    src/Node/TextNode.cpp
    src/Node/Variable.cpp
    src/Parser/ExpressionParser.cpp
    src/Parser/Fragment.cpp
    src/Parser/Parser.cpp
    src/Template/FileTemplate.cpp
    src/Template/Template.cpp
)

set(RZ_HEADERS
    src/Common.h
    src/Context/Context.h
    src/Context/json11.hpp
    src/Exception/Exception.h
    src/Exception/ExpressionException.h
    src/Exception/IOError.h
    src/Exception/JsonError.h
    src/Exception/TemplateContextError.h
    src/Exception/TemplateSyntaxError.h
    src/IO/FileReader.h
    src/IO/FileWriter.h
    src/IO/Reader.h
    src/IO/StringReader.h
    src/IO/StringWriter.h
    src/IO/Writer.h
    src/Node/IfNode.h
    src/Node/IncludeNode.h
    src/Node/EachNode.h
    src/Node/ElseNode.h
    src/Node/Node.h
    src/Node/Root.h
    src/Node/TextNode.h
    src/Node/Variable.h
    src/Parser/ExpressionParser.h
    src/Parser/Fragment.h
    src/Parser/Parser.h
    src/Template/FileTemplate.h
    src/Template/Template.h
)

option(BUILD_RZ_SHARED "Build the RedZone library shared." ON)

include_directories(src)

if(BUILD_RZ_SHARED)
    set(RZ_LIBRARY_TYPE SHARED)
    message(STATUS "Building shared library")
else(BUILD_RZ_SHARED)
    set(RZ_LIBRARY_TYPE STATIC)
    message(STATUS "Building static library")
endif(BUILD_RZ_SHARED)

add_library(RedZone ${RZ_LIBRARY_TYPE} ${RZ_SOURCES})
