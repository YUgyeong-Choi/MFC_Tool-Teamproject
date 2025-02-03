#include "pch.h"
#include "MainGame.h"
#include "CDevice.h"

#include "SceneMgr.h"
#include "ObjMgr.h"
#include "TimeMgr.h"


CMainGame::CMainGame()
	: m_pGraphicDev(CDevice::Get_Instance())
{

}

CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Initialize(void)
{
	if (FAILED(m_pGraphicDev->Init_Device()))
	{
		ERR_MSG(L"Client Init_Device Create Failed");
		return E_FAIL;
	}

	CSceneMgr::Get_Instance()->Change_SceneMgr(CSceneMgr::STAGE);

	CTimeMgr::Get_Instance()->Initialize();

/*
#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif // _DEBUG*/


	return S_OK;
}

void CMainGame::Update(void)
{
	CTimeMgr::Get_Instance()->Update();
	CSceneMgr::Get_Instance()->Update_SceneMgr();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update_SceneMgr();
}

void CMainGame::Render(void)
{

	m_pGraphicDev->Render_Begin();

	CSceneMgr::Get_Instance()->Render_SceneMgr();

	m_pGraphicDev->Render_End();
}

void CMainGame::Release(void)
{
#ifdef _DEBUG

	//FreeConsole();

#endif // _DEBUG

	CTimeMgr::Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CTextureMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	m_pGraphicDev->Destroy_Instance();
}