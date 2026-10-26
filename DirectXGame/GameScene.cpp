#include "GameScene.h"
#include "HitBox.h"
using namespace KamataEngine;


GameScene::~GameScene()
{
	delete stageModel_;
	delete yenModel_;
	delete goalModel_;
	delete haikeiModel_;

	goalModel_;
}

void GameScene::Initialize()
{

	//カメラ
	camera_.Initialize();
	camera_.rotation_ = { 0.0f,0.0f,0.0f };
	camera_.translation_ = { -5.0f,0.0f,-25.0f };

	//ステージ
	stageModel_ = Model::CreateFromOBJ("stage_kari");
	stageTransform.Initialize();
	stageTransform.translation_ = { -12.0f,5.0f,9.0f };
	stageTransform.scale_ = { 1.0f,1.0f,1.0f };
	stageTransform.rotation_ = { 0.0f,0.0f,0.2f };//0.0 右斜め上　//2.0~左斜め上

	stageTransform2.Initialize();
	stageTransform2.translation_ = { 6.0f,-7.0f,9.0f };
	stageTransform2.scale_ = { 1.0f,1.0f,1.0f };
	stageTransform2.rotation_ = { 0.0f,0.0f,0.5f };//0.0 右斜め上　//2.0~左斜め上

	stageTransform3.Initialize();
	stageTransform3.translation_ = { -12.0f,-20.0f,9.0f };
	stageTransform3.scale_ = { 1.0f,1.0f,1.0f };
	stageTransform3.rotation_ = { 0.0f,0.0f,0.1f };//0.0 右斜め上　//2.0~左斜め上

	stageTransform4.Initialize();
	stageTransform4.translation_ = { 6.0f,-30.0f,9.0f };
	stageTransform4.scale_ = { 1.0f,1.0f,1.0f };
	stageTransform4.rotation_ = { 0.0f,0.0f,0.2f };//0.0 右斜め上　//2.0~左斜め上

	stageTransform5.Initialize();
	stageTransform5.translation_ = { -18.0f,-44.0f,9.0f };
	stageTransform5.scale_ = { 1.0f,1.0f,1.0f };
	stageTransform5.rotation_ = { 0.0f,0.0f,0.2f };//0.0 右斜め上　//2.0~左斜め上

	//10円
	yenModel_ = Model::CreateFromOBJ("coin");
	coin_.Initialize(yenModel_, &camera_, { -3.0f,16.0f,0.0f });
	yenPosition_ = { -3.0f,16.0f,0.0f };
	yenRotation_ = { 0.0f,0.0f,0.0f };

	//ゴール
	goalModel_ = Model::CreateFromOBJ("cube");
	goalTransform.Initialize();
	goalTransform.translation_ = { 6.0f,-44.0f,0.0f };
	goalTransform.scale_ = { 1.0f,1.0f,1.0f };
	goalTransform.rotation_ = { 0.0f,0.0f,0.0f };

	//背景
	haikeiModel_ = Model::CreateFromOBJ("haikei");
	haikeiTransform.Initialize();
	haikeiTransform.translation_ = { -5.0f,0.0f,8.0f };
	haikeiTransform.scale_ = { 0.6f,1.5f,1.0f };
	haikeiTransform.rotation_ = { 0.0f,3.14f,0.0f };

	//スタート演出
	startBlackTexture = TextureManager::Load("startBlack/startBlack3.png");
	spriteStart3_ = Sprite::Create(startBlackTexture, { 640,360 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	startBlackTexture = TextureManager::Load("startBlack/startBlack2.png");
	spriteStart2_ = Sprite::Create(startBlackTexture, { 640,360 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	startBlackTexture = TextureManager::Load("startBlack/startBlack1.png");
	spriteStart1_ = Sprite::Create(startBlackTexture, { 640,360 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	startBlackTexture = TextureManager::Load("startBlack/startBlackGO.png");
	spriteStartGO_ = Sprite::Create(startBlackTexture, { 640,360 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });

	startTimer = 3.0f;



	camera_.UpdateMatrix();
	camera_.TransferMatrix();

	isHit = true;

	hitPosition_ = { 0.0f,0.0f,0.0f };
	gravity_ = 0.1f;

	shot_ = false;
	hitWall_ = false;

	isClear_ = false;
	isOver_ = false;
}

void GameScene::Update()
{
	AllCollision();

	MoveCoin();

	
	coin_.Update();
	coin_.SetPosition(yenPosition_);
	coin_.SetRotation(yenRotation_);


	if (yenPosition_.x <= -20.0f)
	{
		hitWall_ = true;
		yenPosition_.x = -20.0f;
	}

	else if (yenPosition_.x > 10.0f)
	{
		hitWall_ = true;
		yenPosition_.x = 10.0f;
	}
	else
	{
		hitWall_ = false;
	}

	if (hitWall_)
	{

		shot_ = false;
		if (isHit)
		{
			gravity_ = 0.0f;

		}
		if (isHit2)
		{
			hitPower_ = 0.0f;
		}
		if (isHit3)
		{
			gravity_ = 0.0f;

		}
		if (isHit4)
		{
			hitPower_ = 0.0f;
		}
		if (isHit5)
		{
			gravity_ = 0.0f;
			hitPower_ = 0.0f;

		}


	}

	if (hitPower_ == 0)
	{
		shot_ = false;
	}

	if (!isHit && !isHit2 && !isHit3 && !isHit4 && !isHit5)
	{
		hitPosition_.y = yenPosition_.y;
		yenPosition_.y -= gravity_;//重力落下
	}
	camera_.translation_.y = yenPosition_.y;

	if (yenPosition_.y < -49.0f)
	{
		isOver_ = true;
	}

	if (camera_.translation_.y <= -50.0f)
	{
		camera_.translation_.y = -50.0f;
	}

	stageTransform.UpdateMatrix();
	stageTransform2.UpdateMatrix();
	stageTransform3.UpdateMatrix();
	stageTransform4.UpdateMatrix();
	stageTransform5.UpdateMatrix();
	goalTransform.UpdateMatrix();
	haikeiTransform.UpdateMatrix();

	camera_.UpdateMatrix();

}

void GameScene::Start()
{
	startTimer -= 1.0f / 60.0f;
	if (startTimer <= 3.0f && startTimer > 2.0f)
	{
		spriteStart3_->Draw();
	}
	if (startTimer <= 2.0f && startTimer > 1.0f)
	{
		spriteStart2_->Draw();
	}
	if (startTimer <= 1.0f && startTimer > 0.0f)
	{
		spriteStart1_->Draw();
	}
	if (startTimer <= 0.0f && startTimer > -0.5f)
	{
		spriteStartGO_->Draw();
	}

	if (startTimer > 0.0f)
	{
		gravity_ = 0.0f;
	}
	else
	{
		gravity_ = 0.1f;
	}
}

void GameScene::MoveCoin()
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

		yenPosition_.x += shotPower_ * 1.0f;
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


		if (isHit || isHit2 || isHit3 || isHit4 || isHit5)
		{
			yenPosition_.y += 1.0f;
		}



		gravity_ = 0.1f;
	}



}

void GameScene::AllCollision()
{
	WorldTransform yenWorld;
	yenWorld.Initialize();
	yenWorld.translation_ = yenPosition_;
	yenWorld.rotation_ = { 0.0f,0.0f,0.0f };
	yenWorld.scale_ = { 1.0f,1.0f,1.0f };
	isHit = hitBox_.IsCollisionStage(yenWorld, stageTransform);
	isHit2 = hitBox_.IsCollisionStage(yenWorld, stageTransform2);
	isHit3 = hitBox_.IsCollisionStage(yenWorld, stageTransform3);
	isHit4 = hitBox_.IsCollisionStage(yenWorld, stageTransform4);
	isHit5 = hitBox_.IsCollisionStage(yenWorld, stageTransform5);

	hitGoal_ = hitBox_.IsCollisionGoal(yenWorld, goalTransform);


	if (isHit)
	{
		float angle = stageTransform.rotation_.z;
		float speed = 0.1f;

		// ステージの接線方向
		Vector2 dir = {
			std::cos(angle),
			std::sin(angle)
		};

		yenPosition_.x -= dir.x * speed;
		if (!hitWall_)
		{
			yenPosition_.y -= dir.y * speed;
		}
	}
	else if (isHit2)
	{
		float angle = stageTransform2.rotation_.z;
		float speed = 0.1f;

		// ステージの接線方向
		Vector2 dir = {
			std::cos(angle),
			std::sin(angle)
		};

		yenPosition_.x -= dir.x * speed;
		if (!hitWall_)
		{
			yenPosition_.y -= dir.y * speed;
		}

	}
	else if (isHit3)
	{
		float angle = stageTransform3.rotation_.z;
		float speed = 0.1f;

		// ステージの接線方向
		Vector2 dir = {
			std::cos(angle),
			std::sin(angle)
		};

		yenPosition_.x -= dir.x * speed;
		if (!hitWall_)
		{
			yenPosition_.y -= dir.y * speed;
		}

	}
	else if (isHit4)
	{
		float angle = stageTransform4.rotation_.z;
		float speed = 0.1f;

		// ステージの接線方向
		Vector2 dir = {
			std::cos(angle),
			std::sin(angle)
		};

		yenPosition_.x -= dir.x * speed;
		if (!hitWall_)
		{
			yenPosition_.y -= dir.y * speed;
		}

	}
	else if (isHit5)
	{
		float angle = stageTransform5.rotation_.z;
		float speed = 0.1f;

		// ステージの接線方向
		Vector2 dir = {
			std::cos(angle),
			std::sin(angle)
		};

		yenPosition_.x -= dir.x * speed;
		if (!hitWall_)
		{
			yenPosition_.y -= dir.y * speed;
		}

	}

	if (hitGoal_)
	{
		isClear_ = true;
	}
}

void GameScene::Draw()
{
	stageModel_->Draw(stageTransform, camera_);
	stageModel_->Draw(stageTransform2, camera_);
	stageModel_->Draw(stageTransform3, camera_);
	stageModel_->Draw(stageTransform4, camera_);
	stageModel_->Draw(stageTransform5, camera_);
	coin_.Draw();
	goalModel_->Draw(goalTransform, camera_);
	haikeiModel_->Draw(haikeiTransform, camera_);

	Sprite::PreDraw();

	Start();


	Sprite::PostDraw();
}
