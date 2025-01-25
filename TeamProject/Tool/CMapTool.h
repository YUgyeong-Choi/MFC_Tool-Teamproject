#pragma once
#include "afxdialogex.h"
#include "Include.h"

// CMapTool 대화 상자

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMapTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	void	Horizontal_Scroll();
	void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnLoadTileAssets();
	afx_msg void OnListBox();

public:
	// 리스트 박스
	CListBox m_ListBox;
	// 지형 콤보 박스
	CComboBox m_ctrlCMapType;
	// 유형 콤보 박스
	CComboBox m_crtlCType;

public:
	map<CString, CImage*>		m_mapPngImage;
	CStatic MapToolPreviewImg;
};
