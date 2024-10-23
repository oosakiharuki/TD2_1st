#include "Attack.h"

void Attack::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	worldTransform_.translation_.x = 1000;

	viewProjeciton_ = viewProjection;
}

void Attack::Update() {
	if (isAttackStart) {

		AttackTimer -= deltaTimer;

		if (AttackTimer < 0) {
			worldTransform_.translation_.x = 1000;
			AttackTimer = 1.0f;
			isAttackStart = false;
		}
	}
	worldTransform_.UpdateMatrix();
}

void Attack::Draw() {

	model_->Draw(worldTransform_,*viewProjeciton_,textureHandle_);

}

void Attack::SetPosition(Vector3 pos) {

	worldTransform_.translation_.x = pos.x;
	isAttackStart = true;
}

Vector3 Attack::GetWorldPosition() {
	Vector3 worldPos{};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

AABB Attack::GetAABB() {
	Vector3 worldPos_ = GetWorldPosition();

	AABB aabb;
	aabb.min = {worldPos_.x - kWidth / 2.0f, worldPos_.y - kHeight / 2.0f, worldPos_.z - kWidth / 2.0f};
	aabb.max = {worldPos_.x + kWidth / 2.0f, worldPos_.y + kHeight / 2.0f, worldPos_.z + kWidth / 2.0f};

	return aabb;
};
