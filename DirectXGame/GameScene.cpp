#include "GameScene.h"
#include "HitBox.h"
using namespace KamataEngine;

#include <random>
std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);


GameScene::~GameScene()
{
	delete goalModel_;
	delete haikeiModel_;

	// 3Dモデルデータの解放
	delete modelParticle_;

	// パーティクルの解放
	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();
}

void GameScene::Initialize()
{

	//カメラ
	camera_.Initialize();
	camera_.rotation_ = { 0.0f,0.0f,0.0f };
	camera_.translation_ = { -5.0f,0.0f,-25.0f };

	//ステージ
	stageModel_ = Model::CreateFromOBJ("stage_kari");

	stage_.Initialize(stageModel_, &camera_);

	//10円
	yenModel_ = Model::CreateFromOBJ("coin");
	coin_.Initialize(yenModel_, &camera_, { 6.0f,-40.0f,0.0f });//スタートは x = -3.0f, y = 16.0f
	yenPosition_ = { 0.0f,0.0f,0.0f };
	yenRotation_ = { 0.0f,0.0f,0.0f };

	//ゴール
	goalModel_ = Model::CreateFromOBJ("cube");
	goalTransform.Initialize();
	goalTransform.translation_ = { 6.0f,-44.0f,1.4f };
	goalTransform.scale_ = { 1.0f,1.0f,1.0f };
	goalTransform.rotation_ = { 0.0f,0.0f,0.0f };

	//背景
	haikeiModel_ = Model::CreateFromOBJ("haikei");
	haikeiTransform.Initialize();
	haikeiTransform.translation_ = { -5.0f,0.0f,8.0f };
	haikeiTransform.scale_ = { 0.6f,1.5f,1.0f };
	haikeiTransform.rotation_ = { 0.0f,3.14f,0.0f };

	//スタート演出
	startBlackTexture = TextureManager::Load("startBlack/startBlack3.png");
	spriteStart3_ = Sprite::Create(startBlackTexture, { 640,360 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	startBlackTexture = TextureManager::Load("startBlack/startBlack2.png");
	spriteStart2_ = Sprite::Create(startBlackTexture, { 640,360 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	startBlackTexture = TextureManager::Load("startBlack/startBlack1.png");
	spriteStart1_ = Sprite::Create(startBlackTexture, { 640,360 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	startBlackTexture = TextureManager::Load("startBlack/startBlackGO.png");
	spriteStartGO_ = Sprite::Create(startBlackTexture, { 640,360 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });

	//ゲームオーバー演出用	
	directiontexture = TextureManager::Load("death.png");
	spriteDirection_ = Sprite::Create(directiontexture, { 640,360 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	directionTimer = 0;

	startTimer = 3.0f;

	// 乱数の初期化
	srand((unsigned)time(NULL));
	modelParticle_ = Model::CreateSphere(4, 4);

	camera_.UpdateMatrix();
	camera_.TransferMatrix();



	isClear_ = false;
	isOver_ = false;
}

void GameScene::Update()
{
	AllCollision();

	coin_.Update();
	stage_.Update();
	yenPosition_ = coin_.GetPosition();
	yenRotation_ = coin_.GetRotation();



	coin_.MoveCoin();

	// 確率で発生
	if (rand() % 20 == 0) {
		// 発生位置は乱数
		Vector3 position = { distribution(randomEngine) * 30.0f + camera_.translation_.x, distribution(randomEngine) * 20.0f + camera_.translation_.y, 1.45f };
		// パーティクルの生成
		ParticleBorn(position);
	}
	// パーティクルの更新
	for (Particle* particle : particles_) {
		particle->Update();
	}

	// 終了フラグの立ったパーティクルを削除
	particles_.remove_if([](Particle* particle) {
		if (particle->IsFinished() == true) {
			delete particle;
			return true;
		}
		return false;
		});


	camera_.translation_.y = yenPosition_.y;

	if (yenPosition_.y < -49.0f)
	{
		directionTimer += 1.0f / 60.0f;

		


		if (directionTimer >= 2.0f)
		{
			isOver_ = true;
		}

	}

	if (camera_.translation_.y <= -37.0f)
	{
		camera_.translation_.y = -37.0f;
	}


	goalTransform.UpdateMatrix();
	haikeiTransform.UpdateMatrix();

	camera_.UpdateMatrix();

}

void GameScene::Start()
{
	startTimer -= 1.0f / 60.0f;
	if (startTimer <= 3.0f && startTimer > 2.0f)
	{
		spriteStart3_->Draw();
	}
	if (startTimer <= 2.0f && startTimer > 1.0f)
	{
		spriteStart2_->Draw();
	}
	if (startTimer <= 1.0f && startTimer > 0.0f)
	{
		spriteStart1_->Draw();
	}
	if (startTimer <= 0.0f && startTimer > -0.5f)
	{
		spriteStartGO_->Draw();
	}

	if (startTimer > 0.0f)
	{
		coin_.SetGravity(0.0f);
	}
	else
	{
		coin_.SetGravity(0.1f);
	}
}



void GameScene::AllCollision()
{
	WorldTransform yenWorld;
	yenWorld.Initialize();
	yenWorld.translation_ = yenPosition_;
	yenWorld.rotation_ = { 0.0f,0.0f,0.0f };
	yenWorld.scale_ = { 1.0f,1.0f,1.0f };
	yenWorld.UpdateMatrix();

	hitGoal_ = hitBox_.IsCollisionGoal(yenWorld, goalTransform);

	coin_.Collision(stage_.GetWorld1(), stage_.GetWorld2(), stage_.GetWorld3(), stage_.GetWorld4(), stage_.GetWorld5());



	if (hitGoal_)
	{
		coin_.SetClear(true);

	}

	if (coin_.GetFinish())
	{
		isClear_ = true;
	}

}

void GameScene::Draw()
{
	stage_.Draw();
	coin_.Draw();
	goalModel_->Draw(goalTransform, camera_);
	haikeiModel_->Draw(haikeiTransform, camera_);

	for (Particle* particle : particles_) {
		particle->Draw(camera_);
	}

	Sprite::PreDraw();

	Start();

	if (directionTimer < 2.0f && yenPosition_.y < -49.0f)
	{
		spriteDirection_->Draw();
	}


	Sprite::PostDraw();
}

// パーティクルの発生
void GameScene::ParticleBorn(Vector3 position) {
	// パーティクルの生成
	for (int i = 0; i < 150; i++) {
		// 生成
		Particle* particle = new Particle();
		// 位置
		// Vector3 position = { 0.0, 0.0f, 0.0f };
		// 移動量
		Vector3 velocity = { distribution(randomEngine), distribution(randomEngine), 0 };

		normalize(velocity);
		velocity.x *= distribution(randomEngine);
		velocity.y *= distribution(randomEngine);
		velocity.z *= distribution(randomEngine);

		velocity.x *= 0.1f;
		velocity.y *= 0.1f;
		velocity.z *= 0.1f;
		// 初期化
		particle->Initialize(modelParticle_, position, velocity);
		// リストに追加
		particles_.push_back(particle);
	}
}

Vector3 GameScene::normalize(Vector3 v)
{
	Vector3 result = {};
	result.x = v.x / static_cast<float>(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	result.y = v.y / static_cast<float>(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	result.z = v.z / static_cast<float>(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	return result;
}