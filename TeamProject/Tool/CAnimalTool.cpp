// CAnimalTool.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CAnimalTool.h"


// CAnimalTool 대화 상자

IMPLEMENT_DYNAMIC(CAnimalTool, CDialog)

CAnimalTool::CAnimalTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CAnimalTool, pParent)
{

}

CAnimalTool::~CAnimalTool()
{
}

void CAnimalTool::OnInitialUpdate()
{
}

void CAnimalTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAnimalTool, CDialog)
END_MESSAGE_MAP()


// CAnimalTool 메시지 처리기
