#pragma once
#include <string>
namespace Engine
{

	// char*型→wchar_t*型に変換
	inline const wchar_t* ConvertCharToWChar(const char* base);

	// wchar_t型→char*型に変換
	inline const char* ConvertWCharToChar(const wchar_t* base);

	// string型をwstring型に変換
	//std::wstring StringToWStringConvert(std::string base);
	// utf8,utf16は全てstd::stringに集約する
	// wstring型をstring型に変換
	//std::string WStringToStringConvert(std::wstring base);

	// uint8_t型をstring型に変換
	inline std::string ConvertUint8_tToString(uint8_t* base, uint32_t length);

	// char16_t型→char型
	inline std::string ConvertChar16_tToChar(std::u16string* base);
	// 

	// 大文字→小文字に変換
	inline const char* ToLower(const char* base, const uint32_t length);

	// 小文字→大文字に変換
	inline const char* ToUpper(const char* base, const uint32_t length);

	// Baseまでのパス作成
	inline const char* CreateBasePath(const char* base, char search = '/');

	// 文字列切り取り(Left〜Right)
	inline const char* StringCut(const char* base, char searchLeft, char searchRight);
	//inline const std::string & StringCut(const char * base, char searchLeft, char searchRight);

	template<class BlobType>
	inline std::string ConvertBlobToString(BlobType* pBlob);

}
#include "StringHelperImpl.h"