// CMapTool.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CMapTool.h"
#include "CFileInfo.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "CTerrain.h"

// CMapTool 대화 상자

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CMapTool, pParent)
{

}

CMapTool::~CMapTool()
{
}

void CMapTool::OnInitialUpdate()  
{
	m_ctrlCMapType.AddString(_T("Dirt"));
	m_ctrlCMapType.AddString(_T("Sand"));
	m_ctrlCMapType.AddString(_T("Nature"));
	m_ctrlCMapType.AddString(_T("Stone"));
	m_ctrlCMapType.AddString(_T("Water"));

	m_crtlCType.AddString(_T("Ground"));
	m_crtlCType.AddString(_T("Wall"));
	m_crtlCType.AddString(_T("Ore"));
	m_crtlCType.AddString(_T("Deco"));


	//기본값 0
	if (m_ctrlCMapType.GetCount() > 0)
	{
		m_ctrlCMapType.SetCurSel(0);
	}

	if (m_crtlCType.GetCount() > 0)
	{
		m_crtlCType.SetCurSel(0);
	}
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlCMapType);
	DDX_Control(pDX, IDC_COMBO3, m_crtlCType);
	DDX_Control(pDX, IDC_PICTURE1, MapToolPreviewImg);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnListBox)
	ON_WM_DROPFILES()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnLoadTileAssets)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON14, &CMapTool::OnBnClickedLoad)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기

// 리스트 선택
void CMapTool::OnListBox()
{
	UpdateData(TRUE);

	CString	strFindName;

	// GetCurSel : 커서가 선택한 셀의 인덱스 값을 반환
	int	iIndex = m_ListBox.GetCurSel();

	m_ListBox.GetText(iIndex, strFindName);

	auto	iter = m_mapPngImage.find(strFindName);

	if (iter == m_mapPngImage.end())
		return;

	//선택한 이미지 종류 보여주는 곳
	MapToolPreviewImg.SetBitmap(*(iter->second)); 
		
	UpdateData(FALSE);
}


// 리스트 가로 길이가 텍스트보다 짧을 경우 스크롤 추가
void CMapTool::Horizontal_Scroll()
{
	CString		strName;

	CSize		Size;

	int		iWidth(0);

	CDC* pDC = m_ListBox.GetDC();

	for(int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strName);

		// GetTextExtent : 매개 변수에 해당하는 문자열의 길이를 픽셀 단위로 변환
		Size = pDC->GetTextExtent(strName);

		if (Size.cx > iWidth)
			iWidth = Size.cx;
	}

	m_ListBox.ReleaseDC(pDC);

	// GetHorizontalExtent : 리스트 박스가 가로로 스크롤 할 수 있는 최대 범위를 얻어오는 함수
	if (iWidth > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iWidth);

}

void CMapTool::OnDestroy()
{
	CDialog::OnDestroy();

	for_each(m_mapPngImage.begin(), m_mapPngImage.end(), [](auto& MyPair)
		{
			MyPair.second->Destroy();
			Safe_Delete(MyPair.second);
		});

	m_mapPngImage.clear();
}


