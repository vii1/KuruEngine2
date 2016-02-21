cmake_minimum_required(VERSION 3.0)

project(KuruEngine2)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeTests") 

# Activamos C++11. MSVC lo hace automáticamente si está soportado
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
   SET(ENABLE_CXX14 "-std=c++14")

   # GNU C++ debe ser >= 4.7, en caso contrario activamos C++0x
   if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	   EXECUTE_PROCESS(COMMAND "${CMAKE_CXX_COMPILER} -dumpversion" OUTPUT_VARIABLE GCC_VERSION)
	   if (GCC_VERSION VERSION_LESS 4.7)
	      SET(ENABLE_CXX14 "-std=c++0x")
		elseif( GCC_VERSION VERSION_LESS 4.8 )
			SET( ENABLE_CXX14 "-std=c++11" )
	   endif()
	endif()

   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX14}")
endif()

# Caprichos de MSVC
if(MSVC)
	if(NOT MSVC_VERSION LESS 1800)
		add_compile_options(/FS)
	endif()
#	list(APPEND DEFINES _ITERATOR_DEBUG_LEVEL=0)
endif()

set(BIN_TARGET_DIR ${CMAKE_SOURCE_DIR}/bin)
set(LIB_TARGET_DIR ${CMAKE_SOURCE_DIR}/lib)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
#set(DEPS_DIR ${CMAKE_SOURCE_DIR}/deps)

include_directories(${INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)
