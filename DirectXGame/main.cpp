#include "GameScene.h"
#include "KamataEngine.h"
#include <Windows.h>
using namespace KamataEngine;
#include "TitleScene.h"
#include "GameOver.h"
#include "GameClear.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	KamataEngine::Initialize(L"LE3C_05_イセリ_シュンスケ_10円ゲーム");
	// sorry
	DirectXCommon* dxcommon = DirectXCommon::GetInstance();
	
	GameScene* gameScene = nullptr;
	TitleScene* titleScene = nullptr;
	GameOver* gameOver = nullptr;
	GameClear* gameClear = nullptr;

	enum class Scene
	{
		kUnkown = 0,
		KTITLE,
		KWAITING,
		KGAME,
		KGAMEOVER,
		KGAMECLEAR,
	};

	Scene scene = Scene::kUnkown;

	scene = Scene::KTITLE;

	titleScene = new TitleScene;
	titleScene->Initialize();
	/*gameScene = new GameScene;
	gameScene->Initialize();*/


	void ChangeScene();
	
	void UpdateScene();

	void DrawScene();


	// メインループ
	while (true) {
		if (KamataEngine::Update()) {
			break;
		}
		
		//シーン切り替え
		switch (scene) {
		case Scene::KTITLE:

			if (titleScene->GetFinish())
			{
				scene = Scene::KGAME;

				delete titleScene;
				titleScene = nullptr;

				gameScene = new GameScene();
				gameScene->Initialize();
			}

			break;
		case Scene::KGAME:
			if (gameScene->GetClear())
			{
				scene = Scene::KGAMECLEAR;

				delete gameScene;
				gameScene = nullptr;

				gameClear = new GameClear();
				gameClear->Initialize();
			}
			else if (gameScene->GetOver())
			{
				scene = Scene::KGAMEOVER;

				delete gameScene;
				gameScene = nullptr;

				gameOver = new GameOver();
				gameOver->Initialize();
			}
			break;
		case Scene::KGAMECLEAR:
			if (gameClear->GetFinish())
			{
				scene = Scene::KTITLE;

				delete gameClear;
				gameClear = nullptr;

				titleScene = new TitleScene();
				titleScene->Initialize();
			}
			break;
		case Scene::KGAMEOVER:
			if (gameOver->GetFinish())
			{
				scene = Scene::KTITLE;

				delete gameOver;
				gameOver = nullptr;

				titleScene = new TitleScene();
				titleScene->Initialize();
			}
			break;
		}

		// ゲームシーンの更新
		switch (scene) {
		case Scene::KTITLE:
			titleScene->Update();
			break;
		case Scene::KGAME:
			gameScene->Update();
			break;
		case Scene::KGAMEOVER:
			gameOver->Update();
			break;
		case Scene::KGAMECLEAR:
			gameClear->Update();
			break;

		}

		

		// 描画開始
		dxcommon->PreDraw();
		Model::PreDraw();

		// ゲームシーンの描画
		switch (scene) {
		case Scene::KTITLE:
			titleScene->Draw();
			break;
		case Scene::KGAME:
			gameScene->Draw();
			break;
		case Scene::KGAMEOVER:
			gameOver->Draw();
			break;
		case Scene::KGAMECLEAR:
			gameClear->Draw();
			break;
		}


		Model::PostDraw();
		// 描画終了
		dxcommon->PostDraw();
	}

	// nullptrの代入
	delete titleScene;
	delete gameScene;
	delete gameClear;
	delete gameOver;
	// エンジン終了
	KamataEngine::Finalize();
	return 0;
}
