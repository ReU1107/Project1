RWBuffer<float3> deltaPosition : register(u0);
struct BlendValue
{
	float3 value;	// �ǉ�����l
	uint index;		// �ύX���钸�_�ԍ�
};

StructuredBuffer<BlendValue> blendPosition : register(t0);

struct BlendWeight
{
	float weight;
};

ConstantBuffer<BlendWeight> blendWeight : register(b0);

[numthreads(1, 1, 1)]
void main(uint3 threadID : SV_DispatchThreadID )
{
	uint index = threadID.x;

	BlendValue blend = blendPosition[index];

	deltaPosition[blend.index] = blend.value * blendWeight.weight;
}