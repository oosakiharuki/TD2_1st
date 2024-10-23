#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "MyMath.h"
#define _USE_MATH_DEFINES
#include <math.h>

class DeathParticle {
public:
	
	void Initialize(Model* model, ViewProjection* viewProjection);
	void Update();
	void Draw();
	void SetPosition(const Vector3& position);
	bool isFinish() { return isFinished_; }

private:

	static inline const uint32_t kNumParticles = 8;

	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	std::array<WorldTransform, kNumParticles> worldTransforms_;

	static inline const float pi = 2 * float(M_PI); // 2 pai

	static inline const float kDuration = 2.0f;
	static inline const float kSpeed = 0.05f;
	static inline const float kAngleUnit = pi / kNumParticles;

	bool isFinished_ = false;
	float counter_ = 0.0f;

	ObjectColor objectColor_;
	Vector4 color_;

};