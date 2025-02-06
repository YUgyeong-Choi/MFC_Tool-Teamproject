#include "pch.h"
#include "CAstarMgr.h"
#include "ObjMgr.h"
IMPLEMENT_SINGLETON(CAstarMgr)

CAstarMgr::CAstarMgr()
{
}

CAstarMgr::~CAstarMgr()
{
	Release();
}

void CAstarMgr::Start_Astar(const D3DXVECTOR3& vStart, const D3DXVECTOR3& vGoal)
{
	Release();

	CObj* pMyTerrain = CObjMgr::Get_Instance()->Get_Terrain();
	vector<TILE*>& vecTile = dynamic_cast<CMyTerrain*>(pMyTerrain)->Get_VecTile();

	m_iStartIdx = Get_TileIdx(vStart);

	int iGoalIdx = Get_TileIdx(vGoal);

	if (0 > m_iStartIdx ||
		0 > iGoalIdx ||
		(size_t)m_iStartIdx >= vecTile.size() ||
		(size_t)iGoalIdx >= vecTile.size())
	{
		return;
	}

	if (m_iStartIdx == iGoalIdx)
		return;

	if (OPTION_NOCOLLISION != vecTile[iGoalIdx]->byOption)
		return;

	if (true == Make_Route(m_iStartIdx, iGoalIdx))
	{
		Make_BestList(m_iStartIdx, iGoalIdx);
	}

}


bool CAstarMgr::Make_Route(int iStartIdx, int iGoalIdx)
{
	CObj* pMyTerrain = CObjMgr::Get_Instance()->Get_Terrain();
	vector<TILE*>& vecTile = dynamic_cast<CMyTerrain*>(pMyTerrain)->Get_VecTile();
	vector<list<TILE*>>& vecAdj = dynamic_cast<CMyTerrain*>(pMyTerrain)->Get_VecAdj();

	if (!m_OpenList.empty())
		m_OpenList.pop_front();

	m_CloseList.push_back(iStartIdx);

	for (auto& pTile : vecAdj[iStartIdx])
	{
		if (iGoalIdx == pTile->iIndex)
		{
			pTile->iParentIndex = iStartIdx;
			return true;
		}

		if (false == Check_Close(pTile->iIndex) &&
			false == Check_Open(pTile->iIndex))
		{
			pTile->iParentIndex = iStartIdx;

			m_OpenList.push_back(pTile->iIndex);
		}
	}

	if (m_OpenList.empty())
		return false;

	int iStart = m_iStartIdx;

	m_OpenList.sort([&vecTile, &iGoalIdx, &iStart](int Dst, int Src)->bool
		{
			D3DXVECTOR3	vPCost1 = vecTile[iStart]->vPos - vecTile[Dst]->vPos;
			D3DXVECTOR3	vPCost2 = vecTile[iStart]->vPos - vecTile[Src]->vPos;

			D3DXVECTOR3	vGCost1 = vecTile[iGoalIdx]->vPos - vecTile[Dst]->vPos;
			D3DXVECTOR3	vGCost2 = vecTile[iGoalIdx]->vPos - vecTile[Src]->vPos;

			float	fCost1 = D3DXVec3Length(&vPCost1) + D3DXVec3Length(&vGCost1);
			float	fCost2 = D3DXVec3Length(&vPCost2) + D3DXVec3Length(&vGCost2);

			return fCost1 < fCost2;
		});

	return Make_Route(m_OpenList.front(), iGoalIdx);
}

