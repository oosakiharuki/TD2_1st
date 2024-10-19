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
		timer_ -= kDeltaTimer_;
		if (timer_ > 0) {
			worldTransform_.translation_.y += kJumpSpeed_;
		}
		worldTransform_.translation_.y -= move.y;

	}

	const float kMoveLimitY = 16.0f;

	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, kMoveLimitY);

	////ダメージを受けた後の無敵時間
	//if (isHit) {
	//	HitCount -= deltaTimer;
	//	if (HitCount < 0.0f) {
	//		isHit = false;
	//		HitCount = 5.0f;
	//	}
	//}
			
	worldTransform_.UpdateMatrix();
}

void Player::Draw() {

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);

}

void Player::IsPlayer(bool isMove) { 
	if (isMove) {
		isPlayer = true;
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

//void Player::OnCollision() { 
//	//プレイヤーのやつだけダメージ
//	if (isPlayer && !isHit) {
//		hp -= 1;
//		isHit = true;
//	}
//}