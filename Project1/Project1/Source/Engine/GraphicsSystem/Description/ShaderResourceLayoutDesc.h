#pragma once
#include <cstdint>

/*
リソースをシェーダーのどこに対して何を置くかを
記述したもの
*/

/*
D3D12_ROOT_PARAMETER
*/
namespace Engine 
{

	namespace GraphicsSystem 
	{

		// 前方宣言
		struct ShaderResourceParameterDesc;
		struct ShaderResourceConstantsDesc;
		struct ShaderResourceDescriptorDesc;
		enum class ShaderResourceLayoutType : uint8_t;
		enum class ShaderType : uint8_t;

		// シェーダーリソースの配置を記述
		struct ShaderResourceLayoutDesc
		{
			union
			{
				struct {
					ShaderResourceParameterDesc* parameters;// パラメーター配列
					uint32_t parameterCount;				// パラメーター数
				}descriptorTable;
				ShaderResourceConstantsDesc constans;		// 定数
				ShaderResourceDescriptorDesc descriptor;	// 任意のリソースビュー

			};
			ShaderResourceLayoutType layoutType;			// レイアウトの種類
			ShaderType shaderType;							// 使用するシェーダータイプ
		};
	}

}