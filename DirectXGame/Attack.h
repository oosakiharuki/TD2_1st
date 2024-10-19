#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Attack {
public:
	void Initialize(Model* model,uint32_t textureHandle ,ViewProjection* viewProjection);
	void Update();
	void Draw();
	void SetPosition(Vector3 pos);
	Vector3 GetWorldPosition();

private:
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection* viewProjeciton_;
	uint32_t textureHandle_ = 0u;
	bool isAttackStart = false;
	float AttackTimer = 1.0f;
	const float deltaTimer = 1.0f / 60.0f;
};