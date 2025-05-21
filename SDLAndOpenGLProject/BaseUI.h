#pragma once
#include "Math.h"
#include "Texture.h"
#include "Shader.h"
#include "WinMain.h"
#include "BaseScene.h"


class BaseUI
{
public:
	// UI���A�N�e�B�u�����Ă��邩��ǐՂ��܂�
	enum UIState
	{
		EActive,
		EClosing,
		EDestroy
	};
								BaseUI();
		virtual					~BaseUI();
		//�ǂݍ��ݏ���
		virtual void			Load(string file);
		virtual void			Update(float deltaTime);
		virtual void			Draw(class Shader* shader);
		// �e�N�X�`����`�����߂̊֐�
		void					DrawTexture(class Shader* shader);

		Vector4					UVCalculation();

		Matrix4					WorldMatrixCalculation();

		virtual void			UnLoad();
		// ��Ԃ���ɐݒ�
		void					Close();

		void					Active();

		//***Getter***
		virtual SDL_Rect		GetSDL_Rect() { return mTextureRect; }

		// UI��ʂ̏�Ԃ��擾����
		UIState					GetState() const { return mState; }

		

		//***Setter***
		//�摜��ݒ�
		virtual void			SetTexture(class Texture* texture);
		//�摜�̈ʒu��ݒ�
		virtual void			SetPosition(Vector2 pos);
		//�摜�̃X�P�[�����O��ݒ�
		virtual void			SetScale(Vector3 scale);
		virtual void			SetSDL_Rect(SDL_Rect rect) { mTextureRect = rect; }
		//�摜�̉�]���s��
		virtual void			SetAngleZ(float angle);

		virtual void 			SetState(UIState state) { mState = state; }

protected:
	class BaseScene* mGame;

	// Configure positions
	Vector2					mTexturePos;
	//�X�P�[�����O
	Vector3					mTexScale;

	float					mAngleZ;

	SDL_Rect				mTextureRect;

	// State
	UIState					mState;
};

