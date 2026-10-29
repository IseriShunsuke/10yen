#pragma once
#include "KamataEngine.h"

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

	void PowerAndGravity(bool stage1, bool stage2, bool stage3, bool stage4, bool stage5);

	KamataEngine::Vector3 SetPosition(KamataEngine::Vector3 position) { return worldTransform_.translation_ = position; }
	KamataEngine::Vector3 SetRotation(KamataEngine::Vector3 rotation) { return worldTransform_.rotation_ = rotation; }

	KamataEngine::Vector3 GetPosition() { return worldTransform_.translation_; }
	KamataEngine::Vector3 GetRotation() { return worldTransform_.rotation_; }

	float  SetGravity(float gravity) { return gravity_ = gravity; }
	float  SetPower(float power) { return shotPower_ = power; }

	bool GetHitWall() { return hitWall_; }
	bool SetHitStage(bool hitStage) { return hitStage_ = hitStage; }

	
	
private:
	KamataEngine::WorldTransform worldTransform_;	//
	KamataEngine::Model* model_ = nullptr;			//描画
													//
	KamataEngine::Camera* camera_ = nullptr;		//

	float gravity_;
	float hitPower_;
	float shotPower_;


	bool shot_;
	bool hitWall_;
	bool hitStage_;
};

