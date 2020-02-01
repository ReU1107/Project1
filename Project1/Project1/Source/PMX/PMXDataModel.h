#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <DirectXMath.h>
#include "..//Engine/Math/Color3.h"
#include "..//Engine/Math/Color4.h"
#include "..//Engine/Math/Vector2.h"
#include "..//Engine/Math/Vector3.h"
#include "..//Engine/Math/Vector4.h"

// 前方宣言
class PMXBinaryReader;

// インデックスサイズ
enum class PMXIndexSize : uint8_t
{
	Int8 = 1,
	Int16 = 2,
	Int32 = 4
};

// PMXヘッダーデータ
struct PMXHeader
{
	char signature[4];				// PMX
	float version;					// バージョン
	uint8_t indexSizeTableCount;	// 型テーブルのサイズ
	uint8_t encoding;				// エンコード方式( 0:UTF16 1:UTF8)
	uint8_t additionalUVCount;		// 追加UV数 (0～4)
	uint8_t indexSizeTable[6];

	PMXHeader(PMXBinaryReader& reader);
};

// PMXモデルの説明
struct PMXModelInformation
{
	std::string name;				// モデル名
	std::string nameEnglish;		// モデル名英
	std::string comment;			// コメント
	std::string commentEnglish;		// コメント英
	PMXModelInformation(PMXBinaryReader& reader);
};

// ウェイト変形方式
enum class PMXWeightType : uint8_t
{
	BDEF1,	// BoneDefomation(ボーン変形) 
	BDEF2,
	BDEF4,
	SDEF	// SphereDefomation(球体変形)
};

// PMX頂点データ
struct PMXVertex
{
	Engine::Vector3 position;			// 位置
	Engine::Vector3 normal;				// 法線
	Engine::Vector2 texcoord;			// テクスチャコード(u,v)
	std::vector<Engine::Vector4> addTexcoord;	// 追加UV
	PMXWeightType type;					// ウェイト変形方式

	static const uint32_t maxBone = 4;	// 1頂点に影響を与える最大ボーン数
	uint32_t boneIndex[maxBone];		// ボーン番号
	float boneWeight[maxBone];			// ボーンのウェイト値
	Engine::Vector3 sdefC;				// SDEF-C値(x,y,z)
	Engine::Vector3 sdefR0;				// SDEF-R0値(x,y,z)
	Engine::Vector3 sdefR1;				// SDEF-R1値(x,y,z)

	float edge;							// エッジ倍率

};

// PMX面データ
struct PMXIndex
{
	uint32_t index[3];		// インデックスバッファ用
};

// PMXテクスチャデータ
struct PMXTexture
{
	std::string textureFileName;
};

// 描画フラグ
enum class PMXRenderFlag : uint8_t
{
	Both = 0x01,				// 両面描画
	GroundShadow = 0x02,		// 地面影
	CasterSelfShadow = 0x04,	// セルフシャドウマップへの描画
	ReceviorSelfShadow = 0x08,	// セルフシャドウの描画
	RenderEdge = 0x10			// エッジ描画
};

// スフィアモード
enum class PMXSphereMode : uint8_t
{
	None = 0,		// 無効
	Sph = 1,		// 乗算
	Spa = 2,		// 加算
	SubTexture = 3	// サブテクスチャ(追加UV1のx,yをUV参照して通常テクスチャ描画を行う)
};

// 共有トゥーンフラグ
enum class PMXShareToonFlag : uint8_t
{
	Individual = 0,	// 個別
	Share = 1		// 共有
};

// PMXマテリアルデータ
struct PMXMaterial
{
	std::string name;				// 材質名
	std::string nameEnglish;		// 材質名英
	Engine::Color4 diffuseCoeff;	// ディフューズ係数
	Engine::Color3 specularCoeff;	// スペキュラー係数
	float specularity;				// 鏡面反射強度
	Engine::Color3 ambientCoeff;	// アンビエイト係数
	PMXRenderFlag renderFlag;		// 描画フラグ
	Engine::Vector4 edge;					// エッジ色
	float edgeSize;					// エッジサイズ

	uint32_t decalIndex;				// 通常テクスチャ
	uint32_t sphereIndex;			// スフィアテクスチャ

	PMXSphereMode sphereFlag;		// スフィアモード

	PMXShareToonFlag shareToonFlag;	// 共有トゥーンフラグ
	uint32_t toonIndex;				// トゥーンテクスチャ
	uint8_t shereToonTexture;		// 共有トゥーンテクスチャ

