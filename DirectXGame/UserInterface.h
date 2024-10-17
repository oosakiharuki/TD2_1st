#pragma once
#include<assert.h>
#include<2d/Sprite.h>
#include <base\TextureManager.h>
#include<3d/Model.h>
#include<3d/WorldTransform.h>
#include<imgui.h>
#include<base/WinApp.h>
#include<input/Input.h>

class UserInterface
{
public:

	/// 初期化
	void Initialize();

	/// 毎フレーム処理
	void Update();

	/// 描画
	void Draw2D();

	bool IsAttackActive() const {
		return attack_;
	}

private:

	// 2Dスプライト
	Sprite* sprite2Dgauge = nullptr;          // ゲージ
	Sprite* sprite2Dcharge = nullptr;          // チャージ
	// 座標
	Vector2 gaugepos_;
	Vector2 chargepos_;
	// カラー
	Vector4 gaugecolor_;
	Vector4 chargecolor_;
	// サイズ
	Vector2 chargesize_;
	// フラグ
	bool Chargeswitch_ = false;
	bool attack_ = false;

	// キーボード入力
	Input* input_ = nullptr;

};

