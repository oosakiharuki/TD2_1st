#include "Model.h"
#include "WorldTransform.h"
#include "MyMath.h"

class Player;

class Soul {
public:

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


	void Initialize(Model* model, uint32_t texture, ViewProjection* viewProjection);
	void Update();
	void Draw();

	Vector3 GetWorldPosition();
	void GetPosition(Vector3 posS, Vector3 posE);
	void Start(bool right);
	bool IsMove() const { return isMove; }

private:
	uint32_t textureHandle_ = 0u;
	Model* model_;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_;

	Segment segment;
	Player* player_;

	Vector3 velocity_;
	bool isMove = false;
	HowToMove how;
};