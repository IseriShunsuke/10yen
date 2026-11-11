#include "Coin.h"

using namespace KamataEngine;

Coin::~Coin()
{
}

void Coin::Initialize(Model* model, Camera* camera, const Vector3& position)
{

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransform_.rotation_ = { 0.0f,0.0f,0.0f };

	//ステージ

	stageHitBox_;

	camera_ = camera;

	model_ = model;

	gravity_ = 0.1f;
}

void Coin::Update()
{

	if (isHit || isHit2 || isHit3 || isHit4 || isHit5)
	{
		hitStage_ = true;
	}
	else
	{
		hitStage_ = false;
	}


	if (!isHit && !isHit2 && !isHit3 && !isHit4 && !isHit5)
	{

		GravityFall();
	}


	if (worldTransform_.translation_.x <= -20.0f)
	{
		worldTransform_.translation_.x = -20.0f;
		hitWall_ = true;
	}
	else if (worldTransform_.translation_.x > 10.0f)
	{
		worldTransform_.translation_.x = 10.0f;
		hitWall_ = true;
	}
	else
	{
		hitWall_ = false;
	}

	if (hitPower_ == 0)
	{
		shot_ = false;
	}


	worldTransform_.UpdateMatrix();
	stageHitBox_.Update();
}

void Coin::MoveCoin()
{
	if (Input::GetInstance()->PushKey(DIK_A)) {

		hitPower_ -= 0.01f;
		if (hitPower_ <= -1.0f)
		{
			hitPower_ = -1.0f;
		}

	}
	else if (Input::GetInstance()->PushKey(DIK_D)) {


		hitPower_ += 0.01f;
		if (hitPower_ >= 1.0f)
		{
			hitPower_ = 1.0f;
		}

	}
	else
	{
		shotPower_ = hitPower_;
		if (shotPower_ != 0.0f)
		{
			shot_ = true;

		}
		else
		{
			hitPower_ = 0.0f;
		}

	}

	if (shot_)
	{

		worldTransform_.translation_.x += shotPower_ * 1.0f;
		if (shotPower_ > 0.0f)
		{
			shotPower_ -= 0.1f;
			if (shotPower_ <= 0)
			{
				hitPower_ = 0.0f;
				shot_ = false;
			}
		}
		if (shotPower_ < 0.0f)
		{
			shotPower_ += 0.1f;
			if (shotPower_ >= 0)
			{
				hitPower_ = 0.0f;
				shot_ = false;
			}
		}

		if (shotPower_ == 0)
		{
			hitPower_ = 0.0f;
			shot_ = false;
		}


		if (hitStage_)
		{
			worldTransform_.translation_.y += 1.0f;
		}



		gravity_ = 0.1f;
	}



}

void Coin::HitStage(float angle)
{
	float speed = 0.1f;

	// ステージの接線方向
	Vector2 dir = {
		std::cos(angle),
		std::sin(angle)
	};

	worldTransform_.translation_.x -= dir.x * speed;
	if (!hitWall_)
	{
		worldTransform_.translation_.y -= dir.y * speed;
	}
}

void Coin::GravityFall()
{
	worldTransform_.translation_.y -= gravity_;//重力落下
}

void Coin::Collision(Vector3 stageAngle)
{


	WorldTransform stageWorld;
	stageWorld.Initialize();
	stageWorld.translation_ = stageHitBox_.GetStageWorldPos1();
	stageWorld.rotation_ = stageHitBox_.GetStageRotate1();
	stageWorld.scale_ = { 1.0f,1.0f,1.0f };
	stageWorld.UpdateMatrix();


	isHit = hitBox_.IsCollisionStage(worldTransform_, stageWorld);

	stageWorld.translation_ = stageHitBox_.GetStageWorldPos2();
	stageWorld.rotation_ = stageHitBox_.GetStageRotate2();
	stageWorld.scale_ = { 1.0f,1.0f,1.0f };
	stageWorld.UpdateMatrix();

	isHit2 = hitBox_.IsCollisionStage(worldTransform_, stageWorld);

	stageWorld.translation_ = stageHitBox_.GetStageWorldPos3();
	stageWorld.rotation_ = stageHitBox_.GetStageRotate3();
	stageWorld.scale_ = { 1.0f,1.0f,1.0f };
	stageWorld.UpdateMatrix();

	isHit3 = hitBox_.IsCollisionStage(worldTransform_, stageWorld);

	stageWorld.translation_ = stageHitBox_.GetStageWorldPos4();
	stageWorld.rotation_ = stageHitBox_.GetStageRotate4();
	stageWorld.scale_ = { 1.0f,1.0f,1.0f };
	stageWorld.UpdateMatrix();

	isHit4 = hitBox_.IsCollisionStage(worldTransform_, stageWorld);

	stageWorld.translation_ = stageHitBox_.GetStageWorldPos5();
	stageWorld.rotation_ = stageHitBox_.GetStageRotate5();
	stageWorld.scale_ = { 1.0f,1.0f,1.0f };
	stageWorld.UpdateMatrix();

	isHit5 = hitBox_.IsCollisionStage(worldTransform_, stageWorld);


	
	if (isHit)
	{
		stageAngle = stageHitBox_.GetStageWorldPos1();
		HitStage(stageAngle.z);								//									//
	}														//									//
	else if (isHit2)										//									//
	{														//									//
		stageAngle = stageHitBox_.GetStageWorldPos2();		//									//
		HitStage(stageAngle.z);								//									//
	}														//									//
	else if (isHit3)										//									//
	{														//				計算はcoin.cpp		//
		stageAngle = stageHitBox_.GetStageWorldPos3();		//					HitStageで		//
		HitStage(stageAngle.z);								//									//
	}														//									//
	else if (hitWall_)										//									//
	{														//									//
		stageAngle = stageHitBox_.GetStageWorldPos4();		//									//
		HitStage(stageAngle.z);								//									//
	}														//									//
	else if (isHit5)										//									//
	{														//									//
															//									//
		stageAngle = stageHitBox_.GetStageWorldPos5();		//									//
		HitStage(stageAngle.z);								//									//

	}
}

void Coin::PowerAndGravity()
{
	if (hitWall_)
	{
		if (isHit)
		{
			gravity_ = 0.0f;

		}
		if (isHit2)
		{
			shotPower_ = 0.0f;
		}
		if (isHit3)
		{
			gravity_ = 0.0f;

		}
		if (isHit4)
		{
			shotPower_ = 0.0f;
		}
		if (isHit5)
		{
			gravity_ = 0.0f;
			shotPower_ = 0.0f;

		}


	}
}

void Coin::Draw()
{
	model_->Draw(worldTransform_, *camera_);
}
