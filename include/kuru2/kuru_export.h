
#ifndef KURU_EXPORT_H
#define KURU_EXPORT_H

#ifdef KURU_BUILT_AS_STATIC
#  define KURU_EXPORT
#  define KURU_NO_EXPORT
#else
#  ifndef KURU_EXPORT
#    ifdef kuru2_EXPORTS
        /* We are building this library */
#      define KURU_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KURU_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KURU_NO_EXPORT
#    define KURU_NO_EXPORT 
#  endif
#endif

#ifndef KURU_DEPRECATED
#  define KURU_DEPRECATED __declspec(deprecated)
#endif

#ifndef KURU_DEPRECATED_EXPORT
#  define KURU_DEPRECATED_EXPORT KURU_EXPORT KURU_DEPRECATED
#endif

#ifndef KURU_DEPRECATED_NO_EXPORT
#  define KURU_DEPRECATED_NO_EXPORT KURU_NO_EXPORT KURU_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define KURU_NO_DEPRECATED
#endif

#endif
