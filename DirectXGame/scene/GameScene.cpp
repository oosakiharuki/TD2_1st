#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete PlayerOnModel_;
	delete PlayerOffModel_;
	delete PlayerDamageModel_;
	for (int i = 0; i < 3; i++) {
		delete player[i];
	}
	delete SoulModel_;
	delete soul_;
	delete EnemyModel_;
	delete enemy_;
	delete screenBack;
	delete userInterface_;
	delete particlemodel_;
	delete particle_;
	delete StageModel_;
	delete soundBGM_;
	delete soundSE_;
	delete deathParticle_;

	for (BaseEnemy* baseenemy_ : enemies_) {
		delete baseenemy_;
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	worldTransform_.Initialize();
	viewProjection_.Initialize();

	PlayerOnModel_ = Model::CreateFromOBJ("playerOn", true);
	PlayerOffModel_ = Model::CreateFromOBJ("playerOff", true);
	PlayerDamageModel_= Model::CreateFromOBJ("PlayerDamage", true);
	textureHandleP_ = TextureManager::Load("playerOn/playerOn.png");
	textureDamage_  = TextureManager::Load("PlayerDamage/PlayerDamage.png");
	currentTexture_ = TextureManager::Load("PlayerDamage/PlayerDamage.png");
	textureHandleE1_ = TextureManager::Load("enemy.png");
	textureHandleE2_ = TextureManager::Load("enemyDamage.png");

	for (int i = 0; i < 3; i++) {
		player[i] = new Player();
		player[i]->Initialize({-20.0f + float(i * 20), 0, 0}, PlayerOnModel_, PlayerOffModel_, textureHandleP_, &viewProjection_);
	}

	number = 0;
	playerNum = PlayerNum::right;
	scene_ = GameSystem::game;

	SoulModel_ = Model::CreateFromOBJ("playerOn", true);
	soul_ = new Soul();
	soul_->Initialize(SoulModel_, textureHandleP_, &viewProjection_, {-20,0,0});


	EnemyModel_ = Model::CreateFromOBJ("enemy", true);
	enemy_ = new Enemy();
	enemy_->Initialize(EnemyModel_, textureHandleE1_,textureHandleE2_, &viewProjection_);


	screenBack = new ScreenBack();
	screenBack->Initialisz();

	userInterface_ = new UserInterface();
	userInterface_->Initialize();
	timeSinceLastRemove_ = 3;
	removeInterval_ = 3;
	soul_->SetUI(userInterface_);

	particlemodel_ = Model::CreateFromOBJ("particle", true);
	particle_ = new Particle();
	particle_->Initialize(particlemodel_, &viewProjection_, Vector3(-20.0f, 0, 0));

	StageModel_ = Model::CreateFromOBJ("Stage", true);

	// サウンドの生成
	soundBGM_ = new Sound(filenameBGM_);
	soundSE_ = new Sound(filenameSE_);
	// ファイルの指定
	soundBGM_->LoadWav(filenameBGM_);
	soundSE_->LoadWav(filenameSE_);
	soundBGM_->SetVolume(volume1);
	soundSE_->SetVolume(volume2);

	deathParticle_ = new DeathParticle();
	deathParticle_->Initialize(particlemodel_,&viewProjection_);
}

