// CMyForm.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "CMyForm.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "CTerrain.h"



// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_CMyForm)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyForm::OnPlayerClick)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm::OnMapTool)
	ON_BN_CLICKED(IDC_CHECK1, &CMyForm::OnGrid)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyForm::OnMapObjectTool)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyForm::OnAnimalTool)
END_MESSAGE_MAP()


// CMyForm 진단

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_Font.CreatePointFont(180, L"궁서");

}

void CMyForm::OnPlayerClick()
{
	if (nullptr == m_PlayerTool.GetSafeHwnd()) {
		m_PlayerTool.Create(IDD_CPlayerTool);
		m_PlayerTool.OnInitialUpdate();
	}
		

	m_PlayerTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnMapTool()
{
	if (nullptr == m_MapTool.GetSafeHwnd()){
		m_MapTool.Create(IDD_CMapTool);	// 해당 id에 맞는 다이얼로그 생성
		m_MapTool.OnInitialUpdate();
	}

	m_MapTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnGrid()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CToolView* _view = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 0));

	_view->m_bGrid = !_view->m_bGrid;
	pMainFrm->Invalidate(FALSE);
}


void CMyForm::OnMapObjectTool()
{
	if (nullptr == m_MapObjTool.GetSafeHwnd()) {
		m_MapObjTool.Create(IDD_CMapObjTool);	// 해당 id에 맞는 다이얼로그 생성
		m_MapObjTool.OnInitialUpdate();
	}

	m_MapObjTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnAnimalTool()
{
	if (nullptr == m_AnimalTool.GetSafeHwnd()) {
		m_AnimalTool.Create(IDD_CAnimalTool);	// 해당 id에 맞는 다이얼로그 생성
		m_AnimalTool.OnInitialUpdate();
	}

	m_AnimalTool.ShowWindow(SW_SHOW);
}
