#include "GameOver.h"
#include "TextureManager.h"
#include "DirectXCommon.h"

GameOver::~GameOver() { delete sprite_; }

void GameOver::Initialize() {

	textureHandle_ = TextureManager::Load("gameover.png");
	// sprite_ = new Sprite();
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
	worldTransform_.Initialize();
}

void GameOver::Update() {
	worldTransform_.UpdateMatrix();

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		finished_ = true;
	}
}

void GameOver::Draw() {
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);
	sprite_->Draw();
	Sprite::PostDraw();
}
