#include "HitBox.h"
#include <cmath>

using namespace KamataEngine;
bool HitBox::IsCollisionStage(const WorldTransform& coin,const  WorldTransform& stage)
{
	float angle = -stage.rotation_.z;   // 逆回転

	float dx = coin.translation_.x - stage.translation_.x;
	float dy = coin.translation_.y - stage.translation_.y;

	// ステージ座標系へ変換
	float localX = dx * cosf(angle) - dy * sinf(angle);
	float localY = dx * sinf(angle) + dy * cosf(angle);
	
	if (localX + 1.0f > -10.0f && localX - 1.0f < 10.0f)
	{
		if (localY + 0.2f > -2.0f && localY - 0.2f < 2.0f)
		{
			return true;
		}
	}

	return false;
}

bool HitBox::IsCollisionGoal(const WorldTransform& coin, const WorldTransform& goal)
{
	float angle = -goal.rotation_.z;   // 逆回転

	float dx = coin.translation_.x - goal.translation_.x;
	float dy = coin.translation_.y - goal.translation_.y;

	// ステージ座標系へ変換
	float localX = dx * cosf(angle) - dy * sinf(angle);
	float localY = dx * sinf(angle) + dy * cosf(angle);

	if (localX + 1.0f > -1.0f && localX - 1.0f < 1.0f)
	{
		if (localY + 1.0f > -2.0f && localY - 1.0f < 1.0f)
		{
			return true;
		}
	}

	return false;
}