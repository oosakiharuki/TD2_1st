#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <xaudio2.h>
#include <iostream>
#include <string>

class Sound {
public:
    Sound(const std::wstring& filePath);
    ~Sound();

    void Play();
    void PlayLoop();
    void Stop();

    void LoadWav(const std::wstring& filePath);

private:
    HMMIO hMmio;
    MMCKINFO parent, child;
    WAVEFORMATEX waveFormat;
    BYTE* waveData;
    DWORD waveSize;

    IXAudio2* pXAudio2;           // XAudio2 インターフェイス
    IXAudio2MasteringVoice* pMasteringVoice; // マスターボイス
    IXAudio2SourceVoice* pSourceVoice; // ソースボイス

};