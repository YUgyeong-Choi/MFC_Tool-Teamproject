﻿#pragma once
#include "afxdialogex.h"
#include "Include.h"

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
	virtual BOOL OnInitDialog();
	void	OnInitialUpdate();
	afx_msg void OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult);

	// // func2, general3, deco5
	CButton m_FurnitureSelect[3];

	CSpinButtonCtrl			m_spinCtrl;
	CStatic					m_ImgPreview;
	list<IMGPATH*>			m_PathInfoList;
	map<CString, CImage*>	m_mapPngImage;
	int		m_iImgCurIndex;
	afx_msg void OnDestroy();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	MAPOBJTYPE		Get_SelectedType() {
		for (int i = 0; i < MAPOBJ_END; ++i)
		{
			if (m_FurnitureSelect[i].GetCheck())
				return (MAPOBJTYPE)i;
		}
		return MAPOBJ_END;
	}
};
