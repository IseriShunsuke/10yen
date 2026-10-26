#include "TitleScene.h"

using namespace KamataEngine;

TitleScene::~TitleScene()
{
	delete spriteTitleNameUI_;
	delete spriteUI_;
	delete stageModel_;
	delete haikeiModel_;
	delete yenModel_;
}

void TitleScene::Initialize()
{
	camera_.Initialize();
	camera_.rotation_ = { 0.0f,0.0f,0.0f };
	camera_.translation_ = { 0.0f, 0.0f,0.0f };

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
	coin_.Initialize(yenModel_,&camera_, { -5.0f,16.0f,-10.0f });
	yenRotation_ = { 0.0f,0.0f,0.0f };
	yenPosition_ = { -5.0f,16.0f,-10.0f };

	//背景
	haikeiModel_ = Model::CreateFromOBJ("haikei");
	haikeiTransform.Initialize();
	haikeiTransform.translation_ = { -5.0f,0.0f,8.0f };
	haikeiTransform.scale_ = { 0.6f,1.5f,1.0f };
	haikeiTransform.rotation_ = { 0.0f,3.14f,0.0f };

	fade_ = new Fade();

	fade_->Initialize(yenModel_,&camera_);



	cameraPosition = { -5.0f,0.0f,-25.0f };

	UItexture_ = TextureManager::Load("TitleUI.png");

	spriteUI_ = Sprite::Create(UItexture_, { 640.0f, 580.0f }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });

	nameUItexture_ = TextureManager::Load("TitleNameUI.png");

	spriteTitleNameUI_ = Sprite::Create(nameUItexture_, { 640.0f, 270.0f }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });

	soundDataHandle = Audio::GetInstance()->LoadWave("kasumisou.wav");

	voiceHandle = Audio::GetInstance()->PlayWave(soundDataHandle, true);

	SEDataHandle = Audio::GetInstance()->LoadWave("pushBotan.wav");

	

	isFinish = false;
	cameraSpeed = 0.1f;
	roop = 0;
	viewTimer = 0.0f;
	isView = false;

	fade_->Start(Fade::Status::FadeIn, 1.0f);
}

void TitleScene::Update()
{

	switch (phase_) {
	case Phase::kFadeIn:
		

		if (fade_->isFinished()) {
			phase_ = Phase::kMain;
		}
		break;
	case Phase::kMain:
		if (Input::GetInstance()->TriggerKey(DIK_SPACE))
		{
			

			SEHandle = Audio::GetInstance()->PlayWave(SEDataHandle, true);

			Audio::GetInstance()->StopWave(soundDataHandle);
			

			fade_->Start(Fade::Status::FadeOut, 10.0f);
			phase_ = Phase::kFadeOut;

		}
		break;
	case Phase::kFadeOut:
		fade_->Update();
		if (fade_->isFinished()) {
			isFinish = true;
			
		}
		break;
	}
	fade_->SetPosition({ cameraPosition.x,cameraPosition.y ,cameraPosition.z });
	

	coin_.SetPosition(yenPosition_);
	coin_.SetRotation(yenRotation_);
	coin_.Update();
	
	viewTimer += 1.0f / 60.0f;

	if (viewTimer > 0.5f && viewTimer <= 1.5f)
	{
		isView = true;
	}
	if (viewTimer > 1.5f)
	{
		isView = false;
		viewTimer = 0.0f;
	}

	if (!isRolling)
	{
		waitTimer += 1.0f / 60.0f;
		yenRotation_.y += 0.1f;
	}
	if (isRolling)
	{
		yenPosition_.x += 0.1f;
		yenRotation_.z -= 0.03f;
		if (yenPosition_.x >= 12.0f)
		{
			yenPosition_.x = -21.0f;
			roop++;
		}
		if (roop >= 2 && yenPosition_.x >= -5.0f)
		{
			isRolling = false;
		}
	}

	if (waitTimer >= 10.0f)
	{
		waitTimer = 0.0f;
		roop = 0;
		yenRotation_.y = 0.0f;
		isRolling = true;
	}

	cameraPosition.y -= cameraSpeed;

	yenPosition_.y = cameraPosition.y +4.5f;
	
	fade_->Update();

	if (cameraPosition.y <= -38.0f)
	{
		cameraSpeed = -cameraSpeed;
	}

	if (cameraPosition.y >= 10.0f)
	{
		cameraSpeed = -cameraSpeed;
	}

	camera_.translation_ = cameraPosition;

	stageTransform.UpdateMatrix();
	stageTransform2.UpdateMatrix();
	stageTransform3.UpdateMatrix();
	stageTransform4.UpdateMatrix();
	stageTransform5.UpdateMatrix();

	haikeiTransform.UpdateMatrix();

	camera_.UpdateMatrix();

	camera_.TransferMatrix();


}

void TitleScene::Draw()
{
	stageModel_->Draw(stageTransform, camera_);
	stageModel_->Draw(stageTransform2, camera_);
	stageModel_->Draw(stageTransform3, camera_);
	stageModel_->Draw(stageTransform4, camera_);
	stageModel_->Draw(stageTransform5, camera_);

	haikeiModel_->Draw(haikeiTransform, camera_);

	if (phase_ != Phase::kFadeOut)
	{
		coin_.Draw();
	}
	else
	{
		fade_->Draw();
	}

	

	Sprite::PreDraw();
	if (phase_ != Phase::kFadeOut)
	{
		if (isView)
		{
			spriteUI_->Draw();
		}
		spriteTitleNameUI_->Draw();

	}
	Sprite::PostDraw();
}