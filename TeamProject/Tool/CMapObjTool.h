#pragma once
#include "afxdialogex.h"


// CMapObjTool 대화 상자

class CMapObjTool : public CDialog
{
	DECLARE_DYNAMIC(CMapObjTool)

public:
	CMapObjTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMapObjTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMapObjTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void	OnInitialUpdate();

};
