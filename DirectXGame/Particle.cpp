#include "Particle.h"

Vector3 Particle::GetWorldPosition() {
	Vector3 worldPos{};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Particle::Initialize(Model* model, ViewProjection* viewprojection, Vector3 position) {
	model_ = model;
	viewprojection_ = viewprojection;
	for (auto& WorldTransform : WorldTransform_) {
		WorldTransform.Initialize();
		WorldTransform.translation_ = position;
	}
}

void Particle::Update(Vector3 position) {


	Vector3 soulPosition = position;

	// モデル間のオフセット距離を定義
	const float offsetDistanceX = 0.0f; // X軸方向のオフセット
	const float offsetDistanceY = 0.0f; // Y軸方向のオフセット
	const float offsetDistanceZ = 2.0f; // Z軸方向のオフセット

  for (int i = 0; i < WorldTransform_.size(); ++i) {
		auto& worldTransform = WorldTransform_[i];

		// 距離の計算
		float distance = static_cast<float>(sqrt(
			pow(soulPosition.x - worldTransform.translation_.x, 2) +
			pow(soulPosition.y - worldTransform.translation_.y, 2) +
			pow(soulPosition.z - worldTransform.translation_.z, 2)
		));

		// イージング係数の調整 (パーティクルごとに遅延を設定)
		float delayFactor = 13.0f * (i+1); // 各パーティクルに遅延を追加
		float easingFactor = 0.05f + 0.1f * (1.0f - exp(-distance / delayFactor + 0.5f));

		// イージング計算（遅延を考慮）
		worldTransform.translation_.x += (soulPosition.x - worldTransform.translation_.x + offsetDistanceX) * easingFactor;
		worldTransform.translation_.y += (soulPosition.y - worldTransform.translation_.y + offsetDistanceY) * easingFactor;
		worldTransform.translation_.z += (soulPosition.z - worldTransform.translation_.z + offsetDistanceZ) * easingFactor;
	}

	
    for (auto& worldTransform : WorldTransform_) {

		// スケーリング行列
		Matrix4x4 scale = MakeScaleMatrix(worldTransform.scale_);
		// X軸の回転行列
		Matrix4x4 rotateX = MakeRotateXMatrix(worldTransform.rotation_.x);
		// Y軸の回転行列
		Matrix4x4 rotateY = MakeRotateYMatrix(worldTransform.rotation_.y);
		// Z軸の回転行列
		Matrix4x4 rotateZ = MakeRotateZMatrix(worldTransform.rotation_.z);
		// 回転行列の合成
		Matrix4x4 rotationZXY = Multiply(rotateZ, Multiply(rotateX, rotateY));
		// 平行移動行列の作成
		Matrix4x4 translate = MakeTranslateMatrix(worldTransform.translation_);

		// ワールド行列の作成
		worldTransform.matWorld_ = Multiply(translate, rotationZXY); // 行列の合成

		// 行列を定数バッファに転送
		worldTransform.TransferMatrix();
	}
}

void Particle::Draw() {
	for (auto& worldTransform : WorldTransform_) {
		model_->Draw(worldTransform, *viewprojection_);
	}
}