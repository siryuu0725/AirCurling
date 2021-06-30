#include "Effect.h"

#include <d3dx9.h>

Effect* Effect::mp_instance = nullptr;

//インスタンス化関数
Effect* Effect::Instance()
{
	if (mp_instance == nullptr) { mp_instance = new Effect; }

	return mp_instance;
}

//初期化関数
void Effect::InitEffect()
{
	e_device = Graphics::Instance()->GetD3DDevice();

	window_size = GetWindowSize();

	// 描画用インスタンスの生成
	e_renderer = ::EffekseerRendererDX9::Renderer::Create(e_device, SpriteNum);

	// エフェクト管理用インスタンスの生成
	e_manager = ::Effekseer::Manager::Create(InstanceNum);

	// 描画用インスタンスから描画機能を設定
	e_manager->SetSpriteRenderer(e_renderer->CreateSpriteRenderer());
	e_manager->SetRibbonRenderer(e_renderer->CreateRibbonRenderer());
	e_manager->SetRingRenderer(e_renderer->CreateRingRenderer());
	e_manager->SetTrackRenderer(e_renderer->CreateTrackRenderer());
	e_manager->SetModelRenderer(e_renderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	e_manager->SetTextureLoader(e_renderer->CreateTextureLoader());
	e_manager->SetModelLoader(e_renderer->CreateModelLoader());

	e_camera_pos = ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f); //カメラの位置 
	e_eye_pos = ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f);    //注視点
	e_camera_up = ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f);  //カメラの上向きのベクトル
}

//エフェクト読み込み関数
void Effect::LoadEffect()
{
	efcs[HitEfc] = Effekseer::Effect::Create(e_manager, (const EFK_CHAR*)L"Res/Effect/reflection.efk");
	efcs[ResetEfc] = Effekseer::Effect::Create(e_manager, (const EFK_CHAR*)L"Res/Effect/respawn.efk");
	efcs[FallEfc] = Effekseer::Effect::Create(e_manager, (const EFK_CHAR*)L"Res/Effect/fall.efk");
	efcs[GoalEfc] = Effekseer::Effect::Create(e_manager, (const EFK_CHAR*)L"Res/Effect/goal.efk");
}

//描画関数
void Effect::DrawEffect()
{
	e_manager->Draw();
}

//エフェクト再生関数
void Effect::PlayEffect(EffectType type_, float x_, float y_, float z_)
{
	e_handle = e_manager->Play(efcs[type_], x_, y_, z_);
}

//エフェクト描画開始関数
void Effect::StartEffect()
{
	//エフェクトの描画開始処理を行う。
	e_renderer->BeginRendering();
}

//エフェクト停止関数
void Effect::StopEffect()
{
	//エフェクトの停止
	e_manager->StopEffect(e_handle);
}

//エフェクト終了関数
void Effect::EndEffect()
{
	//エフェクトの描画終了処理を行う。
	e_renderer->EndRendering();
}

//エフェクト更新関数
void Effect::UpdateEffect(Camera* camera_)
{
	Camera::CameraInfo camera_info;

	camera_->GetCameraInfo(camera_info);

	//Shotモード時
	if (camera_info.m_is_shotmode == true)
	{
		e_camera_pos.X = camera_info.m_pos.x;
		e_camera_pos.Y = camera_info.m_pos.y;
		e_camera_pos.Z = camera_info.m_pos.z;

		e_eye_pos.X = camera_info.m_eye_pos.x;
		e_eye_pos.Y = camera_info.m_eye_pos.y;
		e_eye_pos.Z = camera_info.m_eye_pos.z;
	}
	//Viewモード時
	else
	{
		e_camera_pos.X = camera_info.m_pos.x;
		e_camera_pos.Y = camera_info.m_pos.y;
		e_camera_pos.Z = camera_info.m_pos.z;

		e_eye_pos.X = camera_info.m_eye_pos.x;
		e_eye_pos.Y = camera_info.m_eye_pos.y;
		e_eye_pos.Z = camera_info.m_eye_pos.z;
	}

	e_camera_up = ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f);

	e_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(D3DXToRadian(EffectCameraAngleofView), window_size.x / window_size.y, 1.0f, 20000.0f));
	e_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(e_camera_pos, e_eye_pos, e_camera_up));

	e_manager->Update();

}

//エフェクト解放関数
void Effect::ReleaseEffect()
{
	// エフェクトの破棄
	for (__int8 i = 0; i < (__int8)EffectType::MaxNum; i++)
	{
		//ES_SAFE_RELEASE(efcs[i]);
		efcs[i]->Release();
	}

	// 先にエフェクト管理用インスタンスを破棄
	e_manager->Destroy();

	// 次に描画用インスタンスを破棄
	e_renderer->Destroy();
}

//Instance解放関数(Debug用)
void Effect::ReleaseInstance()
{
	delete mp_instance;
	mp_instance = nullptr;
}


