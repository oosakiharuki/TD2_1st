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
	MyMath* myMath_ = nullptr;

};