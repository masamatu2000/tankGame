#include "TankHead.h"
#include"Engine/Model.h"
#include"Tank.h"
#include"Engine/Input.h"
#include"Engine/Debug.h"
#include"Bullet.h"
namespace {
	const float HEADER_POS_BIAS = 0.2f;
}
TankHead::TankHead(GameObject* parent):GameObject(parent,"TankHead"),hModel_(-1)
{
}

void TankHead::Initialize()
{
	hModel_=Model::Load("TankHead.fbx");
	isNeedLeseted = false;
	isLeseting = false;
}

void TankHead::Update()
{
	//Tank* tank = (Tank*)FindObject("Tank");
	//transform_.position_ = tank->GetPosition() ;
	//transform_.position_.y += HEADER_POS_BIAS;
	//	if (Input::IsKey(DIK_LEFT)) {
	//		transform_.rotate_.y -= 0.5f;
	//		isNeedLeseted = true;
	//	}
	//	if (Input::IsKey(DIK_RIGHT)) {
	//		transform_.rotate_.y += 0.5f;
	//		isNeedLeseted = true;
	//	}
	//	if (!isNeedLeseted) {
	//		transform_.rotate_ = tank->GetRotate();
	//	}
	//	else if (Input::IsKey(DIK_R) && isNeedLeseted) {
	//		transform_.rotate_ = tank->GetRotate();
	//		isNeedLeseted = false;
	//		//isLeseting = true;
	//	}
	if (Input::IsKey(DIK_LEFT)) {
		transform_.rotate_.y -= 0.5f;
	}
	if (Input::IsKey(DIK_RIGHT)) {
		transform_.rotate_.y += 0.5f;
	}
	if (Input::IsKey(DIK_SPACE)) {
		const float BULLET_SPEED = 0.2;
		XMFLOAT3 cannonTop=Model::GetBonePosition(hModel_, "Top");
		XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");
		XMVECTOR vTop = XMLoadFloat3(&cannonTop);
		XMVECTOR vRoot = XMLoadFloat3(&cannonRoot);
		XMVECTOR vMove=vTop-vRoot;
		vMove = vMove * BULLET_SPEED;
		XMFLOAT3 Move;
		XMStoreFloat3(&Move, vMove);
		//弾を撃つ
		Bullet* pBullet=Instantiate<Bullet>(GetParent()->GetParent());
		pBullet->SetMoveVector(Move);
		pBullet->SetPosition(cannonTop);
	}
}

void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
