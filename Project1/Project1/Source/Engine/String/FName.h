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
		// コンストラクタ
		FName(const std::string& name);
		FName(const std::wstring& name);
		// デストラクタ
		~FName();

		// 比較演算子オーバーライド
		bool operator!=(const FName& other);
		bool operator==(const FName& other);
		
	};
}