// CAnimalTool.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CAnimalTool.h"
#include "Include.h"


// CAnimalTool 대화 상자

IMPLEMENT_DYNAMIC(CAnimalTool, CDialog)

CAnimalTool::CAnimalTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CAnimalTool, pParent)
{

}

CAnimalTool::~CAnimalTool()
{
}

BEGIN_MESSAGE_MAP(CAnimalTool, CDialog)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CAnimalTool::OnClickCow)
	ON_BN_CLICKED(IDC_BUTTON2, &CAnimalTool::OnClickTurtle)
	ON_BN_CLICKED(IDC_BUTTON3, &CAnimalTool::OnClickDodo)
	ON_BN_CLICKED(IDC_CHECK1, &CAnimalTool::OnAnimaltion)
	ON_BN_CLICKED(IDC_BUTTON4, &CAnimalTool::OnClickIdle)
	ON_BN_CLICKED(IDC_BUTTON5, &CAnimalTool::OnClickwalk)
	ON_BN_CLICKED(IDC_BUTTON6, &CAnimalTool::OnClickeat)
	ON_BN_CLICKED(IDC_BUTTON7, &CAnimalTool::OnClicksleep)
	ON_BN_CLICKED(IDC_BUTTON8, &CAnimalTool::OnClicksleeping)
	ON_BN_CLICKED(IDC_BUTTON9, &CAnimalTool::OnClickwakeup)
END_MESSAGE_MAP()

void CAnimalTool::OnInitialUpdate()
{
	m_maxIndex[COW][IDLE] = 6;
	m_maxIndex[COW][WALK] = 8;
	m_maxIndex[COW][EAT] = 16;
	m_maxIndex[COW][SLEEP] = 6;
	m_maxIndex[COW][SLEEPING] = 1;
	m_maxIndex[COW][WAKEUP] = 10;

	m_maxIndex[TURTLE][IDLE] = 5;
	m_maxIndex[TURTLE][WALK] = 8;
	m_maxIndex[TURTLE][EAT] = 13;
	m_maxIndex[TURTLE][SLEEP] = 0;
	m_maxIndex[TURTLE][SLEEPING] = 0;
	m_maxIndex[TURTLE][WAKEUP] = 0;

	m_maxIndex[DODO][IDLE] = 6;
	m_maxIndex[DODO][WALK] = 8;
	m_maxIndex[DODO][EAT] = 12;
	m_maxIndex[DODO][SLEEP] = 6;
	m_maxIndex[DODO][SLEEPING] = 1;
	m_maxIndex[DODO][WAKEUP] = 5;

	m_currentImageIndex = 0;
	m_eAnimal = ANIMAL_END;
	m_eAction = IDLE;
	OnLoadData();
}

void CAnimalTool::OnLoadData()
{

	AddMap(L"dodo",6, 8, 12, 6, 1, 5);
	AddMap(L"cow",6, 8, 16, 6, 1, 10);
	AddMap(L"turtle",5, 8, 13, 0, 0, 0);
}

void CAnimalTool::AddMap(const CString& type, int idleCnt, int walkCnt, int eatCnt, int sleepCnt, int sleepingCnt, int wakeupCnt)
{
	TCHAR szFullPath[MAX_PATH] = L"../Assets/Animal/";
	TCHAR pFilePathType[6][MAX_STR] = { L"idle", L"walk", L"eat", L"sleep", L"sleeping", L"wakeup" };
	TCHAR pFilePathState[3][MAX_STR] = { L"front", L"side", L"back" };
	int numImages = 0;

	for (int i = 0; i < 6; ++i) {
		switch (i)
		{
		case 0:
			numImages = idleCnt;
			break;
		case 1:
			numImages = walkCnt;
			break;
		case 2:
			numImages = eatCnt;
			break;
		case 3:
			numImages = sleepCnt;
			break;
		case 4:
			numImages = sleepingCnt;
			break;
		case 5:
			numImages = wakeupCnt;
			break;
		default:
			break;
		}
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < numImages; ++k) {

				CString strTileName;
				CString szFilePath;

				szFilePath.Format(L"../Assets/Animal/%s/%s/%s/%s_%d.png", type, pFilePathType[i], pFilePathState[j], pFilePathState[j], k + 1);
				strTileName.Format(L"%s%s_%s%d", type, pFilePathType[i], pFilePathState[j], k + 1);
				CImage* image = new CImage;
				image->Load(szFilePath);
				m_animalImage.insert({ strTileName, image });
			}
		}
	}
}

