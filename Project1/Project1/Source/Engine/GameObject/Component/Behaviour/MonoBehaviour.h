#pragma once
#include "Behaviour.h"

namespace Engine 
{
	// 動作再生装置(モノラルビヘイビア)モノラル:再生方式
	class MonoBehaviour : public Behaviour
	{
	private:
		using base = Behaviour;
		using MonoBehaviourPtr = std::shared_ptr<MonoBehaviour>;
	public:
		// コンストラクタ
		MonoBehaviour(const std::string& name = "MonoBehaviour") noexcept;
		// 仮想デストラクタ
		virtual ~MonoBehaviour() noexcept;
	public:
		// インスタンスID
		static const InstanceID ID() { return InstanceID::MonoBehaviour; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::MonoBehaviour; }
	public:
		// 動作開始にやりたいこと
		virtual void OnStart() {}

		// 別オブジェクトに依存する可能性のある処理
		virtual void OnAwake() {}

		// 本描画後にやりたいこと
		virtual void OnPostRender() {}

		// 本描画前にやりたいこと
		virtual void OnPreRender() {}

		// 更新処理
		virtual void OnUpdate(float deltaTime);
		// 更新処理(アニメーション適用後)
		virtual void OnLateUpdate(float deltaTime);
		// 更新処理(一定時間)
		virtual void OnFixedUpdate(float deltaTime);
	};

}