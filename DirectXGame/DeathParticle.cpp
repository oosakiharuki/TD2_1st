#include "DeathParticle.h"
#include <algorithm>

void DeathParticle::Initialize(Model* model, ViewProjection* viewProjection) {
	model_ = model;
	viewProjection_ = viewProjection;
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
	}
	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};
}

void DeathParticle::SetPosition(const Vector3& position) {
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.translation_ = position;
	}
}


void DeathParticle::Update() {
	if (isFinished_) {
		return;
	}

	for (auto& worldTransform : worldTransforms_) {
		worldTransform.UpdateMatrix();
	}
	for (uint32_t i = 0; i < kNumParticles; i++) {
		Vector3 velocity_ = {kSpeed, 0, 0};

		float angle = kAngleUnit * i;

		Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);

		velocity_ = Transform(velocity_, matrixRotation);

		worldTransforms_[i].translation_.x += velocity_.x;
		worldTransforms_[i].translation_.y += velocity_.y;
		worldTransforms_[i].translation_.z += velocity_.z;
	}

	counter_ += 1.0f / 60.0f;
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		isFinished_ = true;
	}

	color_.w = std::clamp(kDuration - counter_, 0.0f, 1.0f);
	objectColor_.SetColor(color_);
	objectColor_.TransferMatrix();
}

void DeathParticle::Draw() {
	if (isFinished_) {
		return;
	}
	for (auto& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *viewProjection_, &objectColor_);
	}
}