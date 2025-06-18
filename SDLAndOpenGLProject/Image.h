#pragma once
#include "Math.h"
#include "Texture.h"
#include "Shader.h"
#include "WinMain.h"
#include "BaseScene.h"

/*
* ===�G���W����������/Engine internal processing===
*/

//�摜�`����J�v�Z���������N���X
// Unity��Image�ɋ߂��N���X
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
		None,
		Horizontal,
		Vertical,
		Radial360
	};
protected:
	class BaseScene*		mGame;
	//�摜
	class Texture*			mTexture;
	// Configure positions
	Vector2					mTexturePos;

	float					mOffsetX;
	float					mOffsetY;

	//�X�P�[�����O
	Vector3					mTexScale;

	float					mRectScaleWidth;
	float					mRectScaleHeight;

	float					mAngleZ;

	SDL_Rect				mTextureRect;

	float					mFillAmount;

	// State
	UIState					mState;

	FillType				mFillType;

	FillMethod				mFillMethod;

	int						mVerticesCount;

	vector<Image*>			mImages;
public:
							Image();
	virtual					~Image();
	//�ǂݍ��ݏ���
	virtual void			Load(string file);
	virtual void			Update(float deltaTime);
	virtual void			Draw(class Shader* shader);
	// �e�N�X�`����`�����߂̊֐�
	void					DrawTexture(class Shader* shader);

	void					FillMethodCalculation(Vector4& uv,int& verticesCount);

	void					WorldMatrixCalculation(Matrix4& trans,Matrix4& rotate,Matrix4& scale);

	virtual void			UnLoad();
	// ��Ԃ���ɐݒ�
	void					Close();

	void					Active();

	//***Getter***
	virtual SDL_Rect		GetSDL_Rect() { return mTextureRect; }
	
	virtual float			GetFillAmount() { return mFillAmount; }
	// UI��ʂ̏�Ԃ��擾����
	UIState					GetState() const 
	{
		return mState; 
	}

	class Texture*			GetTexture() const { return mTexture; }

	//***Setter***
	//�摜��ݒ�
	virtual void			SetTexture(class Texture* texture);
	//�摜�̈ʒu��ݒ�
	virtual void			SetPosition(Vector2 pos);
	//�摜�̃X�P�[�����O��ݒ�
	virtual void			SetScale(Vector3 scale);
	virtual void			SetSDL_Rect(SDL_Rect rect) { mTextureRect = rect; }
	virtual void			SetFillAmount(float fill);
	//�摜�̉�]���s��
	virtual void			SetAngleZ(float angle);

	virtual void			SetFillType(FillType type) { mFillType = type; }

	virtual void			SetFillMethod(FillMethod method) { mFillMethod = method; }

	virtual FillMethod		GetFillMethod() { return mFillMethod; }

	virtual void			SetVerticesCount(int count) { mVerticesCount = count; }
	virtual int				GetVerticesCount() { return mVerticesCount; }

	virtual void 			SetState(UIState state);

	void					AddChildUIImage(Image* image);
};