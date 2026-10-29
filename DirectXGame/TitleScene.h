#pragma once
#include "KamataEngine.h"
#include "Coin.h"
#include "Fade.h"

class TitleScene
{
public:
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
	};

	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	bool GetFinish() { return isFinish; }
private:

	Fade* fade_ = nullptr;

	Phase phase_ = Phase::kFadeIn;

	//ステージ
	KamataEngine::WorldTransform stageTransform;
	KamataEngine::WorldTransform stageTransform2;
	KamataEngine::WorldTransform stageTransform3;
	KamataEngine::WorldTransform stageTransform4;
	KamataEngine::WorldTransform stageTransform5;
	KamataEngine::Model* stageModel_;

	//10円
	Coin coin_;
	KamataEngine::Model* yenModel_;
	KamataEngine::Vector3 yenRotation_;
	KamataEngine::Vector3 yenPosition_;

	//背景
	KamataEngine::WorldTransform haikeiTransform;
	KamataEngine::Model* haikeiModel_;

	KamataEngine::Camera camera_;
	
	KamataEngine::Vector3 cameraPosition;
	float cameraSpeed;

	KamataEngine::Sprite* spriteUI_ = nullptr;

	uint32_t UItexture_;
	 
	KamataEngine::Sprite* spriteTitleNameUI_ = nullptr;

	uint32_t nameUItexture_;

	

	bool isFinish;

	float viewTimer;
	bool isView;

	bool isRolling;
	float waitTimer;
	int roop;

	uint32_t soundDataHandle;
	uint32_t voiceHandle;

	
};

