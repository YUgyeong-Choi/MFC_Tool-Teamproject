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
}

void CPlayerTool::OnInitialUpdate()
{
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
	//스킨
	m_Skin[IDLE][FRONT] = L"../Assets/Player/skin/idle/front/front_1.png";
	m_Skin[IDLE][SIDE] = L"../Assets/Player/skin/idle/side/side_1.png";
	m_Skin[IDLE][BACK] = L"../Assets/Player/skin/idle/back/back_1.png";

	//눈
	m_eye[IDLE][FRONT] = L"../Assets/Player/eye/idle/front/front_1.png";
	m_eye[IDLE][SIDE] = L"../Assets/Player/eye/idle/side/side_1.png";

	//셔츠
	m_shirt[IDLE][FRONT] = L"../Assets/Player/shirt/idle/front/front_1.png";
	m_shirt[IDLE][SIDE] = L"../Assets/Player/shirt/idle/side/side_1.png";
	m_shirt[IDLE][BACK] = L"../Assets/Player/shirt/idle/back/back_1.png";

	//바지
	m_pant[IDLE][FRONT] = L"../Assets/Player/pant/idle/front/front_1.png";
	m_pant[IDLE][SIDE] = L"../Assets/Player/pant/idle/side/side_1.png";
	m_pant[IDLE][BACK] = L"../Assets/Player/pant/idle/back/back_1.png";

	//머리
	m_vecHair[IDLE][FRONT].push_back(L"../Assets/Player/hair/hair1/idle/front/front_1.png");
	m_vecHair[IDLE][SIDE].push_back(L"../Assets/Player/hair/hair1/idle/side/side_1.png");
	m_vecHair[IDLE][BACK].push_back(L"../Assets/Player/hair/hair1/idle/back/back_1.png");

	m_vecHair[IDLE][FRONT].push_back(L"../Assets/Player/hair/hair2/idle/front/front_1.png");
	m_vecHair[IDLE][SIDE].push_back(L"../Assets/Player/hair/hair2/idle/side/side_1.png");
	m_vecHair[IDLE][BACK].push_back(L"../Assets/Player/hair/hair2/idle/back/back_1.png");

	m_vecHair[IDLE][FRONT].push_back(L"../Assets/Player/hair/hair3/idle/front/front_1.png");
	m_vecHair[IDLE][SIDE].push_back(L"../Assets/Player/hair/hair3/idle/side/side_1.png");
	m_vecHair[IDLE][BACK].push_back(L"../Assets/Player/hair/hair3/idle/back/back_1.png");

	m_vecHair[IDLE][FRONT].push_back(L"../Assets/Player/hair/hair4/idle/front/front_1.png");
	m_vecHair[IDLE][SIDE].push_back(L"../Assets/Player/hair/hair4/idle/side/side_1.png");
	m_vecHair[IDLE][BACK].push_back(L"../Assets/Player/hair/hair4/idle/back/back_1.png");

	m_vecHair[IDLE][FRONT].push_back(L"../Assets/Player/hair/hair5/idle/front/front_1.png");
	m_vecHair[IDLE][SIDE].push_back(L"../Assets/Player/hair/hair5/idle/side/side_1.png");
	m_vecHair[IDLE][BACK].push_back(L"../Assets/Player/hair/hair5/idle/back/back_1.png");
}

void CPlayerTool::ChangeImageColorInitRender()
{
	CImage* _copySkin = new CImage;
	CImage* _copyHair = new CImage;
	CImage* _copyEye = new CImage;
	CImage* _copyShirt = new CImage;
	CImage* _copyPant = new CImage;

	_copySkin->Load(m_Skin[IDLE][FRONT]);
	_copySkin->SetTransparentColor(RGB(255, 255, 255));
	_copyHair->Load(m_vecHair[IDLE][FRONT][m_hairIndex]);
	_copyHair->SetTransparentColor(RGB(255, 255, 255));
	_copyEye->Load(m_eye[IDLE][FRONT]);
	_copyEye->SetTransparentColor(RGB(255, 255, 255));
	_copyShirt->Load(m_shirt[IDLE][FRONT]);
	_copyShirt->SetTransparentColor(RGB(255, 255, 255));
	_copyPant->Load(m_pant[IDLE][FRONT]);
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
	m_DecoSkin->Load(m_Skin[IDLE][FRONT]);
	m_DecoSkin->SetTransparentColor(transparentColor);
	m_DecoHair = new CImage();
	m_DecoHair->Load(m_vecHair[IDLE][FRONT][m_hairIndex]);
	m_DecoHair->SetTransparentColor(transparentColor);
	m_Decoeye = new CImage();
	m_Decoeye->Load(m_eye[IDLE][FRONT]);
	m_Decoeye->SetTransparentColor(transparentColor);
	m_Decoshirt = new CImage();
	m_Decoshirt->Load(m_shirt[IDLE][FRONT]);
	m_Decoshirt->SetTransparentColor(transparentColor);
	m_Decopant = new CImage();
	m_Decopant->Load(m_pant[IDLE][FRONT]);
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
	ON_BN_CLICKED(IDC_BUTTON1, &CPlayerTool::OnFinishColor)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON4, &CPlayerTool::OnLoadPlayerBasic)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CPlayerTool::OnChangeHairType)
	ON_BN_CLICKED(IDC_BUTTON3, &CPlayerTool::OnClickFront)
	ON_BN_CLICKED(IDC_BUTTON5, &CPlayerTool::OnClickSide)
	ON_BN_CLICKED(IDC_BUTTON6, &CPlayerTool::OnClickBack)
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


