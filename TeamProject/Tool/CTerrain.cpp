#include "pch.h"
#include "CTerrain.h"
#include "CTextureMgr.h"
#include "CDevice.h"

CTerrain::CTerrain():m_bGrid(false), m_pMainView(nullptr)
{
	m_vecTile.reserve(TILEX * TILEY);
}

CTerrain::~CTerrain()
{
	Release();
}

HRESULT CTerrain::Initialize()
{
	Initialize_TileTexture();

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			TILE* pTile = new TILE;
			ZeroMemory(pTile, sizeof(TILE));
			float    fY = TILECY * i + (TILECY / 2.f);
			float    fX = TILECX * j + (TILECX / 2.f);

			pTile->vPos = { fX, fY, 0.f };
			pTile->vSize = { (float)TILECX, (float)TILECY };
			pTile->byOption = 0;
			pTile->tObject[OPT_GROUND].bExist = true;
			for (int i = OPT_GROUND + 1; i < OPT_END; ++i) pTile->tObject[i].bExist = false;
			pTile->tObject[OPT_GROUND].byDrawID = 27;
			pTile->tObject[OPT_GROUND].eTileTerrain = TRN_DIRT;
			pTile->iIndex = i * TILEX + j;
			pTile->iParentIndex = 0;
			m_vecTile.push_back(pTile);
		}
	}
	return S_OK;
}

void CTerrain::Update()
{
}

void CTerrain::Render(float fZoomFactor, const CPoint& zoomCenter)
{
	D3DXMATRIX matWorld, matScale, matTrans;

	// 최소 확대/축소 비율 설정
	float minZoomFactor = 0.1f;
	float zoomFactor = max(fZoomFactor, minZoomFactor);

	for (auto pTile : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, zoomFactor, zoomFactor, 1.f);
		D3DXMatrixTranslation(&matTrans,
			(pTile->vPos.x - zoomCenter.x) * zoomFactor + zoomCenter.x,
			(pTile->vPos.y - zoomCenter.y) * zoomFactor + zoomCenter.y,
			pTile->vPos.z);

		matWorld = matScale * matTrans;

		RECT rc{};
		GetClientRect(m_pMainView->m_hWnd, &rc);

		float fX = WINCX / float(rc.right - rc.left);
		float fY = WINCY / float(rc.bottom - rc.top);

		Set_Ratio(&matWorld, fX, fY);

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		TCHAR szTexTerrain[MAX_STR] = L"";
		TCHAR szTexType[MAX_STR] = L"";

		int i(0);

		for (int iOp = 0; iOp < OPT_END; ++iOp)
		{
			// 렌더 순서 조절용 
			switch (iOp) { case 0: i = OPT_GROUND; break; case 1: i = OPT_DECO; break; case 2:i = OPT_WALL; break; case 3: i = OPT_ORE; break; }
			if (pTile->tObject[i].bExist)
			{
				// switch 더러우니 접어둘 것
				switch (i)
				{
				case OPT_GROUND:
					 lstrcpy(szTexType, L"ground"); break;
				case OPT_WALL:
					 lstrcpy(szTexType, L"wallbody"); break;
				case OPT_ORE:
					 lstrcpy(szTexType, L"ore"); break;
				case OPT_DECO:
					 lstrcpy(szTexType, L"deco"); break;
				default: break;
				}
				switch (pTile->tObject[i].eTileTerrain)
				{
				case TRN_DIRT:
					 lstrcpy(szTexTerrain, L"dirt"); break;
				case TRN_SAND:
					 lstrcpy(szTexTerrain, L"sand"); break;
				case TRN_NATURE:
					 lstrcpy(szTexTerrain, L"nature"); break;
				case TRN_STONE:
					 lstrcpy(szTexTerrain, L"stone"); break;
				case TRN_WATER:
					 lstrcpy(szTexTerrain, L"water"); break;
				default: break;
				}
				
				int iDrawID = pTile->tObject[i].byDrawID;
				if (i == OPT_WALL)
					iDrawID = 1;
				const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(szTexTerrain, szTexType, iDrawID);
				
				if (pTexInfo == nullptr)
				{
					 continue;
				}
				float fCenterX = pTexInfo->tImgInfo.Width / 2.f;
				float fCenterY = pTexInfo->tImgInfo.Height / 2.f;
				
				D3DXVECTOR3 vTemp{ fCenterX, fCenterY, 0.f };
				
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, //출력할 텍스처 컴객체
					 nullptr,        // 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0기준으로 출력
					 &vTemp,        // 출력할 이미지의 중심 좌표 vec3 주소, null인 경우 0, 0 이미지 중심
					 nullptr,        // 위치 좌표에 대한 vec3 주소, null인 경우 스크린 상 0, 0 좌표 출력    
					 D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 섞지 않고 원본 색상 유지
				if (i == OPT_WALL)
				{
					const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(szTexTerrain, L"wallhead", pTile->tObject[i].byDrawID);
					if (pTexInfo == nullptr)
					{
						continue;
					}
					float fCenterX = pTexInfo->tImgInfo.Width / 2.f;
					float fCenterY = pTexInfo->tImgInfo.Height / 2.f + pTexInfo->tImgInfo.Height;

					D3DXVECTOR3 vTemp{ fCenterX, fCenterY, 0.f };

					CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, //출력할 텍스처 컴객체
						nullptr,        // 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0기준으로 출력
						&vTemp,        // 출력할 이미지의 중심 좌표 vec3 주소, null인 경우 0, 0 이미지 중심
						nullptr,        // 위치 좌표에 대한 vec3 주소, null인 경우 스크린 상 0, 0 좌표 출력    
						D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 섞지 않고 원본 색상 유지
				}
				
			}
			//if (pTile->tObject[OPT_WALL].bExist)
			//{
			//	// 벽 머리 별개로 설치 
			//	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(szTexTerrain, L"wallhead", pTile->tObject[i].byDrawID);
			//	if (pTexInfo == nullptr)
			//	{
			//		continue;
			//	}
			//	float fCenterX = pTexInfo->tImgInfo.Width / 2.f;
			//	float fCenterY = pTexInfo->tImgInfo.Height / 2.f + pTexInfo->tImgInfo.Height;

			//	D3DXVECTOR3 vTemp{ fCenterX, fCenterY, 0.f };

			//	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, //출력할 텍스처 컴객체
			//		nullptr,        // 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0기준으로 출력
			//		&vTemp,        // 출력할 이미지의 중심 좌표 vec3 주소, null인 경우 0, 0 이미지 중심
			//		nullptr,        // 위치 좌표에 대한 vec3 주소, null인 경우 스크린 상 0, 0 좌표 출력    
			//		D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 섞지 않고 원본 색상 유지
			//}
		}

	}
}

void CTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), [](auto& p) 
		{ 
			if (p)
			{ delete p; p = nullptr; }
		});
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

// 미니맵 렌더(안쓰는중)
void CTerrain::Mini_Render()
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	for (auto pTile : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			pTile->vPos.x,
			pTile->vPos.y,
			pTile->vPos.z);

		matWorld = matScale * matTrans;
				
		Set_Ratio(&matWorld, 0.3f, 0.3f);

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Back", L"Tile", pTile->tObject[OPT_GROUND].byDrawID);

		float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		D3DXVECTOR3	vTemp{ fCenterX, fCenterY, 0.f };

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, //출력할 텍스처 컴객체
			nullptr,		// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0기준으로 출력
			&vTemp,		// 출력할 이미지의 중심 좌표 vec3 주소, null인 경우 0, 0 이미지 중심
			nullptr,		// 위치 좌표에 대한 vec3 주소, null인 경우 스크린 상 0, 0 좌표 출력	
			D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 섞지 않고 원본 색상 유지
	}
}

void CTerrain::Tile_Change(const D3DXVECTOR3& vPos, TILETYPE byTileType, TILETERRAIN byTerrain, const BYTE& byDrawID, const int byOption)
{
	int iIndex = Get_TileIdx(vPos);

	if (-1 == iIndex)
		return;
	if (byTileType == OPT_ORE && !m_vecTile[iIndex]->tObject[OPT_WALL].bExist)
		return;

	m_vecTile[iIndex]->tObject[byTileType].bExist = true;
	m_vecTile[iIndex]->tObject[byTileType].byDrawID = byDrawID;
	m_vecTile[iIndex]->byOption = byOption;
	m_vecTile[iIndex]->tObject[byTileType].eTileTerrain = byTerrain;
	
	if (byTileType == OPT_WALL)
	{
		for (int i = 0; i < 9; ++i)
		{
			int Idx = iIndex + TILEX * ((i / 3) - 1) + ((i % 3) - 1);
			if (Idx >= 0 && Idx <= TILEX * TILEY)
			{
				Check_TileHead(Idx);
			}
		}
	}
}

void CTerrain::Set_Ratio(D3DXMATRIX* pOut, float _fX, float _fY)
{
	pOut->_11 *= _fX;
	pOut->_21 *= _fX;
	pOut->_31 *= _fX;
	pOut->_41 *= _fX;

	pOut->_12 *= _fY;
	pOut->_22 *= _fY;
	pOut->_32 *= _fY;
	pOut->_42 *= _fY;

}

