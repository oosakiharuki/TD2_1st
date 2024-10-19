#include "Model.h"
#include "WorldTransform.h"
#include "MyMath.h"
#include "Attack.h"

class Input;

class Soul {
public:
	~Soul();
	void Initialize(Model* model, uint32_t texture, ViewProjection* viewProjection,Vector3 position);
	void Update();
	void Draw();

	Vector3 GetWorldPosition();
	void GetPosition(Vector3 posS, Vector3 posE);
	void Start(bool right);
	bool IsMove() const { return isMove; }
	void OnCollision();
	bool IsDead() { return isDead_; }
	Attack* GetAttack() { return attack_; }

private:
	enum class HowToMove {
		right,
		left
	};

	Vector3 clamp(Vector3 a, Vector3 b, Vector3 c) // t,0,1
	{

		Vector3 start = {0, 0, 0};
		Vector3 end = {1, 1, 1};

		if (a.x > b.x || a.x < c.x) {
			return a; // t
		} else if (a.x <= b.x) {
			return start; // 0
		} else if (a.x >= c.x) {
			return end; // 1
		}

		return a;
	}

	float Dot(const Vector3& v1, const Vector3& v2) {
		float result;
		result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
		return result;
	}

	float Length(const Vector3& v) {
		float result;
		result = (float)sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
		return result;
	}

	uint32_t textureHandle_ = 0u;
	Model* model_;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_;

	Segment segment;

	Vector3 velocity_;
	Vector3 nextPos;
	bool isMove = false;
	HowToMove how;

	float timer_ = 0.5f;
	const float kDeltaTimer_ = 1.0f / 60.0f;
	const float kJumpSpeed_ = 0.2f;

	uint32_t hp;
	bool isHit = false;
	float HitCount = 5.0f;
	const float deltaTimer = 1.0f / 60.0f;

	bool isDead_ = false;

	Input* input_ = nullptr;
	Attack* attack_ = nullptr;
	
	float AttackCount = 0.0f;
	Model* ModelAttack_ = nullptr;
	uint32_t textureHandle2_ = 0u;

	bool isAttack = false;
};