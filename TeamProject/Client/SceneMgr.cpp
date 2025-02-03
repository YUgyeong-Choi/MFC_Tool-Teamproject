#include "pch.h"
#include "SceneMgr.h"
#include "Stage.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	:m_pScene(nullptr)
	, m_eCurScene(END)
	, m_eNextScene(END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release_SceneMgr();
}

HRESULT CSceneMgr::Change_SceneMgr(ID eID)
{
	m_eNextScene = eID; 

	if (m_eCurScene != m_eNextScene)
	{
		Safe_Delete(m_pScene); 

		switch (m_eNextScene)
		{
		case CSceneMgr::LOADING:
			break;

		case CSceneMgr::STAGE:
			m_pScene = new CStage;		
			break;
						
		default:
			break;
		}
		if (nullptr == m_pScene)
		{
			ERR_MSG(L"SceneChange Failed");
			return E_FAIL; 
		}

		m_pScene->Ready_Scene();

		m_eCurScene = m_eNextScene; 
	}
	return S_OK;
}

void CSceneMgr::Update_SceneMgr()
{
	m_pScene->Update_Scene(); 
}

void CSceneMgr::Late_Update_SceneMgr()
{
	m_pScene->Late_Update_Scene(); 
}

void CSceneMgr::Render_SceneMgr()
{
	m_pScene->Render_Scene(); 
}

void CSceneMgr::Release_SceneMgr()
{
	Safe_Delete<CScene*>(m_pScene); 
}
