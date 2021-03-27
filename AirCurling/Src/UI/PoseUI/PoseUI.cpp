#include "PoseUI.h"
#include "../../Utility/Collision/Collision.h"
#include "../../System/Inputter.h"

//初期化関数
void PoseUI::Init()
{
	if (mp_item == nullptr) { mp_item = new PoseItemUI; }
	if (mp_bg == nullptr) { mp_bg = new PoseBG(mp_item); }

	//外部データ読み込み
	LoadPoseUIExternalInfo();

	//外部データセット
	SetUIPos();

	//各UIを配列でまとめる
	UIBase* ui[PoseUICategoryNum] =
	{ mp_bg ,mp_item };
	for (int i = 0; i < PoseUICategoryNum; i++)
	{
		ui[i]->Init(); //初期化
	}

	m_poseui_info.m_select = false;
	m_poseui_info.m_continue = false;
	m_poseui_info.m_end = false;
	m_poseui_info.m_help = false;
}

//外部データセット関数
void PoseUI::SetUIPos()
{
	mp_bg->SetUIPos(m_poseui_externalinfo[(__int8)PoseUICategory::BG].m_pos,
		m_poseui_externalinfo[(__int8)PoseUICategory::HelpBG].m_pos);

	mp_item->SetUIPos(m_poseui_externalinfo[(__int8)PoseUICategory::Continue].m_pos,
		m_poseui_externalinfo[(__int8)PoseUICategory::End].m_pos,
		m_poseui_externalinfo[(__int8)PoseUICategory::Help].m_pos,
		m_poseui_externalinfo[(__int8)PoseUICategory::Select].m_pos);

}

//外部データ読み込み関数
void PoseUI::LoadPoseUIExternalInfo()
{
	FILE* fp = NULL;

	fopen_s(&fp, "Res/UIData/PoseUIData.dat", "rb");

	if (fp != nullptr)
	{
		fread(&m_ui_num, sizeof(m_ui_num), 1, fp);

		//書き込む
		fread(&m_poseui_externalinfo, sizeof(UIExternalInfo), m_ui_num, fp);

		//ファイルクローズ
		fclose(fp);
	}
}

//更新関数
void PoseUI::Update()
{
	mp_item->Update();

	PoseItemUI::PoseItemInfo item_info;
	mp_item->GetPoseItemInfo(item_info);
	m_poseui_info.m_continue = item_info.m_continue;
	m_poseui_info.m_end = item_info.m_end;
	m_poseui_info.m_help = item_info.m_help;
}

//描画情報送信関数
void PoseUI::Draw()
{
	//各UIを配列でまとめる
	UIBase* ui[PoseUICategoryNum] =
	{ mp_bg ,mp_item };

	for (int i = 0; i < PoseUICategoryNum; i++)
	{
		ui[i]->Draw();
	}
}

//テクスチャ解放関数
void PoseUI::ReleaseTex()
{
	//各UIを配列でまとめる
	UIBase* ui[PoseUICategoryNum] =
	{ mp_bg ,mp_item };

	for (int i = 0; i < PoseUICategoryNum; i++)
	{
		ui[i]->ReleaseTex();
	}
}
