#pragma once
#include <Model.h>
#include <WorldTransform.h>
#include <Input.h>
#include <ViewProjection.h>
#include "GameScene.h"

class BaseEnemy {

public:
	void Initialize(Model* model, uint32_t textureHandle, Vector3 position, ViewProjection* viewProjection);
	void Update();
	void Draw();
	// データ取得設定
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	Vector3 GetWorldPosition();
	bool IsDead() const { return isDead_; }
	AABB GetAABB();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// キー入力
	Input* input_ = nullptr;

	ViewProjection* camara_ = nullptr;

	//GameScene& gameScene_;

	bool isDead_ = false;
	float timer_ = 10.0f;
	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;
};