void CAstarMgr::Make_BestList(int iStartIdx, int iGoalIdx)
{
	CObj* pMyTerrain = CObjMgr::Get_Instance()->Get_Terrain();
	vector<TILE*>& vecTile = dynamic_cast<CMyTerrain*>(pMyTerrain)->Get_VecTile();

	TILEADDLOOK temp;
	temp.pTile = vecTile[iGoalIdx];

	//상단 이동
	if (vecTile[iGoalIdx]->iIndex == vecTile[iGoalIdx]->iParentIndex - TILEX) {
		temp.eLook = UP;
	}

	//하단 이동
	if (vecTile[iGoalIdx]->iIndex == vecTile[iGoalIdx]->iParentIndex + TILEX) {
		temp.eLook = DOWN;
	}

	//우단 이동
	if (vecTile[iGoalIdx]->iParentIndex == vecTile[iGoalIdx]->iIndex - 1) {
		temp.eLook = RIGHT;
	}

	//좌단 이동
	if (vecTile[iGoalIdx]->iParentIndex == vecTile[iGoalIdx]->iIndex + 1) {
		temp.eLook = LEFT;
	}

	// 좌상단이면
	if (vecTile[iGoalIdx]->iIndex == vecTile[iGoalIdx]->iParentIndex - (TILEX + 1)) {
		temp.eLook = LEFT;
	}

	//좌하단 이면
	if (vecTile[iGoalIdx]->iIndex == vecTile[iGoalIdx]->iParentIndex + TILEX - 1) {
		temp.eLook = LEFT;
	}

	// 우상단이면
	if (vecTile[iGoalIdx]->iIndex == vecTile[iGoalIdx]->iParentIndex - (TILEX - 1)) {
		temp.eLook = RIGHT;
	}


	//우하단 이면
	if (vecTile[iGoalIdx]->iIndex == vecTile[iGoalIdx]->iParentIndex + TILEX + 1) {
		temp.eLook = RIGHT;
	}

	//if(vecTile[iGoalIdx]->iIndex = vecTile[iGoalIdx]->iParentIndex - )

	m_BestList.push_front(temp);

	int iRouteIdx = vecTile[iGoalIdx]->iParentIndex;

	while (true)
	{
		if (iRouteIdx == iStartIdx)
			break;

		TILEADDLOOK temp;
		temp.pTile = vecTile[iRouteIdx];
		temp.eLook = LEFT;

		//상단 이동
		if (vecTile[iRouteIdx]->iIndex == vecTile[iRouteIdx]->iParentIndex - TILEX) {
			temp.eLook = UP;
		}

		//하단 이동
		if (vecTile[iRouteIdx]->iIndex == vecTile[iRouteIdx]->iParentIndex + TILEX) {
			temp.eLook = DOWN;
		}

		//우단 이동
		if (vecTile[iRouteIdx]->iParentIndex == vecTile[iRouteIdx]->iIndex - 1) {
			temp.eLook = RIGHT;
		}

		//좌단 이동
		if (vecTile[iRouteIdx]->iParentIndex == vecTile[iRouteIdx]->iIndex + 1) {
			temp.eLook = LEFT;
		}

		// 좌상단이면
		if (vecTile[iRouteIdx]->iIndex == vecTile[iRouteIdx]->iParentIndex - (TILEX + 1)) {
			temp.eLook = LEFT;
		}

		//좌하단 이면
		if (vecTile[iRouteIdx]->iIndex == vecTile[iRouteIdx]->iParentIndex + TILEX - 1) {
			temp.eLook = LEFT;
		}

		// 우상단이면
		if (vecTile[iRouteIdx]->iIndex == vecTile[iRouteIdx]->iParentIndex - (TILEX - 1)) {
			temp.eLook = RIGHT;
		}


		//우하단 이면
		if (vecTile[iRouteIdx]->iIndex == vecTile[iRouteIdx]->iParentIndex + TILEX + 1) {
			temp.eLook = RIGHT;
		}


		m_BestList.push_front(temp);
		iRouteIdx = vecTile[iRouteIdx]->iParentIndex;
	}
}

int CAstarMgr::Get_TileIdx(const D3DXVECTOR3& vPos)
{
	CObj* pMyTerrain = CObjMgr::Get_Instance()->Get_Terrain();
	vector<TILE*>& vecTile = dynamic_cast<CMyTerrain*>(pMyTerrain)->Get_VecTile();

	if (vecTile.empty())
		return -1;

	for (size_t index = 0; index < vecTile.size(); ++index)
	{
		if (Picking(vPos, index))
		{
			return index;
		}
	}

	return -1;
}

bool CAstarMgr::Picking(const D3DXVECTOR3& vPos, const int& iIndex)
{
	CObj* pMyTerrain = CObjMgr::Get_Instance()->Get_Terrain();
	vector<TILE*>& vecTile = dynamic_cast<CMyTerrain*>(pMyTerrain)->Get_VecTile();

	// 12 -> 3 -> 6 -> 9
	D3DXVECTOR3 vPoint[4] =
	{
		{ vecTile[iIndex]->vPos.x - (TILECX / 2.f), vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f }, // 왼쪽 위
		{ vecTile[iIndex]->vPos.x + (TILECX / 2.f), vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f }, // 오른쪽 위
		{ vecTile[iIndex]->vPos.x + (TILECX / 2.f), vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f }, // 오른쪽 아래
		{ vecTile[iIndex]->vPos.x - (TILECX / 2.f), vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f }, // 왼쪽 아래
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

bool CAstarMgr::Check_Close(int iIndex)
{
	for (int& iCloseIdx : m_CloseList)
	{
		if (iIndex == iCloseIdx)
			return true;
	}

	return false;
}

bool CAstarMgr::Check_Open(int iIndex)
{
	for (int& iOpenIdx : m_OpenList)
	{
		if (iIndex == iOpenIdx)
			return true;
	}

	return false;
}

void CAstarMgr::Release()
{
	m_OpenList.clear();
	m_CloseList.clear();

	m_BestList.clear();
}
