#include "Soul.h"

void Soul::Initialize(Model* model, uint32_t texture, ViewProjection* viewProjection, Vector3 position) {

	textureHandle_ = texture;
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	viewProjection_ = viewProjection;

	hp = 3;
	isDead_ = false;
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

	nextPos = posE;
}

void Soul::OnCollision() {
	if (!isHit) {
		hp -= 1;
		isHit = true;
	}
}

void Soul::Update() {
		
	worldTransform_.UpdateMatrix();

	if (!isMove) {

		timer_ -= kDeltaTimer_;
		if (timer_ > 0) {
		    worldTransform_.translation_.y += kJumpSpeed_;
		}
		
		Vector3 pos = {0, 0.06f, 0};

		worldTransform_.translation_.y -= pos.y;

		const float kMoveLimitY = 16.0f;

		worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
		worldTransform_.translation_.y = min(worldTransform_.translation_.y, kMoveLimitY);
	} else {

		worldTransform_.translation_.x += velocity_.x;
		worldTransform_.translation_.y += velocity_.y;

		Vector3 move = clamp(worldTransform_.translation_, segment.origin, segment.diff);

		switch (how) {
		case HowToMove::right:
			if (move.x >= segment.diff.x) {
				isMove = false;
				worldTransform_.translation_ = nextPos; 
			}
			break;
		case HowToMove::left:
			if (move.x < segment.diff.x) {
				isMove = false;
				worldTransform_.translation_ = nextPos; 
			}
			break;
		}
		timer_ = 0.5f;
	}

	// ダメージを受けた後の無敵時間
	if (isHit) {
		HitCount -= deltaTimer;
		if (HitCount < 0.0f) {
			isHit = false;
			HitCount = 5.0f;
		}
	}

	//㏋が0の時
	if (!hp) {
		isDead_ = true;
	}
}


void Soul::Draw() {
	//if (isMove) {
		model_->Draw(worldTransform_, *viewProjection_);
	//}
}