void GameScene::ChangePlayer() {


	if (!soul_->IsMove()) {
		switch (playerNum) {
		case PlayerNum::right:
			player[0]->IsPlayer(true);
			player[1]->IsPlayer(false);
			player[2]->IsPlayer(false);
			break;
		case PlayerNum::flont:
			player[0]->IsPlayer(false);
			player[1]->IsPlayer(true);
			player[2]->IsPlayer(false);
			break;
		case PlayerNum::left:
			player[0]->IsPlayer(false);
			player[1]->IsPlayer(false);
			player[2]->IsPlayer(true);
			break;
		}
	} 
	else  {
		player[0]->IsPlayer(false);
		player[1]->IsPlayer(false);
		player[2]->IsPlayer(false);
	}

	if (number == 0) {
		playerNum = PlayerNum::right;
		if (input_->TriggerKey(DIK_D) && !soul_->IsMove()) {
			number += 1;
			soul_->Start(true);
			soul_->GetPosition(player[0]->GetWorldPosition(), player[1]->GetWorldPosition());
		}		
	} 
	else if (number == 1) {
		playerNum = PlayerNum::flont;
		if (input_->TriggerKey(DIK_D) && !soul_->IsMove()) {
			number += 1;
			soul_->Start(true);
			soul_->GetPosition(player[1]->GetWorldPosition(), player[2]->GetWorldPosition());
		} 
		else if (input_->TriggerKey(DIK_A) && !soul_->IsMove()) {
			number -= 1;
			soul_->Start(false);
			soul_->GetPosition(player[1]->GetWorldPosition(), player[0]->GetWorldPosition());
		}
	}
	else if (number == 2) {
		playerNum = PlayerNum::left;
		if (input_->TriggerKey(DIK_A) && !soul_->IsMove()) {
			number -= 1;
			soul_->Start(false);
			soul_->GetPosition(player[2]->GetWorldPosition(), player[1]->GetWorldPosition());
		}
	}
}

bool GameScene::IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) && (aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) && (aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {
		return true;
	}
	return false;
}

