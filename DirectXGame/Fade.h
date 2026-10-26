#pragma once
#include "Coin.h"

#include "KamataEngine.h"

using namespace KamataEngine;

class Fade 
{
public:

	enum class Status
	{
		None,
		FadeIn,
		FadeOut,
	};



	
	void Initialize(Model* model, Camera* camera);

	void Update();

	void Draw();

	void Start(Status status, float duration);

	void Stop();

	bool isFinished() const;

	~Fade();

	void SetPosition(KamataEngine::Vector3 position);

private:

	KamataEngine::Camera* camera_;

	KamataEngine::Vector3 cameraPosition;
	float cameraSpeed;

	//10円
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;

	float addScale_;
	float addRotate_;


	Status status_ = Status::None;

	float duration_ = 0.0f;

	float counter_ = 0.0f;
};
