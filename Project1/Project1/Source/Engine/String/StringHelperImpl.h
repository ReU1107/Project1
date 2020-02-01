#pragma once
#include "StringHelper.h"
#include <stdlib.h>
#include <cuchar>
#include <codecvt>
#include <Windows.h>
#include <vector>

namespace Engine
{

	const wchar_t* ConvertCharToWChar(const char* base)
	{
		// 文字サイズ
		size_t size = strlen(base) + 1;

		// 変換文字格納先
		wchar_t* output = new wchar_t[size];

		// 変換された文字数
		size_t value = 0;

		// 変換
		if (mbstowcs_s(&value, output, size, base, _TRUNCATE) == EINVAL) {
			MessageBox(nullptr, "文字変換に失敗しました", base, MB_OK);
			return nullptr;
		}

		return output;
	}

	const char* ConvertWCharToChar(const wchar_t* base)
	{
		size_t size = (wcslen(base) + 1) * 2;
		char* output = new char[size];

		size_t value = 0;
		if (wcstombs_s(&value, output, size, base, _TRUNCATE)) {
			//assert(!"文字列の変換に失敗しました");
		}

		return output;
	}

	std::string ConvertUint8_tToString(uint8_t* base, uint32_t length)
	{
		std::string output(length, 0);
		for (uint32_t index = 0; index < length; index++) {
			output[index] = static_cast<char>(base[index]);
		}
		return std::move(output);
	}

	std::string ConvertChar16_tToChar(std::u16string* base)
	{
		int bufferSize = WideCharToMultiByte(CP_ACP, 0, reinterpret_cast<const wchar_t*>(base->c_str()), -1, nullptr, 0, nullptr, nullptr);
		char* buffer = new char[bufferSize];
		WideCharToMultiByte(CP_ACP, 0, reinterpret_cast<const wchar_t*>(base->c_str()), -1, buffer, bufferSize, nullptr, nullptr);

		std::string mbs(buffer);
		delete[] buffer;

		return std::move(mbs);
	}

	const char* ToLower(const char* base, const uint32_t length)
	{
		char* str = new char[(uint64_t)length + 1];
		memset(str, '\0', (uint64_t)length + 1);
		for (uint32_t i = 0; i < length; i++) {
			// 小文字ならそのまま
			if (strcmp(&base[i], "a") >= 0 && strcmp(&base[i], "z") <= 0) {
				str[i] = base[i];
				continue;
			}
			// 小文字に変換
			str[i] = base[i] + 0x20;
		}
		return str;
	}

	const char* ToUpper(const char* base, const uint32_t length)
	{
		char* str = new char[(uint64_t)length + 1];
		memset(str, '\0', (uint64_t)length + 1);
		for (uint32_t i = 0; i < length; i++) {
			// 大文字ならそのまま
			if (strcmp(&base[i], "A") >= 0 && strcmp(&base[i], "Z") <= 0) {
				str[i] = base[i];
				continue;
			}
			// 大文字に変換
			str[i] = base[i] - 0x20;
		}
		return str;
	}

	const char* CreateBasePath(const char* base, char search)
	{
		size_t length = strlen(base);
		char* path = new char[255];
		strcpy_s(path, 255, base);
		char* place = strrchr(path, search);
		if (place) {
			*place = '\0';
			strcat_s(path, strlen(base), "/");
		}
		else {
			for (uint32_t i = 0; i < length; ++i) {

				*(path + i) = '\0';
			}
		}
		return path;
	}

	inline const char* StringCut(const char* base, char searchLeft, char searchRight)
	{
		char* destination = new char[256];
		strcpy_s(destination, 255, base);
		char* place = strrchr(destination, searchLeft);
		if (!place) {
			return "\0";
		}
		char* place2 = strrchr(destination, searchRight);
		if (!place2) {
			return "\0";
		}
		*(place2) = '\0';
		size_t size = strlen(place) - strlen(place2);
		strcpy_s(destination, size + 2, place + 1);
		return destination;
	}

	template<class BlobType>
	inline std::string ConvertBlobToString(BlobType* pBlob)
	{
		std::vector<char> infoLog(pBlob->GetBufferSize() + 1);
		memcpy(infoLog.data(), pBlob->GetBufferPointer(), pBlob->GetBufferSize());
		infoLog[pBlob->GetBufferSize()] = 0;
		return std::string(infoLog.data());
	}
}
// char* -> wchar_t 変換
// URL https://msdn.microsoft.com/ja-jp/library/ms235631.aspx
// LP ポインタの事
// C コンスト
// W ワイド
// STR 文字列 char
// LPCWSTR = const wchar_t *
// LPWSTR = wchar_t *

//_TRUNCATE nullptrを切り捨て


// utf16ToSiftjis 変換
// URL https://qiita.com/yumetodo/items/453d14eff41b805d8fc4