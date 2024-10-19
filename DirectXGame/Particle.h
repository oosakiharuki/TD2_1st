#pragma once
#include<Model.h>
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"MyMath.h"

class Particle {
public:
	void Initialize(Model* model, ViewProjection* viewprojection, Vector3 position);
	void Update(Vector3 position);
	void Draw();

	Vector3 GetWorldPosition();

private:
	Model* model_;
	ViewProjection* viewprojection_;
	WorldTransform worldTransform_;
	// パーティクルの個数
	static inline const uint32_t KNumParticles = 6;
	std::array<WorldTransform, KNumParticles> WorldTransform_;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
};
