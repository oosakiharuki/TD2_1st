#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Soul.h"
#include "Enemy.h"
#include "ScreenBack.h"
#include"UserInterface.h"
#include"Particle.h"
#include"Sound.h"
#include "DeathParticle.h"
#include "baseEnemy.h"
#include <list>

enum class PlayerNum {
	right,
	flont,
	left,
};

enum class GameSystem {
	setumei,
	//countdown,
	game,
	death,
	clear
};
 
class BaseEnemy;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void ChangePlayer();
	void CheckAllCollisions();
	bool IsCollision(const AABB& aabb1, const AABB& aabb2);
	
	bool IsGameOver() { return isEnd_; }
	bool IsGameClear() { return isClear_; }

	void SetBaseEnemy();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	//プレイヤー
	Player* player[3];
	Model* PlayerOnModel_;
	Model* PlayerOffModel_;
	Model* PlayerDamageModel_;
	uint32_t textureHandleP_;
	uint32_t textureDamage_;
	uint32_t currentTexture_;
	bool PlayerDamagefige_ = false;

	uint32_t number; 
	PlayerNum playerNum;
	GameSystem scene_;

	const float deltaTImer = 1.0f / 60.0f;

	//魂の流れ
	Soul* soul_;
	Model* SoulModel_;

	//敵
	Enemy* enemy_;
	Model* EnemyModel_;
	uint32_t textureHandleE1_;
	uint32_t textureHandleE2_;

	//落下物
	std::list<BaseEnemy*> enemies_;
	BaseEnemy* baseEnemy_ = nullptr;
	int timer = 20;
	int place = 0;

	

	//勝ち負け
	bool isEnd_ = false;
	bool isClear_ = false;
	float deathTimer_ = 2.0f;

	ScreenBack* screenBack;
	// UI
	UserInterface* userInterface_;
	// パーティクル
	Particle* particle_;
	Model* particlemodel_;
	DeathParticle* deathParticle_ = nullptr;

	Model* StageModel_ = nullptr;

	// HPフラグ
	bool HPfige_ = false;
	float timeSinceLastRemove_;
	float removeInterval_;


	// 音声
	Sound* soundBGM_ = nullptr;
	Sound* soundSE_ = nullptr;
	// 音声ファイル
	std::wstring filenameBGM_ = L"./Resources/Sound/GameBGM.wav";
	std::wstring filenameSE_ = L"./Resources/Sound/mokugyo.wav";
	bool playSound = false; // 音声再生フラグ
	bool loopSound = true;  // ループ再生フラグ
	bool isPlaying = false; // 一時的音声の再生中フラグ
	bool isLooping = false; // ループ音声の再生中フラグ
	// 音声
	float volume1 = 0.3f;
	float volume2 = 0.8f;

	// テクスチャの切り替え用タイマー 
    float textureSwitchTimer_ = 0.0f;
	const float kTextureSwitchInterval_ = 0.2f; // 0.5秒ごとに切り替える


uint32_t tetureSetumei;
	Sprite* Setumei;


	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
