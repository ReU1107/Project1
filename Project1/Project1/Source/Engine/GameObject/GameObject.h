#pragma once
#include <vector>
#include <list>
#include <unordered_map>
#include "../InstanceID.h"
#include "../Object.h"
#include "SearchPriority.h"

namespace Engine
{
	class Component;
	class Transform;

	class GameObject final : public std::enable_shared_from_this<GameObject>, public Object
	{
	private:
		using base = Object;
		using Components = std::unordered_map<InstanceID, std::vector<std::shared_ptr<Component>>>;
		using GameObjectPtr = std::shared_ptr<GameObject>;
	private:
		static std::unordered_map<std::string, GameObjectPtr> allObjects;
	private:
		Components m_components;				// コンポーネント配列
		std::weak_ptr<Engine::Transform> m_transform;
		GameObjectPtr m_root;					// 先祖オブジェクト
		GameObjectPtr m_parent;					// 親オブジェクト
		GameObjectPtr m_oldestChild;			// 長男オブジェクト
		GameObjectPtr m_youngestChild;			// 末子オブジェクト
		GameObjectPtr m_prevSibling;			// 兄オブジェクト
		GameObjectPtr m_nextSibling;			// 弟オブジェクト

		uint32_t m_childCount;					// 子オブジェクト人数
		uint32_t m_siblingIndex;				// 兄弟番号(自身が何番目の子供か)
	public:
		// コンストラクタ
		GameObject() noexcept;
		GameObject(const std::string& name) noexcept;
		// デストラクタ
		virtual ~GameObject() noexcept;

	public:
		// ゲームオブジェクト作成関数
		static GameObjectPtr Create(const std::string& name, bool isRegister = true);
		// 検索
		static GameObjectPtr Find(const std::string& name);

	private:
		// 親オブジェクト設定
		void SetParent(GameObjectPtr parent);

		// 長男オブジェクト設定
		void SetOldestChild(GameObjectPtr oldestChild);

		// 末っ子オブジェクト設定
		void SetYoungestChild(GameObjectPtr youngestChild);

		// 兄オブジェクト設定
		void SetPrevSibling(GameObjectPtr prevSibling);

		// 弟オブジェクト設定
		void SetNextSibling(GameObjectPtr nextSibling);

		// 兄弟番号設定
		void SetSiblingIndex(uint32_t siblingIndex);

	public:
		// 子オブジェクト追加
		void AddChild(GameObjectPtr child);

		// 親オブジェクト取得
		GameObjectPtr GetParent() const;

		// 長男オブジェクト取得
		GameObjectPtr GetOldestChild() const;

		// 弟オブジェクト取得
		GameObjectPtr GetNextSibling() const;

		// 子オブジェクト数取得
		uint32_t GetChildCount() const;

		// 子オブジェクト取得
		GameObjectPtr GetChildByName(const std::string& name);

		// 子オブジェクト取得
		GameObjectPtr GetChildByIndex(uint32_t index);

		// 子オブジェクト取得
		GameObjectPtr GetChild(GameObjectPtr search);

		// 子オブジェクトを持っているか
		bool HasChild(GameObjectPtr search);

		// 子孫オブジェクト取得
		GameObjectPtr GetDescendantByName(const std::string& name);
	private:
		// 子孫オブジェクト取得再帰関数
		GameObjectPtr GetDescendantRecurse(GameObjectPtr object, const std::string& name) const;

	public:
		// 子オブジェクト削除
		void RemoveChild(GameObjectPtr child);

		// 子オブジェクト切り離し
		void DetachChildren(GameObjectPtr child);

		template<class T>
		inline std::shared_ptr<T> AddComponent();

		// T型のコンポーネント数取得
		template<class T>
		inline uint32_t GetComponentCount() const;


	public:
		// トランスフォーム取得
		std::shared_ptr<Transform> GetTransform() const;

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
	private:
		template<class T>
		void GetComponentsInDescendantRecurse(std::vector<std::shared_ptr<T>>& componentList, GameObjectPtr object, SearchPriority priority) const;

	public:
		// 作成時にやりたいこと(初期化)
		void Start();

		// 更新時にやりたいこと
		void Update(float deltaTime);

		void FixedUpdate();

		void LateUpdate(float deltaTime);

	};
}

// template関連
#include "GameObjectImpl.h"