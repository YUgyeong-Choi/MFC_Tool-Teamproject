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
	DDX_Control(pDX, IDC_PICTURE2, PlayerPreviewImg);
}

void CPlayerTool::OnInitialUpdate()
{
	m_hairIndex = 0;
	OnLoadData();

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

void CPlayerTool::OnLoadData()
{
	//스킨
	m_vecSkin.push_back(new CImage());
	TCHAR szSkinPath[MAX_PATH] = L"../Assets/Player/skin/idle/front/front_1.png";
	m_vecSkin[0]->Load(szSkinPath);
	COLORREF transparentColor = RGB(255, 255, 255);
	m_vecSkin[0]->SetTransparentColor(transparentColor);

	//눈
	m_eye = new CImage();
	TCHAR szEyePath[MAX_PATH] = L"../Assets/Player/eye/idle/front/front_1.png";
	m_eye->Load(szEyePath);
	m_eye->SetTransparentColor(transparentColor);

	//셔츠
	m_shirt = new CImage();
	TCHAR szShirtPath[MAX_PATH] = L"../Assets/Player/shirt/idle/front/front_1.png";
	m_shirt->Load(szShirtPath);
	m_shirt->SetTransparentColor(transparentColor);

	//바지
	m_pant = new CImage();
	TCHAR szPantPath[MAX_PATH] = L"../Assets/Player/pant/idle/front/front_1.png";
	m_pant->Load(szPantPath);
	m_pant->SetTransparentColor(transparentColor);

	m_vecHair.push_back(new CImage());
	TCHAR szHairPath[MAX_PATH] = L"../Assets/Player/hair/hair1/idle/front/Miner_hair2_10.png";
	m_vecHair[0]->Load(szHairPath);
	m_vecHair[0]->SetTransparentColor(transparentColor);

	//머리
	//for (int i = 0; i < 5; ++i) {
	//	m_vecHair.push_back(new CImage());

	//	TCHAR szHairPath[MAX_PATH];
	//	wsprintf(szHairPath, L"../Assets/Player/hair/hair%d/idle/front/front_1.png", i + 1);

	//	m_vecHair[i]->Load(szHairPath);
	//	m_vecHair[i]->SetTransparentColor(RGB(255, 255, 255));
	//}
}

void CPlayerTool::ChangeImageColor(CImage* image, CEdit* R, CEdit* G, CEdit* B)
{
	for (int y = 0; y < image->GetHeight(); ++y)
	{
		for (int x = 0; x < image->GetWidth(); ++x)
		{
			// 현재 픽셀 색상 가져오기
			COLORREF pixelColor = image->GetPixel(x, y);

			// 투명한 색상인 경우 건드리지 않음
			if (pixelColor != RGB(255, 255, 255))
			{
				// 각 색상 채널의 값 가져오기
				int r = GetRValue(pixelColor);
				int g = GetGValue(pixelColor);
				int b = GetBValue(pixelColor);

				// 새로운 색상의 RGB 채널 값 가져오기
				CString strR, strG, strB;
				R->GetWindowTextW(strR);
				G->GetWindowTextW(strG);
				B->GetWindowTextW(strB);
				int myr = _ttoi(strR);
				int myg = _ttoi(strG);
				int myb = _ttoi(strB);

				// 색상 비율에 맞춰 텍스쳐 색상 변경
				int rResult = (r * myr) / 255;
				int gResult = (g * myg) / 255;
				int bResult = (b * myb) / 255;

				// 변경된 색으로 픽셀을 설정
				image->SetPixel(x, y, RGB(rResult, gResult, bResult));
			}
		}
	}
}


BEGIN_MESSAGE_MAP(CPlayerTool, CDialog)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &CPlayerTool::OnHairColor)
	ON_BN_CLICKED(IDC_BUTTON3, &CPlayerTool::OnPantColor)
	ON_BN_CLICKED(IDC_BUTTON8, &CPlayerTool::OnEyeColor)
	ON_BN_CLICKED(IDC_BUTTON9, &CPlayerTool::OnShirtColor)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON4, &CPlayerTool::OnLoadPlayerBasic)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CPlayerTool::OnChangeHairType)
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
	ChangeImageColor(m_vecHair[m_hairIndex], &m_hairR, &m_hairG, &m_hairB);

	Invalidate(FALSE);
	CClientDC dc(&PlayerPreviewImg);
	CRect rect;
	PlayerPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));

	m_vecSkin[0]->Draw(dc, rect);
	m_vecHair[m_hairIndex]->Draw(dc, rect);
	m_eye->Draw(dc, rect);
	m_shirt->Draw(dc, rect);
	m_pant->Draw(dc, rect);

}

void CPlayerTool::OnPantColor()
{
	ChangeImageColor(m_pant, &m_pantR, &m_pantG, &m_pantB);

	Invalidate(FALSE);
	CClientDC dc(&PlayerPreviewImg);
	CRect rect;
	PlayerPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));

	m_vecSkin[0]->Draw(dc, rect);
	m_vecHair[m_hairIndex]->Draw(dc, rect);
	m_eye->Draw(dc, rect);
	m_shirt->Draw(dc, rect);
	m_pant->Draw(dc, rect);
}

void CPlayerTool::OnShirtColor()
{
}


void CPlayerTool::OnEyeColor()
{
}


void CPlayerTool::OnDestroy()
{
	CDialog::OnDestroy();
	for (size_t i = 0; i < m_vecSkin.size(); ++i) {
		Safe_Delete(m_vecSkin[i]);
	}
	for (size_t i = 0; i < m_vecHair.size(); ++i) {
		Safe_Delete(m_vecHair[i]);
	}

	Safe_Delete(m_eye);
	Safe_Delete(m_shirt);
	Safe_Delete(m_pant);
}


void CPlayerTool::OnLoadPlayerBasic()
{
	CClientDC dc(&PlayerPreviewImg);
	CRect rect;
	PlayerPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));

	m_vecSkin[0]->Draw(dc, rect);
	m_vecHair[0]->Draw(dc, rect);
	m_eye->Draw(dc, rect);
	m_shirt->Draw(dc, rect);
	m_pant->Draw(dc, rect);
}


void CPlayerTool::OnChangeHairType(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (pNMUpDown->iDelta < 0) {
		//오른쪽 누름
		m_hairIndex++;
		if (m_hairIndex == m_vecHair.size()) {
			m_hairIndex = 0;
		}
	}
	else {
		//왼쪽 누름
		m_hairIndex--;
		if (m_hairIndex < 0) {
			m_hairIndex = m_vecHair.size() - 1;
		}
	}

	Invalidate(FALSE);
	CClientDC dc(&PlayerPreviewImg);
	CRect rect;
	PlayerPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));

	m_vecSkin[0]->Draw(dc, rect);
	m_vecHair[m_hairIndex]->Draw(dc, rect);
	m_eye->Draw(dc, rect);
	m_shirt->Draw(dc, rect);
	m_pant->Draw(dc, rect);


	*pResult = 0;
}
