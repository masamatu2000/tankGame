#include "Tank.h"
#include"Engine/Model.h"
#include"Engine/Input.h"
Tank::Tank(GameObject* parent):GameObject(parent,"Tank"),hModel_(-1)
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
}

void Tank::Update()
{
	if (Input::IsKey(DIK_A)) {
		transform_.rotate_.y -= 0.5f;
	}
	if (Input::IsKey(DIK_D)) {
		transform_.rotate_.y+=0.5f;
	}
	if (Input::IsKey(DIK_W)) {
		transform_.position_.z += 0.1f;
	}
	if (Input::IsKey(DIK_S)) {
		transform_.position_.z -= 0.1f;
	}
}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}
