struct VSInput
{
	float2 position : POSITION;	// 頂点座標
	uint index : SV_VERTEXID;	// システム値の頂点IDが入ってくる
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

typedef VSOutput PSInput;
