#pragma once
#include <string>
namespace Engine
{

	// char*Œ^¨wchar_t*Œ^‚É•ÏŠ·
	inline const wchar_t* ConvertCharToWChar(const char* base);

	// wchar_tŒ^¨char*Œ^‚É•ÏŠ·
	inline const char* ConvertWCharToChar(const wchar_t* base);

	// stringŒ^‚ğwstringŒ^‚É•ÏŠ·
	//std::wstring StringToWStringConvert(std::string base);
	// utf8,utf16‚Í‘S‚Ästd::string‚ÉW–ñ‚·‚é
	// wstringŒ^‚ğstringŒ^‚É•ÏŠ·
	//std::string WStringToStringConvert(std::wstring base);

	// uint8_tŒ^‚ğstringŒ^‚É•ÏŠ·
	inline std::string ConvertUint8_tToString(uint8_t* base, uint32_t length);

	// char16_tŒ^¨charŒ^
	inline std::string ConvertChar16_tToChar(std::u16string* base);
	// 

	// ‘å•¶š¨¬•¶š‚É•ÏŠ·
	inline const char* ToLower(const char* base, const uint32_t length);

	// ¬•¶š¨‘å•¶š‚É•ÏŠ·
	inline const char* ToUpper(const char* base, const uint32_t length);

	// Base‚Ü‚Å‚ÌƒpƒXì¬
	inline const char* CreateBasePath(const char* base, char search = '/');

	// •¶š—ñØ‚èæ‚è(Left`Right)
	inline const char* StringCut(const char* base, char searchLeft, char searchRight);
	//inline const std::string & StringCut(const char * base, char searchLeft, char searchRight);

	template<class BlobType>
	inline std::string ConvertBlobToString(BlobType* pBlob);

}
#include "StringHelperImpl.h"