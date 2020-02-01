
// 平行
struct DirectionalLight
{
	float3 direction;	// 向き
};

// 点
struct PointLight
{
	float3 position;	// 位置
	float range;		// 範囲
};

// スポット
struct SpotLight
{
	float3 position;	// 位置
	float3 direction;	// 向き
	float range;		// 範囲
	float angle;		// アングル
};

// 自己発行
struct EmissiveLight
{

};

#define DirectionalID 0
#define PointID 1
#define SpotID 2

/*
SpotLightを選んでいる理由
全ての共通パラメータを持っていて
配列で持つため最大バイト数に合わせなくてはいけないから
*/
struct Light
{
	float3 color;			// 色
	float3 position;	// 位置
	float3 direction;	// 向き
	float range;		// 範囲
	float angle;		// アングル

	uint type;
};
