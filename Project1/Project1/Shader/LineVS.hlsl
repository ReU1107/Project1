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
	float4x4 viewMatrix;			// �r���[�ϊ��s��
	float4x4 projectionMatrix;		// �v���W�F�N�V�����ϊ��s��
	float4x4 viewProjectionMatrix;	// �r���[�v���W�F�N�V�����ϊ��s��
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