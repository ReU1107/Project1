#pragma once
#include <cstdint>
#include <Windows.h>
//#include <mmsystem.h>

/*
�Q�lURL
http://www.web-sky.org/program/other/wave.php
*/

/*
RIFF(Resource Interchange File Format)
*/

/*
size�Ɋւ���⑫
Intel CPU�̃A�[�L�e�N�`���̓��g���G���f�B�A��������
�̗p���Ă����
���ɂ���Ă͒l�̊i�[�����Ă����
*/

class RIFFBinaryReader;

struct RIFFHeader
{
	uint8_t signature[4];	// RIFF
	uint32_t size;			// �t�@�C���T�C�Y-8byte�̃T�C�Y
	uint8_t type[4];		// �^�C�v WAVE,AVI
	RIFFHeader(RIFFBinaryReader& reader);
};

// �`�����N�c�f�[�^�̉�
// �㑱�̃f�[�^���ς���Ă���
struct RIFFChunk
{
	char id[4];		// �`�����N�����ʂ���ID
	uint32_t size;	// �`�����N�̃f�[�^�̃T�C�Y
	RIFFChunk(RIFFBinaryReader& reader);
};

/*
fmt �`�����N(�K�{)
data �`�����N�i�K�{�j
fact �`�����N�i�I�v�V�����j
cue �`�����N�i�I�v�V�����j
plst �`�����N�i�I�v�V�����j
list �`�����N�i�I�v�V�����j
labl �`�����N�i�I�v�V�����j
note �`�����N�i�I�v�V�����j
ltxt �`�����N�i�I�v�V�����j
smpl �`�����N�i�I�v�V�����j
inst �`�����N�i�I�v�V�����j
*/

/*
FormatChunk
*/

struct WAVEFormat
{
	uint16_t format;				// �g�`�f�[�^�̃t�H�[�}�b�gWAVE_FORMAT�Z�Z
	uint16_t channelCount;			// �g�p�`�����l���� ���m����,�X�e���I
	uint32_t frequency;				// �T���v�����O���g��(Hz)Sampler Per Second
	uint32_t bytePerSec;			// ���σf�[�^����1�b�Ԃɉ��o�C�g�g�p���邩
	uint16_t bytePerSam;			// 1�T���v���ɉ��o�C�g�g�p���邩
	uint16_t depth;					// �r�b�g�[�x

	WAVEFormat(RIFFBinaryReader& reader);
};

// ���j�APCM����Ȃ��Ƃ��͂�����
struct WAVEFormatEx
{
	WAVEFormat defaultData;			// �f�t�H���g�̃f�[�^
	uint16_t extensSize;			// �g���f�[�^�T�C�Y
	uint8_t* extensData;			// �g���f�[�^�i�[�A�h���X
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