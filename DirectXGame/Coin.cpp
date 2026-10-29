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

	camera_ = camera;

	model_ = model;

	gravity_ = 0.1f;
}

void Coin::Update()
{
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

void Coin::PowerAndGravity(bool stage1, bool stage2, bool stage3, bool stage4, bool stage5)
{
	if (hitWall_)
	{
		if (stage1)
		{
			gravity_ = 0.0f;

		}
		if (stage2)
		{
			shotPower_ = 0.0f;
		}
		if (stage3)
		{
			gravity_ = 0.0f;

		}
		if (stage4)
		{
			shotPower_ = 0.0f;
		}
		if (stage5)
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
