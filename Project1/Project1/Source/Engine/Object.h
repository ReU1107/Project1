#pragma once
#include <string>
#include <memory>
#include "InstanceID.h"

namespace Engine
{
	// 全てのオブジェクトの基底クラス
	class Object
	{
	private:
		std::string m_name;	// オブジェクト名
		uint32_t m_nameHash;	// ハッシュ値
	public:
		// コンストラクタ
		Object(const std::string& name) noexcept;
		// デストラクタ
		virtual ~Object() noexcept;
	public:
		// インスタンスID
		static const InstanceID ID() { return InstanceID::Object; }
		// インスタンスID取得
		virtual InstanceID GetInstanceID() const { return InstanceID::Object; }

		// 違うオブジェクトを参照しているか
		bool operator!=(const Object* other) const;
		// 同じオブジェクトを参照しているか
		bool operator==(const Object* other) const;

	public:
		// 名前設定
		void SetName(const std::string& name);
		// 名前取得
		const std::string& GetName() const;
		// ハッシュ値取得
		uint32_t GetNameHash() const;

		// 変数アドレス取得
		virtual void* GetPropertyAddress(const std::string& name);

	};
}

/*
オブジェクトの名前比較をする場合は
ハッシュ値を使用した方がいい
理由:
stricmp等の比較関数は
文字のコード番号を文字列分比較している≒数値比較を文字数分している
≒数値比較は1回で済む
文字列と数値では数値の方が比較がはやい
*/
/*
GetProperty()
引数には取得したい変数名
名前が一致していたらその変数のアドレスを返す
*/