#pragma once
#include <string>
namespace Engine
{

	// char*�^��wchar_t*�^�ɕϊ�
	inline const wchar_t* ConvertCharToWChar(const char* base);

	// wchar_t�^��char*�^�ɕϊ�
	inline const char* ConvertWCharToChar(const wchar_t* base);

	// string�^��wstring�^�ɕϊ�
	//std::wstring StringToWStringConvert(std::string base);
	// utf8,utf16�͑S��std::string�ɏW�񂷂�
	// wstring�^��string�^�ɕϊ�
	//std::string WStringToStringConvert(std::wstring base);

	// uint8_t�^��string�^�ɕϊ�
	inline std::string ConvertUint8_tToString(uint8_t* base, uint32_t length);

	// char16_t�^��char�^
	inline std::string ConvertChar16_tToChar(std::u16string* base);
	// 

	// �啶�����������ɕϊ�
	inline const char* ToLower(const char* base, const uint32_t length);

	// ���������啶���ɕϊ�
	inline const char* ToUpper(const char* base, const uint32_t length);

	// Base�܂ł̃p�X�쐬
	inline const char* CreateBasePath(const char* base, char search = '/');

	// ������؂���(Left�`Right)
	inline const char* StringCut(const char* base, char searchLeft, char searchRight);
	//inline const std::string & StringCut(const char * base, char searchLeft, char searchRight);

	template<class BlobType>
	inline std::string ConvertBlobToString(BlobType* pBlob);

}
#include "StringHelperImpl.h"