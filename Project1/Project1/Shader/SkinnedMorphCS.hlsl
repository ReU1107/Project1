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

	// スレッド数で頂点の数を制御する≒定数バッファで頂点数等を送らないローカル空間のみでの変換
	float4 position = float4(asfloat(basePosition.Load3(address1)), 1.0f);

	float3 delta = asfloat(deltaPosition.Load3(address1));

	// モーフデータ分移動
	position.xyz += delta;

	// スキニング処理
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