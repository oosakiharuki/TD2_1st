#include "Clear.h"
#include "TextureManager.h"
#include "DirectXCommon.h"

Clear::~Clear() { delete sprite_; }

void Clear::Initialize() {

	textureHandle_ = TextureManager::Load("sample.png");
	// sprite_ = new Sprite();
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
	worldTransform_.Initialize();
}

void Clear::Update() {
	worldTransform_.UpdateMatrix();

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		finished_ = true;
	}
}

void Clear::Draw() {
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);
	sprite_->Draw();
	Sprite::PostDraw();
}
