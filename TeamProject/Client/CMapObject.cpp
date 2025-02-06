#include "pch.h"
#include "CMapObject.h"
#include "Include.h"
#include "CTextureMgr.h"
#include "CDevice.h"

CMapObject::CMapObject()
{
}

CMapObject::~CMapObject()
{
	Release();
}

HRESULT CMapObject::Initialize(void)
{
	Load_Object(L"../Data/20250207obj.dat");
    m_eRender = R_MAPOBJ;


	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
		L"../Assets/Map/object/object_deco_/object_deco_%d.png",
		TEX_MULTI, L"object", L"object_deco_", 25)))
	{
		ERR_MSG(L"object_deco_ Texture Insert Failed");
		//return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
		L"../Assets/Map/object/object_function_/object_function_%d.png",
		TEX_MULTI, L"object", L"object_function_", 14)))
	{
		ERR_MSG(L"object_function_ Texture Insert Failed");
		//return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
		L"../Assets/Map/object/object_furniture_/object_furniture_%d.png",
		TEX_MULTI, L"object", L"object_furniture_", 4)))
	{
		ERR_MSG(L"object_furniture_ Texture Insert Failed");
		//return E_FAIL;
	}


    return E_NOTIMPL;
}

int CMapObject::Update(void)
{
    return 0;
}

void CMapObject::Late_Update(void)
{
}

void CMapObject::Render(void)
{
	D3DXMATRIX matWorld, matScale, matTrans;
	for (auto& pObj : m_vecObject)
	{

		TCHAR	szBuf[MIN_STR] = L"";
		int		iIndex(0);

		int		iScrollX = int(-m_vScroll.x) / TILECX;
		int		iScrollY = int(-m_vScroll.y) / TILECY;

		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			pObj->vPos.x + m_vScroll.x,
			pObj->vPos.y + m_vScroll.y,
			0.f);

		matWorld = matScale * matTrans;

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		TCHAR szTexType[MAX_STR] = L"";
		switch (pObj->eObjType)
		{
		case MAPOBJ_DECO:
			lstrcpy(szTexType, L"object_deco_"); break;
			break;
		case MAPOBJ_FUNCTION:
			lstrcpy(szTexType, L"object_function_"); break;
			break;
		case MAPOBJ_FURNITURE:
			lstrcpy(szTexType, L"object_furniture_"); break;
			break;
		}
		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"object", szTexType, pObj->byDrawID);

		if (pTexInfo == nullptr)
		{
			continue;
		}
		float fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float fCenterY = pTexInfo->tImgInfo.Height;

		D3DXVECTOR3 vTemp{ fCenterX, fCenterY, 0.f };

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, //출력할 텍스처 컴객체
			nullptr,        // 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0기준으로 출력
			&vTemp,        // 출력할 이미지의 중심 좌표 vec3 주소, null인 경우 0, 0 이미지 중심
			nullptr,        // 위치 좌표에 대한 vec3 주소, null인 경우 스크린 상 0, 0 좌표 출력    
			D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 섞지 않고 원본 색상 유지
	}


}

void CMapObject::Release(void)
{
	for_each(m_vecObject.begin(), m_vecObject.end(), [](auto& p)
	{	if (p)
		{
			delete p; p = nullptr;
		}});
	m_vecObject.clear();
	m_vecObject.shrink_to_fit();
}

HRESULT CMapObject::Load_Object(const TCHAR* pTilePath)
{

	HANDLE hFile = CreateFile(pTilePath,
		GENERIC_READ,
		0, 0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD	dwByte(0), dwStrByte(0);

	MAPOBJ pMapObj;
	ZeroMemory(&pMapObj, sizeof(MAPOBJ));

	while (true)
	{
		ReadFile(hFile, &pMapObj, sizeof(MAPOBJ), &dwByte, nullptr);

		if (0 == dwByte)
		{
			break;
		}
		MAPOBJ* pMObjtemp = new MAPOBJ;

		pMObjtemp->byDrawID = pMapObj.byDrawID;
		pMObjtemp->eObjType = pMapObj.eObjType;
		pMObjtemp->iTileIndex = pMapObj.iTileIndex;
		pMObjtemp->vPos = pMapObj.vPos;

		m_vecObject.push_back(pMObjtemp);
	}

	CloseHandle(hFile);
}
