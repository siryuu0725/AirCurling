#include "DirectGraphics.h"
#include "Window.h"
#include "FBX.h"

Graphics* Graphics::mp_instance = nullptr;

//インスタンス化関数
Graphics* Graphics::Instance()
{
	if (mp_instance == nullptr) { mp_instance = new Graphics; }

	return mp_instance;
}

//描画情報初期化まとめ関数
bool Graphics::InitGraphics()
{
	D3DPRESENT_PARAMETERS present_param;
	ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

	//インターフェース作成
	if (CreateGraphicsInterface() == false)
	{
		return false;
	}
	//デバイス作成
	if (CreateGraphicsDevice(&present_param) == false)
	{
		return false;
	}
	//ビューポート設定
	if (SetUpViewPort(&present_param) == false)
	{
		return false;
	}
	//文字描画用デバイス作成
	if (CreateFontDevice() == false)
	{
		return false;
	}

	return true;
}

//インターフェース作成関数
bool Graphics::CreateGraphicsInterface()
{
	// インターフェース作成
	g_interface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_interface == nullptr)
	{
		return false;
	}

	return true;
}

//デバイス作成関数
bool Graphics::CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param_)
{
	present_param_->BackBufferCount = 1;
	present_param_->BackBufferFormat = D3DFMT_A8R8G8B8;
	present_param_->Windowed = true;
	present_param_->SwapEffect = D3DSWAPEFFECT_DISCARD;
	present_param_->EnableAutoDepthStencil = true;
	present_param_->MultiSampleType = D3DMULTISAMPLE_NONE;
	present_param_->MultiSampleQuality = 0;
	present_param_->BackBufferWidth = static_cast<UINT>(1920.0f);
	present_param_->BackBufferHeight = static_cast<UINT>(1080.0f);
	// デプスとステンシルバッファのフォーマット設定
	present_param_->AutoDepthStencilFormat = D3DFMT_D24S8;

	// もしフルスクリーンなら
	if (present_param_->Windowed == false)
	{
		present_param_->FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	}

	if (FAILED(g_interface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		present_param_,
		&g_device)))
	{
		return false;
	}

	return true;
}

//ビューポート設定関数
bool Graphics::SetUpViewPort(D3DPRESENT_PARAMETERS* present_param_)
{
	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	view_port.X = 0;
	view_port.Y = 0;
	view_port.Width = present_param_->BackBufferWidth;
	view_port.Height = present_param_->BackBufferHeight;
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	if (FAILED(g_device->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

//描画情報解放関数
void  Graphics::ReleaseGraphics()
{
	g_device->Release();
	g_device = nullptr;

	g_interface->Release();
	g_interface = nullptr;

	for (__int8 i = 0; i < (__int8)Graphics::FontSize::FontSizeMax; i++)
	{
		g_font_list[i]->Release();
		g_font_list[i] = nullptr;
	}
}

//α値設定関数
void Graphics::SetRenderMode(bool enableAlpa_)
{
	IDirect3DDevice9* pDevice = GetD3DDevice();
	// αが無向な場合入力されたカラーをそのまま使う
	DWORD srcColorblend = D3DBLEND_ONE;
	DWORD dstColorblend = D3DBLEND_ZERO;
	if (enableAlpa_)
	{
		// αが有効な場合はα値をカラーに影響させる
		srcColorblend = D3DBLEND_SRCALPHA;
		dstColorblend = D3DBLEND_INVSRCALPHA;
		// αテストでα値が0の場合は描画をしないように設定
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}
	// αブレンドとαテストの有無を設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, enableAlpa_);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, enableAlpa_);
}

//描画開始関数
void Graphics::DrawStart()
{
	if (g_device != nullptr)
	{
		g_device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		g_device->BeginScene();
	}
	
}

//描画終了関数
void Graphics::DrawEnd()
{
	if (g_device != nullptr)
	{
		g_device->EndScene();
		g_device->Present(nullptr, nullptr, nullptr, nullptr);
	}
}

//テクスチャ読み込み関数
bool Graphics::LoadTexture(const char* file_name_, TextureData* texture_)
{
	D3DXIMAGE_INFO info;

	D3DXGetImageInfoFromFileA(file_name_, &info);

	if (FAILED(D3DXCreateTextureFromFileExA(g_device,
		file_name_,
		info.Width,
		info.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x0000ff00,
		nullptr,
		nullptr,
		&texture_->Texture)))
	{
		return false;
	}
	else
	{
		D3DSURFACE_DESC desc;

		if (FAILED(texture_->Texture->GetLevelDesc(0, &desc)))
		{
			texture_->Texture->Release();
			texture_->Texture = NULL;
			return false;
		}
		texture_->Width = (float)desc.Width;
		texture_->Height = (float)desc.Height;
	}
	return true;
}

//テクスチャ描画関数
void Graphics::DrawTexture(TextureData* texture_, D3DXVECTOR2 pos_)
{
	CustomVertex vertex[4] =
	{
		// 左上頂点
		{ pos_.x, pos_.y, 0.0f, 1.0f, 0.0f, 0.0f },
		// 右上頂点
		{ pos_.x + texture_->Width, pos_.y, 0.0f, 1.0f, 1.0f, 0.0f },
		// 右下頂点
		{ pos_.x + texture_->Width, pos_.y + texture_->Height, 0.0f, 1.0f, 1.0f, 1.0f },
		// 左下頂点
		{ pos_.x, pos_.y + texture_->Height, 0.0f, 1.0f, 0.0f, 1.0f },
	};

	if (g_device != nullptr)
	{
		g_device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

		g_device->SetTexture(0, texture_->Texture);

		g_device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(CustomVertex));
	}
}

//テクスチャ描画関数(UV指定用)
void Graphics::DrawUVTexture(TextureData* texture_, D3DXVECTOR2 pos_, float sprite_width_, float sprite_height_, float tu_, float tv_)
{
	float Ttu = sprite_width_ / texture_->Width;
	float Ttv = sprite_height_ / texture_->Height;

	CustomVertex vertex[4] =
	{
		{ pos_.x, pos_.y, 0.0f, 1.0f, tu_, tv_ },
		{ pos_.x + sprite_width_, pos_.y, 0.0f, 1.0f, tu_ + Ttu , tv_ },
		{ pos_.x + sprite_width_, pos_.y + sprite_height_, 0.0f, 1.0f, tu_ + Ttu, tv_ + Ttv},
		{ pos_.x, pos_.y + sprite_height_, 0.0f, 1.0f, tu_, tv_ + Ttv },
	};

	if (g_device != nullptr)
	{
		// 頂点構造の指定
		g_device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

		g_device->SetTexture(0, texture_->Texture);

		g_device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(CustomVertex));
	}
}

//テクスチャ描画関数(テクスチャ回転用)
void Graphics::DrawRotTexture(TextureData* texture_, D3DXVECTOR2 lefttop_pos_, D3DXVECTOR2 righttop_pos_, D3DXVECTOR2 leftdown_pos_, D3DXVECTOR2 rightdown_pos_)
{

	CustomVertex vertex[4] =
	{
		// 左上頂点
		{ lefttop_pos_.x, lefttop_pos_.y, 0.0f, 1.0f, 0.0f, 0.0f },
		// 右上頂点
		{ righttop_pos_.x, righttop_pos_.y, 0.0f, 1.0f, 1.0f, 0.0f },
		// 右下頂点
		{ rightdown_pos_.x, rightdown_pos_.y, 0.0f, 1.0f, 1.0f, 1.0f },
		// 左下頂点
		{ leftdown_pos_.x, leftdown_pos_.y, 0.0f, 1.0f, 0.0f, 1.0f },
	};


	if (g_device != nullptr)
	{
		// 頂点構造の指定
		g_device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

		g_device->SetTexture(0, texture_->Texture);

		g_device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(CustomVertex));
	}
}

