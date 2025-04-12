#pragma once
#include <string>
#include "Math.h"

//SE,BGMを取得・再生するクラス
class SoundEvent
{
public:
	SoundEvent();
	// 関連するFMODイベントがまだ存在する場合、trueを返します。
	bool IsValid();
	// イベントを最初から再起動する。
	void Restart();
	// このイベントを停止。
	void Stop(bool allowFadeOut = true);
	// Setters
	void SetPaused(bool pause);
	void SetVolume(float value);
	void SetPitch(float value);
	void SetParameter(const std::string& name, float value);
	// Getters
	bool GetPaused() const;
	float GetVolume() const;
	float GetPitch() const;
	float GetParameter(const std::string& name);
	// Positional
	bool Is3D() const;
	void Set3DAttributes(const Matrix4& worldTrans);
protected:
	// このコンストラクタをprotectedにし、AudioSystemを友達として設定して、
	// AudioSystemのみがこのコンストラクタにアクセスできるようにします。
	friend class AudioSystem;
	SoundEvent(class AudioSystem* system, unsigned int id);
private:
	class AudioSystem* mSystem;
	unsigned int mID;
};