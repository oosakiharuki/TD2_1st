#include "Sprite.h"
#include "Model.h"
#include "WorldTransform.h"

class Enemy{
public:
	~Enemy();
	void Initialize(Model* model, uint32_t texture, uint32_t texture2, ViewProjection* viewProjection);
	void Update();
	void Draw();
	void Draw2D();
	Vector3 GetWorldPosition();
	void OnCollision();

	bool IsHit() const { return isHit_; }
	bool IsDead() const { return isDead_; }
	bool IsFinish() const { return isFinish_; }

private:

	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	uint32_t textureHandleDamage_ = 0u;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_;

	Vector4 color_;
	ObjectColor objectColor_;
	static inline const float kDuration = 2.0f;
	float counter_ = 0.0f;

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
	bool isFinish_ = false;

	uint32_t textureHp_ = 0u;
	uint32_t textureBer_ = 0u;
	Sprite* spriteHp_ = nullptr;
	Sprite* spriteBar_ = nullptr;

	Vector2 hpBarPos;
};