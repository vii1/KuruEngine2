cmake_minimum_required(VERSION 3.0)

project(KuruEngine2)

include(FindSDL2 REQUIRED)
# debería ser SDL2 >= 2.0.4 pero el script no comprueba la versión :/
include(FindSDL2_image REQUIRED)
if("${SDL2_IMAGE_VERSION_STRING}" VERSION_LESS "2.0.0")
	message(SEND_ERROR "Se requiere SDL_image >= 2.0.0")
endif()
include(FindSDL2_mixer REQUIRED)
if("${SDL2_MIXER_VERSION_STRING}" VERSION_LESS "2.0.0")
	message(SEND_ERROR "Se requiere SDL_mixer >= 2.0.0")
endif()
#include(FindSDL2_ttf REQUIRED)
#if("${SDL2_MIXER_VERSION_STRING}" VERSION_LESS "2.0.0")
#	message(SEND_ERROR "Se requiere SDL_ttf >= 2.0.0")
#endif()
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

include_directories("${INCLUDE_DIR}/kuru2")

if(MSVC)
	#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	#set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "/NODEFAULTLIB:msvcrt")
endif()

file(GLOB KURU_HEADERS
	"${INCLUDE_DIR}/kuru2/*.h"
)

file(GLOB KURU_SOURCES
	"*.cpp"
)

add_library(kuru2 SHARED ${KURU_SOURCES} ${KURU_HEADERS})

include(GenerateExportHeader REQUIRED)
GENERATE_EXPORT_HEADER( kuru2
	BASE_NAME KURU
	EXPORT_MACRO_NAME KURU_EXPORT
	EXPORT_FILE_NAME "${INCLUDE_DIR}/kuru2/kuru_export.h"
	STATIC_DEFINE KURU_BUILT_AS_STATIC
)

set_target_properties(kuru2 PROPERTIES
	COMPILE_DEFINITIONS "${DEFINES}"
    DEBUG_POSTFIX "-debug"
    LINK_FLAGS "-no_warning_for_no_symbols"
)

target_link_libraries(kuru2 ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

# copia el lib, pdb, etc a lib y bin
#if(MSVC)
	add_custom_command(TARGET kuru2 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"$<TARGET_FILE_DIR:kuru2>" "${LIB_TARGET_DIR}")
	add_custom_command(TARGET kuru2 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"$<TARGET_FILE_DIR:kuru2>" "${BIN_TARGET_DIR}")
#endif()

#install(TARGETS kuru DESTINATION ${LIB_TARGET_DIR})
