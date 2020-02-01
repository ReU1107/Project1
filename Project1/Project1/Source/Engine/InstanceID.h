#pragma once
#include <cstdint>

namespace Engine
{
	// オブジェクトクラスを継承しているそれぞれのID
	// TypeID
	enum class InstanceID : uint32_t
	{
		Object,				// オブジェクト
		GameObject,			// ゲームオブジェクト
		Motion,				// モーション
		Shader,				// シェーダー
		Texture,			// テクスチャ
		Texture2D,			// 
		RenderTexture,		// レンダーテクスチャ
		DepthTexture,		// デプステクスチャ
		Mesh,				// メッシュ
		SubMesh,			// サブメッシュ
		Material,			// マテリアル
		BlendShape,			// ブレンドシェイプ
		PhysicsMaterial,	// 物理演算用材質
		Billboard,			// ビルボード
		Sprite,				// スプライト
		Component,			// コンポーネント
		Transform,			// 変換
		Behaviour,			// 動作を表す基底クラス
		Animation,			// アニメーション
		Animator,			// アニメーター
		Camera,				// カメラ
		Light,				// ライト
		Terrain,			// 地形
		SkyBox,				// キューブマップ
		MonoBehaviour,		// スクリプトの基底クラス
		Renderer,			// レンダラーの基底クラス
		MeshRenderer,		// メッシュ描画
		LineRenderer,		// ライン描画
		SpriteRenderer,		// スプライト描画
		RayTracer,			// レイトレーサー
		SkinnedMeshRenderer,// メッシュスキニング
		Collider,			// 衝突検知の基底クラス
		Filter,				// フィルターの基底クラス
		RigidBody,			// 剛体(物理演算)
		SoftBody,			// 軟体(物理演算)
		Joint,				// ジョイント(関節)の基底クラス
		Bone,				// ボーンクラス(スキニングに必要)
		AudioSource,		// 音源クラス
		AudioListener,		// 音を聞く
	};

	using TypeID = InstanceID;
}