#include "Sprite.h"
#include "WorldTransform.h"
#include "Input.h"

class GameOver {
public:
	~GameOver();
	void Initialize();
	void Update();
	void Draw();

	bool IsFinished() const { return finished_; }

private:
	Sprite* sprite_ = nullptr;
	WorldTransform worldTransform_;
	uint32_t textureHandle_ = 0u;

	bool finished_ = false;
};