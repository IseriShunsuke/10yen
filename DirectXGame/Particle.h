#pragma once
#include "KamataEngine.h"

class Particle
{
public:
	/*~Particle();*/

	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position, KamataEngine::Vector3 velocity);

	void Update();

	void Draw(KamataEngine::Camera& camera);

	bool IsFinished() { return isFinished_; }
private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// 色変更オブジェクト
	KamataEngine::ObjectColor objectColor_;
	// 色の数値
	KamataEngine::Vector4 color_ = {};
	// 移動量
	KamataEngine::Vector3 velocity_ = {};
	// 終了フラグ
	bool isFinished_ = false;
	// 経過時間カウント
	float counter_ = 0.0f;
	// 存続時間（消滅までの時間）<秒>
	const float kDuration = 1.0f;
};

