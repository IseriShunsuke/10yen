#include "Fade.h"
#include "algorithm"

using namespace KamataEngine;

void Fade::Initialize(Model* model, Camera* camera)
{

	//10円
	model_ = model;

	camera_ = camera;
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 1.0f,10.0f,-10.0f };
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransform_.rotation_ = { 0.0f,0.0f,0.0f };

	cameraSpeed = 0.1f;

	addRotate_ = 0.1f;
	addScale_ = 0.049f;
}

void Fade::Update()
{
	switch (status_) {
	case Fade::Status::FadeIn:
		counter_ += 1.0f / 60.0f;

		if (counter_ >= duration_) {
			counter_ = duration_;
		}
		break;
	case Fade::Status::FadeOut:
		counter_ += 1.0f / 60.0f;

		if (counter_ >= duration_) {
			counter_ = duration_;
		}

		

		if (counter_ > duration_ / 2)
		{
			worldTransform_.scale_.x -= addScale_;
			worldTransform_.scale_.y -= addScale_;
		}
		else
		{
			worldTransform_.scale_.x += addScale_;
			worldTransform_.scale_.y += addScale_;
		}

		
		if (worldTransform_.rotation_.y <= 6.0f)
		{
			worldTransform_.rotation_.y += addRotate_;
		}
		
		break;
	}

	worldTransform_.UpdateMatrix();
}

void Fade::Draw()
{
	if (status_ == Status::None)
	{
		return;
	}


	model_->Draw(worldTransform_, *camera_);


}

void Fade::Start(Status status, float duration) {
	status_ = status;
	duration_ = duration;
	counter_ = 0.0f;
}

void Fade::Stop()
{
	status_ = Status::None;
}

bool Fade::isFinished() const
{
	switch (status_) {
	case Fade::Status::FadeIn:
	case Fade::Status::FadeOut:
		if (counter_ >= duration_) {
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}

Fade::~Fade()
{

}

void Fade::SetPosition(KamataEngine::Vector3 position)
{
	worldTransform_.translation_.x = position.x;
	worldTransform_.translation_.y = position.y;
}