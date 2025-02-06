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
	ON_BN_CLICKED(IDC_BUTTON10, &CAnimalTool::OnAddAnimal)
	ON_BN_CLICKED(IDC_BUTTON12, &CAnimalTool::OnClickDelete)
	ON_BN_CLICKED(IDC_BUTTON13, &CAnimalTool::OnClickSave)
	ON_BN_CLICKED(IDC_BUTTON11, &CAnimalTool::OnClickLoad)
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
	case COW:	
		m_animalImage[L"cowidle_front1"]->Draw(dc, rect);
		break;
	case TURTLE:
		m_animalImage[L"turtleidle_front1"]->Draw(dc, rect);
		break;
	case DODO:
		m_animalImage[L"dodoidle_front1"]->Draw(dc, rect);
		break;
	case ANIMAL_END:
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
	DDX_Control(pDX, IDC_EDIT2, m_SpawnX);
	DDX_Control(pDX, IDC_EDIT3, m_SpawnY);
	DDX_Control(pDX, IDC_EDIT4, m_SpawnHp);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
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

	for (auto& data : m_AnimalData) {
		Safe_Delete(data.second);
	}

	m_AnimalData.clear();
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
		case COW:
			strAnimal.Format(L"cow");
			break;
		case TURTLE:
			strAnimal.Format(L"turtle");
			break;
		case DODO:
			strAnimal.Format(L"dodo");
			break;
		case ANIMAL_END:
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


void CAnimalTool::OnAddAnimal()
{
	CString X, Y, Hp, Name;
	m_SpawnX.GetWindowTextW(X);
	m_SpawnY.GetWindowTextW(Y);
	m_SpawnHp.GetWindowTextW(Hp);
	
	switch (m_eAnimal)
	{
	case COW:
		Name.Format(L"cow");
		break;
	case TURTLE:
		Name.Format(L"turtle");
		break;
	case DODO:
		Name.Format(L"dodo");
		break;
	case ANIMAL_END:
		break;
	default:
		break;
	}

	ANIMALDATA* pUnit = new ANIMALDATA;
	pUnit->eAnimalType = m_eAnimal;

	pUnit->iSpawnX = _ttoi(X);
	pUnit->iSpawnY = _ttoi(Y);
	pUnit->iHp = _ttoi(Hp);

	CString strName;
	strName.Format(L"%s-x:%d y:%d hp:%d", Name, pUnit->iSpawnX, pUnit->iSpawnY, pUnit->iHp);

	m_ListBox.AddString(strName);
	m_AnimalData.insert({ strName, pUnit });
}


void CAnimalTool::OnClickDelete()
{
	CString	strFindName;

	// GetCurSel : 커서가 선택한 셀의 인덱스 값을 반환
	int	iIndex = m_ListBox.GetCurSel();

	if (LB_ERR == iIndex)
		return;

	m_ListBox.GetText(iIndex, strFindName);

	auto	iter = m_AnimalData.find(strFindName);

	if (iter == m_AnimalData.end())
		return;

	Safe_Delete(iter->second);
	m_AnimalData.erase(strFindName);

	//DeleteString : 해당 인덱스의 리스트 목록을 제거
	m_ListBox.DeleteString(iIndex);
}


void CAnimalTool::OnClickSave()
{
	CFileDialog		Dlg(FALSE,		// TRUE(불러오기), FALSE(다른 이름으로 저장) 모드 지정
		L"dat",		// default 확장자명
		L"*.dat",	// 대화 상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	// 읽기 전용 체크 박스 숨김 | 중복된 이름으로 파일 저장 시 경고 메세지 띄움
		L"Data Files(*.dat) | *.dat ||", // 대화 상자에 표시될 파일 형식
		this);	// 부모 윈도우 주소

	// DoModal : 대화 상자를 실행

	TCHAR	szPath[MAX_PATH] = L"";

	// 현재 프로젝트의 경로를 얻어오는 함수(절대 경로)
	GetCurrentDirectory(MAX_PATH, szPath);

	// PathRemoveFileSpec : 전체 경로에서 파일 이름만 잘라주는 함수
	// 경로 상에 파일 이름이 없을 경우엔 마지막 폴더명을 잘라낸다.

	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		// GetPathName : 선택된 경로를 반환
		// GetString : 원시 문자열의 형태로 반환

		CString	str = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();

		HANDLE hFile = CreateFile(pGetPath,
			GENERIC_WRITE,
			0, 0,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte(0), dwStrByte(0);

		for (auto& MyPair : m_AnimalData)
		{
			// key 값 저장

			dwStrByte = sizeof(TCHAR) * (MyPair.first.GetLength() + 1);

			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, MyPair.first.GetString(), dwStrByte, &dwByte, nullptr);

			// value 값 저장
			ANIMALDATA temp;
			temp.eAnimalType = MyPair.second->eAnimalType;
			temp.iHp = MyPair.second->iHp;
			temp.iSpawnX = MyPair.second->iSpawnX;
			temp.iSpawnY = MyPair.second->iSpawnY;

			WriteFile(hFile, &temp, sizeof(ANIMALDATA), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}
}


void CAnimalTool::OnClickLoad()
{
	CFileDialog		Dlg(TRUE,		// TRUE(불러오기), FALSE(다른 이름으로 저장) 모드 지정
		L"dat",		// default 확장자명
		L"*.dat",	// 대화 상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	// 읽기 전용 체크 박스 숨김 | 중복된 이름으로 파일 저장 시 경고 메세지 띄움
		L"Data Files(*.dat) | *.dat ||", // 대화 상자에 표시될 파일 형식
		this);	// 부모 윈도우 주소

	// DoModal : 대화 상자를 실행

	TCHAR	szPath[MAX_PATH] = L"";

	// 현재 프로젝트의 경로를 얻어오는 함수(절대 경로)
	GetCurrentDirectory(MAX_PATH, szPath);

	// PathRemoveFileSpec : 전체 경로에서 파일 이름만 잘라주는 함수
	// 경로 상에 파일 이름이 없을 경우엔 마지막 폴더명을 잘라낸다.

	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		for (auto& MyPair : m_AnimalData)
			delete MyPair.second;

		m_AnimalData.clear();

		// ResetContent : 리스트 박스 목록 초기화 함수
		m_ListBox.ResetContent();


		CString	str = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();

		HANDLE hFile = CreateFile(pGetPath,
			GENERIC_READ,
			0, 0,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte(0), dwStrByte(0);
		UNITDATA		tData{};

		while (true)
		{
			// key 값 로드

			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

			TCHAR* pName = new TCHAR[dwStrByte];

			ReadFile(hFile, pName, dwStrByte, &dwByte, nullptr);

			// value 값 로드
			ANIMALDATA temp;
			ReadFile(hFile, &temp, sizeof(ANIMALDATA), &dwByte, nullptr);

			if (0 == dwByte)
			{
				delete[] pName;
				break;
			}

			ANIMALDATA* pUnit = new ANIMALDATA;

			CString strName = pName;
			delete[]pName;

			pUnit->eAnimalType = temp.eAnimalType;
			pUnit->iHp = temp.iHp;
			pUnit->iSpawnX = temp.iSpawnX;
			pUnit->iSpawnY = temp.iSpawnY;

			m_AnimalData.insert({strName, pUnit });

			m_ListBox.AddString(strName);
		}

		CloseHandle(hFile);
	}
}
