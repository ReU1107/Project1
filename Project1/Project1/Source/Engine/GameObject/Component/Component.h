#pragma once
#include <vector>
#include "../../Object.h"
#include <string>
#include <memory>
#include "../SearchPriority.h"

namespace Engine
{
	// 前方宣言
	class GameObject;
	class Transform;

	// 振る舞い
	class Component : public Object
	{
	private:
		using base = Object;
		using GameObjectPtr = std::shared_ptr<GameObject>;
	private:
		GameObjectPtr m_owner;
	protected:
		// コンストラクタ
		Component(const std::string& name) noexcept;
		// 仮想デストラクタ
		virtual ~Component() noexcept;
	public:
		// オブジェクトID
		static const InstanceID ID() { return InstanceID::Component; }

		template<class T>
		static std::shared_ptr<T> Create();

		// 自身を持つゲームオブジェクト
		void SetOwner(GameObjectPtr owner);
	public:

		// 所有者取得
		GameObjectPtr GetOwner() const;

		// 親オブジェクト取得
		GameObjectPtr GetParent() const;

		// 長男オブジェクト取得
		GameObjectPtr GetOldestChild() const;

		// 弟オブジェクト取得
		GameObjectPtr GetNextSibling() const;

		std::shared_ptr<Engine::Transform> GetTransform() const;

		template<class T>
		std::shared_ptr<T> AddComponent();

		// T型のコンポーネント数取得
		template<class T>
		inline uint32_t GetComponentCount() const;

	public:
		// T型のコンポーネント取得
		template<class T>
		inline std::shared_ptr<T> GetComponent(uint32_t index = 0);

		// T型のコンポーネント配列取得
		template<class T>
		inline std::vector<std::shared_ptr<Component>>* GetComponents();

		// 親からT型のコンポーネント取得
		template<class T>
		inline std::shared_ptr<T> GetComponentInParent();

		// 子供からT型のコンポーネント取得
		template<class T>
		inline std::shared_ptr<T> GetComponentInChildren();

		// T型のコンポーネントを持つ全ての子オブジェクトのコンポーネント取得
		template<class T>
		inline std::vector<std::shared_ptr<T>> GetComponentsInChildren();

		// T型のコンポーネント持つ全ての子孫のコンポーネント取得
		template<class T>
		inline std::vector<std::shared_ptr<T>> GetComponentsInDescendant(SearchPriority priority = SearchPriority::DepthFirst) const;
	};
}
using ComponentPtr = std::shared_ptr<Engine::Component>;

#include "ComponentImpl.h"