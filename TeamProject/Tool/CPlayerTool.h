#pragma once
#include "afxdialogex.h"


// CPlayerTool 대화 상자

class CPlayerTool : public CDialog
{
	DECLARE_DYNAMIC(CPlayerTool)

public:
	CPlayerTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPlayerTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPlayerTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void OnInitialUpdate();
private:
	void Ui_Silder_Set(CSliderCtrl* silder);
private:
	CEdit m_hairR;
	CEdit m_hairG;
	CEdit m_hairB;
	CEdit m_eyeR;
	CEdit m_eyeG;
	CEdit m_eyeB;
	CEdit m_shirtR;
	CEdit m_shirtG;
	CEdit m_shirtB;
	CEdit m_pantR;
	CEdit m_pantG;
	CEdit m_pantB;
	CSliderCtrl m_silderHairR;
	CSliderCtrl m_silderHairG;
	CSliderCtrl m_silderHairB;
	CSliderCtrl m_silderEyeR;
	CSliderCtrl m_silderEyeG;
	CSliderCtrl m_silderEyeB;
	CSliderCtrl m_silderShirtR;
	CSliderCtrl m_silderShirtG;
	CSliderCtrl m_silderShirtB;
	CSliderCtrl m_silderPantR;
	CSliderCtrl m_silderPantG;
	CSliderCtrl m_silderPantB;
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHairColor();
	afx_msg void OnPantColor();
	afx_msg void OnShirtColor();
	afx_msg void OnEyeColor();
};
