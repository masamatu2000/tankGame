#include "Bullet.h"
#include"Engine/Model.h"
#include"Engine/SphereCollider.h"
#include"Enemy.h"
namespace {
	const float GRAVITY= 9.8f/60.0f;
}
Bullet::Bullet(GameObject* parent):GameObject(parent,"Bullet"),hModel_(-1),move_(XMFLOAT3(0.0f,0.0f,0.0f))
{
}

void Bullet::Initialize()
{
	hModel_=Model::Load("Bullet.fbx");
	assert(hModel_ >= 0);
	sc_ = new SphereCollider(transform_.position_, 0.5f);
	AddCollider(sc_);
}

void Bullet::Update()
{
	//transform_.position_+= move_;
	move_.y -= 0.01f;
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	XMVECTOR vMove = XMLoadFloat3(&move_);
	vPos += vMove;
	XMStoreFloat3(&transform_.position_, vPos);
	Enemy* enemy = (Enemy*)FindObject("Enemy");
	//遠くに行ったら消す
	if (transform_.position_.z > 50.0f || transform_.position_.z < -50.0f || transform_.position_.x>50.0f || transform_.position_.x < -50.0f||transform_.position_.y<-10.0f) {
		KillMe();
	}
	if (enemy != nullptr){
		if (sc_->IsHit(enemy->GetCollider())) {
			OnCollision(enemy);
		}
	}
}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	
}

void Bullet::Release()
{
	
}

void Bullet::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Enemy") {
		pTarget->KillMe();
		KillMe();
	}
}
