#include "pch.h"
#include "MyTerrain.h"
#include "CDevice.h"
#include "CTextureMgr.h"
#include "TimeMgr.h"


CMyTerrain::CMyTerrain()
{
}

CMyTerrain::~CMyTerrain()
{
	Release();
}

HRESULT CMyTerrain::Initialize(void)
{
	m_vecTile.reserve(TILEX * TILEY);

	if (FAILED(Load_Tile(L"../Data/Map.dat")))
	{
		return E_FAIL;
	}

	m_wstrObjKey = L"Terrain";
	m_wstrStateKey = L"Tile";

	return S_OK;
}

int CMyTerrain::Update(void)
{
	
	if (0.f > Get_Mouse().x)
		m_vScroll.x += 5.f * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (WINCX < Get_Mouse().x)
		m_vScroll.x -= 5.f * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (0.f > Get_Mouse().y)
		m_vScroll.y += 5.f * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (WINCY < Get_Mouse().y)
		m_vScroll.y -= 5.f * CTimeMgr::Get_Instance()->Get_TimeDelta();

	return 0;
}

void CMyTerrain::Late_Update(void)
{


}

void CMyTerrain::Render(void)
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR	szBuf[MIN_STR] = L"";
	int		iIndex(0);

	int		iScrollX = int(-m_vScroll.x) / TILECX;
	int		iScrollY = int(-m_vScroll.y) / (TILECY / 2);

	int		iMaxX = WINCX / TILECX;
	int		iMaxY = WINCY / (TILECY / 2);

	for (int i = iScrollY; i < iScrollY + iMaxY; ++i)
	{
		for(int j = iScrollX; j < iScrollX + iMaxX; ++j)
		{
			int			iIndex = i * TILEX + j;

			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;


			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
			D3DXMatrixTranslation(&matTrans,
				m_vecTile[iIndex]->vPos.x + m_vScroll.x,
				m_vecTile[iIndex]->vPos.y + m_vScroll.y,
				0.f);

			matWorld = matScale * matTrans;

			CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

			const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), 
				m_vecTile[iIndex]->byDrawID);

			float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
			float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

			D3DXVECTOR3	vTemp = { fCenterX, fCenterY, 0.f };

			CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
				nullptr, // 출력할 이미지 영역의 RECT 주소, NULL인 경우 0, 0 기준으로 출력
				&vTemp, // 출력할 이미지의 중심 좌표, VEC3주소, NULL 인 경우 0, 0이 중심 좌표
				nullptr, // 텍스처를 출력할 위치 좌표, VEC3주소, 스크린상 0, 0 좌표에 출력
				D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상, 0xffffffff를 넘겨주면 원본색 유지

			swprintf_s(szBuf, L"%d", iIndex);
			CDevice::Get_Instance()->Get_Font()->DrawTextW(CDevice::Get_Instance()->Get_Sprite(), szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
			++iIndex;
		}
	}

	
	
}

void CMyTerrain::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
	m_vecTile.clear();
}

HRESULT CMyTerrain::Load_Tile(const TCHAR * pTilePath)
{
	HANDLE hFile = CreateFile(pTilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD	dwByte(0);

	TILE*	pTile = nullptr;

	while (true)
	{
		pTile = new TILE;

		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

		if (0 == dwByte)
		{
			Safe_Delete(pTile);
			break;
		}

		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);

	return S_OK;
}
