#include "Camera.h"
#include "../System/Inputter.h"
#include "../Object/Player.h"
#include "../System/Window.h"

//初期化関数
void Camera::Init(std::string stage_str_)
{
	//外部データ読み込み
	LoadExternalInfo(stage_str_);

	m_camerainfo.m_pos = m_camera_externalinfo.m_pos;   //座標

	m_camerainfo.m_eye_pos = m_camera_externalinfo.m_eye_pos; //注視点

	m_camerainfo.m_camera_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //上向きベクトル

	m_camerainfo.m_yaw = 0.0f;    //X軸回転用

	m_camerainfo.m_speed = 1.0f;  //移動スピード

	m_camerainfo.m_packup = m_camera_externalinfo.m_packup; //パックの位置からどれだけ離れているか

	m_camerainfo.m_is_shotmode = false;  //打つモードかどうか
	m_camerainfo.m_is_operation = false; //操作可能フラグ


	D3DXMatrixIdentity(&m_camerainfo.mat_view);

	CreateFrustum(); //視錐台関数
}

//外部データ読み込み関数
void Camera::LoadExternalInfo(std::string stage_str_)
{
	FILE* fp = nullptr;

	std::string file_name = "Res/ObjectData/" + stage_str_ + "CameraData.dat";

	//ファイル読み込み
	fopen_s(&fp, file_name.c_str(), "rb");

	if (fp != nullptr)
	{
		//書き込む
		fread(&m_camera_externalinfo, sizeof(CameraExternalInfo), 1, fp);

		//ファイルクローズ
		fclose(fp);
	}
}

//視錐台関数
void Camera::CreateFrustum()
{
	D3DXMATRIX mat_proj;
	D3DXMatrixIdentity(&mat_proj);

	//射影座標変換用の行列算出 start
	D3DVIEWPORT9 vp;
	Graphics::Instance()->GetD3DDevice()->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	//視錐台の作成
	D3DXMatrixPerspectiveFovLH(
		&mat_proj,
		D3DXToRadian(AngleofView),	//画角
		aspect,		//アスペクト比
		Near,		//near
		Far);	    //far
	Graphics::Instance()->GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &mat_proj);
}

//更新関数
void Camera::Update(D3DXVECTOR3 player_pos_)
{
	//操作可能判定
	if (m_camerainfo.m_is_operation == true)
	{
		Move(player_pos_);
	}

	//ビュー座標変換用の行列算出 start
	D3DXVECTOR3 camera_pos(m_camerainfo.m_pos.x, m_camerainfo.m_pos.y, m_camerainfo.m_pos.z);	                //カメラ位置
	D3DXVECTOR3 eye_pos(m_camerainfo.m_eye_pos.x, m_camerainfo.m_eye_pos.y, m_camerainfo.m_eye_pos.z);		//注視点
	D3DXVECTOR3 up_vector(m_camerainfo.m_camera_up.x, m_camerainfo.m_camera_up.y, m_camerainfo.m_camera_up.z);  //カメラの向き;
	D3DXMatrixLookAtLH(&m_camerainfo.mat_view,
		&camera_pos,				//カメラ座標
		&eye_pos,					//注視点座標
		&up_vector);				//カメラの上の向きのベクトル

	Graphics::Instance()->GetD3DDevice()->SetTransform(D3DTS_VIEW, &m_camerainfo.mat_view);
}

//カメラ移動関数
void Camera::Move(D3DXVECTOR3 player_pos_)
{
	//カメラの前向きベクトルを出す
	D3DXVECTOR3 forward(0.0f, 0.0f, 0.0f);
	m_camerainfo.m_forward = m_camerainfo.m_eye_pos - m_camerainfo.m_pos;

	//ベクトルの正規化
	D3DXVec3Normalize(&m_camerainfo.m_forward, &m_camerainfo.m_forward);

	//カメラの左向きのベクトル
	//前向きのベクトルに直角なベクトルを算出する
	D3DXVECTOR3 left(m_camerainfo.m_forward.z, m_camerainfo.m_forward.y, m_camerainfo.m_forward.x);

	//モード切り替え判定
	ModeChange(player_pos_);

	//shotモード(打つ)時
	if (m_camerainfo.m_is_shotmode == true)
	{
		//!座標更新(プレイヤーの上についてくる形)
		m_camerainfo.m_pos.x = player_pos_.x;
		m_camerainfo.m_pos.y = player_pos_.y + m_camerainfo.m_packup; //プレイヤーの上にくるようにずらす
		m_camerainfo.m_pos.z = player_pos_.z;

		//注視点更新
		m_camerainfo.m_eye_pos.y = -27.8f;

		//注視点移動
		RotEyePos();

	}
	//viewモード(見る)時
	else
	{
		//左移動
		if (Inputter::Instance()->GetKey(Inputter::AKey))
		{
			m_camerainfo.m_pos.x -= m_camerainfo.m_speed;
			m_camerainfo.m_eye_pos.x -= m_camerainfo.m_speed;
		}
		//右移動
		else if (Inputter::Instance()->GetKey(Inputter::DKey))
		{
			m_camerainfo.m_pos.x += m_camerainfo.m_speed;
			m_camerainfo.m_eye_pos.x += m_camerainfo.m_speed;
		}
		//上移動
		else if (Inputter::Instance()->GetKey(Inputter::WKey))
		{
			m_camerainfo.m_pos.z += m_camerainfo.m_speed;
			m_camerainfo.m_eye_pos.z += m_camerainfo.m_speed;
		}
		//下移動
		else if (Inputter::Instance()->GetKey(Inputter::SKey))
		{
			m_camerainfo.m_pos.z -= m_camerainfo.m_speed;
			m_camerainfo.m_eye_pos.z -= m_camerainfo.m_speed;
		}
	}

#pragma endregion
}

//カメラ回転関数
void Camera::RotEyePos()
{
	SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);

	//ここでカメラ感度変更可能
	m_camerainfo.m_yaw += (Inputter::Instance()->GetMousePos().x - (GetWindowSize().x / 2)) / GetWindowSize().x * CameraSensitivity;

	m_camerainfo.m_eye_pos.x = m_camerainfo.m_pos.x + sinf(D3DXToRadian(m_camerainfo.m_yaw));
	m_camerainfo.m_eye_pos.z = m_camerainfo.m_pos.z + cosf(D3DXToRadian(m_camerainfo.m_yaw));
}

//モード切替関数
void Camera::ModeChange(D3DXVECTOR3 player_pos_)
{
	//切り替えキーが押された場合
	if (Inputter::Instance()->GetKeyDown(Inputter::FKey))
	{
		if (m_camerainfo.m_is_shotmode == false)
		{
			m_camerainfo.m_is_shotmode = true;
		}
		else
		{
			m_camerainfo.m_is_shotmode = false;

			m_camerainfo.m_pos.y = 30.0f;  //カメラの位置をプレイヤーから上空に移動
			m_camerainfo.m_eye_pos = D3DXVECTOR3(player_pos_.x, m_camera_externalinfo.m_eye_pos.y, player_pos_.z + 1.0f); //!注視点
			m_camerainfo.m_eye_pos.y = -50.0f; //真下を向くように設定

		}
	}
}
