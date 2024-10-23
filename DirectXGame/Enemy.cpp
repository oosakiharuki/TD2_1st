#include "Enemy.h"
#include <numbers>
#define _USE_MATH_DEFINES
#include <math.h>
#include "TextureManager.h"
#include <algorithm>

Enemy::~Enemy() {
	delete spriteHp_;
	delete spriteBar_;
}

void Enemy::Initialize(Model* model, uint32_t texture, uint32_t texture2, ViewProjection* viewProjection) {

	model_ = model;
	textureHandle_ = texture;
	textureHandleDamage_ = texture2;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;

	worldTransform_.translation_ = {30,-10,0};
	worldTransform_.scale_ = {2,2,2};
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / -2.0f;

	move = {-kSpeed, 0, 0};
	hp = 10;

	a = 2 * float(M_PI);


	textureHp_ = TextureManager::Load("enemyHp.png");
	textureBer_ = TextureManager::Load("enemyGauge.png");

	spriteHp_ = Sprite::Create(textureHp_, hpBarPos);
	spriteBar_ = Sprite::Create(textureBer_, hpBarPos);
	
	hpBarPos = {1000,660};

	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};
}

void Enemy::Update() {

	worldTransform_.UpdateMatrix();

	worldTransform_.translation_.x += move.x;

	walkTimer_ += 1.0f / 30.0f;

	param = std::sin(a * walkTimer_ / kMaxTime);

	if (Muki) {
		radian = kAngleStart + kAngleEnd * (param + 1.0f) / 2.0f;
	} else {
		radian = -(kAngleStart + kAngleEnd * (param + 1.0f) / 2.0f);
	}

	if (worldTransform_.translation_.x < -50.0f) {
		worldTransform_.translation_.y = (float)PosY;
		move.x = kSpeed;
		PosY = rand() % kPosY;
		Muki = false;
	}

	if (worldTransform_.translation_.x > 50.0f) {
		worldTransform_.translation_.y = (float)PosY;
		move.x = -kSpeed;
		PosY = rand() % kPosY - 16;
		Muki = true;
	}

	if (isHit_) {
		worldTransform_.translation_.x += move.x * 2;
		worldTransform_.rotation_.x += std::sin(radian / 2.0f);
		timer -= 1.0f / 60.0f;
		if (timer < 0) {		
			isHit_ = false;
			timer = 2.0f;
			worldTransform_.rotation_.x = 0.0f;
		}
	} else {
		worldTransform_.rotation_.x = std::sin(radian);
	}
	
	if (hp <= 0) {
		isDead_ = true;
	}

	spriteHp_->SetPosition(hpBarPos);
	spriteBar_->SetPosition(hpBarPos);
	spriteHp_->SetSize({200.0f - (20 *(10 - hp)), 60.0f});
}

void Enemy::Draw() { 
	if (!isHit_) {
		model_->Draw(worldTransform_, *viewProjection_, textureHandle_,&objectColor_);
	} 
	else {
		model_->Draw(worldTransform_, *viewProjection_, textureHandleDamage_, &objectColor_);
	}

	if (isDead_) {
		worldTransform_.rotation_.x += std::sin(radian / 2.0f);

		counter_ += 1.0f / 60.0f;
		if (counter_ >= kDuration) {
			counter_ = kDuration;
			isFinish_ = true;
		}

		color_.w = std::clamp(kDuration - counter_, 0.0f, 1.0f);
		objectColor_.SetColor(color_);
		objectColor_.TransferMatrix();
	}
}

void Enemy::Draw2D() { 
	spriteHp_->Draw();
	spriteBar_->Draw();
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos{};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}


AABB Enemy::GetAABB() {
	Vector3 worldPos_ = GetWorldPosition();

	AABB aabb;
	aabb.min = {worldPos_.x - kWidth / 2.0f, worldPos_.y - kHeight / 2.0f, worldPos_.z - kWidth / 2.0f};
	aabb.max = {worldPos_.x + kWidth / 2.0f, worldPos_.y + kHeight / 2.0f, worldPos_.z + kWidth / 2.0f};

	return aabb;
};

void Enemy::OnCollision() { 
	if (!isHit_) {
		hp -= 1;
	}
	isHit_ = true; 
}