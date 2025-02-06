#include "pch.h"
#include "CMapObject.h"

HRESULT CMapObject::Initialize(void)
{
	Load_Object(L"");
    m_eRender = R_MAPOBJ;
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
}

void CMapObject::Release(void)
{
}

HRESULT CMapObject::Load_Object(const TCHAR* pTilePath)
{
	HANDLE hFile = CreateFile(pTilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD	dwByte(0);
	MAPOBJ	pMapobj;
	ZeroMemory(&pMapobj, sizeof(MAPOBJ));

	while (true)
	{
		ReadFile(hFile, &pMapobj, sizeof(MAPOBJ), &dwByte, nullptr);

		if (0 == dwByte)
		{
			break;
		}
		MAPOBJ* pMapobjtemp = new MAPOBJ;

		pMapobjtemp->vPos = pMapobj.vPos;
		pMapobjtemp->vSize = pMapobj.vSize;
		pMapobjtemp->vTileSize = pMapobj.vTileSize;
		pMapobjtemp->iTileIndex = pMapobj.iTileIndex;
		pMapobjtemp->eObjType = pMapobj.eObjType;
		pMapobjtemp->byDrawID = pMapobj.byDrawID;

		m_vecObject.push_back(pMapobjtemp);
	}

	CloseHandle(hFile);
}
