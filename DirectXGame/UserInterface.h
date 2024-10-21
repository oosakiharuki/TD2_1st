#pragma once
#include<assert.h>
#include<2d/Sprite.h>
#include <base\TextureManager.h>
#include<3d/Model.h>
#include<3d/WorldTransform.h>
#include<base/WinApp.h>
#include<input/Input.h>
#include<list>

class UserInterface
{
public:
	~UserInterface();
	/// 初期化
	void Initialize();

	/// 毎フレーム処理
	void Update();

	/// 描画
	void Draw2D();

	bool IsAttackActive() const {
		return attack_;
	}

	bool IsButtonPressed() {
		return true;
	}

	void RemoveHeart();

private:

	// 2Dスプライト
	Sprite* sprite2Dgauge  = nullptr;           // ゲージ
	Sprite* sprite2Dcharge = nullptr;           // チャージ
	std::list<Sprite*> sprite2DHP_;             // ハート
	// 座標
	Vector2 gaugepos_;
	Vector2 chargepos_;
	Vector2 HPpos_;
	// カラー
	Vector4 gaugecolor_;
	Vector4 chargecolor_;
	Vector4 HPcolor_;
	// サイズ
	Vector2 chargesize_;
	// フラグ
	bool Chargeswitch_ = false;
	bool attack_ = false;

	// キーボード入力
	Input* input_ = nullptr;
};

