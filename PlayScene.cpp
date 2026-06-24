#include "PlayScene.h"
#include"Ground.h"
#include"Tank.h"
#include"TankHead.h"
#include"Enemy.h"
#include <random>
namespace {
	const int ENEMY_NUM = 5;
	const int ENEMY_APPEAR_TIMER = 60 * 5;
}
PlayScene::PlayScene(GameObject* parent):GameObject(parent,"PlayScene")
{

}

void PlayScene::Initialize()
{

	Instantiate<Ground>(this);
	Instantiate<Tank>(this);
	for (int i = 0;i < ENEMY_NUM;i++) {
		std::random_device rd;
		std::mt19937 mt(rd());
		// X座標を -50～50 の範囲で生成
		std::uniform_real_distribution<float> distX(-25.0f, 25.0f);
		// Z座標を -50～50 の範囲で生成
		std::uniform_real_distribution<float> distZ(-25.0f, 25.0f);
		Enemy* enemy=Instantiate<Enemy>(this);
		XMFLOAT3 epos ;
		epos.x = distX(mt);
		epos.y = 0.0f;
		epos.z = distZ(mt);
		enemy->SetPosition(epos);
	}
}

void PlayScene::Update()
{
	static int timer = 0;
	timer++;
	if (timer > ENEMY_APPEAR_TIMER) {
		std::random_device rd;
		std::mt19937 mt(rd());
		// X座標を -50～50 の範囲で生成
		std::uniform_real_distribution<float> distX(-25.0f, 25.0f);
		// Z座標を -50～50 の範囲で生成
		std::uniform_real_distribution<float> distZ(-25.0f, 25.0f);
		Enemy* enemy = Instantiate<Enemy>(this);
		XMFLOAT3 epos;
		epos.x = distX(mt);
		epos.y = 0.0f;
		epos.z = distZ(mt);
		enemy->SetPosition(epos);
		timer = 0;
	}
}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{

}
