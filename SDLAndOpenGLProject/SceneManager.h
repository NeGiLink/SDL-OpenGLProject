#pragma once
#include "StandardLibrary.h"

//�V�[���̊Ǘ��A���[�h�������s���N���X
class SceneManager
{
private:
	//���[�h�Ώۂ̃V�[�����X�g
	static std::unordered_map<int, class BaseScene*>	mScenes;
	//���݂̃V�[��
	static class BaseScene*								mNowScene;
	//���[�h�t���O
	static bool											loading;
public:
	//�V�[���̃��[�h����
	static void											LoadScene(int index);
	//�V�[�����X�g�ɒǉ�
	static void											AddSceneList(class BaseScene* scene);
	//���݂̃V�[���̎擾
	static class BaseScene*								GetNowScene() { return mNowScene; }
	//���[�h�t���O�̎擾
	static bool											IsLoading() { return loading; }
	//���[�h�t���O������
	static void											DisabledLoading() { loading = false; }
};

