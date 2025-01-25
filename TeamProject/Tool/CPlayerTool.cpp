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
	OnLoadHair();

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

void CPlayerTool::OnLoadHair()
{
	m_vecHair.push_back(new CImage());
	TCHAR szHairPath1[MAX_PATH] = L"../Assets/Player/hair/hair1/Miner_hair1_1.png";
	m_vecHair[0]->Load(szHairPath1);
	m_vecHair[0]->SetTransparentColor(RGB(255, 255, 255));

	m_vecHair.push_back(new CImage());
	TCHAR szHairPath2[MAX_PATH] = L"../Assets/Player/hair/hair2/Miner_hair2_1.png";
	m_vecHair[1]->Load(szHairPath2);
	m_vecHair[1]->SetTransparentColor(RGB(255, 255, 255));

	m_vecHair.push_back(new CImage());
	TCHAR szHairPath3[MAX_PATH] = L"../Assets/Player/hair/hair3/Miner_hair3_1.png";
	m_vecHair[2]->Load(szHairPath3);
	m_vecHair[2]->SetTransparentColor(RGB(255, 255, 255));


	//UpdateData(TRUE);

	//TCHAR szFullPath[MAX_PATH] = L"../Assets/Player/hair/har1/Miner_hair1_1";
	//TCHAR pFilePath[MAX_STR] = L"";
	//TCHAR szTileOption[MAX_STR] = L"";

	//int iFullCnt = 0;
	//int iCnt = 0;
	//int iErr = 0;

	//// 선택된 지형 받아옴
	//switch (m_ctrlCMapType.GetCurSel())
	//{
	//case 0://dirt
	//	lstrcpy(pFilePath, L"dirt_tileset");
	//	iFullCnt = 86;
	//	break;
	//case 1://sand
	//	lstrcpy(pFilePath, L"sand_tileset");
	//	iFullCnt = 55;
	//	break;
	//case 2://nature
	//	lstrcpy(pFilePath, L"nature_tileset");
	//	iFullCnt = 72;
	//	break;
	//case 3://stone
	//	lstrcpy(pFilePath, L"stone_tileset");
	//	iFullCnt = 70;
	//	break;
	//case 4://water
	//	lstrcpy(pFilePath, L"water_tileset");
	//	iFullCnt = 17;
	//	break;
	//default:
	//	iErr = -1;
	//	break;
	//}

	//// 선택된 유형 받아옴
	//switch (m_crtlCType.GetCurSel())
	//{
	//case 0://ground
	//	lstrcpy(szTileOption, L"ground");
	//	iCnt = 28;
	//	break;
	//case 1://wall
	//	lstrcpy(szTileOption, L"wallhead");
	//	iCnt = 21;
	//	break;
	//case 2://ore
	//	lstrcpy(szTileOption, L"ore");
	//	iCnt = 3;
	//	break;
	//case 3://deco
	//	lstrcpy(szTileOption, L"deco");
	//	iCnt = 18;
	//	break;
	//default:
	//	iErr = -1;
	//	break;
	//}


	//for (int i = 0; i < iCnt; ++i)
	//{
	//	CString strTileName;
	//	TCHAR pFilePath2[MAX_STR];
	//	CImage* pPngImage = new CImage;

	//	swprintf_s(szFullPath, MAX_PATH, L"../Assets/Map/%s/%s/%s_%s%d.png", pFilePath, szTileOption, pFilePath, szTileOption, i + 1);
	//	if (iErr == 0 && FAILED(pPngImage->Load(szFullPath)))
	//	{
	//		AfxMessageBox(lstrcat(szFullPath, L" Load Failed"));
	//		iErr = -1;
	//		iCnt = iFullCnt;
	//	}

	//	if (iErr == 0)
	//	{
	//		strTileName.Format(L"%s_%s%d", pFilePath, szTileOption, i + 1);
	//		swprintf_s(pFilePath2, MAX_STR, L"%s_%s%d", pFilePath, szTileOption, i + 1);
	//	}
	//	else // 선택된 값과 동일한 폴더가 존재하지 않을 경우 바깥쪽 폴더에서 분류 안 된 이미지 그냥 다 받아옴 (지금 흙만 분류해서 나머지는 기존과 동일하게 다받음) // 파일 다 정리되면 삭제 예정
	//	{
	//		swprintf_s(szFullPath, MAX_PATH, L"../Assets/Map/%s/%s%d.png", pFilePath, pFilePath, i + 1);
	//		pPngImage->Load(szFullPath);
	//		strTileName.Format(L"%s_%d", pFilePath, i + 1);
	//		swprintf_s(pFilePath2, MAX_STR, L"%s_%d", pFilePath, i + 1);
	//	}

	//	m_mapPngImage.insert({ strTileName, pPngImage });
	//	m_ListBox.AddString(pFilePath2);
	//}

	//Horizontal_Scroll();

	//UpdateData(FALSE);
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




	//image2 = new CImage;
	//TCHAR szFullPath2[MAX_PATH] = L"../Assets/Player/hair/hair1/Miner_hair1_1.png"; //머리
	//image2->Load(szFullPath2);

	//CRect rect;
	//PlayerPreviewImg.GetClientRect(&rect);
	//int centerX = rect.Width() * 0.5;
	//int centerY = rect.Height() * 0.5;
	//int leftX = centerX - image2->GetWidth() * 0.5;
	//int leftY = centerY - image2->GetHeight() * 0.5;

	//CDC* _dc = PlayerPreviewImg.GetDC();
	//
	//image2->Draw(_dc->m_hDC, leftX, leftY, image2->GetWidth(), image2->GetHeight());
	//image2->SetTransparentColor(RGB(255, 255, 255));

	//image3 = new CImage;
	//TCHAR szFullPath3[MAX_PATH] = L"../Assets/Player/pant/Miner_pants_1.png"; //머리
	//image3->Load(szFullPath3);

	//image3->Draw(_dc->m_hDC, leftX, leftY, image3->GetWidth(), image3->GetHeight());
	//image3->SetTransparentColor(RGB(255, 255, 255));
	//PlayerPreviewImg.ReleaseDC(_dc);
}

void CPlayerTool::OnPantColor()
{
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
	//스킨
	m_vecSkin.push_back(new CImage());
	TCHAR szSkinPath[MAX_PATH] = L"../Assets/Player/skin/idle/front/idle_front1.png"; 
	m_vecSkin[0]->Load(szSkinPath);
	COLORREF transparentColor = RGB(255, 255, 255);
	m_vecSkin[0]->SetTransparentColor(transparentColor);

	//눈
	m_eye = new CImage();
	TCHAR szEyePath[MAX_PATH] = L"../Assets/Player/eye/Miner_eyes_1.png";
	m_eye->Load(szEyePath);
	m_eye->SetTransparentColor(transparentColor);

	//셔츠
	m_shirt = new CImage();
	TCHAR szShirtPath[MAX_PATH] = L"../Assets/Player/shirt/Miner_shirt_1.png";
	m_shirt->Load(szShirtPath);
	m_shirt->SetTransparentColor(transparentColor);

	//바지
	m_pant = new CImage();
	TCHAR szPantPath[MAX_PATH] = L"../Assets/Player/pant/Miner_pants_1.png";
	m_pant->Load(szPantPath);
	m_pant->SetTransparentColor(transparentColor);

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
