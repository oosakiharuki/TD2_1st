#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"

#include "Title.h"
#include "Clear.h"
#include "GameOver.h"

enum class Scene {
	Title,
	Game,
	Clear,
	GameOver
};

Scene scene_ = Scene::Title;

GameScene* gameScene = nullptr;
Title* title = nullptr;
Clear* clear = nullptr;
GameOver* gameOver = nullptr;

void ChangeScene() {
	switch (scene_) {
	case Scene::Title:
		if (title->IsFinished()) {
			scene_ = Scene::Game;
			delete title;
			title = nullptr;

			gameScene = new GameScene();
			gameScene->Initialize();
		}
		break;
	case Scene::Game:

		// クリアとゲームオーオーバー
		if (gameScene->IsGameClear()) {
			scene_ = Scene::Clear;
			delete gameScene;
			gameScene = nullptr;

			clear = new Clear();
			clear->Initialize();
		}
		else if (gameScene->IsGameOver()) {

			scene_ = Scene::GameOver;
			delete gameScene;
			gameScene = nullptr;

			gameOver = new GameOver();
			gameOver->Initialize();
		}
		
		//ポース入れるとき用
		// if (gameScene->IsFinished()) {
		//	scene_ = Scene::Title;
		//	delete gameScene;
		//	gameScene = nullptr;

		//	title = new Title();
		//	title->Initialize();
		//}

		break;
	case Scene::Clear:
		if (clear->IsFinished()) {
			scene_ = Scene::Title;
			delete clear;
			clear = nullptr;

			title = new Title();
			title->Initialize();
		}

		break;
	case Scene::GameOver:
		if (gameOver->IsFinished()) {
			scene_ = Scene::Title;
			delete gameOver;
			gameOver = nullptr;

			title = new Title();
			title->Initialize();
		}

		break;
	}
}

void ChangeUpdate() {
	switch (scene_) {
	case Scene::Title:
		title->Update();
		break;
	case Scene::Game:
		gameScene->Update();
		break;
	case Scene::Clear:
		clear->Update();
		break;
	case Scene::GameOver:
		gameOver->Update();
		break;
	}
}

void ChangeDraw() {
	switch (scene_) {
	case Scene::Title:
		title->Draw();
		break;
	case Scene::Game:
		gameScene->Draw();
		break;
	case Scene::Clear:
		clear->Draw();
		break;
	case Scene::GameOver:
		gameOver->Draw();
		break;
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;
	//GameScene* gameScene = nullptr;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow(L"TD2_1st");

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	// ゲームシーンの初期化
	//gameScene = new GameScene();
	//gameScene->Initialize();
	title = new Title();
	title->Initialize();

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();
		// ゲームシーンの毎フレーム処理
		
		ChangeScene();

		ChangeUpdate();

		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		// ゲームシーンの描画
		ChangeDraw();
		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	delete gameScene;
	delete title;
	delete clear;
	delete gameOver;
	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}