#include "Model.h"
#include "WorldTransform.h"

#include "Input.h"
#include "MyMath.h"

class Player{
public:
	void Initialize(Vector3 position, Model* model, uint32_t texture, ViewProjection* viewProjection);
	void Update();
	void Draw();

	void IsPlayer(bool isMove);
	Vector3 GetWorldPosition();
	//void OnCollision();

private:

	Vector3 move;
	uint32_t textureHandle_ = 0u;
	Model* model_;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_;

	bool isPlayer = false;
	float timer_ = 0.5f;
	const float kDeltaTimer_ = 1.0f / 60.0f; 
	const float kJumpSpeed_ = 0.2f;

	Input* input_ = nullptr;
	//uint32_t hp;
	//bool isHit = false;
	//float HitCount = 5.0f;
	//const float deltaTimer = 1.0f / 60.0f;
};