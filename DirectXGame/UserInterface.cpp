#include "UserInterface.h"


void UserInterface::Initialize() {

	gaugepos_ = { 1000.0f,30.0f };
	gaugecolor_ = { 1.0f,1.0f,1.0f,1.0f };
	chargepos_ = { 1000.0f,30.0f };
	chargecolor_ = { 1.0f,1.0f,1.0f,1.0f };


	chargesize_ = { 0.0f,60.0f };
	// レティクル用テクスチャ取得
	uint32_t GaugeReticle = TextureManager::Load("gauge.png");
	uint32_t ChargeReticle = TextureManager::Load("charge.png");
	// スプライト生成
	sprite2Dgauge = Sprite::Create(GaugeReticle, gaugepos_, gaugecolor_);
	sprite2Dcharge = Sprite::Create(ChargeReticle, chargepos_, chargecolor_);

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

}

void UserInterface::Update() {

	if (input_->PushKey(DIK_SPACE) && chargesize_.x == 200) {
		attack_ = true;
	}

	if (attack_) {
		attack_ = true;
		Chargeswitch_ = true;
	}

	if (!Chargeswitch_) {
		chargesize_.x += 2.0f;
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


	//ImGui::Begin("UI");
	////ImGui::Checkbox("Check", &fige_);
	//ImGui::DragFloat2("gauge", &gaugepos_.x);
	//ImGui::DragFloat2("charge", &chargepos_.x);
	//ImGui::DragFloat2("size", &chargesize_.x);
	//ImGui::End();
}

void UserInterface::Draw2D() {
	sprite2Dcharge->Draw();
	sprite2Dgauge->Draw();
}