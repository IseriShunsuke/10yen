#include "Stage.h"

using namespace KamataEngine;

Stage::~Stage()
{
	delete model_;
}

void Stage::Initialize(Model* model, Camera* camera)
{

	worldTransform1_.Initialize();
	worldTransform1_.translation_ = { -12.0f,5.0f,9.0f };
	worldTransform1_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransform1_.rotation_ = { 0.0f,0.0f,0.2f };//0.0 右斜め上　//2.0~左斜め上

	worldTransform2_.Initialize();
	worldTransform2_.translation_ = { 6.0f,-7.0f,9.0f };
	worldTransform2_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransform2_.rotation_ = { 0.0f,0.0f,0.5f };//0.0 右斜め上　//2.0~左斜め上

	worldTransform3_.Initialize();
	worldTransform3_.translation_ = { -12.0f,-20.0f,9.0f };
	worldTransform3_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransform3_.rotation_ = { 0.0f,0.0f,0.1f };//0.0 右斜め上　//2.0~左斜め上

	worldTransform4_.Initialize();
	worldTransform4_.translation_ = { 6.0f,-30.0f,9.0f };
	worldTransform4_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransform4_.rotation_ = { 0.0f,0.0f,0.2f };//0.0 右斜め上　//2.0~左斜め上

	worldTransform5_.Initialize();
	worldTransform5_.translation_ = { -18.0f,-44.0f,9.0f };
	worldTransform5_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransform5_.rotation_ = { 0.0f,0.0f,0.2f };//0.0 右斜め上　//2.0~左斜め上

	camera_ = camera;

	model_ = model;
}

void Stage::Update()
{
	worldTransform1_.UpdateMatrix();
	worldTransform2_.UpdateMatrix();
	worldTransform3_.UpdateMatrix();
	worldTransform4_.UpdateMatrix();
	worldTransform5_.UpdateMatrix();
}

void Stage::Draw()
{
	model_->Draw(worldTransform1_, *camera_);
	model_->Draw(worldTransform2_, *camera_);
	model_->Draw(worldTransform3_, *camera_);
	model_->Draw(worldTransform4_, *camera_);
	model_->Draw(worldTransform5_, *camera_);
}

