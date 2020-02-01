
struct Payload
{
	float4 color;
	half traceCount;
};

struct ShadowPayload
{
	float shadowCoeff;	// シャドウ係数
};

struct CameraData
{
	float4x4 viewMatrix;			// ビュー変換行列
	float4x4 projectionMatrix;		// プロジェクション変換行列
	float4x4 viewProjectionMatrix;	// ビュープロジェクション変換行列
	float4x4 projViewMatrix;
	float4 position;
};

struct SceneData
{
	uint lightCount;		// ライトの数
	float refraction;		// 空気中の屈折率
};

struct LightData
{
	float3 color;		// 色
	float3 position;	// 位置
	float3 direction;	// 向き
	float range;		// 範囲
	float angle;		// アングル

	uint type;
};

/*
定数バッファはfloat4境界がある
そのため下のような構造になっている
*/
struct MaterialData
{
	float3 color;			// 単体の色
	float opacity;			// 不透明度(0.0 ～ 1.0)
	float3 diffuseCoeff;	// 拡散反射係数(r,g,b,a)
	float specularity;		// 鏡面性強度(0.0 ～ 200.0)
	float3 ambientCoeff;	// 環境反射係数(r,g,b)
	float refraction;		// 屈折率
	float3 specularCoeff;	// 鏡面反射係数(r,g,b)
	float dummy;
};

struct ProceduralInstance
{
	float3 min;
	float3 max;
};

struct Ray
{
	float3 origin;
	float3 direction;
};

struct Sphere
{
	float3 center;		// 中心座標
	float radius;		// 半径
};

// 
struct SphereAttribute
{
	float3 position;
	float3 normal;
	bool front;
};
