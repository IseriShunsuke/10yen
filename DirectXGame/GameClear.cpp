#include "GameClear.h"

using namespace KamataEngine;

GameClear::~GameClear()
{
}

void GameClear::Initialize()
{

	model_ = Model::CreateFromOBJ("ticket");

	camera_.Initialize();
	camera_.rotation_ = { 0.0f,0.0f,0.0f };
	camera_.translation_ = { 0.0f, 0.0f,0.0f };

	worldTransform_.Initialize();
	worldTransform_.translation_ = { 15.0f,0.0f,-1.0f };
	worldTransform_.rotation_ = { 0.0f,1.5f,1.5f };
	worldTransform_.scale_ = { 5.0f,5.0f,5.0f };

	modelHaikei_ = Model::CreateFromOBJ("clear");

	haikeiWorldTransform_.Initialize();
	haikeiWorldTransform_.translation_ = { 0.0f,0.0f,10.0f };
	haikeiWorldTransform_.rotation_ = { 0.0f,1.57f,0.0f };
	haikeiWorldTransform_.scale_ = { 1.0f,4.0f,8.0f };


	UItexture_ = TextureManager::Load("clearUI.png");

	spriteUI_ = Sprite::Create(UItexture_, { 640.0f, 360.0f }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });


	isFinish = false;
}

void GameClear::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_D))
	{
		isFinish = true;
	}

	worldTransform_.translation_.y -= 0.1f;
	worldTransform_.rotation_.y += 0.01f;
	
	if (worldTransform_.translation_.y <= -12.0f)
	{
		worldTransform_.translation_.y = -12.0f;
	}
	

	worldTransform_.UpdateMatrix();
	haikeiWorldTransform_.UpdateMatrix();
}

void GameClear::Draw()
{
	model_->Draw(worldTransform_, camera_);

	modelHaikei_->Draw(haikeiWorldTransform_, camera_);

	Sprite::PreDraw();
	
	spriteUI_->Draw();

	Sprite::PostDraw();
}