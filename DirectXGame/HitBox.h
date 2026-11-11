#pragma once
#include "KamataEngine.h"
#include <cmath>



class HitBox
{
public:
	bool IsCollisionStage(const KamataEngine::WorldTransform& coin,const KamataEngine::WorldTransform& stage);
	bool IsCollisionGoal(const KamataEngine::WorldTransform& coin, const KamataEngine::WorldTransform& goal);

	

private:
	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;
};

