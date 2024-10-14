#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t texture, ViewProjection* viewProjection) {

	model_ = model;
	textureHandle_ = texture;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;

	worldTransform_.translation_ = {30,-10,0};
	worldTransform_.scale_.x = 1.0f;

	move = {-kSpeed, 0, 0};
}

void Enemy::Update() {
	
	worldTransform_.UpdateMatrix();

	worldTransform_.translation_.x += move.x;

	int PosY = rand() % kPosY;

	if (worldTransform_.translation_.x < -50.0f) {
		worldTransform_.translation_.y = (float)PosY;
		move.x = kSpeed;
		PosY = rand() % kPosY;
	}

	if (worldTransform_.translation_.x > 50.0f) {
		worldTransform_.translation_.y = (float)PosY;
		move.x = -kSpeed;
		PosY = rand() % 16;
	}

}

void Enemy::Draw() {

	model_->Draw(worldTransform_,*viewProjection_,textureHandle_);

}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos{};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}