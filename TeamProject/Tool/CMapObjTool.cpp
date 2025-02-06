﻿// CMapObjTool.cpp: 구현 파일
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
	: CDialog(IDD_CMapObjTool, pParent), m_iImgCurIndex(1)
{

}

CMapObjTool::~CMapObjTool()
{
}

void CMapObjTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO2, m_FurnitureSelect[0]); // deco
	DDX_Control(pDX, IDC_RADIO3, m_FurnitureSelect[1]); // func
	DDX_Control(pDX, IDC_RADIO5, m_FurnitureSelect[2]); // furn
	DDX_Control(pDX, IDC_SPIN3, m_spinCtrl);
	DDX_Control(pDX, IDC_PICTURE, m_ImgPreview);
}

void CMapObjTool::OnInitialUpdate()
{

}


BEGIN_MESSAGE_MAP(CMapObjTool, CDialog)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CMapObjTool::OnDeltaposSpin3)
	ON_WM_DESTROY()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CMapObjTool 메시지 처리기





BOOL CMapObjTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	HBITMAP		hBitmap0 = (HBITMAP)LoadImage(NULL,
		L"../Assets/Map/Button_Icon/button_deco.bmp",
		IMAGE_BITMAP,
		32,
		32,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HBITMAP		hBitmap1 = (HBITMAP)LoadImage(NULL,
		L"../Assets/Map/Button_Icon/button_function.bmp",
		IMAGE_BITMAP,
		32,
		32,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HBITMAP		hBitmap2 = (HBITMAP)LoadImage(NULL,
		L"../Assets/Map/Button_Icon/button_furniture.bmp",
		IMAGE_BITMAP,
		32,
		32,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);


	m_FurnitureSelect[0].SetBitmap(hBitmap0);
	m_FurnitureSelect[1].SetBitmap(hBitmap1);
	m_FurnitureSelect[2].SetBitmap(hBitmap2);

	
	m_spinCtrl.SetRange(0, 43); // all 43
	m_spinCtrl.SetPos(0);
	
	m_FurnitureSelect[0].SetCheck(BST_CHECKED);

	TCHAR	szFilePath[MAX_PATH] = L"../Assets/Map/object";

	int	iFileCnt = CFileInfo::DirFileCount(szFilePath);

	CFileInfo::DirInfoExtraction(szFilePath, m_PathInfoList);

	TCHAR		szBuf[MAX_STR] = L"";

	for (auto& pImgPath : m_PathInfoList)
	{
		for (int i = 0; i < pImgPath->iCount; ++i)
		{
			CImage* pPngImage = new CImage;
			TCHAR		szFullPath[MAX_PATH] = L"";
			swprintf_s(szFullPath, MAX_PATH, pImgPath->wstrPath.c_str(), i + 1);
			if (FAILED(pPngImage->Load(szFullPath)))
			{
				AfxMessageBox(L" Load Failed");
			}
			m_mapPngImage.insert({ szFullPath, pPngImage });
		}
	}

	auto& iter = m_PathInfoList.begin();

	TCHAR		szFullPath[MAX_PATH] = L"";
	swprintf_s(szFullPath, MAX_PATH, (*iter)->wstrPath.c_str(), 1);
	auto&	iterpngimage = m_mapPngImage.find(szFullPath);

	//선택한 이미지 종류 보여주는 곳
	m_ImgPreview.SetBitmap(*(iterpngimage->second));




	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMapObjTool::OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int ibuttonIndex = 0;
	auto& iter = m_PathInfoList.begin();
	for (; ibuttonIndex < 3; ++ibuttonIndex, ++iter)
	{
		if (m_FurnitureSelect[ibuttonIndex].GetCheck())
			break;
	}
	if (ibuttonIndex >= 3 || 0 > ibuttonIndex) return;


	int iMaxIndexCnt = (*iter)->iCount;
	int newIndex = m_iImgCurIndex + pNMUpDown->iDelta;
	if (newIndex < 1)
		newIndex = iMaxIndexCnt;
	if (newIndex > iMaxIndexCnt)
		newIndex = 1;
	m_iImgCurIndex = newIndex;


	TCHAR		szFullPath[MAX_PATH] = L"";
	swprintf_s(szFullPath, MAX_PATH, (*iter)->wstrPath.c_str(), m_iImgCurIndex);
	auto	iterpngimage = m_mapPngImage.find(szFullPath);

	if (iterpngimage == m_mapPngImage.end())
		return;

	//선택한 이미지 종류 보여주는 곳
	m_ImgPreview.SetBitmap(*(iterpngimage->second));

	*pResult = 0;
}


void CMapObjTool::OnDestroy()
{
	CDialog::OnDestroy();

	for_each(m_mapPngImage.begin(), m_mapPngImage.end(), [](auto& MyPair)
		{
			MyPair.second->Destroy();
			Safe_Delete(MyPair.second);
		});

	m_mapPngImage.clear();

	for_each(m_PathInfoList.begin(), m_PathInfoList.end(), Safe_Delete<IMGPATH*>);
	m_PathInfoList.clear();


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMapObjTool::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnRButtonDown(nFlags, point);
}
