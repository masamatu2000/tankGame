#include "TankHead.h"
#include"Engine/Model.h"
#include"Tank.h"
TankHead::TankHead(GameObject* parent):GameObject(parent,"TankHead"),hModel_(-1)
{
}

void TankHead::Initialize()
{
	hModel_=Model::Load("TankHead.fbx");
}

void TankHead::Update()
{
	Tank* tank = (Tank*)FindObject("Tank");
	transform_.position_ = tank->GetPosition() ;
	transform_.position_.y += 0.2f;
	transform_.rotate_ = tank->GetRotate();
}

void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
