#pragma once
#include "KamataEngine.h"

class GameClear
{
public:
	~GameClear();

	void Initialize();

	void Update();

	void Draw();

	bool GetFinish() { return isFinish; }
private:

	KamataEngine::Model* model_;
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* modelHaikei_;
	KamataEngine::WorldTransform haikeiWorldTransform_;

	KamataEngine::Sprite* spriteUI_ = nullptr;

	uint32_t UItexture_;

	KamataEngine::Camera camera_;

	bool isFinish = false; 
};

