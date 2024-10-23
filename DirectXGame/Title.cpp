#include "Title.h"
#include "TextureManager.h"
#include "DirectXCommon.h"

Title::~Title() { delete sprite_; }

void Title::Initialize() { 
	
	textureHandle_ = TextureManager::Load("title.png");
	//sprite_ = new Sprite();
	sprite_ = Sprite::Create(textureHandle_, {0, 0});	
	worldTransform_.Initialize();
}

void Title::Update() { 
	worldTransform_.UpdateMatrix();

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		finished_ = true;
	}
}

void Title::Draw() { 
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);
	sprite_->Draw();
	Sprite::PostDraw();

}