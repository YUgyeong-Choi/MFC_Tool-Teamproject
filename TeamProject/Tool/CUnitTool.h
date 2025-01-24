#pragma once

#include "afxdialogex.h"
#include "Include.h"

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUnitTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
	afx_msg void OnDelete();
	afx_msg void OnSave();
	afx_msg void OnLoad();
	afx_msg void OnAdd();
	afx_msg void OnListBox();
	afx_msg void OnDestroy();

public:	// value

	CString m_strName;
	int m_iAttack;
	int m_iHp;

public:// control
	CListBox m_ListBox;
	CButton m_Radio[3];
	CButton m_Check[3];
	CButton m_Bitmap;
	CString m_strFindName;

private:
	map<CString, UNITDATA*>		m_mapUnitData;
public:
	

};
