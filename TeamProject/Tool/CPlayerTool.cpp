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
	DDX_Control(pDX, IDC_EDIT14, m_skinR);
	DDX_Control(pDX, IDC_EDIT15, m_skinG);
	DDX_Control(pDX, IDC_EDIT16, m_skinB);
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
	DDX_Control(pDX, IDC_SLIDER13, m_silderSkinR);
	DDX_Control(pDX, IDC_SLIDER14, m_silderSkinG);
	DDX_Control(pDX, IDC_SLIDER15, m_silderSkinB);
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
	DDX_Control(pDX, IDC_CHECK2, m_AnimationOn);
}

void CPlayerTool::OnInitialUpdate()
{
	m_playerLook = FRONT;
	m_hairIndex = 0;
	OnLoadData();

	Ui_Silder_Set(&m_silderSkinR);
	Ui_Silder_Set(&m_silderSkinG);
	Ui_Silder_Set(&m_silderSkinB);
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

	m_skinR.SetWindowTextW(_T("255"));
	m_skinG.SetWindowTextW(_T("255"));
	m_skinB.SetWindowTextW(_T("255"));
	m_hairR.SetWindowTextW(_T("255"));
	m_hairG.SetWindowTextW(_T("255"));
	m_hairB.SetWindowTextW(_T("255"));
	m_eyeR.SetWindowTextW(_T("255"));
	m_eyeG.SetWindowTextW(_T("255"));
	m_eyeB.SetWindowTextW(_T("255"));
	m_shirtR.SetWindowTextW(_T("255"));
	m_shirtG.SetWindowTextW(_T("255"));
	m_shirtB.SetWindowTextW(_T("255"));
	m_pantR.SetWindowTextW(_T("255"));
	m_pantG.SetWindowTextW(_T("255"));
	m_pantB.SetWindowTextW(_T("255"));
}

void CPlayerTool::Ui_Silder_Set(CSliderCtrl* silder)
{
	silder->SetRange(0, 255);
	silder->SetRangeMin(0);
	silder->SetRangeMax(255);
	silder->SetTicFreq(1);
	silder->SetLineSize(1);
	silder->SetPageSize(1);
	silder->SetPos(255);
}

void CPlayerTool::OnLoadData()
{

	TCHAR szFullPath[MAX_PATH] = L"../Assets/Player/";
	TCHAR pFilePathType[9][MAX_STR] = { L"eye", L"hair1", L"hair2", L"hair3", L"hair4", L"hair5", L"pant", L"shirt", L"skin" };
	TCHAR pFilePathState[3][MAX_STR] = { L"front", L"side", L"back" };


	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 6; ++k) {
				//눈이 back일때
				if (i == 0 && j == 2) {
					continue;
				}

				CString strTileName;
				CString szFilePath;

				szFilePath.Format(L"../Assets/Player/%s/walk/%s/%s_%d.png", pFilePathType[i], pFilePathState[j], pFilePathState[j], k + 1);
				strTileName.Format(L"%s_walk%s_%d", pFilePathType[i], pFilePathState[j], k + 1);
				m_playerImagePath.insert({ strTileName, szFilePath });
			}
		}
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 3; ++j) {
			//눈이 back일때
			if (i == 0 && j == 2) {
				continue;
			}

			CString strTileName;
			CString szFilePath;

			szFilePath.Format(L"../Assets/Player/%s/idle/%s/%s_%d.png", pFilePathType[i], pFilePathState[j], pFilePathState[j], 1);
			strTileName.Format(L"%s_idle%s_%d", pFilePathType[i], pFilePathState[j], 1);
			m_playerImagePath.insert({ strTileName, szFilePath });
		}
	}
}

