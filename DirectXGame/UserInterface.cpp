#include "UserInterface.h"

UserInterface::~UserInterface() {
	delete sprite2Dgauge ;
	delete sprite2Dcharge;
	for (Sprite* heart : sprite2DHP_) {
		if (heart) {
			delete heart;
			heart = nullptr;
		}
	}
	sprite2DHP_.clear();
}

void UserInterface::Initialize() {

	// レティクル用テクスチャ取得
	uint32_t GaugeReticle = TextureManager::Load("gauge.png");
	uint32_t ChargeReticle = TextureManager::Load("charge.png");
	uint32_t HPReticle = TextureManager::Load("HP.png");

	gaugepos_ = { 1000.0f,30.0f };
	gaugecolor_ = { 1.0f,1.0f,1.0f,1.0f };
	chargepos_ = { 1000.0f,30.0f };
	chargecolor_ = { 1.0f,1.0f,1.0f,1.0f };
	chargesize_ = { 0.0f,60.0f };
	HPpos_ = {40.0f, 17.0f};
	HPcolor_ = {1.0f, 1.0f, 1.0f, 1.0f};

	// 3つのハートを初期化
	for (int i = 0; i < 3; ++i) {
		Sprite* newsprite2DHP = Sprite::Create(HPReticle, HPpos_, HPcolor_);
		newsprite2DHP->Initialize();
		Vector2 position = {40.0f + i * 47.0f, 17.0f};
		newsprite2DHP->SetPosition(position);
		sprite2DHP_.push_back(newsprite2DHP);
	}

	// スプライト生成
	sprite2Dgauge = Sprite::Create(GaugeReticle, gaugepos_, gaugecolor_);
	sprite2Dcharge = Sprite::Create(ChargeReticle, chargepos_, chargecolor_);

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

}

void UserInterface::Update() {
	if (!isMove_) {
		if (input_->PushKey(DIK_SPACE) && chargesize_.x == 200) {
			attack_ = true;
		}
	}

	if (attack_) {
		attack_ = true;
		Chargeswitch_ = true;
	}

	// 攻撃後のクールタイム
	if (!Chargeswitch_) {
		chargesize_.x += 0.2f;
		if (chargesize_.x >= 200) {
			chargesize_.x = 200.0f;
		}
	} else if (Chargeswitch_) {
		chargesize_.x -= 5.0f;
		if (chargesize_.x < 0) {
			chargesize_.x = 0.0f;
			attack_ = false;
			Chargeswitch_ = false;
		}
	}


	sprite2Dgauge->SetPosition(gaugepos_);
	sprite2Dcharge->SetPosition(chargepos_);
	sprite2Dcharge->SetSize(chargesize_);
}

void UserInterface::Draw2D() {
	sprite2Dcharge->Draw();
	sprite2Dgauge->Draw();
	for (Sprite* HP : sprite2DHP_){
		HP->Draw();
	}
}

void UserInterface::RemoveHeart() {
	if (!sprite2DHP_.empty()) {
		Sprite* lastHeart = sprite2DHP_.back();

		delete lastHeart;
		sprite2DHP_.pop_back();
	}
}