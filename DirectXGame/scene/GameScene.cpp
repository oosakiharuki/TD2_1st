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


	EnemyModel_ = Model::CreateFromOBJ("cube", true);
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
}

void GameScene::ChangePlayer() {

	if (playerDeath_ || soul_->IsMove()) {
		player[0]->IsPlayer(false);
		player[1]->IsPlayer(false);
		player[2]->IsPlayer(false);
	}
	else  {
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

void GameScene::Update() {

	switch (scene_) {
	case GameSystem::setumei:
		break;
	//case GameSystem::countdown:
	//	countDownTimer_ -= deltaTImer;
	//	if (countDownTimer_ < 0) {
	//		scene_ = GameSystem::game;
	//	}
	//	if (!soul_->IsMove()) {
	//		for (int i = 0; i < 3; i++) {
	//			player[i]->Update();
	//		}
	//	}

	//	//soul_->Update();
	//	//particle_->Update(soul_->GetWorldPosition());
	//	//ChangePlayer();

	//	break;
	case GameSystem::game:

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
			playerDeath_ = true;
			scene_ = GameSystem::death;	
		}

		userInterface_->Update();
		userInterface_->SetIsMove(soul_->IsMove());

		// 無敵タイマー
		if (!HPfige_) {
			timeSinceLastRemove_ += deltaTImer;
		}
		if (timeSinceLastRemove_ >= 3) {
			timeSinceLastRemove_ = 3;
		}
		// 当たったらHPを減らしフラグリセット
		if (HPfige_) {
			userInterface_->RemoveHeart();
			timeSinceLastRemove_ = 0;
			HPfige_ = false;
		}

		particle_->Update(soul_->GetWorldPosition());

		if (enemy_->IsDead()) {
			scene_ = GameSystem::clear;
		}

		break;
	case GameSystem::death:
		//死んだパーティクルを入れたい
		deathTimer_ -= deltaTImer;
		if (deathTimer_ < 0) {
			isEnd_ = true;
		}
		enemy_->Update();
		break;
	case GameSystem::clear:
		// 倒したパーティクルを入れたい
		deathTimer_ -= deltaTImer;
		if (deathTimer_ < 0) {
			isClear_ = true;
		}

		if (!soul_->IsMove()) {
			for (int i = 0; i < 3; i++) {
				player[i]->Update();
			}
		}

		soul_->Update();
		break;
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
	//case GameSystem::countdown:
	//	//soul_->Draw();

	//	for (int i = 0; i < 3; i++) {
	//		player[i]->Draw();
	//	}
	//	//particle_->Draw();
	//	
	//	break;
	case GameSystem::game:
		soul_->Draw();
		enemy_->Draw();
		particle_->Draw();
		break;
	case GameSystem::death:
		enemy_->Draw();

		break;
	case GameSystem::clear:
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
	userInterface_->Draw2D();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() { 
	Vector3 A, B;

	const float playerRadius = 1.0f;
	
	const float enemyRadius = 2.0f; 

	Vector3 distance{};

	//float L;


	///プレイヤーと敵の当たり判定(一マスのみ)

	A = soul_->GetWorldPosition();
	B = enemy_->GetWorldPosition();

	distance.x = (B.x - A.x) * (B.x - A.x);
	distance.y = (B.y - A.y) * (B.y - A.y);
	distance.z = (B.z - A.z) * (B.z - A.z);
	
	if (A.x <= B.x + enemyRadius && A.x + playerRadius >= B.x && //30秒ごとに判定がでる
		A.y <= B.y + enemyRadius && A.y + playerRadius >= B.y && timeSinceLastRemove_ >= removeInterval_) {
		soul_->OnCollision();
		HPfige_ = userInterface_->IsButtonPressed();
	}

	//L = (playerRadius + enemyRadiusX) * (playerRadius + enemyRadiusX);

	//if (distance.x + distance.y + distance.z <= L) {
	//	for (uint32_t i = 0; i < 3; i++) {
	//		soul_->OnCollision();
	//	}
	//}

	///プレイヤーと敵の当たり判定
	/// 
	///プレイヤーとアイテム
	/// 
	/// プレイヤー攻撃と敵

	A = soul_->GetAttack()->GetWorldPosition();
	B = enemy_->GetWorldPosition();

	distance.x = (B.x - A.x) * (B.x - A.x);
	distance.y = (B.y - A.y) * (B.y - A.y);
	distance.z = (B.z - A.z) * (B.z - A.z);

	const float attackRadiusX = 3.0f; 
	const float attackRadiusY = 16.0f; 

	if (A.x + -attackRadiusX <= B.x + enemyRadius && A.x + attackRadiusX >= B.x && 
		A.y <= B.y + enemyRadius && A.y + attackRadiusY >= B.y) {
		  enemy_->OnCollision();
	}
	
	if (A.x + -attackRadiusX <= B.x + enemyRadius && A.x + attackRadiusX >= B.x && 
		A.y >= B.y + -enemyRadius && A.y + -attackRadiusY <= B.y)
	{
		  enemy_->OnCollision();
	}
	///攻撃をくらわしてもプレイヤーと敵の当たり判定は残るよ
	///UserInterfaceとAttackのクールタイムがちがうので合わせる

}