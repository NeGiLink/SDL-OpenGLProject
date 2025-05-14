#pragma once
#include "SDL3.h"
#include "Renderer.h"

//�Q�[���S�̂̏������s���N���X
//�����ɃQ�[���ɕK�v�ȏ����������Ă����z��Ő��삵�܂����B
class GameApp
{
public:
								GameApp(class GameWinMain* main);
	//������
	bool						Initialize();
	//���͏���
	bool						ProcessInput();
	//�V�[���̃��[�h����
	bool						LoadUpdate();
	//�X�V����
	bool						Update();
	//���
	bool						Release();
	//���ݗL���ȃV�[����static�Ŏ擾
	static class BaseScene*		GetActiveScene() { return mActiveScene; }
private:
	//���݂̗L���ȃV�[��
	static class BaseScene*		mActiveScene;
	//�V�[��01
	class DebugScene01*			mDebugScene01;
	//�V�[��02
	class DebugScene02*			mDebugScene02;
	//�`��Ǘ��N���X
	class GameWinMain*			mWinMain;
};