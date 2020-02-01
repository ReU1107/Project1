struct VSInput
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

struct CameraData
{
	float4x4 viewMatrix;			// ビュー変換行列
	float4x4 projectionMatrix;		// プロジェクション変換行列
	float4x4 viewProjectionMatrix;	// ビュープロジェクション変換行列
};

ConstantBuffer<CameraData> cameraBuffer : register(b0);


VSOutput main(in VSInput input)
{
	VSOutput output = (VSOutput)0;

	float4 position = float4(input.position, 1.0f);

	output.position = mul(cameraBuffer.viewProjectionMatrix, position);
	output.color = input.color;

	return output;
}