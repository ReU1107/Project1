#pragma once
#include <string>
#include <vector>
#include "../Enumerations/ShaderType.h"

/*
テクスチャはRangesで必ず設定しないといけない
*/
/*
シェーダーで使用するリソースをどのように配置してあるかの記述
*/

namespace Engine 
{
	namespace GraphicsSystem 
	{
		class IRootSignature;
		struct ShaderResourceLayoutDesc;
		struct ShaderResourceParameterDesc;
		struct ShaderResourceConstantsDesc;
		struct ShaderResourceDescriptorDesc;
		class Shader;
		enum class RootSignatureType : uint8_t;
		enum class RootSignatureFlags : uint8_t;

		class SamplerState;

		struct ShaderResourceRange
		{
			ShaderResourceParameterDesc* parameters;
			uint32_t count;
			uint32_t index;
			ShaderType usedShader;
		};

		class RootSignature
		{
			using Layouts = std::vector<ShaderResourceLayoutDesc>;
			using Ranges = std::vector<ShaderResourceRange>;
			using StaticSamplerStates = std::vector<SamplerState>;
		private:
			Layouts m_layouts;					// レイアウト配列
			Ranges m_ranges;					// パラメーター配列
			StaticSamplerStates m_staticSampler;// 静的サンプラーステート
			IRootSignature* m_interface;		// 
			Shader* m_shader;					// シェーダーから作成する場合はこちら
			RootSignatureType m_type;			// タイプ
			RootSignatureFlags m_flags;			// フラグ
		public:
			// コンストラクタ
			RootSignature();
			// デストラクタ
			~RootSignature();
			// フラグ設定
			void SetFlags(RootSignatureFlags flags);
			// タイプ設定
			void SetType(RootSignatureType type);
			// レイアウト追加
			void AddLayout(const ShaderResourceLayoutDesc& layout);

			// レンジ追加
			void AddDescriptorTableLayout(ShaderResourceParameterDesc* parameters, uint32_t count, ShaderType usedShader = ShaderType::All);

			// コンスタンツ追加
			void AddConstantsLayout(const ShaderResourceConstantsDesc& constants, ShaderType usedShader = ShaderType::All);

			// デスクリプター追加
			void AddDescriptorLayout(const ShaderResourceDescriptorDesc& descriptor, ShaderType usedShader = ShaderType::All);

			// 作成
			void AddRange(uint32_t parameterCount, ShaderType usedShader = ShaderType::All);

			// 定数バッファ追加
			void AddConstantBufferView(uint32_t index, uint32_t space = 0, ShaderType usedShader = ShaderType::All);
			void AddConstantBufferViewInRanges(uint32_t registerIndex, uint32_t rangeIndex, uint32_t count = 1, uint32_t space = 0, uint32_t offset = 0xffffffff);

			// シェーダーリソースビュー追加
			void AddShaderResourceView(uint32_t index, uint32_t space = 0, ShaderType usedShader = ShaderType::All);
			void AddShaderResourceViewInRanges(uint32_t registerIndex, uint32_t rangeIndex, uint32_t count = 1, uint32_t space = 0, uint32_t offset = 0xffffffff);

			// アンオーダードアクセスビュー追加
			void AddUnorderedAccessView(uint32_t index, uint32_t space = 0, ShaderType usedShader = ShaderType::All);
			void AddUnorderedAccessViewInRanges(uint32_t registerIndex, uint32_t rangeIndex, uint32_t count = 1, uint32_t space = 0, uint32_t offset = 0xffffffff);

			// 静的サンプラーステート追加
			void AddStaticSamplerState();

			// シェーダー設定
			void SetShader(Shader* shader);

			// 作成
			void Create();

			// 低レベルシグネチャ取得
			IRootSignature* GetInterface() const;

			// タイプ取得
			RootSignatureType GetType() const;

			void SetName(const std::wstring& name);

		};

	}

}