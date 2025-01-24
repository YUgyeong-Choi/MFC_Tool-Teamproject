// CMapTool.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CMapTool.h"
#include "CFileInfo.h"

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
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnListBox)
	ON_WM_DROPFILES()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnLoadTileAssets)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기

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

	m_Picture.SetBitmap(*(iter->second));

	UpdateData(FALSE);
}

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

void CMapTool::OnLoadTileAssets()
{
	UpdateData(TRUE);

	TCHAR szFullPath[MAX_PATH] = L"../Assets/Map/dirt_tileset/";
	TCHAR pFilePath[MAX_STR] = L"dirt_tileset";
	const int iCnt = 86;

	for (int i = 0; i < 86; ++i)
	{
		swprintf_s(szFullPath, MAX_PATH, L"../Assets/Map/dirt_tileset/%s%d.png", pFilePath, i + 1);
		CImage* pPngImage = new CImage;
		pPngImage->Load(szFullPath); 

		CString strTileName;
		strTileName.Format(L"%s%d", pFilePath, i + 1);
		TCHAR pFilePath2[MAX_STR];
		swprintf_s(pFilePath2, MAX_STR, L"%s%d", pFilePath, i + 1);

		m_mapPngImage.insert({ strTileName, pPngImage});
		m_ListBox.AddString(pFilePath2);
	}

	//Horizontal_Scroll();

	UpdateData(FALSE);
}
