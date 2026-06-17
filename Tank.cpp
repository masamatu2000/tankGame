#include "Tank.h"
#include"Engine/Model.h"
#include"Engine/Input.h"
#include<assert.h>
#include"Engine/Debug.h"
#include"Ground.h"
#include<string>
#include"Engine/Camera.h"
namespace {
	XMVECTOR vFront = { 0,0,1,0 };//タンクの前ベクトル
	const float moveSpeed = 0.1f;
	const float FPS_CAM_BIAS = 0.2f;//カメラの高さの調整
	const float TPS_CAM_BIAS = 5.0f;//カメラの高さの調整
	const float TPS_CAM_BEHIND = -10.0f;
	enum CAM_TYPE {
		FIXED_CAM,
		TPS_CAM,
		TPS_CAMROT,
		FPS_CAM,
		CAM_TYPE_MAX,
	};
	char CAMTYPES[4][12] = {
		"FIXED_CAM",
		"TPS_CAM",
		"TPS_CAMROT",
		"FPS_CAM"
	};

}
Tank::Tank(GameObject* parent):GameObject(parent,"Tank"),hModel_(-1),cam_Type(FIXED_CAM)
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
	assert(hModel_ >= 0);//モデルの読み込み失敗確認
	cam_Type = FIXED_CAM;
}

void Tank::Update()
{
	XMVECTOR vpos = XMLoadFloat3(&transform_.position_);
	XMMATRIX matrot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//y軸回転行列
	XMVECTOR move = XMVector3TransformCoord(vFront, matrot);
	XMVECTOR vcam = { 0.0f,TPS_CAM_BIAS,TPS_CAM_BEHIND,0.0f };
	switch (cam_Type) {
	case FIXED_CAM:
		SetFixedCam();
		break;
	case TPS_CAM:
		XMFLOAT3 Tcampos = transform_.position_;
		Tcampos.y = Tcampos.y+ TPS_CAM_BIAS;
		Tcampos.z = Tcampos.z+TPS_CAM_BEHIND;
		XMFLOAT3 TcamTarget = transform_.position_;
		Camera::SetTarget(TcamTarget);
		Camera::SetPosition(Tcampos);
		break;
	case TPS_CAMROT:
		XMFLOAT3 TRcampos;
		vcam = XMVector3TransformCoord(vcam, matrot);//タンクの回転をカメラに反映
		XMStoreFloat3(&TRcampos, vpos + vcam);
		Camera::SetTarget(transform_.position_);
		Camera::SetPosition(TRcampos);
		break;
	case FPS_CAM:
		XMFLOAT3 camTarget;
		XMFLOAT3 campos=transform_.position_;
		campos.y = campos.y + FPS_CAM_BIAS;
		XMStoreFloat3(&camTarget, vpos + move);
		Camera::SetTarget(camTarget);
		Camera::SetPosition(campos);
		//SetFpsCam();
		break;
	}
	if (Input::IsKeyDown(DIK_C)) {
		//0,1,2..CAM_TYPE_MAX-1の順でcam_typeを変更していく
		cam_Type = (cam_Type + 1) % CAM_TYPE_MAX;
	}
	Debug::Log("CAMTYPE=");
	Debug::Log(CAMTYPES[cam_Type], true);
	if (Input::IsKey(DIK_A)) {//左回転
		transform_.rotate_.y -= 0.5f;
	}
	if (Input::IsKey(DIK_D)) {//右回転
		transform_.rotate_.y+=0.5f;
	}
	if (Input::IsKey(DIK_W)) {//前進
		vpos += moveSpeed * move;
		XMStoreFloat3(&transform_.position_, vpos);
	}
	if (Input::IsKey(DIK_S)) {//後退
		XMVECTOR vpos = XMLoadFloat3(&transform_.position_);
		vpos -= moveSpeed * vFront;
		XMStoreFloat3(&transform_.position_, vpos);
	}

	Debug::Log("Y angle=");
	Debug::Log(transform_.rotate_.y,true);//trueは改行するかどうか
	//レイキャストして、浮いてたら地面まで落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;//地面は０より下に作られている。そうじゃないときはもっと上から
	data.dir = { 0,-1,0 };
	Ground* gr = (Ground*)FindObject("Ground");
	Model::RayCast(gr->GetModelHandle(), &data);
	if (data.hit) {
		//地面（レイがヒットした位置）まで下げる
		transform_.position_.y =-data.dist;
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

void Tank::SetFixedCam()
{
	Camera::SetTarget(XMFLOAT3(0.0f, 0.0f, 0.0f));
	Camera::SetPosition(XMFLOAT3(0.0f, 20.0f, -30.0f));
}

void Tank::SetFpsCam()
{
	
}