void GameScene::Update() {

	switch (scene_) {
	case GameSystem::setumei:
		break;
	case GameSystem::game:

		
	if (PlayerDamagefige_) {
			// テクスチャの切り替え処理
			if (textureSwitchTimer_ >= kTextureSwitchInterval_) {
				textureSwitchTimer_ = 0.0f; // タイマーをリセット

				// テクスチャを交互に切り替え
				if (currentTexture_ == textureDamage_) {
					currentTexture_ = textureHandleP_;
				} else {
					currentTexture_ = textureDamage_;
				}
			}
			for (int i = 0; i < 3; i++) {
				player[i]->SetTexture(currentTexture_);
			}
			soul_->SetTexture(currentTexture_);
		} else {
			for (int i = 0; i < 3; i++) {
				player[i]->SetTexture(textureHandleP_);
			}
			soul_->SetTexture(textureHandleP_);
		}


		if (!soul_->IsMove()) {
			for (int i = 0; i < 3; i++) {
				player[i]->Update();
			}
		}

		soul_->Update();

		enemy_->Update();
		
		CheckAllCollisions();
		ChangePlayer();


		if (soul_->IsDead()) {		
			deathParticle_->SetPosition(soul_->GetWorldPosition());
			scene_ = GameSystem::death;	
		}

		userInterface_->Update();
		userInterface_->SetIsMove(soul_->IsMove());

		// 無敵タイマー
		if (!HPfige_) {
			timeSinceLastRemove_ += deltaTImer;
			textureSwitchTimer_ += deltaTImer;  
		}
		if (timeSinceLastRemove_ >= 3) {
			timeSinceLastRemove_ = 3;
			PlayerDamagefige_ = false;
		}
		// 当たったらHPを減らしフラグリセット
		if (HPfige_) {
			userInterface_->RemoveHeart();
			timeSinceLastRemove_ = 0;
			HPfige_ = false;
			PlayerDamagefige_ = true;
			textureSwitchTimer_ = 0.0f;
		}

		particle_->Update(soul_->GetWorldPosition());

		if (enemy_->IsDead()) {
			scene_ = GameSystem::clear;
		}


		timer++;

		if (timer >= 110) {
			SetBaseEnemy();
			timer = 0;
		}

		// 自キャラの更新
		for (BaseEnemy* baseenemy_ : enemies_) {
			baseenemy_->Update();
		}

		enemies_.remove_if([](BaseEnemy* enemy) { 
			if (enemy->IsDead()) {
				delete enemy;
				return true;
			}
			return false;
		});

		break;
	case GameSystem::death:
		player[0]->IsPlayer(false);
		player[1]->IsPlayer(false);
		player[2]->IsPlayer(false);

		deathParticle_->Update();
		enemy_->Update();
		if (deathParticle_->isFinish()) {
			isEnd_ = true;
		}
		break;
	case GameSystem::clear:
		userInterface_->Update();
		userInterface_->SetIsMove(!soul_->IsMove());

		if (!soul_->IsMove()) {
			for (int i = 0; i < 3; i++) {
				//player[i]->Update();
			}
		}

		soul_->Update();

		if (enemy_->IsFinish()) {
			isClear_ = true;	
		}
		break;
	}


	// 音声の更新　: 例

	//// 一回だけの音声
	//if (playSound) {
	//	if (!isPlaying) {     // 再生中でない場合
	//		soundSE_->Play(); // 一回だけ再生
	//	}
	//	isPlaying = true; // 再生中フラグを立てる
	//} else {
	//	if (isPlaying) {       // 再生中の場合のみ停止
	//		soundSE_->Stop();  // 音声を停止
	//		isPlaying = false; // 再生中フラグを下げる
	//	}
	//}

	// ループ音声
	if (loopSound) {
		if (!isLooping) {              // ループ中でない場合
			soundBGM_->PlayLoop(); // ループ再生を開始
			isLooping = true;          // ループ中フラグを立てる
		}
	} else {
		if (isLooping) {           // ループ中の場合のみ停止
			soundBGM_->Stop(); // ループ再生を停止
			isLooping = false;     // ループ中フラグを下げる
		}
	}



}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	screenBack->Drwa();//背景,skydomeに変えてもよい
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	StageModel_->Draw(worldTransform_, viewProjection_);
	
	for (int i = 0; i < 3; i++) {	
		player[i]->Draw();	
	}

	switch (scene_) {
	case GameSystem::setumei:
		break;
	case GameSystem::game:
		soul_->Draw();
		enemy_->Draw();
		particle_->Draw();

		// 自キャラの描画
		
		for (BaseEnemy* baseenemy_ : enemies_) {
			baseenemy_->Draw();
		}
		

		break;
	case GameSystem::death:
		enemy_->Draw();
		deathParticle_->Draw();
		break;
	case GameSystem::clear:
		enemy_->Draw();
		soul_->Draw();
		particle_->Draw();
		break;
	}
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	enemy_->Draw2D();
	switch (scene_) {
	case GameSystem::game:
		userInterface_->Draw2D();
		break;
	}
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	Vector3 A, B;

	/// プレイヤーと敵の当たり判定(一マスのみ)

	A = soul_->GetWorldPosition();
	B = enemy_->GetWorldPosition();

	if (IsCollision(soul_->GetAABB(), enemy_->GetAABB()) && timeSinceLastRemove_ >= removeInterval_) {
		soul_->OnCollision();
		HPfige_ = userInterface_->IsButtonPressed();
	}

	///プレイヤーと敵の当たり判定

	A = soul_->GetWorldPosition();

	for (BaseEnemy* baseenemy_ : enemies_) {
	
		B = baseenemy_->GetWorldPosition();
		if (IsCollision(soul_->GetAABB(), baseenemy_->GetAABB()) && timeSinceLastRemove_ >= removeInterval_) {
			soul_->OnCollision();
			HPfige_ = userInterface_->IsButtonPressed();
		}
	}

	/// プレイヤー攻撃と敵

	A = soul_->GetAttack()->GetWorldPosition();
	B = enemy_->GetWorldPosition();

	if (IsCollision(soul_->GetAttack()->GetAABB(), enemy_->GetAABB())) {
		  enemy_->OnCollision();
	}
}


void GameScene::SetBaseEnemy() {
	int randam = rand() % 5 - 1;
	place += randam;
	if (place > 4) {
		 place = randam;
	}

	baseEnemy_ = new BaseEnemy();
	baseEnemy_->Initialize(EnemyModel_, textureHandleE1_, {-20.0f + float(place * 10), 18, 0}, &viewProjection_);
	enemies_.push_back(baseEnemy_);
}