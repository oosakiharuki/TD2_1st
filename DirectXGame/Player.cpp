#include "Player.h"

void Player::Initialize(Vector3 position,Model* model, uint32_t texture, ViewProjection* viewProjection) {

	model_ = model;
	textureHandle_ = texture;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	viewProjection_ = viewProjection;

}

void Player::Update() {
	move = {0, 0.06f, 0};

	if (isPlayer) {
		worldTransform_.translation_.y -= move.y;
	}

	const float kMoveLimitY = 10.0f;

	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, kMoveLimitY);


	worldTransform_.UpdateMatrix();
}

void Player::Draw() {

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);

}

void Player::IsPlayer(bool isMove) { 
	if (isMove) {
		isPlayer = true;
		timer_ -= kDeltaTimer_;
		if (timer_ > 0) {
			worldTransform_.translation_.y += kJumpSpeed_;
		}

	} else {
		isPlayer = false;
		timer_ = 0.5f;
	}

}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos{};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}