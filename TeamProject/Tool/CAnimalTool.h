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
private:
	enum ANIMAL{COW, TURTLE, DODO, ANIMAL_END};
	enum ACTION{IDLE, WALK, EAT, SLEEP, SLEEPING, WAKEUP, ACTION_END};
	void OnLoadData();
	void AddMap(const CString& type, int idleCnt, int walkCnt, int eatCnt, int sleepCnt, int sleepingCnt, int wakeupCnt);
	void StopRender(); //애니메이션 멈췄을 때
private:
	map<CString, CImage*>	m_animalImage;
	int m_currentImageIndex;
	int m_maxIndex[ANIMAL_END][ACTION_END];

	ANIMAL m_eAnimal;
	ACTION m_eAction;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickCow();
	afx_msg void OnClickTurtle();
	afx_msg void OnClickDodo();
	CStatic AnimalPreviewImg;
	afx_msg void OnAnimaltion();
	CButton m_AnimationOn;
	afx_msg void OnClickIdle();
	afx_msg void OnClickwalk();
	afx_msg void OnClickeat();
	afx_msg void OnClicksleep();
	afx_msg void OnClicksleeping();
	afx_msg void OnClickwakeup();
};
