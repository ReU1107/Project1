#pragma once
#include "../Engine/Utility/BinaryReader.h"

enum class VMDType : uint8_t
{
	Body = 0x01, 
	Morph = 0x02, 
	Camera = 0x04,
	Light = 0x08, 
	SelfShadow = 0x10,
};

uint8_t GetBit(VMDType type);

class VMDBinaryReader final : public Engine::BinaryReader
{
private:
	using base = Engine::BinaryReader;
private:
	//VMDType m_type;

	uint8_t m_type;// 1�̃��[�V�����f�[�^�ɕ��������Ă������߃r�b�g�`���ɕύX

public:
	// �R���X�g���N�^
	VMDBinaryReader(const std::string& filePath);
	// �f�X�g���N�^
	virtual ~VMDBinaryReader();
public:
	void AddVMDType(VMDType type);

	uint8_t GetVMDType() const;
};
