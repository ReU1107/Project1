#pragma once
#include <cstdint>
#include <Windows.h>
//#include <mmsystem.h>

/*
参考URL
http://www.web-sky.org/program/other/wave.php
*/

/*
RIFF(Resource Interchange File Format)
*/

/*
sizeに関する補足
Intel CPUのアーキテクチャはリトルエンディアン方式を
採用している為
環境によっては値の格納をしてくれる
*/

class RIFFBinaryReader;

struct RIFFHeader
{
	uint8_t signature[4];	// RIFF
	uint32_t size;			// ファイルサイズ-8byteのサイズ
	uint8_t type[4];		// タイプ WAVE,AVI
	RIFFHeader(RIFFBinaryReader& reader);
};

// チャンク…データの塊
// 後続のデータが変わってくる
struct RIFFChunk
{
	char id[4];		// チャンクを識別するID
	uint32_t size;	// チャンクのデータのサイズ
	RIFFChunk(RIFFBinaryReader& reader);
};

/*
fmt チャンク(必須)
data チャンク（必須）
fact チャンク（オプション）
cue チャンク（オプション）
plst チャンク（オプション）
list チャンク（オプション）
labl チャンク（オプション）
note チャンク（オプション）
ltxt チャンク（オプション）
smpl チャンク（オプション）
inst チャンク（オプション）
*/

/*
FormatChunk
*/

struct WAVEFormat
{
	uint16_t format;				// 波形データのフォーマットWAVE_FORMAT〇〇
	uint16_t channelCount;			// 使用チャンネル数 モノラル,ステレオ
	uint32_t frequency;				// サンプリング周波数(Hz)Sampler Per Second
	uint32_t bytePerSec;			// 平均データ割合1秒間に何バイト使用するか
	uint16_t bytePerSam;			// 1サンプルに何バイト使用するか
	uint16_t depth;					// ビット深度

	WAVEFormat(RIFFBinaryReader& reader);
};

// リニアPCMじゃないときはこっち
struct WAVEFormatEx
{
	WAVEFormat defaultData;			// デフォルトのデータ
	uint16_t extensSize;			// 拡張データサイズ
	uint8_t* extensData;			// 拡張データ格納アドレス
	WAVEFormatEx(RIFFBinaryReader& reader);
	~WAVEFormatEx();
};

struct WAVEList
{
	char listType[4];
	WAVEList(RIFFBinaryReader& reader);
};

struct WAVEISFT
{
	char data[14];
	WAVEISFT(RIFFBinaryReader& reader);
};