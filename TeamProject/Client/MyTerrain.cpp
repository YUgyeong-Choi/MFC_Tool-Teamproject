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

	// ���� �ҷ����� �߰��� ��***
	if (FAILED(Load_Tile(L"../Data/20250207map.dat")))
	{
		return E_FAIL;
	}
	m_eRender = R_TERRAIN;


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

	Ready_Adjacency();

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
	int		iMaxY = WINCY / TILECY + TILEX;

	for (int i = iScrollY; i < iScrollY + iMaxY; ++i)
	{
		for (int j = iScrollX; j < iScrollX + iMaxX; ++j)
		{
			int			iIndex = i * TILEX + j;

			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
			{
				continue;
			}

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
				// ���� ���� ������ 
				switch (iOp) { case 0: i = OPT_GROUND; break; case 1: i = OPT_DECO; break; case 2:i = OPT_WALL; break; case 3: i = OPT_ORE; break; }
				if (m_vecTile[iIndex]->tObject[i].bExist)
				{
				 // switch ������� ����� ��
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

					CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, //����� �ؽ�ó �İ�ü
						 nullptr,        // ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0�������� ���
						 &vTemp,        // ����� �̹����� �߽� ��ǥ vec3 �ּ�, null�� ��� 0, 0 �̹��� �߽�
						 nullptr,        // ��ġ ��ǥ�� ���� vec3 �ּ�, null�� ��� ��ũ�� �� 0, 0 ��ǥ ���    
						 D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� �ʰ� ���� ���� ����
					//if (i == OPT_WALL)
					//{
					//	 const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(szTexTerrain, L"wallhead", m_vecTile[iIndex]->tObject[i].byDrawID);
					//	 if (pTexInfo == nullptr)
					//	 {
					//		 continue;
					//	 }
					//	 float fCenterX = pTexInfo->tImgInfo.Width / 2.f;
					//	 float fCenterY = pTexInfo->tImgInfo.Height / 2.f + pTexInfo->tImgInfo.Height;

					//	 D3DXVECTOR3 vTemp{ fCenterX, fCenterY, 0.f };

					//	 CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, //����� �ؽ�ó �İ�ü
					//		 nullptr,        // ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0�������� ���
					//		 &vTemp,        // ����� �̹����� �߽� ��ǥ vec3 �ּ�, null�� ��� 0, 0 �̹��� �߽�
					//		 nullptr,        // ��ġ ��ǥ�� ���� vec3 �ּ�, null�� ��� ��ũ�� �� 0, 0 ��ǥ ���    
					//		 D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� �ʰ� ���� ���� ����
					//}
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

void CMyTerrain::Render_WallHead(void)
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR	szBuf[MIN_STR] = L"";
	int		iIndex(0);

	int		iScrollX = int(-m_vScroll.x) / TILECX;
	int		iScrollY = int(-m_vScroll.y) / TILECY;

	int		iMaxX = WINCX / TILECX + 1;
	int		iMaxY = WINCY / TILECY + TILEX;

	for (int i = iScrollY; i < iScrollY + iMaxY; ++i)
	{
		for (int j = iScrollX; j < iScrollX + iMaxX; ++j)
		{
			int			iIndex = i * TILEX + j;

			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
			{
				continue;
			}

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

			if (m_vecTile[iIndex]->tObject[OPT_WALL].bExist)
			{
				switch (m_vecTile[iIndex]->tObject[OPT_WALL].eTileTerrain)
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

				const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(szTexTerrain, L"wallhead", m_vecTile[iIndex]->tObject[OPT_WALL].byDrawID);
				if (pTexInfo == nullptr)
				{
					continue;
				}
				float fCenterX = pTexInfo->tImgInfo.Width / 2.f;
				float fCenterY = pTexInfo->tImgInfo.Height / 2.f + pTexInfo->tImgInfo.Height;

				D3DXVECTOR3 vTemp{ fCenterX, fCenterY, 0.f };

				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, //����� �ؽ�ó �İ�ü
					nullptr,        // ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0�������� ���
					&vTemp,        // ����� �̹����� �߽� ��ǥ vec3 �ּ�, null�� ��� 0, 0 �̹��� �߽�
					nullptr,        // ��ġ ��ǥ�� ���� vec3 �ּ�, null�� ��� ��ũ�� �� 0, 0 ��ǥ ���    
					D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� �ʰ� ���� ���� ����
				}
			
			}
		}
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
		pTiletemp->iIndex = pTile.iIndex;
		pTiletemp->iParentIndex = pTile.iParentIndex;
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

void CMyTerrain::Ready_Adjacency()
{
	m_vecAdj.resize(m_vecTile.size());

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			int	iIndex = i * TILEX + j;

			// ��� - 1�� ����
			if (0 != i) {
				if (!m_vecTile[iIndex - TILEX]->byOption) {
					m_vecAdj[iIndex].push_back(m_vecTile[iIndex - TILEX]);
				}
			}

			// �ϴ� - TILEY-1�� ����
			if (TILEY-1 != i) {
				if (!m_vecTile[iIndex + TILEX]->byOption) {
					m_vecAdj[iIndex].push_back(m_vecTile[iIndex + TILEX]);
				}
			}

			// �´� - 1�� ����
			if (j!=0) {
				if (!m_vecTile[iIndex - 1]->byOption) {
					m_vecAdj[iIndex].push_back(m_vecTile[iIndex - 1]);
				}
			}


			// ��� - TILEX - 1 �� ����
			if (TILEX-1 != j) {
				if (!m_vecTile[iIndex + 1]->byOption) {
					m_vecAdj[iIndex].push_back(m_vecTile[iIndex + 1]);
				}
			}

			// 0  1  2
			// 40 41 42
			// 80 81 82
			//�� ��� - 1��� 1�� ����
			if ((0 != i) && (0 != iIndex % TILEX)){
				if (!m_vecTile[iIndex - TILEX -1]->byOption) {
					m_vecAdj[iIndex].push_back(m_vecTile[iIndex - TILEX - 1]);
				}
			}

			//�� �ϴ� - TILEY-1 ��� 1�� ����
			if ((TILEY - 1 != i) && (0 != iIndex % TILEX)) {
				if (!m_vecTile[iIndex + (TILEX - 1)]->byOption) {
					m_vecAdj[iIndex].push_back(m_vecTile[iIndex + (TILEX - 1)]);
				}
			}

			// 37  38  39
			// 77  78  79
			// 117 118 119
			//�� ��� - 1��� TILEX-1 �� ����
			if ((0 != i) && ((TILEX - 1) != iIndex % TILEX)) {
				if (!m_vecTile[iIndex - TILEX + 1]->byOption) {
					m_vecAdj[iIndex].push_back(m_vecTile[iIndex - TILEX + 1]);
				}
			}

			// �� �ϴ� - TILEY-1 ��� TILEX-1 �� ����
			if ((TILEY - 1 != i) && (TILEX - 1) != iIndex % (TILEX))
			{
				if (!m_vecTile[iIndex + TILEX + 1]->byOption) {
					m_vecAdj[iIndex].push_back(m_vecTile[iIndex + TILEX + 1]);
				}
			}

		}
	}
}
