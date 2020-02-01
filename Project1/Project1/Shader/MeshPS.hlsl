#include "MeshHeader.hlsli"

Texture2D tex : register(t0);
SamplerState sam : register(s0);
/*
�}���`�����_�[�^�[�Q�b�g���g�p����ۂɂ̓^�[�Q�b�g�𑝂₵�Ă�������
���₷�ۂ̓A�v���P�[�V�����̕��Ɠ������Ԃɂ��Ă�������
*/
struct PSOutput
{
	float4 color : SV_TARGET0;
};

float4 main(in PSInput input) : SV_TARGET
{
	float4 color = tex.Sample(sam,input.texcoord);
	// �A���t�@�e�X�g
	if (color.a < 0.01f)
	{
		//discard;
	}
	//color.rgb = input.normal;
	color.a = 1.0f;
	return color;
	
	//return float4(0.0f, 1.0f, 1.0f, 1.0f);
}