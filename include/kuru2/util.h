///
/// \file util.h
/// Typedefs, clases, plantillas y cosas que sólo son para ayudar a hacer código más limpio.
///

#pragma once

#include "kuru_export.h"

#include "SDL.h"

/// Versión actual de KuruEngine
#define KURU_VERSION "2.0a1"

///
/// \name Sistema operativo y arquitectura
/// @{
#define KURU_OS_VENDOR_MICROSOFT	0x0100
#define KURU_OS_VENDOR_APPLE		0x0200
#define KURU_OS_POSIX				0x1000
#define KURU_OS_WINDOWS				0x0101
#define KURU_OS_OSX					0x1201
#define KURU_OS_IOS					0x1202
#define KURU_OS_LINUX				0x1001
#define KURU_OS_ANDROID				0x1002
#define KURU_OS_UNIX				0x1003
#define KURU_OS_UNKNOWN          	0
/// @}

/// \def KURU_OS
/// \hideinitializer
/// Contiene un valor que se puede comparar con las macros KURU_OS_* para saber en qué sistema operativo está
/// corriendo KuruEngine.

/// \def KURU_OS_DESC
/// \hideinitializer
/// Contiene una cadena con el nombre del sistema operativo detectado.

#ifdef _WIN32
#	define KURU_OS KURU_OS_WINDOWS
#	define KURU_OS_DESC "Windows"
#elif __APPLE__
#	include "TargetConditionals.h"
#	if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#		define KURU_OS KURU_OS_IOS
#		define KURU_OS_DESC "iOS"
#	elif TARGET_OS_MAC
#		define KURU_OS KURU_OS_OSX
#		define KURU_OS_DESC "Mac OS X"
#	else
#		define KURU_OS KURU_OS_VENDOR_APPLE
#		define KURU_OS_DESC "Unknown Apple OS"
#	endif
#elif defined(__ANDROID__)
#	define KURU_OS KURU_OS_ANDROID
#	define KURU_OS_DESC "Android"
#elif defined(__linux) || defined(__linux__)
#	define KURU_OS KURU_OS_LINUX
#	define KURU_OS_DESC "Linux"
#elif defined(unix) || defined(__unix__) || defined(__unix) // all unices not caught above
#	define KURU_OS KURU_OS_UNIX
#	define KURU_OS_DESC "UNIX"
#elif defined(__posix) || defined(_POSIX_VERSION)
#	define KURU_OS KURU_OS_POSIX
#	define KURU_OS_DESC "POSIX compatible OS"
#else
#   define KURU_OS KURU_OS_UNKNOWN
#   define KURU_OS_DESC "Unknown OS"
#endif

/// \def KURU_BITS
/// \hideinitializer
/// Contiene 64 o 32, dependiendo del tipo de binario de la aplicación actual.

#if defined(_WIN64) || defined(__LP64__) || defined(_LP64)
#	define KURU_BITS 64
#else
#	define KURU_BITS 32
#endif

/// \def DIR_SEPARATOR
/// \hideinitializer
/// Contiene el carácter separador que debe usarse para los directorios en el sistema operativo actual.
/// (Generalmente '/').
 
//#if KURU_OS == OS_WINDOWS
//#	define DIR_SEPARATOR '\\'
//#else
#	define DIR_SEPARATOR '/'
//#endif

// Para simplificar los SDL_Log
//#define LOG_APP SDL_LOG_CATEGORY_APPLICATION

/// Categorías de logs de KuruEngine.
enum {
	KURU_LOG_GENERAL = SDL_LOG_CATEGORY_CUSTOM,
	KURU_LOG_RESOURCES,
	KURU_LOG_GRAPHICS,
	KURU_LOG_INPUT,
	KURU_LOG_SOUND,
	/// Si la aplicación crea sus propias categorías, deben empezar desde KURU_LOG_CUSTOM.
	KURU_LOG_CUSTOM
};

//
// Macros
//

/// A macro to disallow the copy constructor and operator= functions
/// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  void operator=(const TypeName&)

// DEPRECATED
/// Marca una función como obsoleta.
/// \see http://stackoverflow.com/questions/295120/c-mark-as-deprecated/21265197#21265197
#ifdef __GNUC__
#define DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED __declspec(deprecated)
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED
#endif

namespace kuru {

//
// Tipos más simples
//

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

// Cadena UNICODE-16, necesaria para SDL_ttf

//#if WCHAR_MAX == 0xFFFF
//typedef std::wstring kustring;
//typedef wchar_t kuchar;
//#else
//typedef std::u16string kustring;
//typedef char16_t kuchar;
//#endif

//kustring to_kustring( const std::string& );
//kustring to_kustring( const std::wstring& );

//template<typename CharIn>
//kustring to_kustring( const std::basic_string<CharIn>& str ) {
//	return boost::locale::conv::utf_to_utf<kustring::value_type>( str );
//}

//template<typename CharIn>
//kustring to_kustring( const CharIn* str ) {
//	const auto s = std::basic_string<CharIn>( str );
//	return to_kustring( s );
//}

//#define u16(x)	(reinterpret_cast<const std::u16string&>(x))


//
// Singleton
//
/// Implementación del patrón Singleton.
template<typename T> class KURU_EXPORT Singleton
{
public:
	static T& Instance()
	{
		static T laInstanciaSingleton; //asumir T posee un constructor por defecto
		return laInstanciaSingleton;
	}

};

//
// Deleters
//

/// Deleter para objetos creados con malloc().
struct KURU_EXPORT free_delete
{
	void operator()( void* x ) { free( x ); }
};

/// Deleter para superficies de SDL (SDL_Surface).
struct KURU_EXPORT surface_delete
{
	void operator()( SDL_Surface* x ) { SDL_FreeSurface( x ); }
};

//
// Funciones
//

namespace util
{
	template<size_t _Size> void dirOfFile( const char* file, char (&outDir)[_Size] ) { dirOfFile_s( file, outDir, sizeof(outDir) ); }
	KURU_EXPORT void dirOfFile_s( const char* file, char* buffer, size_t bufsize );
}

} // namespace kuru