void CPlayerTool::ChangeImageColorInitRender()
{
	CImage* _copySkin = new CImage;
	CImage* _copyHair = new CImage;
	CImage* _copyEye = new CImage;
	CImage* _copyShirt = new CImage;
	CImage* _copyPant = new CImage;

	_copySkin->Load(m_playerImagePath[L"skin_idlefront_1"]);
	_copySkin->SetTransparentColor(RGB(255, 255, 255));
	_copyHair->Load(m_playerImagePath[L"hair1_idlefront_1"]);
	_copyHair->SetTransparentColor(RGB(255, 255, 255));
	_copyEye->Load(m_playerImagePath[L"eye_idlefront_1"]);
	_copyEye->SetTransparentColor(RGB(255, 255, 255));
	_copyShirt->Load(m_playerImagePath[L"shirt_idlefront_1"]);
	_copyShirt->SetTransparentColor(RGB(255, 255, 255));
	_copyPant->Load(m_playerImagePath[L"pant_idlefront_1"]);
	_copyPant->SetTransparentColor(RGB(255, 255, 255));

	ChangeColor(_copySkin, &m_skinR, &m_skinG, &m_skinB);
	ChangeColor(_copyHair, &m_hairR, &m_hairG, &m_hairB);
	ChangeColor(_copyEye, &m_eyeR, &m_eyeG, &m_eyeB);
	ChangeColor(_copyShirt, &m_shirtR, &m_shirtG, &m_shirtB);
	ChangeColor(_copyPant, &m_pantR, &m_pantG, &m_pantB);

	

	Invalidate(FALSE);
	CClientDC dc(&PlayerPreviewImg);
	CRect rect;
	PlayerPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	_copySkin->Draw(dc, rect);
	_copyHair->Draw(dc, rect);
	_copyEye->Draw(dc, rect);
	_copyShirt->Draw(dc, rect);
	_copyPant->Draw(dc, rect);

	Safe_Delete(_copySkin);
	Safe_Delete(_copyHair);
	Safe_Delete(_copyEye);
	Safe_Delete(_copyShirt);
	Safe_Delete(_copyPant);
}


void CPlayerTool::ChangeColor(CImage* image, CEdit* R, CEdit* G, CEdit* B)
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

void CPlayerTool::RenderPlayer()
{
	Invalidate(FALSE);
	CClientDC dc(&PlayerPreviewImg);
	CRect rect;
	PlayerPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));

	m_DecoSkin->Draw(dc, rect);
	m_DecoHair->Draw(dc, rect);
	m_Decoeye->Draw(dc, rect);
	m_Decoshirt->Draw(dc, rect);
	m_Decopant->Draw(dc, rect);
}

void CPlayerTool::InitDeco()
{
	Safe_Delete(m_DecoSkin);
	Safe_Delete(m_DecoHair);
	Safe_Delete(m_Decoeye);
	Safe_Delete(m_Decoshirt);
	Safe_Delete(m_Decopant);

	COLORREF transparentColor = RGB(255, 255, 255);

	m_DecoSkin = new CImage();
	m_DecoSkin->Load(m_playerImagePath[L"skin_idlefront_1"]);
	m_DecoSkin->SetTransparentColor(transparentColor);
	m_DecoHair = new CImage();
	m_DecoHair->Load(m_playerImagePath[L"hair1_idlefront_1"]);
	m_DecoHair->SetTransparentColor(transparentColor);
	m_Decoeye = new CImage();
	m_Decoeye->Load(m_playerImagePath[L"eye_idlefront_1"]);
	m_Decoeye->SetTransparentColor(transparentColor);
	m_Decoshirt = new CImage();
	m_Decoshirt->Load(m_playerImagePath[L"shirt_idlefront_1"]);
	m_Decoshirt->SetTransparentColor(transparentColor);
	m_Decopant = new CImage();
	m_Decopant->Load(m_playerImagePath[L"pant_idlefront_1"]);
	m_Decopant->SetTransparentColor(transparentColor);


	m_skinR.SetWindowTextW(_T("255"));
	m_skinG.SetWindowTextW(_T("255"));
	m_skinB.SetWindowTextW(_T("255"));
	m_hairR.SetWindowTextW(_T("255"));
	m_hairG.SetWindowTextW(_T("255"));
	m_hairB.SetWindowTextW(_T("255"));
	m_eyeR.SetWindowTextW(_T("255"));
	m_eyeG.SetWindowTextW(_T("255"));
	m_eyeB.SetWindowTextW(_T("255"));
	m_shirtR.SetWindowTextW(_T("255"));
	m_shirtG.SetWindowTextW(_T("255"));
	m_shirtB.SetWindowTextW(_T("255"));
	m_pantR.SetWindowTextW(_T("255"));
	m_pantG.SetWindowTextW(_T("255"));
	m_pantB.SetWindowTextW(_T("255"));


	m_silderSkinR.SetPos(255);
	m_silderSkinG.SetPos(255);
	m_silderSkinB.SetPos(255);
	m_silderHairR.SetPos(255);
	m_silderHairG.SetPos(255);
	m_silderHairB.SetPos(255);
	m_silderEyeR.SetPos(255);
	m_silderEyeG.SetPos(255);
	m_silderEyeB.SetPos(255);
	m_silderShirtR.SetPos(255);
	m_silderShirtG.SetPos(255);
	m_silderShirtB.SetPos(255);
	m_silderPantR.SetPos(255);
	m_silderPantG.SetPos(255);
	m_silderPantB.SetPos(255);

}



