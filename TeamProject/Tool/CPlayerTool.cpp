// CPlayerTool.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CPlayerTool.h"


// CPlayerTool 대화 상자

IMPLEMENT_DYNAMIC(CPlayerTool, CDialog)

CPlayerTool::CPlayerTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CPlayerTool, pParent)
{

}

CPlayerTool::~CPlayerTool()
{
}

void CPlayerTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_hairR);
	DDX_Control(pDX, IDC_EDIT2, m_hairG);
	DDX_Control(pDX, IDC_EDIT7, m_hairB);
	DDX_Control(pDX, IDC_EDIT3, m_eyeR);
	DDX_Control(pDX, IDC_EDIT4, m_eyeG);
	DDX_Control(pDX, IDC_EDIT5, m_eyeB);
	DDX_Control(pDX, IDC_EDIT8, m_shirtR);
	DDX_Control(pDX, IDC_EDIT9, m_shirtG);
	DDX_Control(pDX, IDC_EDIT10, m_shirtB);
	DDX_Control(pDX, IDC_EDIT11, m_pantR);
	DDX_Control(pDX, IDC_EDIT12, m_pantG);
	DDX_Control(pDX, IDC_EDIT13, m_pantB);
	DDX_Control(pDX, IDC_SLIDER1, m_silderHairR);
	DDX_Control(pDX, IDC_SLIDER2, m_silderHairG);
	DDX_Control(pDX, IDC_SLIDER3, m_silderHairB);
	DDX_Control(pDX, IDC_SLIDER4, m_silderEyeR);
	DDX_Control(pDX, IDC_SLIDER5, m_silderEyeG);
	DDX_Control(pDX, IDC_SLIDER6, m_silderEyeB);
	DDX_Control(pDX, IDC_SLIDER7, m_silderShirtR);
	DDX_Control(pDX, IDC_SLIDER8, m_silderShirtG);
	DDX_Control(pDX, IDC_SLIDER9, m_silderShirtB);
	DDX_Control(pDX, IDC_SLIDER10, m_silderPantR);
	DDX_Control(pDX, IDC_SLIDER11, m_silderPantG);
	DDX_Control(pDX, IDC_SLIDER12, m_silderPantB);
}

void CPlayerTool::OnInitialUpdate()
{
	Ui_Silder_Set(&m_silderHairR);
	Ui_Silder_Set(&m_silderHairG);
	Ui_Silder_Set(&m_silderHairB);
	Ui_Silder_Set(&m_silderEyeR);
	Ui_Silder_Set(&m_silderEyeG);
	Ui_Silder_Set(&m_silderEyeB);
	Ui_Silder_Set(&m_silderShirtR);
	Ui_Silder_Set(&m_silderShirtG);
	Ui_Silder_Set(&m_silderShirtB);
	Ui_Silder_Set(&m_silderPantR);
	Ui_Silder_Set(&m_silderPantG);
	Ui_Silder_Set(&m_silderPantB);


	m_hairR.SetWindowTextW(_T("0"));
	m_hairG.SetWindowTextW(_T("0"));
	m_hairB.SetWindowTextW(_T("0"));
	m_eyeR.SetWindowTextW(_T("0"));
	m_eyeG.SetWindowTextW(_T("0"));
	m_eyeB.SetWindowTextW(_T("0"));
	m_shirtR.SetWindowTextW(_T("0"));
	m_shirtG.SetWindowTextW(_T("0"));
	m_shirtB.SetWindowTextW(_T("0"));
	m_pantR.SetWindowTextW(_T("0"));
	m_pantG.SetWindowTextW(_T("0"));
	m_pantB.SetWindowTextW(_T("0"));
}

void CPlayerTool::Ui_Silder_Set(CSliderCtrl* silder)
{
	silder->SetRange(0, 255);
	silder->SetRangeMin(0);
	silder->SetRangeMax(255);
	silder->SetTicFreq(1);
	silder->SetLineSize(1);
	silder->SetPageSize(1);
}


BEGIN_MESSAGE_MAP(CPlayerTool, CDialog)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &CPlayerTool::OnHairColor)
	ON_BN_CLICKED(IDC_BUTTON3, &CPlayerTool::OnPantColor)
	ON_BN_CLICKED(IDC_BUTTON8, &CPlayerTool::OnEyeColor)
	ON_BN_CLICKED(IDC_BUTTON9, &CPlayerTool::OnShirtColor)
END_MESSAGE_MAP()


void CPlayerTool::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CString temp;
	int nSPos = 0;
	if (pScrollBar) {
		if (pScrollBar == (CScrollBar*)&m_silderHairR) {
			nSPos = m_silderHairR.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_hairR.SetWindowTextW(temp);
		}else if (pScrollBar == (CScrollBar*)&m_silderHairG) {
			nSPos = m_silderHairG.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_hairG.SetWindowTextW(temp);
		}
		else if (pScrollBar == (CScrollBar*)&m_silderHairB) {
			nSPos = m_silderHairB.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_hairB.SetWindowTextW(temp);
		}
		else if (pScrollBar == (CScrollBar*)&m_silderEyeR) {
			nSPos = m_silderEyeR.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_eyeR.SetWindowTextW(temp);
		}
		else if (pScrollBar == (CScrollBar*)&m_silderEyeG) {
			nSPos = m_silderEyeG.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_eyeG.SetWindowTextW(temp);
		}
		else if (pScrollBar == (CScrollBar*)&m_silderEyeB) {
			nSPos = m_silderEyeB.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_eyeB.SetWindowTextW(temp);
		}
		else if (pScrollBar == (CScrollBar*)&m_silderShirtR) {
			nSPos = m_silderShirtR.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_shirtR.SetWindowTextW(temp);
		}
		else if (pScrollBar == (CScrollBar*)&m_silderShirtG) {
			nSPos = m_silderShirtG.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_shirtG.SetWindowTextW(temp);
		}
		else if (pScrollBar == (CScrollBar*)&m_silderShirtB) {
			nSPos = m_silderShirtB.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_shirtB.SetWindowTextW(temp);
		}
		else if (pScrollBar == (CScrollBar*)&m_silderPantR) {
			nSPos = m_silderPantR.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_pantR.SetWindowTextW(temp);
		}
		else if (pScrollBar == (CScrollBar*)&m_silderPantG) {
			nSPos = m_silderPantG.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_pantG.SetWindowTextW(temp);
		}
		else if (pScrollBar == (CScrollBar*)&m_silderPantB) {
			nSPos = m_silderPantB.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_pantB.SetWindowTextW(temp);
		}
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CPlayerTool::OnHairColor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CPlayerTool::OnPantColor()
{
}

void CPlayerTool::OnShirtColor()
{
}


void CPlayerTool::OnEyeColor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
