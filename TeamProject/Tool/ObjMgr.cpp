#include "pch.h"
#include "ObjMgr.h"
#include "Obj.h"

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
			pObject->Late_Update();
	}
}

void CObjMgr::Render()
{
	for (int i = 0; i < END; ++i)
	{
		for (auto& pObject : m_listObject[i])
			pObject->Render();
	}
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
