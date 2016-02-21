cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

project(KuruEngine)

SET(CMAKE_PROJECT_NAME KuruEngine2)
SET(PROJECT_NAME KuruEngine2)
if(MSVC)
  #set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcprt /NODEFAULTLIB:MSVCRT")
  #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt")
  add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
endif()

include(FindSDL2 REQUIRED)
include(FindSDL2_image REQUIRED)
if("${SDL2_IMAGE_VERSION_STRING}" VERSION_LESS "2.0.0")
	message(SEND_ERROR "Se requiere SDL_image >= 2.0.0")
endif()
include(FindSDL2_mixer REQUIRED)
if("${SDL2_MIXER_VERSION_STRING}" VERSION_LESS "2.0.0")
	message(SEND_ERROR "Se requiere SDL_mixer >= 2.0.0")
endif()
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${INCLUDE_DIR})

file(GLOB TEST_SOURCES
  "*.cpp"
)

add_executable(KuruTest ${TEST_SOURCES})

add_dependencies(KuruTest gtest kuru2)
target_link_libraries(
    KuruTest
    general gtest
    general $<TARGET_FILE:kuru2>
    #debug ${LIB_INSTALL_DIR}/kuru-debug.lib
    #optimized ${LIB_INSTALL_DIR}/kuru.lib
)
