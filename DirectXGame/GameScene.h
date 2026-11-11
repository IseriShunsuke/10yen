#pragma once
#include "KamataEngine.h"
#include "Coin.h"
#include"HitBox.h"
#include "Stage.h"
class GameScene
{
public:
	~GameScene();

	void Initialize();

	void Update();

	void Draw();

	void AllCollision();

	

	void Start();

	bool GetClear() { return isClear_; };
	bool GetOver() { return isOver_; };

	

private:
	//ステージ
	Stage stage_;
	KamataEngine::Model* stageModel_;
	//10円
	Coin coin_;
	KamataEngine::Model* yenModel_;
	KamataEngine::Vector3 yenRotation_;
	KamataEngine::Vector3 yenPosition_;
	//ゴール
	KamataEngine::WorldTransform goalTransform;
	KamataEngine::Model* goalModel_ = nullptr;

	//背景
	KamataEngine::WorldTransform haikeiTransform;
	KamataEngine::Model* haikeiModel_;

	//スタート演出
	uint32_t startBlackTexture;
	KamataEngine::Sprite* spriteStart3_;
	KamataEngine::Sprite* spriteStart2_;
	KamataEngine::Sprite* spriteStart1_;
	KamataEngine::Sprite* spriteStartGO_;
	float startTimer;

	KamataEngine::Camera camera_;
	
	HitBox hitBox_;
	
	//ゲームオーバー演出用	
	uint32_t directiontexture;
	KamataEngine::Sprite* spriteDirection_;
	float directionTimer;

	bool hitGoal_;

	bool isClear_;
	bool isOver_;
	
	
};

