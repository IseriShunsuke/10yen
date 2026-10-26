#pragma once
#include "KamataEngine.h"
#include "Coin.h"
#include"HitBox.h"
class GameScene
{
public:
	~GameScene();

	void Initialize();

	void Update();

	void Draw();

	void AllCollision();

	void MoveCoin();

	void Start();

	bool GetClear() { return isClear_; };
	bool GetOver() { return isOver_; };

	

private:
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
	//当たり判定
	bool isHit;
	bool isHit2;
	bool isHit3;
	bool isHit4;
	bool isHit5;
	HitBox hitBox_;

	float hitPower_;
	float shotPower_;
	float gravity_;

	bool shot_;
	bool hitWall_;

	bool hitGoal_;

	bool isClear_;
	bool isOver_;
	
	KamataEngine::Vector3 hitPosition_;
};

