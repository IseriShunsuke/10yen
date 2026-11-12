#pragma once
#include "KamataEngine.h"

class Stage
{
public:
	~Stage();

	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera);

	void Update();

	// 描画
	void Draw();

	KamataEngine::WorldTransform* GetWorld1() { return worldTransform1_; }
	KamataEngine::WorldTransform* GetWorld2() { return worldTransform2_; }
	KamataEngine::WorldTransform* GetWorld3() { return worldTransform3_; }
	KamataEngine::WorldTransform* GetWorld4() { return worldTransform4_; }
	KamataEngine::WorldTransform* GetWorld5() { return worldTransform5_; }


private:
	KamataEngine::WorldTransform* worldTransform1_;
	KamataEngine::WorldTransform* worldTransform2_;
	KamataEngine::WorldTransform* worldTransform3_;
	KamataEngine::WorldTransform* worldTransform4_;
	KamataEngine::WorldTransform* worldTransform5_;
	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;
};

