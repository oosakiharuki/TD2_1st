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

enum class PlayerNum {
	right,
	flont,
	left,
	move,
};

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
	
	bool IsGameOver() { return isEnd_; }
	bool IsGameClear() { return isClear_; }


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
	uint32_t textureHandleP_;

	uint32_t number; 
	PlayerNum playerNum;

	//魂の流れ
	Soul* soul_;
	Model* SoulModel_;

	//敵
	Enemy* enemy_;
	Model* EnemyModel_;
	uint32_t textureHandle_;

	//勝ち負け
	bool isEnd_ = false;
	bool isClear_ = false;

	ScreenBack* screenBack;
	// UI
	UserInterface* userInterface_;
	// パーティクル
	Particle* particle_;
	Model* particlemodel_;

	Model* StageModel_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
