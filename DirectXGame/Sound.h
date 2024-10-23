#pragma once
#include <Windows.h>
#include <iostream>
#include <mmreg.h>
#include <mmsystem.h>
#include <string>
#include <xaudio2.h>

class Sound {
public:
	Sound(const std::wstring& filePath);
	~Sound();

	void Play();
	void PlayLoop();
	void Stop();
	void LoadWav(const std::wstring& filePath);
	void SetVolume(float volume); // 音量を設定するメソッドを追加

	void Settexture();

private:
	HMMIO hMmio;
	BYTE* waveData;
	IXAudio2* pXAudio2;
	IXAudio2MasteringVoice* pMasteringVoice;
	IXAudio2SourceVoice* pSourceVoice;
	WAVEFORMATEX waveFormat;
	MMCKINFO parent;
	MMCKINFO child;
	DWORD waveSize;
	float currentVolume = 1.0f; // 音量を保持するメンバ変数
};