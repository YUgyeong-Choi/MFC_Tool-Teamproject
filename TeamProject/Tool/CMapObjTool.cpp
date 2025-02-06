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
	: CDialog(IDD_CMapObjTool, pParent)
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
}

void CMapObjTool::OnInitialUpdate()
{

}


BEGIN_MESSAGE_MAP(CMapObjTool, CDialog)
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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
