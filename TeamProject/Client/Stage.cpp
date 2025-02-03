#include "pch.h"
#include "Stage.h"
#include "CTextureMgr.h"
#include "ObjMgr.h"
#include "MyTerrain.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
		L"../Texture/Stage/Terrain/Tile/Tile%d.png", 
		TEX_MULTI, L"Terrain", L"Tile", 36)))
	{
		ERR_MSG(L"Tile Img Insert Failed");
		return E_FAIL;
	}	

	CObj*	pObj = new CMyTerrain;
	
	if (nullptr == pObj)
		return E_FAIL;
	
	pObj->Initialize();
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::TERRAIN, pObj);

	// 플레이어
	/*pObj = new CPlayer;
	if (nullptr == pObj)
		return E_FAIL;

	pObj->Initialize();

	CObjMgr::Get_Instance()->Add_Object(CObjMgr::PLAYER, pObj);*/
	
	return S_OK;
}

void CStage::Update_Scene()
{
	CObjMgr::Get_Instance()->Update();
}

void CStage::Late_Update_Scene()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render_Scene()
{
	CObjMgr::Get_Instance()->Render();
}

void CStage::Release_Scene()
{
}