BEGIN_MESSAGE_MAP(CPlayerTool, CDialog)
	ON_WM_HSCROLL()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON4, &CPlayerTool::OnLoadPlayerBasic)
	//ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CPlayerTool::OnChangeHairType)
	ON_BN_CLICKED(IDC_BUTTON3, &CPlayerTool::OnClickFront)
	ON_BN_CLICKED(IDC_BUTTON5, &CPlayerTool::OnClickSide)
	ON_BN_CLICKED(IDC_BUTTON6, &CPlayerTool::OnClickBack)
	ON_BN_CLICKED(IDC_BUTTON8, &CPlayerTool::OnPlayerSave)
	ON_BN_CLICKED(IDC_BUTTON9, &CPlayerTool::OnPlayerLoad)
	ON_BN_CLICKED(IDC_CHECK2, &CPlayerTool::OnAnimation)
END_MESSAGE_MAP()


void CPlayerTool::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CString temp;
	int nSPos = 0;
	if (pScrollBar) {
		if (pScrollBar == (CScrollBar*)&m_silderSkinR) {
			nSPos = m_silderSkinR.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_skinR.SetWindowTextW(temp);
		}else if (pScrollBar == (CScrollBar*)&m_silderSkinG) {
			nSPos = m_silderSkinG.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_skinG.SetWindowTextW(temp);
		}else if (pScrollBar == (CScrollBar*)&m_silderSkinB) {
			nSPos = m_silderSkinB.GetPos();
			temp.Format(_T("%d"), nSPos);
			m_skinB.SetWindowTextW(temp);
		}else if (pScrollBar == (CScrollBar*)&m_silderHairR) {
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
	ChangeImageColorInitRender();
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPlayerTool::OnDestroy()
{
	Safe_Delete(m_DecoSkin);
	Safe_Delete(m_DecoHair);
	Safe_Delete(m_Decoeye);
	Safe_Delete(m_Decoshirt);
	Safe_Delete(m_Decopant);
}


void CPlayerTool::OnLoadPlayerBasic()
{
	InitDeco();

	m_hairIndex = 0;

	CClientDC dc(&PlayerPreviewImg);
	CRect rect;
	PlayerPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));

	m_DecoSkin->Draw(dc, rect);
	m_DecoHair->Draw(dc, rect);
	m_Decoeye->Draw(dc, rect);
	m_Decoshirt->Draw(dc, rect);
	m_Decopant->Draw(dc, rect);
}


//void CPlayerTool::OnChangeHairType(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
//
//	if (pNMUpDown->iDelta < 0) {
//		//오른쪽 누름
//		m_hairIndex++;
//		if (m_hairIndex == m_vecHair[IDLE][FRONT].size()) {
//			m_hairIndex = 0;
//		}
//	}
//	else {
//		//왼쪽 누름
//		m_hairIndex--;
//		if (m_hairIndex < 0) {
//			m_hairIndex = m_vecHair[IDLE][FRONT].size() - 1;
//		}
//	}
//
//	Safe_Delete(m_DecoHair);
//
//	m_DecoHair = new CImage();
//	m_DecoHair->Load(m_vecHair[IDLE][FRONT][m_hairIndex]);
//	m_DecoHair->SetTransparentColor(RGB(255, 255, 255));
//
//	RenderPlayer();
//
//	*pResult = 0;
//}