int CTerrain::Get_TileIdx(const D3DXVECTOR3& vPos)
{
	for (size_t index = 0; index < m_vecTile.size(); ++index)
	{
		if (Picking_Dot(vPos, index))
		{
			return index;
		}
	}
	return -1;
}

// 타일 이미지 전체 불러오기
HRESULT CTerrain::Initialize_TileTexture()
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
		L"../Assets/Map//back/dark.png",
		TEX_SINGLE, L"Back", L"Tile", 1)))
	{
		AfxMessageBox(L"Back Texture Insert Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
		L"../Assets/Map/water_tileset/ground/water_tileset_ground%d.png",
		TEX_MULTI, L"water", L"ground", 17)))
	{
		AfxMessageBox(L"water ground Texture Insert Failed");
		//return E_FAIL;
	}

	TCHAR szTexFullPath[MAX_PATH] = L"";
	TCHAR szTexTerrain[MAX_STR] = L"";
	TCHAR szTexType[MAX_STR] = L"";
	int		iCnt;
	for (int j = 0; j < TRN_WATER; ++j)
	{
		for (int i = 0; i < OPT_END; ++i)
		{
			switch (j)
			{
			case TRN_DIRT:
				lstrcpy(szTexTerrain, L"dirt"); break;
			case TRN_SAND:
				lstrcpy(szTexTerrain, L"sand"); break;
			case TRN_NATURE:
				lstrcpy(szTexTerrain, L"nature"); break;
			case TRN_STONE:
				lstrcpy(szTexTerrain, L"stone"); break;
			default: break;
			}
			switch (i)
			{
			case OPT_GROUND:
				lstrcpy(szTexType, L"ground");
				iCnt = GROUND_ALL_CNT; break;
			case OPT_WALL:
				lstrcpy(szTexType, L"wall"); break;
				// body 6, head 21
			case OPT_ORE:
				lstrcpy(szTexType, L"ore");
				iCnt = ORE_DEFAULT_CNT;
				if (j == TRN_SAND) iCnt = ORE_SAND_CNT; break;
			case OPT_DECO:
				lstrcpy(szTexType, L"deco");
				iCnt = DECO_DEFAULT_CNT;
				if (j == TRN_SAND) iCnt = DECO_SAND_CNT;
				else if (j == TRN_DIRT) iCnt = DECO_DIRT_CNT; break;
			default: break;
			}

			if (i != OPT_WALL)
			{
				swprintf_s(szTexFullPath, L"../Assets/Map/%s_tileset/%s/%s_tileset_%s", szTexTerrain, szTexType, szTexTerrain, szTexType);
				lstrcat(szTexFullPath, L"%d.png");
				if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
					szTexFullPath, TEX_MULTI, szTexTerrain, szTexType, iCnt)))
				{
					AfxMessageBox(L"Texture Insert Failed");
					//return E_FAIL;
				}
			}  
			else
			{
				swprintf_s(szTexFullPath, L"../Assets/Map/%s_tileset/%sbody/%s_tileset_%sbody", szTexTerrain, szTexType, szTexTerrain, szTexType);
				lstrcat(szTexFullPath, L"%d.png");
				if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
					szTexFullPath, TEX_MULTI, szTexTerrain, L"wallbody", WALLBODY_ALL_CNT)))
				{
					AfxMessageBox(L"Texture Insert Failed");
					//return E_FAIL;
				}
				swprintf_s(szTexFullPath, L"../Assets/Map/%s_tileset/%shead/%s_tileset_%shead", szTexTerrain, szTexType, szTexTerrain, szTexType);
				lstrcat(szTexFullPath, L"%d.png");
				if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
					szTexFullPath, TEX_MULTI, szTexTerrain, L"wallhead", WALLHEAD_ALL_CNT)))
				{
					AfxMessageBox(L"Texture Insert Failed");
					//return E_FAIL;
				}
			}
		}
	}
}

