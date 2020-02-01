#pragma once
#include <cstdint>
#include <vector>
#include "../Engine/Math/Vector3.h"
#include "../Engine/Math/Vector4.h"
#include "../Engine/Math/Color3.h"

// https://blog.goo.ne.jp/torisu_tetosuki/e/bc9f1c4d597341b394bd02b64597499d
// VMDファイルフォーマット
// PMD,PMX用モーションデータ

// 前方宣言
class VMDBinaryReader;

// VMDヘッダーデータ
struct VMDHeader
{
	char signature[30];			// 
	char motionName[20];		// モーション,カメラ,照明,…
	VMDHeader(VMDBinaryReader& reader);
};

// VMD身体を動かすモーション
struct VMDBodyMotion
{
	char boneName[15];					// ボーン名
	uint32_t frameIndex;				// フレーム番号
	Engine::Vector3 position;			// 位置
	Engine::Vector4 rotataion;			// 回転(四元数)
	uint8_t bezierControllPoint[64];	// ベジェ曲線用制御点
};

// VMDモーフを動かすモーション
struct VMDMorphMotion
{
	char name[15];				// モーフ対象名
	uint32_t frameIndex;		// フレーム番号
	float weight;				// モーフの設定値
};

// VMDカメラを動かすモーション
struct VMDCameraMotion
{
	uint32_t frameIndex;		// フレーム番号
	float length;				// 距離
	Engine::Vector3 position;			// 位置
	Engine::Vector3 rotation;			// 回転
	uint8_t interpolation[24];	// 補間
	uint32_t angle;				// 視野角
	uint8_t perspectiveFlag;	// 射影変換フラグ
};

// 照明を動かすモーション
struct VMDLightMotion
{
	uint32_t frameIndex;	// フレーム番号
	Engine::Color3 color;			// 色(0～256)
	Engine::Vector3 position;		// 位置
};

// セルフシャドウを動かすモーション
struct VMDSelfShadowMotion
{
	uint32_t frameIndex;	// フレーム番号
	uint8_t mode;			// モード
	float distance;			// 距離
};