void CPlayerTool::OnClickFront()
{
	m_playerLook = FRONT;
	CImage* _copySkin = new CImage;
	CImage* _copyHair = new CImage;
	CImage* _copyEye = new CImage;
	CImage* _copyShirt = new CImage;
	CImage* _copyPant = new CImage;

	_copySkin->Load(m_playerImagePath[L"skin_idlefront_1"]);
	_copySkin->SetTransparentColor(RGB(255, 255, 255));
	_copyHair->Load(m_playerImagePath[L"hair1_idlefront_1"]);
	_copyHair->SetTransparentColor(RGB(255, 255, 255));
	_copyEye->Load(m_playerImagePath[L"eye_idlefront_1"]);
	_copyEye->SetTransparentColor(RGB(255, 255, 255));
	_copyShirt->Load(m_playerImagePath[L"shirt_idlefront_1"]);
	_copyShirt->SetTransparentColor(RGB(255, 255, 255));
	_copyPant->Load(m_playerImagePath[L"pant_idlefront_1"]);
	_copyPant->SetTransparentColor(RGB(255, 255, 255));

	ChangeColor(_copySkin, &m_skinR, &m_skinG, &m_skinB);
	ChangeColor(_copyHair, &m_hairR, &m_hairG, &m_hairB);
	ChangeColor(_copyEye, &m_eyeR, &m_eyeG, &m_eyeB);
	ChangeColor(_copyShirt, &m_shirtR, &m_shirtG, &m_shirtB);
	ChangeColor(_copyPant, &m_pantR, &m_pantG, &m_pantB);



	Invalidate(FALSE);
	CClientDC dc(&PlayerPreviewImg);
	CRect rect;
	PlayerPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	_copySkin->Draw(dc, rect);
	_copyHair->Draw(dc, rect);
	_copyEye->Draw(dc, rect);
	_copyShirt->Draw(dc, rect);
	_copyPant->Draw(dc, rect);

	Safe_Delete(_copySkin);
	Safe_Delete(_copyHair);
	Safe_Delete(_copyEye);
	Safe_Delete(_copyShirt);
	Safe_Delete(_copyPant);
}


void CPlayerTool::OnClickSide()
{
	m_playerLook = SIDE;
	CImage* _copySkin = new CImage;
	CImage* _copyHair = new CImage;
	CImage* _copyEye = new CImage;
	CImage* _copyShirt = new CImage;
	CImage* _copyPant = new CImage;

	_copySkin->Load(m_playerImagePath[L"skin_idleside_1"]);
	_copySkin->SetTransparentColor(RGB(255, 255, 255));
	_copyHair->Load(m_playerImagePath[L"hair1_idleside_1"]);
	_copyHair->SetTransparentColor(RGB(255, 255, 255));
	_copyEye->Load(m_playerImagePath[L"eye_idleside_1"]);
	_copyEye->SetTransparentColor(RGB(255, 255, 255));
	_copyShirt->Load(m_playerImagePath[L"shirt_idleside_1"]);
	_copyShirt->SetTransparentColor(RGB(255, 255, 255));
	_copyPant->Load(m_playerImagePath[L"pant_idleside_1"]);
	_copyPant->SetTransparentColor(RGB(255, 255, 255));

	ChangeColor(_copySkin, &m_skinR, &m_skinG, &m_skinB);
	ChangeColor(_copyHair, &m_hairR, &m_hairG, &m_hairB);
	ChangeColor(_copyEye, &m_eyeR, &m_eyeG, &m_eyeB);
	ChangeColor(_copyShirt, &m_shirtR, &m_shirtG, &m_shirtB);
	ChangeColor(_copyPant, &m_pantR, &m_pantG, &m_pantB);



	Invalidate(FALSE);
	CClientDC dc(&PlayerPreviewImg);
	CRect rect;
	PlayerPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	_copySkin->Draw(dc, rect);
	_copyHair->Draw(dc, rect);
	_copyEye->Draw(dc, rect);
	_copyShirt->Draw(dc, rect);
	_copyPant->Draw(dc, rect);

	Safe_Delete(_copySkin);
	Safe_Delete(_copyHair);
	Safe_Delete(_copyEye);
	Safe_Delete(_copyShirt);
	Safe_Delete(_copyPant);
}


