#pragma once
#include "KamataEngine.h"
#include "Stage.h"
#include "HitBox.h"

class Coin
{
public:

	~Coin();

	void Initialize(KamataEngine::Model* model,KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	void Update();

	// 描画
	void Draw();

	void GravityFall();

	void MoveCoin();

	void HitStage(float angle);

	void PowerAndGravity();

	void Collision(KamataEngine::WorldTransform* stage1, KamataEngine::WorldTransform* stage2, KamataEngine::WorldTransform* stage3, KamataEngine::WorldTransform* stage4, KamataEngine::WorldTransform* stage5);


	KamataEngine::Vector3 GetPosition() { return worldTransform_.translation_; }
	KamataEngine::Vector3 GetRotation() { return worldTransform_.rotation_; }

	float  SetGravity(float gravity) { return gravity_ = gravity; }
	float  SetPower(float power) { return shotPower_ = power; }

	
	
private:
	KamataEngine::WorldTransform worldTransform_;	//
	KamataEngine::Model* model_ = nullptr;			//描画
													//
	KamataEngine::Camera* camera_ = nullptr;		//

	float gravity_ = 0.0f;
	float hitPower_ = 0.0f;
	float shotPower_ = 0.0f;

	//当たり判定
	bool isHit;
	bool isHit2;
	bool isHit3;
	bool isHit4;
	bool isHit5;
	HitBox hitBox_;


	bool shot_;
	bool hitWall_;
	bool hitStage_;
};

