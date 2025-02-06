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

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, //����� �ؽ�ó �İ�ü
			nullptr,        // ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0�������� ���
			&vTemp,        // ����� �̹����� �߽� ��ǥ vec3 �ּ�, null�� ��� 0, 0 �̹��� �߽�
			nullptr,        // ��ġ ��ǥ�� ���� vec3 �ּ�, null�� ��� ��ũ�� �� 0, 0 ��ǥ ���    
			D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� �ʰ� ���� ���� ����
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
