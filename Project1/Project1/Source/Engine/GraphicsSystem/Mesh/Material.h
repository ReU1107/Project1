#pragma once

#include "..//..//Math/Color3.h"
#include "..//..//Math/Color4.h"
#include <vector>
#include <iostream>
#include "../../Object.h"

namespace Engine
{
	// 前方宣言
	//struct GameContext;
	namespace GraphicsSystem
	{
		class Shader;
		class Texture;
		class ConstantBuffer;

		// テクスチャ合成法
		enum class BlendType
		{
			Addition,		// 加算
			Multiplication	// 乗算
		};

		struct MaterialData
		{
			Color3 color;			// 
			float opacity;			// 不透明度(0.0 ～ 1.0)
			Color3 diffuseCoeff;	// 拡散反射係数(r,g,b,a)
			float specularity;		// 鏡面性強度(0.0 ～ 200.0)
			Color3 ambientCoeff;	// 環境反射係数(r,g,b)
			float refraction;		// 屈折率
			Color3 specularCoeff;	// 鏡面反射係数(r,g,b)
			float dummy;
		};

		class Material final : public Object
		{
		private:
			using base = Object;
			using TexturePtr = std::shared_ptr<Texture>;
			using Textures = std::vector<TexturePtr>;
		private:

			TexturePtr m_decalTexture;				// デカールテクスチャ(メインテクスチャ)

			ConstantBuffer* m_constantBuffer;		// 定数バッファ
			MaterialData m_data;

		public:
			// コンストラクタ
			Material(const std::string& name = "");
			// デストラクタ
			virtual ~Material();
		public:
			// インスタンスID
			static const InstanceID ID() { return InstanceID::Material; }
			// インスタンスID取得
			virtual InstanceID GetInstanceID() const { return InstanceID::Material; }

		public:
			// 複製
			//Material* Clone();
			// 定数バッファ作成
			void CreateConstantBuffer();
		public:
			// 基本色追加
			void SetColor(const Color3& color);

			// 環境反射係数設定
			void SetAmbientCoeff(const Color3& coeff);

			// 鏡面反射係数設定
			void SetSpecularCoeff(const Color3& coeff);

			// 拡散反射係数設定
			void SetDiffuseCoeff(const Color3& coeff);

			// 鏡面性強度設定
			void SetSpecularity(float specularity);

			// 不透明度設定
			void SetOpacity(float opacity);

			// 屈折率設定
			void SetRefraction(float refraction);

			// デカールテクスチャ設定
			void SetDecalTexture(TexturePtr texture);

		public:

			// デカールテクスチャ取得
			TexturePtr GetDecalTexture() const;

			// 定数バッファ取得
			ConstantBuffer* GetConstantBuffer() const;

			// アンビエント係数取得
			const Color3& GetAmbientCoeff() const;
			// ディフューズ係数取得
			const Color3& GetDiffuseCoeff() const;
			// スペキュラー係数取得
			const Color3& GetSpecularCoeff() const;
			// スペキュラー取得
			float GetSpecularity() const;
			// オパシティ取得
			float GetOpacity() const;
		};
	}
}

using MaterialPtr = std::shared_ptr<Engine::GraphicsSystem::Material>;