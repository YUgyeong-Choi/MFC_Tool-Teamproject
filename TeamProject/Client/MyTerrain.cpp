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

	// 저장 불러오기 추가할 것***
	if (FAILED(Load_Tile(L"../Data/Maptest.dat")))
	{
		return E_FAIL;
	}


	// Initialize_TileTexture
	{

		if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
			L"../Assets/Map//back/dark.png",
			TEX_SINGLE, L"Back", L"Tile", 1)))
		{
			ERR_MSG(L"Back Texture Insert Failed");
			return E_FAIL;
		}

		if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
			L"../Assets/Map/water_tileset/ground/water_tileset_ground%d.png",
			TEX_MULTI, L"water", L"ground", 17)))
		{
			ERR_MSG(L"water ground Texture Insert Failed");
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
						ERR_MSG(L"Texture Insert Failed");
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
						ERR_MSG(L"Texture Insert Failed");
						//return E_FAIL;
					}
					swprintf_s(szTexFullPath, L"../Assets/Map/%s_tileset/%shead/%s_tileset_%shead", szTexTerrain, szTexType, szTexTerrain, szTexType);
					lstrcat(szTexFullPath, L"%d.png");
					if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
						szTexFullPath, TEX_MULTI, szTexTerrain, L"wallhead", WALLHEAD_ALL_CNT)))
					{
						ERR_MSG(L"Texture Insert Failed");
						//return E_FAIL;
					}
				}
			}
		}
	}


	//for (int i = 0; i < TILEY; ++i)
	//{
	//	for (int j = 0; j < TILEX; ++j)
	//	{
	//		TILE* pTile = new TILE;
	//		ZeroMemory(pTile, sizeof(TILE));
	//		float    fY = TILECY * i + (TILECY / 2.f);
	//		float    fX = TILECX * j + (TILECX / 2.f);

	//		pTile->vPos = { fX, fY, 0.f };
	//		pTile->vSize = { (float)TILECX, (float)TILECY };
	//		pTile->byOption = 0;
	//		pTile->tObject[OPT_GROUND].bExist = true;
	//		for (int i = OPT_GROUND + 1; i < OPT_END; ++i) pTile->tObject[i].bExist = false;
	//		pTile->tObject[OPT_GROUND].byDrawID = 27;
	//		pTile->tObject[OPT_GROUND].eTileTerrain = TRN_DIRT;
	//		m_vecTile.push_back(pTile);
	//	}
	//}

	//m_wstrObjKey = L"dirt";
	//m_wstrStateKey = L"ground";

	return S_OK;
}

int CMyTerrain::Update(void)
{

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
	int		iScrollY = int(-m_vScroll.y) / TILECY;

	int		iMaxX = WINCX / TILECX + 1;
	int		iMaxY = WINCY / TILECY + 1;

	for (int i = iScrollY; i < iScrollY + iMaxY; ++i)
	{
		for (int j = iScrollX; j < iScrollX + iMaxX; ++j)
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

			TCHAR szTexTerrain[MAX_STR] = L"";
			TCHAR szTexType[MAX_STR] = L"";

			int i(0);

			for (int iOp = 0; iOp < OPT_END; ++iOp)
			{
				// 렌더 순서 조절용 
				switch (iOp) { case 0: i = OPT_GROUND; break; case 1: i = OPT_DECO; break; case 2:i = OPT_WALL; break; case 3: i = OPT_ORE; break; }
				if (m_vecTile[iIndex]->tObject[i].bExist)
				{
					if (iIndex == 132)
						int a = 1;
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
					switch (m_vecTile[iIndex]->tObject[i].eTileTerrain)
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

					int iDrawID = m_vecTile[iIndex]->tObject[i].byDrawID;
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
						 const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(szTexTerrain, L"wallhead", m_vecTile[iIndex]->tObject[i].byDrawID);
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
			}
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
	TILE pTile;
	ZeroMemory(&pTile, sizeof(TILE));

	while (true)
	{
		ReadFile(hFile, &pTile, sizeof(TILE), &dwByte, nullptr);

		//ReadFile(hFile, &pTile->byOption, sizeof(BYTE), &dwByte, nullptr);
		//ReadFile(hFile, &pTile->vPos, sizeof(D3DXVECTOR3), &dwByte, nullptr);
		//ReadFile(hFile, &pTile->vSize, sizeof(D3DXVECTOR3), &dwByte, nullptr);
		//for (int i = 0; i < OPT_END; ++i)
		//{
		//	ReadFile(hFile, &(pTile->tObject[i]), sizeof(TILEOBJ), &dwByte, nullptr);
		//}

		if (0 == dwByte)
		{
			break;
		}
		TILE* pTiletemp = new TILE;

		pTiletemp->byOption = pTile.byOption;
		pTiletemp->vPos = pTile.vPos;
		pTiletemp->vSize = pTile.vSize;
		for (int i = 0; i < OPT_END; ++i)
		{
			pTiletemp->tObject[i].bExist = pTile.tObject[i].bExist;
			if (i != 0 && pTile.tObject[i].bExist)
			{
				pTiletemp->tObject[i].bExist = pTile.tObject[i].bExist;

			}

			pTiletemp->tObject[i].byDrawID = pTile.tObject[i].byDrawID;
			pTiletemp->tObject[i].eTileTerrain = pTile.tObject[i].eTileTerrain;
		}

		m_vecTile.push_back(pTiletemp);
	}

	CloseHandle(hFile);
}