	std::string memo;				// メモ　スクリプト,エフェクトのパラメータ配置
	uint32_t indexCount;				// このマテリアルが使用する頂点数(必ず3の倍数)

};

// ボーンフラグ
enum class PMXBoneFlag : uint16_t
{
	AccessShowMode = 0x0001,			// 接続先(PMD子ボーン指定)表示方法 -> 0:座標オフセットで指定 1:ボーンで指定

	VailableRotation = 0x0002,			// 回転可能
	VailableTranslation = 0x0004,		// 移動可能
	Visible = 0x0008,					// 表示
	VailableControl = 0x0010,			// 操作可能

	IK = 0x0020,						// IK

	RotateAppend = 0x0100,				// 回転付加
	TranlateAppend = 0x0200,			// 移動付加

	FixedAxis = 0x0400,					// 軸固定
	LocalAxis = 0x0800,					// ローカル軸

	DeformationPhysical = 0x1000,		// 物理後変形
	DeformOuterParent = 0x2000			// 外部親変形
};

// 角度制限フラグ
enum class PMXLimitFlag : uint8_t
{
	OFF = 0,
	ON = 1
};

struct PMXIKLink
{
	uint32_t linkIndex;				// リンクボーン番号
	PMXLimitFlag limitFlag;			// 角度制限フラグ()

	// 角度制限1
	Engine::Vector3 lowerLimitAngle;			// 下限(x,y,z)ラジアン角
	Engine::Vector3 upperLimitAngle;			// 上限(x,y,z)ラジアン角

};

// PMXボーンデータ
struct PMXBone
{
	std::string name;				// 名前
	std::string nameEnglish;		// 名前英語
	Engine::Vector3 position;				// 位置
	uint32_t parentIndex;			// 親ボーン番号
	uint32_t transformHierarchy;	// 変形階層

	PMXBoneFlag boneFlag;			// ボーンフラグ

	// 接続先0
	Engine::Vector3 offsetPosition;			// 座標オフセット
	// 接続先1
	uint32_t connectIndex;			// 接続先ボーン番号
	// 回転付与1,移動付与1
	uint32_t influenceTargetIndex;	// 影響を与えるボーン番号
	float influenceCoeff;			// 影響度(付与率)(どの程度影響を与えるか)

	// 軸固定1
	Engine::Vector3 axisVector;				// 軸の方向ベクトル
	// ローカル軸1
	Engine::Vector3 xAxis;					// X軸の方向ベクトル
	Engine::Vector3 zAxis;					// Z軸の方向ベクトル

	// 外部親変形1
	uint32_t key;					// key値

	// IK1
	uint32_t ikTargetIndex;			// IKターゲットボーン番号
	uint32_t ikLoopCount;			// IKループ数
	float ikLimitAngle;				// IKループ計算時1回あたりの制限角度(ラジアン)
	uint32_t ikLinkCount;			// IKリンク数

	std::vector<PMXIKLink> ikLink;	// IKリンク

};

// モーフ操作パネル
enum class PMXMorphOperation : uint8_t
{
	None = 0,		// 
	Eyebrow = 1,	// 眉(左下)
	Eye = 2,		// 根(左上)
	Mouth = 3,		// 口(右上)
	Other = 4,		// その他(右下)
};

// モーフ種類
enum class PMXMorphType : uint8_t
{
	Group = 0,			// グループ
	Vertex = 1,			// 頂点
	Bone = 2,			// ボーン
	Texcoord = 3,		// UV
	AddTexcoord1 = 4,	// 追加UV
	AddTexcoord2 = 5,	// 追加UV
	AddTexcoord3 = 6,	// 追加UV
	AddTexcoord4 = 7,	// 追加UV
	Material = 8		// 材質
};

// 頂点モーフ
struct PMXVertexMorph
{
	uint32_t index;
	Engine::Vector3 offset;

};

// UVモーフ
struct PMXTexcoordMorph
{
	uint32_t index;
	Engine::Vector4 offset;

};

// ボーンモーフ
struct PMXBoneMorph
{
	uint32_t index;
	Engine::Vector3 displacement;
	Engine::Vector4 rotation;

};

enum class PMXOffsetOperation : uint8_t
{
	Multi = 0,// 乗算
	Add = 1// 加算
};

// 材質モーフ
struct PMXMaterialMorph
{
	uint32_t index;					// -1全材質対象
	PMXOffsetOperation operation;	// 演算形式
	Engine::Vector4 diffuse;				// 
	Engine::Vector3 specular;				// 
	float specularity;				// 
	Engine::Vector3 ambient;				// 
	Engine::Vector4 edge;					// 
	float edgeSize;					// エッジサイズ
	Engine::Vector4 textureCoeff;			// テクスチャ係数
	Engine::Vector4 sphereTexCoeff;			// スフィアテクスチャ係数
	Engine::Vector4 toonTexCoeff;			// トゥーンテクスチャ係数

};

