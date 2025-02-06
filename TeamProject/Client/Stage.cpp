#include "pch.h"
#include "Stage.h"
#include "CTextureMgr.h"
#include "ObjMgr.h"
#include "MyTerrain.h"
#include "MyPlayer.h"
#include "Animal.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	//if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
	//	L"../Texture/Stage/Terrain/Tile/Tile%d.png", 
	//	TEX_MULTI, L"Terrain", L"Tile", 36)))
	//{
	//	ERR_MSG(L"Tile Img Insert Failed");
	//	return E_FAIL;
	//}	

	CObj*	pObj = new CMyTerrain;
	
	if (nullptr == pObj)
		return E_FAIL;
	
	pObj->Initialize();
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::TERRAIN, pObj);

	CObj* pPlayer = new CMyPlayer;
	pPlayer->Initialize();
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::PLAYER, pPlayer);

	AddAnimal();
	AddMapObject();
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

void CStage::AddAnimal()
{
	HANDLE hFile = CreateFile(L"../Data/Animal.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD	dwByte(0), dwStrByte(0);

	while (true)
	{
		// key 값 로드

		ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

		TCHAR* pName = new TCHAR[dwStrByte];

		ReadFile(hFile, pName, dwStrByte, &dwByte, nullptr);

		// value 값 로드
		ANIMALDATA temp;
		ReadFile(hFile, &temp, sizeof(ANIMALDATA), &dwByte, nullptr);

		if (0 == dwByte)
		{
			delete[] pName;
			break;
		}
		delete[] pName;

		CObj* pAnimal = new CAnimal;
		dynamic_cast<CAnimal*>(pAnimal)->Set_Data(temp);
		pAnimal->Initialize();
		CObjMgr::Get_Instance()->Add_Object(CObjMgr::ANIMAL, pAnimal);

	}

	CloseHandle(hFile);
}

void CStage::AddMapObject()
{


}
