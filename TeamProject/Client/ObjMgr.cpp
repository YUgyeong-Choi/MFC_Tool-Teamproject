#include "pch.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "MyTerrain.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release(); 
}

void CObjMgr::Add_Object(ID eID, CObj * pObject)
{
	if (nullptr == pObject || END <= eID)
		return; 

	m_listObject[eID].emplace_back(pObject); 
}

void CObjMgr::Update()
{
	for (int i = 0 ; i < END; ++i)
	{
		for (auto iter = m_listObject[i].begin() ; iter != m_listObject[i].end(); )
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete(*iter);
				iter = m_listObject[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update()
{
	for (int i = 0 ; i < END ; ++i)
	{
		for (auto& pObject : m_listObject[i])
		{
			pObject->Late_Update();

			if (m_listObject[i].empty())
				break;

			RENDERID	eID = pObject->Get_RenderID();
			m_RenderList[eID].push_back(pObject);
		}
	}
}

void CObjMgr::Render()
{
	//for (int i = 0; i < END; ++i)
	//{
	//	for (auto& pObject : m_listObject[i])
	//		pObject->Render();
	//}

	for (size_t i = 0; i < R_END; ++i)
	{
		m_RenderList[i].sort([](CObj* pDst, CObj* pSrc)->bool
			{
				return pDst->Get_Info().vPos.y < pSrc->Get_Info().vPos.y;
			});

		for (auto& pObj : m_RenderList[i])
			pObj->Render();

		m_RenderList[i].clear();
	}




	static_cast<CMyTerrain*>(m_listObject[ID::TERRAIN].front())->Render_WallHead();
}

void CObjMgr::Release()
{
	for (int i = 0; i < END; ++i)
	{
		for (auto& pObject : m_listObject[i])
			Safe_Delete(pObject); 

		m_listObject[i].clear();
	}
}