// 로드 버튼 선택
void CMapTool::OnLoadTileAssets()
{
	UpdateData(TRUE);

	m_ListBox.ResetContent();

	TCHAR szFullPath[MAX_PATH] = L"../Assets/Map/";
	TCHAR pFilePath[MAX_STR] = L"";
	TCHAR szTileOption[MAX_STR] = L"";

	int iFullCnt = 0;
	int iCnt = 0;
	int iErr = 0;
	TILETERRAIN eTerrain = TILETERRAIN(m_ctrlCMapType.GetCurSel());
	TILETYPE	eType = TILETYPE(m_crtlCType.GetCurSel());
	// 선택된 지형 받아옴
	switch (eTerrain)
	{
	case 0://dirt
		lstrcpy(pFilePath, L"dirt_tileset");
		iFullCnt = 86;
		break;
	case 1://sand
		lstrcpy(pFilePath, L"sand_tileset");
		iFullCnt = 55;
		break;
	case 2://nature
		lstrcpy(pFilePath, L"nature_tileset");
		iFullCnt = 72;
		break;
	case 3://stone
		lstrcpy(pFilePath, L"stone_tileset");
		iFullCnt = 70;
		break;
	case 4://water
		lstrcpy(pFilePath, L"water_tileset");
		iFullCnt = 17;
		break;
	default:
		iErr = -1;
		break;
	}

	// 선택된 유형 받아옴
	switch (eType) 
	{
	case 0://ground
		lstrcpy(szTileOption, L"ground");
		iCnt = GROUND_ALL_CNT;
		break;
	case 1://wall
		lstrcpy(szTileOption, L"wallhead");
		iCnt = WALLHEAD_ALL_CNT;
		break;
	case 2://ore
		lstrcpy(szTileOption, L"ore");
		iCnt = ORE_DEFAULT_CNT;
		if (eTerrain == TRN_SAND) iCnt = ORE_SAND_CNT;
		break;
	case 3://deco
		lstrcpy(szTileOption, L"deco");
		iCnt = 12;
		if (eTerrain == TRN_SAND) iCnt = DECO_SAND_CNT;
		else if (eTerrain == TRN_DIRT) iCnt = DECO_DIRT_CNT;
		break;
	default:
		iErr = -1;
		break;
	}


	for (int i = 0; i < iCnt; ++i)
	{
		CString strTileName;
		TCHAR pFilePath2[MAX_STR];
		CImage* pPngImage = new CImage;

		swprintf_s(szFullPath, MAX_PATH, L"../Assets/Map/%s/%s/%s_%s%d.png", pFilePath, szTileOption, pFilePath, szTileOption, i + 1);
		if (iErr == 0 && FAILED(pPngImage->Load(szFullPath)))
		{
			AfxMessageBox(lstrcat(szFullPath,L" Load Failed"));
			iErr = -1;
			iCnt = iFullCnt;
		}

		if (iErr == 0)
		{
			strTileName.Format(L"%s_%s%d", pFilePath, szTileOption, i + 1);
			swprintf_s(pFilePath2, MAX_STR, L"%s_%s%d", pFilePath, szTileOption, i + 1);		
		}
		else // 선택된 값과 동일한 폴더가 존재하지 않을 경우 바깥쪽 폴더에서 분류 안 된 이미지 그냥 다 받아옴 (지금 흙만 분류해서 나머지는 기존과 동일하게 다받음) // 파일 다 정리되면 삭제 예정
		{
			swprintf_s(szFullPath, MAX_PATH, L"../Assets/Map/%s/%s%d.png", pFilePath, pFilePath, i + 1);
			pPngImage->Load(szFullPath);
			strTileName.Format(L"%s_%d", pFilePath, i + 1);
			swprintf_s(pFilePath2, MAX_STR, L"%s_%d", pFilePath, i + 1);
		}

		m_mapPngImage.insert({ strTileName, pPngImage});
		m_ListBox.AddString(pFilePath2);
	}

	Horizontal_Scroll();

	UpdateData(FALSE);
}


