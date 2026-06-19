#include "Enemy.h"
#include"Engine/Model.h"
#include"Ground.h"
Enemy::Enemy(GameObject* parent):GameObject(parent,"Enemy"),hModel_(-1)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Enemy.fbx");
	sc_ = new SphereCollider(transform_.position_, 0.5f);
	AddCollider(sc_);
}

void Enemy::Update()
{
	//レイキャストして、浮いてたら地面まで落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;//地面は０より下に作られている。そうじゃないときはもっと上から
	data.dir = { 0,-1,0 };
	Ground* gr = (Ground*)FindObject("Ground");
	Model::RayCast(gr->GetModelHandle(), &data);
	if (data.hit) {
		//地面（レイがヒットした位置）まで下げる
		transform_.position_.y = -data.dist;
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}
