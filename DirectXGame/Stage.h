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


	KamataEngine::Vector3 GetStageWorldPos1() { return worldTransform1_.translation_; }
	KamataEngine::Vector3 GetStageWorldPos2() { return worldTransform2_.translation_; }
	KamataEngine::Vector3 GetStageWorldPos3() { return worldTransform3_.translation_; }
	KamataEngine::Vector3 GetStageWorldPos4() { return worldTransform4_.translation_; }
	KamataEngine::Vector3 GetStageWorldPos5() { return worldTransform5_.translation_; }

	KamataEngine::Vector3 GetStageRotate1() { return worldTransform1_.rotation_; }
	KamataEngine::Vector3 GetStageRotate2() { return worldTransform2_.rotation_; }
	KamataEngine::Vector3 GetStageRotate3() { return worldTransform3_.rotation_; }
	KamataEngine::Vector3 GetStageRotate4() { return worldTransform4_.rotation_; }
	KamataEngine::Vector3 GetStageRotate5() { return worldTransform5_.rotation_; }


private:
	KamataEngine::WorldTransform worldTransform1_;
	KamataEngine::WorldTransform worldTransform2_;
	KamataEngine::WorldTransform worldTransform3_;
	KamataEngine::WorldTransform worldTransform4_;
	KamataEngine::WorldTransform worldTransform5_;
	KamataEngine::Model* model_;

	KamataEngine::Camera* camera_ = nullptr;
};

