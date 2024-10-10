#include "Soul.h"
#include "Player.h"

void Soul::Initialize(Model* model, uint32_t texture, ViewProjection* viewProjection) {

	textureHandle_ = texture;
	model_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
}

void Soul::Start(bool right) { 
	if (right) {
		how = HowToMove::right;
	} else {
		how = HowToMove::left;
	}
	isMove = true;
}

Vector3 Soul::GetWorldPosition() {
	Vector3 worldPos{};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Soul::GetPosition(Vector3 posS, Vector3 posE) {
	worldTransform_.translation_ = posS;
	
	const float kBulletSpeed = 0.5f;

	segment.origin = posS;
	segment.diff = posE;

	Vector3 subtract = Subtract(segment.diff, segment.origin);

	Vector3 normalize = Normalize(subtract);

	normalize.x *= kBulletSpeed;
	normalize.y *= kBulletSpeed;
	normalize.z *= kBulletSpeed;

	velocity_ = normalize;

	velocity_ = TransformNormal(velocity_, worldTransform_.matWorld_);

}


void Soul::Update() {


	worldTransform_.UpdateMatrix();

	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	

	Vector3 move =  clamp(worldTransform_.translation_, segment.origin, segment.diff);

	switch (how) {
	case HowToMove::right:
		if (move.x >= segment.diff.x) {
			isMove = false;
		}
		break;
	case HowToMove::left:
		if (move.x < segment.diff.x) {
			isMove = false;
		}
		break;
	}

}


void Soul::Draw() {
	if (isMove) {
		model_->Draw(worldTransform_, *viewProjection_);
	}
}
