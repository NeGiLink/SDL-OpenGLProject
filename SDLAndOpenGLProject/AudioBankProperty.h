#pragma once
#include "Typedefs.h"
#include "Math.h"
#include "StandardLibrary.h"


//AudioSystem�Ɏg��bank�̃p�X���Ǘ�����N���X
//�p�X��cpp����
// Ctrl + F �uAudioBankProperty.cpp�v
class AudioBankProperty
{
private:
	static string mMasterBankString;

	static string mMasterBank;
public:
	static string GetMasterBankString() { return mMasterBankString; }

	static string GetMasterBank() { return mMasterBank; }
};

