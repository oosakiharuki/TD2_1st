#include "BaseEnemy.h"
//#include "Affin.h"
//#include "MathUtility.h"
#include "imgui.h"
#include "math/Vector3.h"
#include <cassert>
#include "GameScene.h"

void BaseEnemy::Initialize(Model* model, uint32_t textureHandle, Vector3 position, 
	ViewProjection* camera) {
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	camara_ = camera;
	//gameScene_ = gameScene;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// シングルトンインスタンスを取得
	input_ = Input::GetInstance();
}

Vector3 BaseEnemy::GetWorldPosition() {
	Vector3 worldPos{};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

AABB BaseEnemy::GetAABB() {
	Vector3 worldPos_ = GetWorldPosition();

	AABB aabb;
	aabb.min = {worldPos_.x - kWidth / 2.0f, worldPos_.y - kHeight / 2.0f, worldPos_.z - kWidth / 2.0f};
	aabb.max = {worldPos_.x + kWidth / 2.0f, worldPos_.y + kHeight / 2.0f, worldPos_.z + kWidth / 2.0f};

	return aabb;
};


void BaseEnemy::Update() {

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0.4f, 0};

	// キャラクターの移動速度
	//const float kCharacterSpeed = 0.2f;
	//move.x -= kCharacterSpeed;


	//	move.x += kCharacterSpeed;

	//	move.y += kCharacterSpeed;
	

	// 移動
	//worldTransform_.translation_ += move;

	worldTransform_.translation_.y -= move.y;


	timer_ -= 1.0f / 60.0f;
	if (timer_ < 0) {
		isDead_ = true;
	}


	worldTransform_.UpdateMatrix();
}

void BaseEnemy::Draw() { model_->Draw(worldTransform_, *camara_, textureHandle_); }