void CMapTool::OnClickedSave()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CToolView* pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 0));
	CTerrain* pTerrain = pToolView->m_pTerrain;
	auto& vecTile = *(pTerrain->Get_TileVector());
	auto& vecObj = *(pTerrain->Get_ObjVector());
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

		for (auto& MyTile : vecTile)
		{
			WriteFile(hFile, MyTile, sizeof(TILE), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}

	CFileDialog		Dlg2(FALSE,		// TRUE(불러오기), FALSE(다른 이름으로 저장) 모드 지정
		L"dat",		// default 확장자명
		L"*.dat",	// 대화 상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	// 읽기 전용 체크 박스 숨김 | 중복된 이름으로 파일 저장 시 경고 메세지 띄움
		L"Data Files(*.dat) | *.dat ||", // 대화 상자에 표시될 파일 형식
		this);	// 부모 윈도우 주소

	// DoModal : 대화 상자를 실행


	// 현재 프로젝트의 경로를 얻어오는 함수(절대 경로)
	GetCurrentDirectory(MAX_PATH, szPath);

	// PathRemoveFileSpec : 전체 경로에서 파일 이름만 잘라주는 함수
	// 경로 상에 파일 이름이 없을 경우엔 마지막 폴더명을 잘라낸다.

	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	Dlg2.m_ofn.lpstrInitialDir = szPath;


	if (IDOK == Dlg2.DoModal())
	{
		// GetPathName : 선택된 경로를 반환
		// GetString : 원시 문자열의 형태로 반환

		CString	str = Dlg2.GetPathName().GetString();
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

		for (auto& MyObj : vecObj)
		{
			WriteFile(hFile, MyObj, sizeof(MAPOBJ), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}

}


void CMapTool::OnBnClickedLoad()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CToolView* pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 0));
	CTerrain* pTerrain = pToolView->m_pTerrain;
	auto& vecTile = *(pTerrain->Get_TileVector());
	auto& vecObj = *(pTerrain->Get_ObjVector());

	UpdateData(TRUE);

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
		for (auto& MyTile : vecTile)
			delete MyTile;
		vecTile.clear();

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

		TILE pTile;
		//ZeroMemory(pTile, sizeof(TILE));

		while (true)
		{
			ReadFile(hFile, &pTile, sizeof(TILE), &dwByte, nullptr);

			if (0 == dwByte)
			{
				break;
			}
			TILE* pTiletemp = new TILE;

			pTiletemp->byOption = pTile.byOption;
			pTiletemp->vPos = pTile.vPos;
			pTiletemp->vSize = pTile.vSize;
			pTiletemp->iIndex = pTile.iIndex;
			pTiletemp->iParentIndex = pTile.iParentIndex;
			for (int i = 0; i < OPT_END; ++i)
			{
				pTiletemp->tObject[i].bExist = pTile.tObject[i].bExist;
				pTiletemp->tObject[i].byDrawID = pTile.tObject[i].byDrawID;
				pTiletemp->tObject[i].eTileTerrain = pTile.tObject[i].eTileTerrain;
			}

			vecTile.push_back(pTiletemp);
		}

		CloseHandle(hFile);
	}

	CFileDialog		Dlg2(TRUE,		// TRUE(불러오기), FALSE(다른 이름으로 저장) 모드 지정
		L"dat",		// default 확장자명
		L"*.dat",	// 대화 상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	// 읽기 전용 체크 박스 숨김 | 중복된 이름으로 파일 저장 시 경고 메세지 띄움
		L"Data Files(*.dat) | *.dat ||", // 대화 상자에 표시될 파일 형식
		this);	// 부모 윈도우 주소

	// DoModal : 대화 상자를 실행

	// 현재 프로젝트의 경로를 얻어오는 함수(절대 경로)
	GetCurrentDirectory(MAX_PATH, szPath);

	// PathRemoveFileSpec : 전체 경로에서 파일 이름만 잘라주는 함수
	// 경로 상에 파일 이름이 없을 경우엔 마지막 폴더명을 잘라낸다.

	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	Dlg2.m_ofn.lpstrInitialDir = szPath;



	if (IDOK == Dlg2.DoModal())
	{
		for (auto& MyObj : vecObj)
			delete MyObj;
		vecObj.clear();

		CString	str = Dlg2.GetPathName().GetString();
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

		MAPOBJ pMapObj;
		ZeroMemory(&pMapObj, sizeof(MAPOBJ));

		while (true)
		{
			ReadFile(hFile, &pMapObj, sizeof(MAPOBJ), &dwByte, nullptr);

			if (0 == dwByte)
			{
				break;
			}
			MAPOBJ* pMObjtemp = new MAPOBJ;

			pMObjtemp->byDrawID   = pMapObj.byDrawID;
			pMObjtemp->eObjType   = pMapObj.eObjType;
			pMObjtemp->iTileIndex = pMapObj.iTileIndex;
			pMObjtemp->vPos		  = pMapObj.vPos;

			vecObj.push_back(pMObjtemp);
		}

		CloseHandle(hFile);
	}
	pToolView->Invalidate(FALSE);

	UpdateData(FALSE);
}
