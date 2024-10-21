#include "Model.h"
#include "WorldTransform.h"

class Enemy{
public:
	void Initialize(Model* model, uint32_t texture, uint32_t texture2, ViewProjection* viewProjection);
	void Update();
	void Draw();
	Vector3 GetWorldPosition();
	void OnCollision();

	bool IsHit() const { return isHit_; }
	bool IsDead() const { return isDead_; }

private:

	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	uint32_t textureHandleDamage_ = 0u;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_;
	
	Vector3 move;
	static inline float kSpeed = 0.25f;//動く速さ
	static inline int kPosY = 16;
	int PosY = 0;

	static inline float kAngleStart = 4.0f;
	static inline float kAngleEnd = -2.0f;
	static inline float kMaxTime = 4.0f;

	float walkTimer_ = 0.0f;

	float a;
	float param = std::sin(a * walkTimer_ / kMaxTime);
	float radian;
	bool Muki = true; //right true /left false

	bool isHit_ = false;
	float timer = 2.0f;
	uint32_t hp;
	bool isDead_ = false;
};