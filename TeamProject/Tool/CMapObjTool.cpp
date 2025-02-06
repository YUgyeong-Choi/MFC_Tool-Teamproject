// CMapObjTool.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CMapObjTool.h"
#include "CFileInfo.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "CTerrain.h"

// CMapObjTool 대화 상자

IMPLEMENT_DYNAMIC(CMapObjTool, CDialog)

CMapObjTool::CMapObjTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CMapObjTool, pParent), m_iImgCurIndex(0)
{

}

CMapObjTool::~CMapObjTool()
{
}

void CMapObjTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO2, m_FurnitureSelect[0]);
	DDX_Control(pDX, IDC_RADIO3, m_FurnitureSelect[1]);
	DDX_Control(pDX, IDC_RADIO5, m_FurnitureSelect[2]);
	DDX_Control(pDX, IDC_SPIN3, m_spinCtrl);
	DDX_Control(pDX, IDC_PICTURE, m_ImgPreview);
}

void CMapObjTool::OnInitialUpdate()
{

}


BEGIN_MESSAGE_MAP(CMapObjTool, CDialog)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CMapObjTool::OnDeltaposSpin3)
END_MESSAGE_MAP()


// CMapObjTool 메시지 처리기





BOOL CMapObjTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	HBITMAP		hBitmap0 = (HBITMAP)LoadImage(NULL,
		L"../Assets/Map/Button_Icon/button_function.bmp",
		IMAGE_BITMAP,
		32,
		32,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HBITMAP		hBitmap1 = (HBITMAP)LoadImage(NULL,
		L"../Assets/Map/Button_Icon/button_furniture.bmp",
		IMAGE_BITMAP,
		32,
		32,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HBITMAP		hBitmap2 = (HBITMAP)LoadImage(NULL,
		L"../Assets/Map/Button_Icon/button_deco.bmp",
		IMAGE_BITMAP,
		32,
		32,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);


	m_FurnitureSelect[0].SetBitmap(hBitmap0);
	m_FurnitureSelect[1].SetBitmap(hBitmap1);
	m_FurnitureSelect[2].SetBitmap(hBitmap2);


	m_spinCtrl.SetRange(0, 25); // all 43
	m_spinCtrl.SetPos(0);



	CImage* pPngImage = new CImage;

	//swprintf_s(szFullPath, MAX_PATH, L"../Assets/Map/%s/%s/%s_%s%d.png", pFilePath, szTileOption, pFilePath, szTileOption, i + 1);
	//if (iErr == 0 && FAILED(pPngImage->Load(L"../Assets/Object/")))
	//{
	//	AfxMessageBox(lstrcat(szFullPath, L" Load Failed"));
	//	iErr = -1;
	//	iCnt = iFullCnt;
	//}

	//m_mapPngImage.insert({ strTileName, pPngImage });


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMapObjTool::OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int newIndex = m_iImgCurIndex + pNMUpDown->iDelta;
	if (newIndex < 0) newIndex = 25;
	if (newIndex > 25) newIndex = 0;
	m_iImgCurIndex = newIndex;


	*pResult = 0;
}