void CTerrain::Check_TileHead(int iIndex)
{
	// 3x3 bool 이차원 배열을 2진법으로 쭉 늘어놓은 것					   0b010011010일 경우	
	// '0b' : 2진법 표시														0 1 0	  상단	   
	// 앞에서부터 LUP, UP, RUP, L, CENTER, R, LDOWN, DOWN, RDOWN		   		0 1 1	기준타일	 우측   
	int iRes = 0b000000000;					//						   		0 1 0	  하단        에 타일이 위치   
	int drawID(-1);
	for (int i = 0; i < 9; ++i)
	{
		int Idx = iIndex + TILEX * ((i / 3) - 1) + ((i % 3) - 1);
		if (Idx >= 0 && Idx <= TILEX*TILEY)
		{
			if (m_vecTile[Idx]->tObject[OPT_WALL].bExist)
			{
				iRes |= 1 << 8 - i;
			}
		}
	}													 
	if ((iRes & 0b010101010) == 0b010101010) {			
		if ((iRes & 0b101000101) == 0b000000000) {		
			drawID = 16;								
		}
		else {
			drawID = 7;
		}
	}
	else
	{
		if ((iRes & 0b000010000) == 0b000'010'000) {
			drawID = 21;
		}

		if ((iRes & 0b010010000) == 0b010010000) {
			drawID = 20;
		}
		else if ((iRes & 0b000110000) == 0b000110000) {
			drawID = 18;
		}
		else if ((iRes & 0b000010010) == 0b000010010) {
			drawID = 14;
		}
		else if ((iRes & 0b000011000) == 0b000011000) {
			drawID = 15;
		}

		if ((iRes & 0b010110000) == 0b010110000) {
			drawID = 13;
		}
		else if ((iRes & 0b000111000) == 0b000111000) {
			drawID = 17;
		}
		else if ((iRes & 0b010010010) == 0b010010010) {
			drawID = 19;
		}
		else if ((iRes & 0b010011000) == 0b010011000) {
			drawID = 9;
		}
		else if ((iRes & 0b000011010) == 0b000011010) {
			drawID = 1;
		}
		else if ((iRes & 0b000110010) == 0b000110010) {
			drawID = 5;
		}

		if ((iRes & 0b000111010) == 0b000111010) {
			drawID = rand() % 3 + 2;
		}
		else if ((iRes & 0b010011010) == 0b010011010) {
			drawID = 6;
		}
		else if ((iRes & 0b010110010) == 0b010110010) {
			drawID = 8;
		}
		else if ((iRes & 0b010111000) == 0b010111000) {
			drawID = rand() % 3 + 10;
		}
	}

	if (drawID != -1) {
		m_vecTile[iIndex]->tObject[OPT_WALL].byDrawID = drawID - 1;
	}


	return;
}

// 피킹 직선의방정식
bool CTerrain::Picking(const D3DXVECTOR3& vPos, const int& iIndex)
{
	// 12 -> 3 -> 6 -> 9
	float	fGradient[4] =
	{
		(TILECY / 2.f) / (TILECX / 2.f) * -1.f,
		(TILECY / 2.f) / (TILECX / 2.f),
		(TILECY / 2.f) / (TILECX / 2.f) * -1.f,
		(TILECY / 2.f) / (TILECX / 2.f)
	};

	// 12 -> 3 -> 6 -> 9
	D3DXVECTOR3	vPoint[4] =
	{
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f },
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f },

	};

	// y = ax + b;
	// -b = ax - y
	// b = y - ax

	float	fB[4] =
	{
		vPoint[0].y - fGradient[0] * vPoint[0].x,
		vPoint[1].y - fGradient[1] * vPoint[1].x,
		vPoint[2].y - fGradient[2] * vPoint[2].x,
		vPoint[3].y - fGradient[3] * vPoint[3].x
	};

	// 0 == ax + b - y // 선 상에 있음
	// 0 > ax + b - y // 선분 위쪽
	// 0 < ax + b - y // 선분 아래쪽

	bool	bCheck[4]{ false };

	// 12 -> 3
	if (0 < fGradient[0] * vPos.x + fB[0] - vPos.y)
		bCheck[0] = true;

	// 3 -> 6
	if (0 >= fGradient[1] * vPos.x + fB[1] - vPos.y)
		bCheck[1] = true;

	// 6 -> 9
	if (0 >= fGradient[2] * vPos.x + fB[2] - vPos.y)
		bCheck[2] = true;

	// 9 -> 12
	if (0 < fGradient[3] * vPos.x + fB[3] - vPos.y)
		bCheck[3] = true;


	return bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3];
}

// 피킹 내적
bool CTerrain::Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex)
{
	// 12 -> 3 -> 6 -> 9
	D3DXVECTOR3	vPoint[4] =
	{
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f },
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f },

	};

	D3DXVECTOR3	vDir[4] =
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	D3DXVECTOR3		vNormal[4] =
	{
		{ -vDir[0].y , vDir[0].x, 0.f },
		{ -vDir[1].y , vDir[1].x, 0.f },
		{ -vDir[2].y , vDir[2].x, 0.f },
		{ -vDir[3].y , vDir[3].x, 0.f },
	};

	D3DXVECTOR3		vMouseDir[4] =
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		if (0.f < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}

	return true;
}
