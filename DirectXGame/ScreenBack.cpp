#include "ScreenBack.h"
#include "TextureManager.h"

ScreenBack::~ScreenBack() { delete sprite_; }

void ScreenBack::Initialisz() {

	texture = TextureManager::Load("screenBack.png");
	sprite_ = Sprite::Create(texture, {0, 0});

}


void ScreenBack::Drwa() {

	sprite_->Draw();

}

