cmake_minimum_required (VERSION 2.6)

project(RedZoneTest)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	# turn on C++11 features
	set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

set(RZT_SOURCES
    main.cpp
)

set(RZT_HEADERS
)

add_subdirectory(libRedZone)

include_directories(${RedZone_SOURCE_DIR}/src)

add_executable(RedZoneTest ${RZT_SOURCES} ${RZT_HEADERS})

target_link_libraries(RedZoneTest RedZone)

configure_file(test.tpl test.tpl COPYONLY)
configure_file(inc_test.tpl inc_test.tpl COPYONLY)
configure_file(test.json test.json COPYONLY)
configure_file(base_test.tpl base_test.tpl COPYONLY)
configure_file(middle_test.tpl middle_test.tpl COPYONLY)


# building language extension

if(DEFINED BUILD_LANG_EXTENSION)

    if(${BUILD_LANG_EXTENSION} MATCHES "python")
        set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake )
    
        include( UseCython )
        
        set_source_files_properties(
            cython/RedZone.pyx
            PROPERTIES CYTHON_IS_CXX TRUE
        )
        cython_add_module(PyRedZone cython/RedZone.pyx)
        target_link_libraries(PyRedZone RedZone)
        set_target_properties(PyRedZone PROPERTIES PREFIX "")
        set_target_properties(PyRedZone PROPERTIES OUTPUT_NAME "RedZone")
        
        configure_file(cython/test.py test.py COPYONLY)
        
	if(WIN32)
		#add_definitions(-DMS_NO_COREDLL)
	endif(WIN32)
        
    endif(${BUILD_LANG_EXTENSION} MATCHES "python")
    
    # TODO: add extensions for other languages

endif(DEFINED BUILD_LANG_EXTENSION)
