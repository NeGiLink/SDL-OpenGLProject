#pragma once
#include "Math.h"
#include "Texture.h"
#include "Shader.h"
#include "WinMain.h"
#include "BaseScene.h"

//�摜�`����J�v�Z���������N���X
class Image
{
public:
	// UI���A�N�e�B�u�����Ă��邩��ǐՂ��܂�
	enum UIState
	{
		EActive,
		EClosing,
		EDestroy
	};

	enum FillType
	{
		Simple,
		Filled
	};

	enum FillMethod
	{
		Horizontal,
		Vertical,
		Radial360
	};
							Image(bool active = true);
	virtual					~Image();
	//�ǂݍ��ݏ���
	virtual void			Load(string file);
	virtual void			Update(float deltaTime);
	virtual void			Draw(class Shader* shader);
	// �e�N�X�`����`�����߂̊֐�
	void					DrawTexture(class Shader* shader);
	virtual void			UnLoad();
	// ��Ԃ���ɐݒ�
	void					Close();

	void					Active();

	//***Getter***
	virtual SDL_Rect		GetSDL_Rect() { return mTextureRect; }
	
	virtual float			GetFillAmount() { return mFillAmount; }
	// UI��ʂ̏�Ԃ��擾����
	UIState					GetState() const { return mState; }

	class Texture*			GetTexture() const { return mTexture; }

	//***Setter***
	//�摜��ݒ�
	virtual void			SetTexture(class Texture* texture);
	//�摜�̈ʒu��ݒ�
	virtual void			SetPosition(Vector2 pos);
	//�摜�̃X�P�[�����O��ݒ�
	virtual void			SetScale(Vector3 scale);
	virtual void			SetSDL_Rect(SDL_Rect rect) { mTextureRect = rect; }
	virtual void			SetFillAmount(float fill) { mFillAmount = fill; }
	//�摜�̉�]���s��
	virtual void			SetAngleZ(float angle);

	void					SetUpdateTogether(bool active) { updateTogether = active; }

protected:
	class BaseScene*		mGame;
	//�摜
	class Texture*			mTexture;
	// Configure positions
	Vector2					mTexturePos;
	//�X�P�[�����O
	Vector3					mTexScale;

	float					mAngleZ;

	SDL_Rect				mTextureRect;

	float					mFillAmount;

	// State
	UIState					mState;

	bool					updateTogether = true;
};

