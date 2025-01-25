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

	// 일단 dirt만 파일이름 + 경로 변경하고 잘 파싱 되는지 확인함
	// 잘 되면 나머지 이미지도 바꿔서 추가할게...
	TCHAR szFullPath[MAX_PATH] = L"../Assets/Map/";
	TCHAR pFilePath[MAX_STR] = L"";
	TCHAR szTileOption[MAX_STR] = L"";

	int iFullCnt = 0;
	int iCnt = 0;
	int iErr = 0;

	// 선택된 지형 받아옴
	switch (m_ctrlCMapType.GetCurSel())
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
	switch (m_crtlCType.GetCurSel()) 
	{
	case 0://ground
		lstrcpy(szTileOption, L"ground");
		iCnt = 28;
		break;
	case 1://wall
		lstrcpy(szTileOption, L"wallhead");
		iCnt = 21;
		break;
	case 2://ore
		lstrcpy(szTileOption, L"ore");
		iCnt = 3;
		break;
	case 3://deco
		lstrcpy(szTileOption, L"deco");
		iCnt = 18;
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
