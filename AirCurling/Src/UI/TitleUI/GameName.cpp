#include "GameName.h"

//初期化関数
void GameName::Init()
{
	//座標初期化
	m_titlename_info.m_ui_pos = m_external_pos[(__int8)GameNameTexCategory::Name];

	//テクスチャ読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/GameTitle.png", &m_titlename_info.m_ui_tex);
}

//描画情報送信関数
void GameName::Draw()
{
	TitleItem::ItemInfo item_info;
	mp_title_item->GetTitleItemInfo(item_info);

	if (item_info.m_is_start == false && item_info.m_is_help == false)
	{
		//背景
		Graphics::Instance()->DrawTexture(&m_titlename_info.m_ui_tex, m_titlename_info.m_ui_pos);
	}

}

//テクスチャ解放関数
void GameName::ReleaseTex()
{
	m_titlename_info.m_ui_tex.Texture->Release();
	m_titlename_info.m_ui_tex.Texture = nullptr;
}
