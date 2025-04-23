#pragma once
#include "Math.h"
#include <cstdint>
#include <string>
#include <functional>
#include <vector>

//�{�^��UI�̃N���X
class Button
{
public:
	Button(const std::string& name, class Font* font,
		std::function<void()> onClick,
		const Vector2& pos, const Vector2& dims);
	~Button();

	// �{�^���̖��O��ݒ肵�܂�
	void SetName(const std::string& name);

	// Getters/setters
	class Texture* GetNameTex() { return mNameTex; }
	const Vector2& GetPosition() const { return mPosition; }
	void SetHighlighted(bool sel) { mHighlighted = sel; }
	bool GetHighlighted() const { return mHighlighted; }

	// �|�C���g���{�^���̋��E���ɂ���ꍇ��true��Ԃ��܂�
	bool ContainsPoint(const Vector2& pt) const;
	// �{�^�����N���b�N���ꂽ�Ƃ��ɌĂяo����܂�
	void OnClick();
private:
	std::function<void()>	mOnClick;
	
	std::string				mName;
	
	class Texture*			mNameTex;
	
	class Font*				mFont;
	
	Vector2					mPosition;
	
	Vector2					mDimensions;
	
	bool					mHighlighted;
};

//�|�[�Y�A�_�C�A���O�Ȃǂ�UI�̊��N���X
class UIScreen
{
public:
	UIScreen();
	virtual ~UIScreen();
	// UIScreen�̃T�u�N���X�͂������I�[�o�[���C�h�ł��܂�
	virtual void Update(float deltaTime);
	virtual void Draw(class Shader* shader);
	virtual void ProcessInput(const struct InputState& keys);
	virtual void HandleKeyPress(int key);
	// UI���A�N�e�B�u���Ǘ�����^�O
	enum UIState
	{
		EActive,
		EClosing
	};
	// ��Ԃ���ɐݒ�
	void Close();
	// UI��ʂ̏�Ԃ��擾����
	UIState GetState() const { return mState; }
	// �^�C�g���e�L�X�g��ύX����
	void SetTitle(const std::string& text,
		const Vector3& color = Color::White,
		int pointSize = 40);
	// ���̉�ʂɃ{�^����ǉ�����֐�
	void AddButton(const std::string& name, std::function<void()> onClick);
protected:
	// �摜��`�悷��֐�
	void DrawTexture(class Shader* shader, class Texture* texture,
		const Vector2& offset = Vector2::Zero,
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f), float angle = 0);
	// �}�E�X���[�h�𑊑΃��[�h�ɐݒ肷�邩�ǂ���
	void SetRelativeMouseMode(bool relative);
	class BaseScene*		mGame;

	class Text*				mTitleFont;
	class Image*			mTitle;
	class Image*			mBackground;
	class Image*			mButtonOn;
	class Image*			mButtonOff;

	// �ʒu��ݒ肷��
	Vector2					mTitlePos;
	Vector2					mNextButtonPos;
	Vector2					mBGPos;

	// ���
	UIState					mState;
	// �{�^���̃��X�g
	std::vector<Button*>	mButtons;
};