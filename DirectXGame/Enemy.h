#include "Model.h"
#include "WorldTransform.h"

class Enemy{
public:
	void Initialize(Model* model, uint32_t texture, ViewProjection* viewProjection);
	void Update();
	void Draw();
	Vector3 GetWorldPosition();

private:

	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_;
	
	Vector3 move;
	static inline float kSpeed = 0.25f;//動く速さ
	static inline int kPosY = 16;

};