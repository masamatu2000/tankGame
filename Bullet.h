#pragma once
#include "Engine/GameObject.h"
#include"Engine/SphereCollider.h"
class Bullet :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Bullet(GameObject* parent);
	~Bullet(){}
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetMoveVector(const XMFLOAT3& move) { move_ = move; }
	void OnCollision(GameObject* pTarget) override;
private:
	int hModel_;
	XMFLOAT3 move_;//弾の進行方向
	SphereCollider* sc_;
};

