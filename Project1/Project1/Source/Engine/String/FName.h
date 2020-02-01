#pragma once
#include <cstdint>
#include <string>

namespace Engine
{
	class FName
	{
	private:
		union Name
		{
			char* narrowString;
			wchar_t* wideString;
		}m_name;
		uint32_t m_size;
		uint64_t m_nameHash;		// 
		bool m_narrow;
	public:
		// �R���X�g���N�^
		FName(const std::string& name);
		FName(const std::wstring& name);
		// �f�X�g���N�^
		~FName();

		// ��r���Z�q�I�[�o�[���C�h
		bool operator!=(const FName& other);
		bool operator==(const FName& other);
		
	};
}