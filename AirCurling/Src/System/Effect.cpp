#include "Effect.h"
#include "Graphics.h"

#include <d3dx9.h>

Effect* Effect::p_instance = nullptr;

//!インスタンス化関数
Effect* Effect::Instance()
{
	if (p_instance == nullptr) { p_instance = new Effect; }

	return p_instance;
}

//!初期化関数
void Effect::InitEffect()
{
	//databank = DataBank::Instance();

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

	e_position = ::Effekseer::Vector3D(0.0f, 30.0f, 0.0f);
}

//!エフェクト読み込み関数
void Effect::LoadEffect()
{
	hit_efc = Effekseer::Effect::Create(e_manager, (const EFK_CHAR*)L"Res/Effect/reflection.efk");
	fall_efc = Effekseer::Effect::Create(e_manager, (const EFK_CHAR*)L"Res/Effect/respawn.efk");
	reset_efc = Effekseer::Effect::Create(e_manager, (const EFK_CHAR*)L"Res/Effect/fall.efk");
	goal_efc = Effekseer::Effect::Create(e_manager, (const EFK_CHAR*)L"Res/Effect/goal.efk");
}

//!描画関数
void Effect::DrawEffect()
{
	e_manager->Draw();
}

//!エフェクト再生関数
void Effect::PlayEffect(EffectType type_, float x_, float y_, float z_)
{
	//!ブロック衝突時
	if (type_ == EffectType::HitEfc)
	{
		e_handle = e_manager->Play(hit_efc, x_, y_, z_);
	}
	//!死亡時
	else if (type_ == EffectType::ResetEfc)
	{
		e_handle = e_manager->Play(reset_efc, x_, y_, z_);
	}
	//!落下時
	else if (type_ == EffectType::FallEfc)
	{
		e_handle = e_manager->Play(fall_efc, x_, y_, z_);
	}
	//!ゴール時
	else if (type_ == EffectType::GoalEfc)
	{
		e_handle = e_manager->Play(goal_efc, x_, y_, z_);
	}
}

//!エフェクト描画開始関数
void Effect::StartEffect()
{
	//!エフェクトの描画開始処理を行う。
	e_renderer->BeginRendering();
}

//!エフェクト停止関数
void Effect::StopEffect()
{
	//!エフェクトの停止
	e_manager->StopEffect(e_handle);
}

//!エフェクト終了関数
void Effect::EndEffect()
{
	//!エフェクトの描画終了処理を行う。
	e_renderer->EndRendering();
}

//!エフェクト更新関数
void Effect::UpdateEffect(Camera* camera_)
{
	Camera::CameraInfo camera_info;

	camera_->GetCameraInfo(camera_info);

	//!Shotモード時
	if (camera_info.m_is_shotmode == true)
	{
		e_camera_pos.X = camera_info.m_pos.x;
		e_camera_pos.Y = camera_info.m_pos.y;
		e_camera_pos.Z = camera_info.m_pos.z;

		e_eye_pos.X = camera_info.m_eye_pos.x;
		e_eye_pos.Y = camera_info.m_eye_pos.y;
		e_eye_pos.Z = camera_info.m_eye_pos.z;
	}
	//!Viewモード時
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

//!エフェクト解放関数
void Effect::ReleaseEffect()
{
	// エフェクトの破棄
	ES_SAFE_RELEASE(hit_efc);
	ES_SAFE_RELEASE(fall_efc);
	ES_SAFE_RELEASE(reset_efc);


	// 先にエフェクト管理用インスタンスを破棄
	e_manager->Destroy();

	// 次に描画用インスタンスを破棄
	e_renderer->Destroy();
}