void CPlayerTool::OnClickBack()
{
	m_playerLook = BACK;
	CImage* _copySkin = new CImage;
	CImage* _copyHair = new CImage;
	CImage* _copyShirt = new CImage;
	CImage* _copyPant = new CImage;

	_copySkin->Load(m_playerImagePath[L"skin_idleback_1"]);
	_copySkin->SetTransparentColor(RGB(255, 255, 255));
	_copyHair->Load(m_playerImagePath[L"hair1_idleback_1"]);
	_copyHair->SetTransparentColor(RGB(255, 255, 255));
	_copyShirt->Load(m_playerImagePath[L"shirt_idleback_1"]);
	_copyShirt->SetTransparentColor(RGB(255, 255, 255));
	_copyPant->Load(m_playerImagePath[L"pant_idleback_1"]);
	_copyPant->SetTransparentColor(RGB(255, 255, 255));

	ChangeColor(_copySkin, &m_skinR, &m_skinG, &m_skinB);
	ChangeColor(_copyShirt, &m_shirtR, &m_shirtG, &m_shirtB);
	ChangeColor(_copyPant, &m_pantR, &m_pantG, &m_pantB);
	ChangeColor(_copyHair, &m_hairR, &m_hairG, &m_hairB);


	Invalidate(FALSE);
	CClientDC dc(&PlayerPreviewImg);
	CRect rect;
	PlayerPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	_copySkin->Draw(dc, rect);
	_copyShirt->Draw(dc, rect);
	_copyPant->Draw(dc, rect);
	_copyHair->Draw(dc, rect);

	Safe_Delete(_copySkin);
	Safe_Delete(_copyHair);
	Safe_Delete(_copyShirt);
	Safe_Delete(_copyPant);
}


