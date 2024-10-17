#include "Sprite.h"
//#include "Model.h"
#include "WorldTransform.h"

class ScreenBack{
public:
	~ScreenBack();
	void Initialisz();
	void Drwa();

private:
	uint32_t texture = 0u;
	Sprite* sprite_;


};