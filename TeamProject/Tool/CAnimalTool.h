#pragma once
#include "afxdialogex.h"


// CAnimalTool 대화 상자

class CAnimalTool : public CDialog
{
	DECLARE_DYNAMIC(CAnimalTool)

public:
	CAnimalTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAnimalTool();
	void	OnInitialUpdate();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAnimalTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
