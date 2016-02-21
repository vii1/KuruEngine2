#include "util.h"
#include <string>
#include <cstring>

namespace kuru {

namespace util
{
	KURU_EXPORT void dirOfFile_s( const char* file, char* buffer, size_t bufsize )
	{
		auto fil = std::string( file );
		auto dir = fil.substr( 0, fil.find_last_of( DIR_SEPARATOR ) ) + DIR_SEPARATOR;
		strcpy_s( buffer, bufsize, dir.c_str() );
	}
}

/*kustring to_kustring( const std::string& str )
{
#if WCHAR_MAX == 0xFFFF
	return boost::locale::conv::utf_to_utf<wchar_t>( str );
#else
	return boost::locale::conv::utf_to_utf<char16_t>( str );
#endif
}

kustring to_kustring( const std::wstring& str )
{
#if WCHAR_MAX == 0xFFFF
	return boost::locale::conv::utf_to_utf<wchar_t>( str );
#else
	return static_cast<kustring>(str);
#endif
}*/

}
