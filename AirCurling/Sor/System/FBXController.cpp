﻿#include "FBXController.h"


FbxController* FbxController::p_instance = 0;

FbxController* FbxController::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new FbxController();
	}

	return p_instance;
}

//!コンストラクタ
FbxController::FbxController()
{
	if (m_Fbx == nullptr)
	{
		m_Fbx = new Fbx();
	}
}

//!デスクトラクタ
FbxController::~FbxController()
{
	if (m_Fbx != nullptr)
	{
		delete m_Fbx;
		m_Fbx = nullptr;
	}
}


//!Meshデータセット関数
FBXMeshData FbxController::LoadFbxMesh(std::string key_, const char* pFilename_)
{
	m_MeshData[key_] = m_Fbx->LoadFbx(pFilename_);

	return m_MeshData[key_];
}

//!メッシュデータ読み込みまとめ関数
void FbxController::LoadFbx()
{
	LoadFbxMesh("skydome", "Res/FBX/sky_dome.fbx");
	LoadFbxMesh("skyfloor", "Res/FBX/SkyFloor.fbx");
	LoadFbxMesh("stage", "Res/FBX/StageFloor.fbx");
	LoadFbxMesh("pac", "Res/FBX/pac.fbx");
	LoadFbxMesh("reset", "Res/FBX/reset2.fbx");
	LoadFbxMesh("stop", "Res/FBX/stop.fbx");
	LoadFbxMesh("goal", "Res/FBX/goal.fbx");
	LoadFbxMesh("rectblock", "Res/FBX/RectBlock.fbx");
	LoadFbxMesh("circleblock", "Res/FBX/CircleBlock.fbx");
	LoadFbxMesh("direction", "Res/FBX/Direction.fbx");
}

//!メッシュデータ解放関数
void FbxController::ReleaseFbxMesh(std::string key_)
{
	if (&m_MeshData[key_] == nullptr)return;

	m_Fbx->ReleaseModel(&m_MeshData[key_].fbxinfo);
}

//!Fbfファイル描画関数
void FbxController::DrawFbx(std::string key_, D3DXMATRIX& mat_world_)
{
	m_MeshData[key_].fbxinfo.world = mat_world_;

	if (&m_MeshData[key_] == nullptr)return;

	m_Fbx->DrawModel(&m_MeshData[key_].fbxinfo);
}


bool FbxController::HasKey(std::string key_)
{
	auto itr = m_MeshData.find(key_);
	if (itr != m_MeshData.end())
	{
		return true;
	}
	return false;
}