// テクスチャーの解放
void Graphics::ReleaseTexture(TextureData* texture_data_)
{
	if (texture_data_ == nullptr)
	{
		return;
	}
	else
	{
		texture_data_->Texture->Release();
		texture_data_->Texture = nullptr;
	}
}

//文字描画
void Graphics::DrawFont(D3DXVECTOR2 pos_, const char* text_, FontSize font_type_, FontColor color_)
{
	RECT rect =
	{
		(long)pos_.x,
		(long)pos_.y,
		(long)pos_.x + 400,
		(long)pos_.y + 200,
	};

	int r, g, b;
	r = g = b = 255;

	if (color_ == FontColor::Black)
	{
		r = g = b = 0;
	}
	else if (color_ == FontColor::Red)
	{
		r = 255;
		g = b = 0;
	}
	else if (color_ == FontColor::Yellow)
	{
		r = 255;
		g = 225;
		b = 0;
	}

	g_font_list[font_type_]->DrawTextA(
		nullptr,
		text_,
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_XRGB(r, g, b)
	);
}

//文字描画用デバイス作成関数
bool Graphics::CreateFontDevice()
{
	int size_list[] =
	{
		SMALL_FONT_SIZE,
		REGULAR_FONT_SIZE,
		LARGE_FONT_SIZE
	};

	for (int i = 0; i < FontSize::FontSizeMax; i++)
	{
		if (FAILED(D3DXCreateFont(g_device,
			size_list[i],
			size_list[i] / 2,
			FW_REGULAR,
			0,
			FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			TEXT("ＭＳ　Ｐゴシック"),
			&g_font_list[i])))
		{
			return false;
		}
	}

	return true;
}

//ライト設定関数
void Graphics::SetLight()
{
	D3DLIGHT9 light;
	D3DXVECTOR3 vec_direction(0, -1, 0);
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction.x = 0.0f;
	light.Direction.y = -0.5f;
	light.Direction.z = 0.2f;
	light.Diffuse.a = 1.0f;
	light.Diffuse.r = 0.8f;
	light.Diffuse.g = 0.8f;
	light.Diffuse.b = 0.8f;
	light.Ambient.a = 1.0f;
	light.Ambient.r = 0.5f;
	light.Ambient.g = 0.5f;
	light.Ambient.b = 0.5f;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vec_direction);
	light.Range = 200.0f;
	g_device->SetLight(0, &light);
	g_device->LightEnable(0, true);
	g_device->SetRenderState(D3DRS_LIGHTING, true);
}

void Graphics::ReleaseInstance()
{
	delete mp_instance;
	mp_instance = nullptr;
}
