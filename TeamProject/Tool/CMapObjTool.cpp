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
}

void CMapObjTool::OnInitialUpdate()
{

}


BEGIN_MESSAGE_MAP(CMapObjTool, CDialog)
END_MESSAGE_MAP()


// CMapObjTool 메시지 처리기


