//RWBuffer<float3> position : register(u0);
RWByteAddressBuffer resultPosition : register(u0);
ByteAddressBuffer basePosition : register(t0);
ByteAddressBuffer deltaPosition : register(t1);

ByteAddressBuffer boneIndexWeight : register(t2);

struct Bones
{
	float4x4 palette[512];
};

ConstantBuffer<Bones> bones : register(b0);

[numthreads(255, 1, 1)]
void main(uint3 threadId : SV_DispatchThreadID)
//void main(uint3 threadId : SV_GroupID)
//void main(uint3 threadId : SV_GroupThreadID)
//void main(uint3 threadId : SV_GroupIndex)
{
	uint index = threadId.x;
	uint address1 = index * 12;
	uint address2 = index * 32;

	// �X���b�h���Œ��_�̐��𐧌䂷����萔�o�b�t�@�Œ��_�����𑗂�Ȃ����[�J����Ԃ݂̂ł̕ϊ�
	float4 position = float4(asfloat(basePosition.Load3(address1)), 1.0f);

	float3 delta = asfloat(deltaPosition.Load3(address1));

	// ���[�t�f�[�^���ړ�
	position.xyz += delta;

	// �X�L�j���O����
	float4x4 skinnedMatrix = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	uint4 boneIndex = boneIndexWeight.Load4(address2);
	float4 boneWeight = asfloat(boneIndexWeight.Load4(address2 + 16));

	skinnedMatrix  = bones.palette[boneIndex.x] * boneWeight.x;
	skinnedMatrix += bones.palette[boneIndex.y] * boneWeight.y;
	skinnedMatrix += bones.palette[boneIndex.z] * boneWeight.z;
	skinnedMatrix += bones.palette[boneIndex.w] * boneWeight.w;

	position = mul(skinnedMatrix, position);

	resultPosition.Store3(address1, asuint(position.xyz));

}