// グループモーフ
struct PMXGroupMorph
{
	uint32_t index;	// 
	float coeff;	// モーフ率

};

// PMXモーフデータ
struct PMXMorph
{
	std::string name;
	std::string nameEnglish;

	PMXMorphOperation operation;	// 操作パネル

	PMXMorphType type;				// モーフ種類

	uint32_t offsetCount;				// モーフオフセット数

	std::vector<PMXVertexMorph> vertexData;		// オフセットデータ
	std::vector<PMXTexcoordMorph> texcoordData;	// 
	std::vector<PMXBoneMorph> boneData;			// 
	std::vector<PMXMaterialMorph> materialData;	// 
	std::vector<PMXGroupMorph> groupData;		// 
};

// 特殊枠フラグ
enum class PMXFrameFlag : uint8_t
{
	Default = 0,	// 通常枠
	Special = 1		// 特殊枠
};

enum class PMXFrameTarget : uint8_t
{
	Bone = 0,
	Morph = 1
};

// 枠内要素
struct PMXFrameworkElement
{
	PMXFrameTarget target;
	uint32_t index;
};
/*
表示枠というよりオブジェクトの属性を知ることが出来る
Boneならどんなボーン属性に所属する等
例:
全てのモデルが統一されているなら使用していた
*/
// PMX表示枠
struct PMXDisplayFrame
{
	std::string name;
	std::string nameEnglish;
	PMXFrameFlag flag;
	uint32_t elementCount;
	std::vector<PMXFrameworkElement> elements;

};

// 形状
enum class PMXShape : uint8_t
{
	Sphere = 0,
	Box = 1,
	Capsule = 2
};

// 物理演算
enum class PMXPhysicsOperation : uint8_t
{
	Static = 0,			// ボーン追従
	Dynamic = 1,		// 物理演算
	BoneRegistration = 2// 物理演算 + Bone位置合わせ
};

// PMX剛体
struct PMXRigidBody
{
	std::string name;
	std::string nameEnglish;

	int32_t index;				// 関連ボーンIndex - 関連なしの場合は-1
	uint8_t group;				// グループ
	uint16_t collisionGroup;	// 非衝突グループフラグ
	PMXShape shape;				// 形状 - 0:球 1:箱 2:カプセル
	Engine::Vector3 size;				// サイズ(x,y,z)
	Engine::Vector3 position;			// 位置(x,y,z)
	Engine::Vector3 rotation;			// 回転(x,y,z) -> ラジアン角

	float mass;					// 質量
	float translationAtten;		// 移動減衰
	float rotationAtten;		// 回転減衰
	float repulsive;			// 反発力
	float friction;				// 摩擦力
	PMXPhysicsOperation operation;	// 剛体の物理演算 - 0:ボーン追従(static) 1:物理演算(dynamic) 2:物理演算 + Bone位置合わせ

};

/*
collisionGroup
65535

0 = 0
1 = -1
2 = -2
3 = -4
4 = -8
5 = -16
6 = -32
7 = -64
8 = -128
9 = -256
10 = -512
11 = -1024
12 = -2048
13 = -4096
14 = -8192
15 = -16384
16 = -32768
*/

enum class PMXJointType : uint8_t
{
	Spring = 0
};

// PMXジョイント
struct PMXJoint
{
	std::string name;
	std::string nameEnglish;

	PMXJointType type;

	// typeが0
	uint32_t indexA;				// 関連剛体AのIndex - 関連なしの場合は-1
	uint32_t indexB;				// 関連剛体BのIndex - 関連なしの場合は-1

	Engine::Vector3 position;			// 位置(x,y,z)
	Engine::Vector3 rotation;			// 回転(x,y,z) -> ラジアン角

	Engine::Vector3 lowerTranslation;	// 移動制限-下限(x,y,z)
	Engine::Vector3 upperTranslation;	// 移動制限-上限(x,y,z)
	Engine::Vector3 lowerRotation;		// 回転制限-下限(x,y,z) -> ラジアン角
	Engine::Vector3 upperRotation;		// 回転制限-上限(x,y,z) -> ラジアン角

	Engine::Vector3 constantTranslatin;	// バネ定数-移動(x,y,z)
	Engine::Vector3 constantRotation;	// バネ定数-回転(x,y,z)

};