void CPlayerTool::OnFinishColor()
{
	ChangeColor(m_DecoSkin, &m_skinR, &m_skinG, &m_skinB);
	ChangeColor(m_DecoHair, &m_hairR, &m_hairG, &m_hairB);
	ChangeColor(m_Decoeye, &m_eyeR, &m_eyeG, &m_eyeB);
	ChangeColor(m_Decoshirt, &m_shirtR, &m_shirtG, &m_shirtB);
	ChangeColor(m_Decopant, &m_pantR, &m_pantG, &m_pantB);
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


void CPlayerTool::OnChangeHairType(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (pNMUpDown->iDelta < 0) {
		//오른쪽 누름
		m_hairIndex++;
		if (m_hairIndex == m_vecHair[IDLE][FRONT].size()) {
			m_hairIndex = 0;
		}
	}
	else {
		//왼쪽 누름
		m_hairIndex--;
		if (m_hairIndex < 0) {
			m_hairIndex = m_vecHair[IDLE][FRONT].size() - 1;
		}
	}

	Safe_Delete(m_DecoHair);

	m_DecoHair = new CImage();
	m_DecoHair->Load(m_vecHair[IDLE][FRONT][m_hairIndex]);
	m_DecoHair->SetTransparentColor(RGB(255, 255, 255));

	RenderPlayer();

	*pResult = 0;
}



void CPlayerTool::OnClickFront()
{
	CImage* _copySkin = new CImage;
	CImage* _copyHair = new CImage;
	CImage* _copyEye = new CImage;
	CImage* _copyShirt = new CImage;
	CImage* _copyPant = new CImage;

	_copySkin->Load(m_Skin[IDLE][FRONT]);
	_copySkin->SetTransparentColor(RGB(255, 255, 255));
	_copyHair->Load(m_vecHair[IDLE][FRONT][m_hairIndex]);
	_copyHair->SetTransparentColor(RGB(255, 255, 255));
	_copyEye->Load(m_eye[IDLE][FRONT]);
	_copyEye->SetTransparentColor(RGB(255, 255, 255));
	_copyShirt->Load(m_shirt[IDLE][FRONT]);
	_copyShirt->SetTransparentColor(RGB(255, 255, 255));
	_copyPant->Load(m_pant[IDLE][FRONT]);
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
	CImage* _copySkin = new CImage;
	CImage* _copyHair = new CImage;
	CImage* _copyEye = new CImage;
	CImage* _copyShirt = new CImage;
	CImage* _copyPant = new CImage;

	_copySkin->Load(m_Skin[IDLE][SIDE]);
	_copySkin->SetTransparentColor(RGB(255, 255, 255));
	_copyHair->Load(m_vecHair[IDLE][SIDE][m_hairIndex]);
	_copyHair->SetTransparentColor(RGB(255, 255, 255));
	_copyEye->Load(m_eye[IDLE][SIDE]);
	_copyEye->SetTransparentColor(RGB(255, 255, 255));
	_copyShirt->Load(m_shirt[IDLE][SIDE]);
	_copyShirt->SetTransparentColor(RGB(255, 255, 255));
	_copyPant->Load(m_pant[IDLE][SIDE]);
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
	CImage* _copySkin = new CImage;
	CImage* _copyHair = new CImage;
	CImage* _copyShirt = new CImage;
	CImage* _copyPant = new CImage;

	_copySkin->Load(m_Skin[IDLE][BACK]);
	_copySkin->SetTransparentColor(RGB(255, 255, 255));
	_copyHair->Load(m_vecHair[IDLE][BACK][m_hairIndex]);
	_copyHair->SetTransparentColor(RGB(255, 255, 255));
	_copyShirt->Load(m_shirt[IDLE][BACK]);
	_copyShirt->SetTransparentColor(RGB(255, 255, 255));
	_copyPant->Load(m_pant[IDLE][BACK]);
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