void CPlayerTool::OnPlayerSave()
{
	m_playerData.iHp = 100;
	m_playerData.iAttack = 10;

	CString strR, strG, strB;
	m_skinR.GetWindowTextW(strR);
	m_playerData.eSkinRGB.iR = _ttoi(strR);
	m_skinG.GetWindowTextW(strG);
	m_playerData.eSkinRGB.iG = _ttoi(strG);
	m_skinB.GetWindowTextW(strB);
	m_playerData.eSkinRGB.iB = _ttoi(strB);

	m_hairR.GetWindowTextW(strR);
	m_playerData.eHairRGB.iR = _ttoi(strR);
	m_hairG.GetWindowTextW(strG);
	m_playerData.eHairRGB.iG = _ttoi(strG);
	m_hairB.GetWindowTextW(strB);
	m_playerData.eHairRGB.iB = _ttoi(strB);

	m_eyeR.GetWindowTextW(strR);
	m_playerData.eEyeRGB.iR = _ttoi(strR);
	m_eyeG.GetWindowTextW(strG);
	m_playerData.eEyeRGB.iG = _ttoi(strG);
	m_eyeB.GetWindowTextW(strB);
	m_playerData.eEyeRGB.iB = _ttoi(strB);

	m_shirtR.GetWindowTextW(strR);
	m_playerData.eShirtRGB.iR = _ttoi(strR);
	m_shirtG.GetWindowTextW(strG);
	m_playerData.eShirtRGB.iG = _ttoi(strG);
	m_shirtB.GetWindowTextW(strB);
	m_playerData.eShirtRGB.iB = _ttoi(strB);

	m_pantR.GetWindowTextW(strR);
	m_playerData.ePantRGB.iR = _ttoi(strR);
	m_pantG.GetWindowTextW(strG);
	m_playerData.ePantRGB.iG = _ttoi(strG);
	m_pantB.GetWindowTextW(strB);
	m_playerData.ePantRGB.iB = _ttoi(strB);

	CFileDialog		Dlg(FALSE,	L"dat",	L"*.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Data Files(*.dat) | *.dat ||", this);

	TCHAR	szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{

		CString	str = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();

		HANDLE hFile = CreateFile(pGetPath,
			GENERIC_WRITE,
			0, 0,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte(0), dwStrByte(0);

		// value 값 저장
		WriteFile(hFile, &(m_playerData.iHp), sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &(m_playerData.iAttack), sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &(m_playerData.eSkinRGB), sizeof(PLAYERRGB), &dwByte, nullptr);
		WriteFile(hFile, &(m_playerData.eHairRGB), sizeof(PLAYERRGB), &dwByte, nullptr);
		WriteFile(hFile, &(m_playerData.eEyeRGB), sizeof(PLAYERRGB), &dwByte, nullptr);
		WriteFile(hFile, &(m_playerData.eShirtRGB), sizeof(PLAYERRGB), &dwByte, nullptr);
		WriteFile(hFile, &(m_playerData.ePantRGB), sizeof(PLAYERRGB), &dwByte, nullptr);

		CloseHandle(hFile);
	}
}


void CPlayerTool::OnPlayerLoad()
{
	CFileDialog		Dlg(TRUE,	L"dat",	L"*.dat",	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Data Files(*.dat) | *.dat ||", this);

	TCHAR	szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);

	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		CString	str = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();

		HANDLE hFile = CreateFile(pGetPath,
			GENERIC_READ,
			0, 0,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte(0), dwStrByte(0);
		UNITDATA		tData{};

		while (true)
		{
			ReadFile(hFile, &(tData.iHp), sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &(tData.iAttack), sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &(tData.eSkinRGB), sizeof(PLAYERRGB), &dwByte, nullptr);
			ReadFile(hFile, &(tData.eHairRGB), sizeof(PLAYERRGB), &dwByte, nullptr);
			ReadFile(hFile, &(tData.eEyeRGB), sizeof(PLAYERRGB), &dwByte, nullptr);
			ReadFile(hFile, &(tData.eShirtRGB), sizeof(PLAYERRGB), &dwByte, nullptr);
			ReadFile(hFile, &(tData.ePantRGB), sizeof(PLAYERRGB), &dwByte, nullptr);

			if (0 == dwByte)
			{
				break;
			}


			m_skinR.SetWindowTextW(std::to_wstring(tData.eSkinRGB.iR).c_str());
			m_skinG.SetWindowTextW(std::to_wstring(tData.eSkinRGB.iG).c_str());
			m_skinB.SetWindowTextW(std::to_wstring(tData.eSkinRGB.iB).c_str());

			m_hairR.SetWindowTextW(std::to_wstring(tData.eHairRGB.iR).c_str());
			m_hairG.SetWindowTextW(std::to_wstring(tData.eHairRGB.iG).c_str());
			m_hairB.SetWindowTextW(std::to_wstring(tData.eHairRGB.iB).c_str());

			m_eyeR.SetWindowTextW(std::to_wstring(tData.eEyeRGB.iR).c_str());
			m_eyeG.SetWindowTextW(std::to_wstring(tData.eEyeRGB.iG).c_str());
			m_eyeB.SetWindowTextW(std::to_wstring(tData.eEyeRGB.iB).c_str());

			m_shirtR.SetWindowTextW(std::to_wstring(tData.eShirtRGB.iR).c_str());
			m_shirtG.SetWindowTextW(std::to_wstring(tData.eShirtRGB.iG).c_str());
			m_shirtB.SetWindowTextW(std::to_wstring(tData.eShirtRGB.iB).c_str());

			m_pantR.SetWindowTextW(std::to_wstring(tData.ePantRGB.iR).c_str());
			m_pantG.SetWindowTextW(std::to_wstring(tData.ePantRGB.iG).c_str());
			m_pantB.SetWindowTextW(std::to_wstring(tData.ePantRGB.iB).c_str());

			m_silderSkinR.SetPos(tData.eSkinRGB.iR);
			m_silderSkinG.SetPos(tData.eSkinRGB.iG);
			m_silderSkinB.SetPos(tData.eSkinRGB.iB);
			m_silderHairR.SetPos(tData.eHairRGB.iR);
			m_silderHairG.SetPos(tData.eHairRGB.iG);
			m_silderHairB.SetPos(tData.eHairRGB.iB);
			m_silderEyeR.SetPos(tData.eEyeRGB.iR);
			m_silderEyeG.SetPos(tData.eEyeRGB.iG);
			m_silderEyeB.SetPos(tData.eEyeRGB.iB);
			m_silderShirtR.SetPos(tData.eShirtRGB.iR);
			m_silderShirtG.SetPos(tData.eShirtRGB.iG);
			m_silderShirtB.SetPos(tData.eShirtRGB.iB);
			m_silderPantR.SetPos(tData.ePantRGB.iR);
			m_silderPantG.SetPos(tData.ePantRGB.iG);
			m_silderPantB.SetPos(tData.ePantRGB.iB);
		}

		CloseHandle(hFile);
	}
}


void CPlayerTool::OnAnimation()
{
	if (m_AnimationOn.GetCheck() == BST_CHECKED)
	{
		m_currentImageIndex = 0; 
		SetTimer(1, 100, NULL);
	}
	else
	{
		KillTimer(1);

		switch (m_playerLook)
		{
		case CPlayerTool::FRONT:
			OnClickFront();
			break;
		case CPlayerTool::SIDE:
			OnClickSide();
			break;
		case CPlayerTool::BACK:
			OnClickBack();
			break;
		case CPlayerTool::LOOK_END:
			break;
		default:
			break;
		}
	}
}

void CPlayerTool::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) 
	{
		TCHAR pFilePathType[9][MAX_STR] = { L"eye", L"hair1", L"hair2", L"hair3", L"hair4", L"hair5", L"pant", L"shirt", L"skin" };
		CImage* _copySkin = new CImage;
		CImage* _copyHair = new CImage;
		CImage* _copyEye = new CImage;
		CImage* _copyShirt = new CImage;
		CImage* _copyPant = new CImage;
		CString strTileName;

		CClientDC dc(&PlayerPreviewImg);
		CRect rect;
		PlayerPreviewImg.GetClientRect(&rect);

		switch (m_playerLook)
		{
		case CPlayerTool::FRONT:
			strTileName.Format(L"%s_walkfront_%d", pFilePathType[0], m_currentImageIndex + 1);
			_copyEye->Load(m_playerImagePath[strTileName]);
			_copyEye->SetTransparentColor(RGB(255, 255, 255));

			strTileName.Format(L"%s_walkfront_%d", pFilePathType[8], m_currentImageIndex + 1);
			_copySkin->Load(m_playerImagePath[strTileName]);
			_copySkin->SetTransparentColor(RGB(255, 255, 255));

			strTileName.Format(L"%s_walkfront_%d", pFilePathType[1], m_currentImageIndex + 1);
			_copyHair->Load(m_playerImagePath[strTileName]);
			_copyHair->SetTransparentColor(RGB(255, 255, 255));

			strTileName.Format(L"%s_walkfront_%d", pFilePathType[7], m_currentImageIndex + 1);
			_copyShirt->Load(m_playerImagePath[strTileName]);
			_copyShirt->SetTransparentColor(RGB(255, 255, 255));

			strTileName.Format(L"%s_walkfront_%d", pFilePathType[6], m_currentImageIndex + 1);
			_copyPant->Load(m_playerImagePath[strTileName]);
			_copyPant->SetTransparentColor(RGB(255, 255, 255));

			ChangeColor(_copySkin, &m_skinR, &m_skinG, &m_skinB);
			ChangeColor(_copyEye, &m_eyeR, &m_eyeG, &m_eyeB);
			ChangeColor(_copyShirt, &m_shirtR, &m_shirtG, &m_shirtB);
			ChangeColor(_copyPant, &m_pantR, &m_pantG, &m_pantB);
			ChangeColor(_copyHair, &m_hairR, &m_hairG, &m_hairB);


			Invalidate(FALSE);

			dc.FillSolidRect(rect, RGB(255, 255, 255));
			_copySkin->Draw(dc, rect);
			_copyShirt->Draw(dc, rect);
			_copyEye->Draw(dc, rect);
			_copyPant->Draw(dc, rect);
			_copyHair->Draw(dc, rect);
			break;
		case CPlayerTool::SIDE:
			strTileName.Format(L"%s_walkside_%d", pFilePathType[0], m_currentImageIndex + 1);
			_copyEye->Load(m_playerImagePath[strTileName]);
			_copyEye->SetTransparentColor(RGB(255, 255, 255));

			strTileName.Format(L"%s_walkside_%d", pFilePathType[8], m_currentImageIndex + 1);
			_copySkin->Load(m_playerImagePath[strTileName]);
			_copySkin->SetTransparentColor(RGB(255, 255, 255));

			strTileName.Format(L"%s_walkside_%d", pFilePathType[1], m_currentImageIndex + 1);
			_copyHair->Load(m_playerImagePath[strTileName]);
			_copyHair->SetTransparentColor(RGB(255, 255, 255));

			strTileName.Format(L"%s_walkside_%d", pFilePathType[7], m_currentImageIndex + 1);
			_copyShirt->Load(m_playerImagePath[strTileName]);
			_copyShirt->SetTransparentColor(RGB(255, 255, 255));

			strTileName.Format(L"%s_walkside_%d", pFilePathType[6], m_currentImageIndex + 1);
			_copyPant->Load(m_playerImagePath[strTileName]);
			_copyPant->SetTransparentColor(RGB(255, 255, 255));

			ChangeColor(_copySkin, &m_skinR, &m_skinG, &m_skinB);
			ChangeColor(_copyEye, &m_eyeR, &m_eyeG, &m_eyeB);
			ChangeColor(_copyShirt, &m_shirtR, &m_shirtG, &m_shirtB);
			ChangeColor(_copyPant, &m_pantR, &m_pantG, &m_pantB);
			ChangeColor(_copyHair, &m_hairR, &m_hairG, &m_hairB);


			Invalidate(FALSE);

			dc.FillSolidRect(rect, RGB(255, 255, 255));
			_copySkin->Draw(dc, rect);
			_copyShirt->Draw(dc, rect);
			_copyEye->Draw(dc, rect);
			_copyPant->Draw(dc, rect);
			_copyHair->Draw(dc, rect);
			break;
		case CPlayerTool::BACK:

			strTileName.Format(L"%s_walkback_%d", pFilePathType[8], m_currentImageIndex + 1);
			_copySkin->Load(m_playerImagePath[strTileName]);
			_copySkin->SetTransparentColor(RGB(255, 255, 255));

			strTileName.Format(L"%s_walkback_%d", pFilePathType[1], m_currentImageIndex + 1);
			_copyHair->Load(m_playerImagePath[strTileName]);
			_copyHair->SetTransparentColor(RGB(255, 255, 255));

			strTileName.Format(L"%s_walkback_%d", pFilePathType[7], m_currentImageIndex + 1);
			_copyShirt->Load(m_playerImagePath[strTileName]);
			_copyShirt->SetTransparentColor(RGB(255, 255, 255));

			strTileName.Format(L"%s_walkback_%d", pFilePathType[6], m_currentImageIndex + 1);
			_copyPant->Load(m_playerImagePath[strTileName]);
			_copyPant->SetTransparentColor(RGB(255, 255, 255));

			ChangeColor(_copySkin, &m_skinR, &m_skinG, &m_skinB);
			ChangeColor(_copyShirt, &m_shirtR, &m_shirtG, &m_shirtB);
			ChangeColor(_copyPant, &m_pantR, &m_pantG, &m_pantB);
			ChangeColor(_copyHair, &m_hairR, &m_hairG, &m_hairB);


			Invalidate(FALSE);

			dc.FillSolidRect(rect, RGB(255, 255, 255));
			_copySkin->Draw(dc, rect);
			_copyShirt->Draw(dc, rect);
			_copyPant->Draw(dc, rect);
			_copyHair->Draw(dc, rect);
			break;
		case CPlayerTool::LOOK_END:
			break;
		default:
			break;
		}
		m_currentImageIndex = (m_currentImageIndex + 1) % 6;

		Safe_Delete(_copySkin);
		Safe_Delete(_copyHair);
		Safe_Delete(_copyEye);
		Safe_Delete(_copyShirt);
		Safe_Delete(_copyPant);
	}

	CWnd::OnTimer(nIDEvent);  // 기본 타이머 처리
}