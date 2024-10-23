#include "Sound.h"

Sound::Sound(const std::wstring& filePath) : hMmio(nullptr), waveData(nullptr),
pXAudio2(nullptr), pMasteringVoice(nullptr), pSourceVoice(nullptr) {
    LoadWav(filePath);

    // XAudio2の初期化
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    XAudio2Create(&pXAudio2, 0);
    pXAudio2->CreateMasteringVoice(&pMasteringVoice);
}

Sound::~Sound() {
    if (waveData) {
        delete[] waveData;
    }
    if (pSourceVoice) {
        pSourceVoice->DestroyVoice();
    }
    if (pMasteringVoice) {
        pMasteringVoice->DestroyVoice();
    }
    if (pXAudio2) {
        pXAudio2->Release();
    }
    mmioClose(hMmio, 0);
    CoUninitialize();
}

void Sound::LoadWav(const std::wstring& filePath) {
    // WAVファイルを開く（ワイド文字列版）
    hMmio = mmioOpenW(const_cast<LPWSTR>(filePath.c_str()), nullptr, MMIO_READ | MMIO_ALLOCBUF);
    if (!hMmio) {
        std::cerr << "Could not open WAV file." << std::endl;
        return;
    }

    // 親チャンクの読み込み
    parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    if (mmioDescend(hMmio, &parent, nullptr, MMIO_FINDRIFF)) {
        std::cerr << "Not a valid WAV file." << std::endl;
        return;
    }

    // 子チャンクの読み込み
    child.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (mmioDescend(hMmio, &child, &parent, MMIO_FINDCHUNK)) {
        std::cerr << "Could not find 'fmt ' chunk." << std::endl;
        return;
    }

    // フォーマットの読み込み
    mmioRead(hMmio, reinterpret_cast<HPSTR>(&waveFormat), sizeof(WAVEFORMATEX));
    mmioAscend(hMmio, &child, 0);

    // データチャンクの読み込み
    child.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (mmioDescend(hMmio, &child, &parent, MMIO_FINDCHUNK)) {
        std::cerr << "Could not find 'data' chunk." << std::endl;
        return;
    }

    // データサイズの取得
    waveSize = child.cksize;
    waveData = new BYTE[waveSize];
    mmioRead(hMmio, reinterpret_cast<HPSTR>(waveData), waveSize);
    mmioAscend(hMmio, &child, 0);
}

void Sound::Play() {
    // ソースボイスの作成
    pXAudio2->CreateSourceVoice(&pSourceVoice, &waveFormat);

    // 音声データを再生するためのバッファを設定
    XAUDIO2_BUFFER buffer = { 0 };
    buffer.AudioBytes = waveSize; // データのサイズ
    buffer.pAudioData = waveData; // WAVデータのポインタ
    buffer.Flags = XAUDIO2_END_OF_STREAM; // ストリームの終わり

    // 再生開始
    pSourceVoice->SubmitSourceBuffer(&buffer);
    pSourceVoice->Start(0);
}

void Sound::PlayLoop() {
    // ソースボイスの作成（既存のソースボイスがある場合は削除）
    if (pSourceVoice) {
        pSourceVoice->DestroyVoice();
    }

    pXAudio2->CreateSourceVoice(&pSourceVoice, &waveFormat);

    // 音声データを再生するためのバッファを設定
    XAUDIO2_BUFFER buffer = { 0 };
    buffer.AudioBytes = waveSize; // データのサイズ
    buffer.pAudioData = waveData; // WAVデータのポインタ
    buffer.Flags = XAUDIO2_END_OF_STREAM; // ストリームの終わり

    // ループを設定
    buffer.LoopCount = XAUDIO2_LOOP_INFINITE; // 無限ループを指定

    // 再生開始
    pSourceVoice->SubmitSourceBuffer(&buffer);
    pSourceVoice->Start(0);
}



void Sound::Stop() {
    if (pSourceVoice) {
        pSourceVoice->Stop(0);
        pSourceVoice->FlushSourceBuffers();
    }
}