void CAnimalTool::StopRender()
{
	CClientDC dc(&AnimalPreviewImg);
	CRect rect;
	AnimalPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));

	switch (m_eAnimal)
	{
	case CAnimalTool::COW:	
		m_animalImage[L"cowidle_front1"]->Draw(dc, rect);
		break;
	case CAnimalTool::TURTLE:
		m_animalImage[L"turtleidle_front1"]->Draw(dc, rect);
		break;
	case CAnimalTool::DODO:
		m_animalImage[L"dodoidle_front1"]->Draw(dc, rect);
		break;
	case CAnimalTool::ANIMAL_END:
		break;
	default:
		break;
	}
}

void CAnimalTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE3, AnimalPreviewImg);
	DDX_Control(pDX, IDC_CHECK1, m_AnimationOn);
}

void CAnimalTool::OnDestroy()
{

	CDialog::OnDestroy();

	for_each(m_animalImage.begin(), m_animalImage.end(), [](auto& MyPair)
		{
			MyPair.second->Destroy();
			Safe_Delete(MyPair.second);
		});

	m_animalImage.clear();
}


void CAnimalTool::OnClickCow()
{
	m_eAnimal = COW;
	CClientDC dc(&AnimalPreviewImg);
	CRect rect;
	AnimalPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	m_animalImage[L"cowidle_front1"]->Draw(dc, rect);
}


void CAnimalTool::OnClickTurtle()
{
	m_eAnimal = TURTLE;
	CClientDC dc(&AnimalPreviewImg);
	CRect rect;
	AnimalPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	m_animalImage[L"turtleidle_front1"]->Draw(dc, rect);
}


void CAnimalTool::OnClickDodo()
{
	m_eAnimal = DODO;
	CClientDC dc(&AnimalPreviewImg);
	CRect rect;
	AnimalPreviewImg.GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	m_animalImage[L"dodoidle_front1"]->Draw(dc, rect);
}


void CAnimalTool::OnAnimaltion()
{
	if (m_AnimationOn.GetCheck() == BST_CHECKED)
	{
		m_currentImageIndex = 0;
		SetTimer(1, 100, NULL);
	}
	else
	{
		KillTimer(1);

		StopRender();
	}
}

void CAnimalTool::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		CString strAnimal;
		CString strAction;

		switch (m_eAnimal)
		{
		case CAnimalTool::COW:
			strAnimal.Format(L"cow");
			break;
		case CAnimalTool::TURTLE:
			strAnimal.Format(L"turtle");
			break;
		case CAnimalTool::DODO:
			strAnimal.Format(L"dodo");
			break;
		case CAnimalTool::ANIMAL_END:
			break;
		default:
			break;
		}
		switch (m_eAction)
		{
		case CAnimalTool::IDLE:
			strAction.Format(L"idle");
			break;
		case CAnimalTool::WALK:
			strAction.Format(L"walk");
			break;
		case CAnimalTool::EAT:
			strAction.Format(L"eat");
			break;
		case CAnimalTool::SLEEP:
			strAction.Format(L"sleep");
			break;
		case CAnimalTool::SLEEPING:
			strAction.Format(L"sleeping");
			break;
		case CAnimalTool::WAKEUP:
			strAction.Format(L"wakeup");
			break;
		case CAnimalTool::ACTION_END:
			break;
		default:
			break;
		}

		CString strKey;
		strKey.Format(L"%s%s_front%d", strAnimal, strAction, m_currentImageIndex+1);

		CClientDC dc(&AnimalPreviewImg);
		CRect rect;
		AnimalPreviewImg.GetClientRect(&rect);
		dc.FillSolidRect(rect, RGB(255, 255, 255));
		m_animalImage[strKey]->Draw(dc, rect);

		m_currentImageIndex = (m_currentImageIndex + 1) % m_maxIndex[m_eAnimal][m_eAction];
	}

	CWnd::OnTimer(nIDEvent);  // 기본 타이머 처리
}

void CAnimalTool::OnClickIdle()
{
	m_currentImageIndex = 0;
	m_eAction = IDLE;
}


void CAnimalTool::OnClickwalk()
{
	m_currentImageIndex = 0;
	m_eAction = WALK;
}


void CAnimalTool::OnClickeat()
{
	m_currentImageIndex = 0;
	m_eAction = EAT;
}


void CAnimalTool::OnClicksleep()
{
	if (m_eAnimal == TURTLE) return;
	m_currentImageIndex = 0;
	m_eAction = SLEEP;
}


void CAnimalTool::OnClicksleeping()
{
	if (m_eAnimal == TURTLE) return;
	m_currentImageIndex = 0;
	m_eAction = SLEEPING;
}


void CAnimalTool::OnClickwakeup()
{
	if (m_eAnimal == TURTLE) return;
	m_currentImageIndex = 0;
	m_eAction = WAKEUP;
}
