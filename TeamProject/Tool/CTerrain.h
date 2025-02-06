#pragma once

#include "Include.h"
#include "ToolView.h"

class CTerrain
{
public:
	CTerrain();
	~CTerrain();

public:
	HRESULT		Initialize();
	void		Update();
	void		Render(float fZoomFactor, const CPoint& zoomCenter);
	void		Release();
	void		Mini_Render();

public:
	void	Tile_Change(const D3DXVECTOR3& vPos, TILETYPE byTileType, TILETERRAIN byTerrain, const BYTE& byDrawID, const int byOption);
	void	Set_MainView(CToolView* pMainView) { m_pMainView = pMainView;  }
	void	Set_Ratio(D3DXMATRIX* pOut, float _fX, float _fY);
	
	HRESULT	Set_TileOption(const D3DXVECTOR3& vPos, const int byOption) { int iIndex = Get_TileIdx(vPos); if (iIndex == -1) return E_FAIL; m_vecTile[iIndex]->byOption = byOption; }
	auto	Get_TileVector() { return &m_vecTile; }
	auto	Get_ObjVector() { return &m_vecObj; }
	int		Get_TileIdx(const D3DXVECTOR3& vPos);

private:
	bool	Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	bool	Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex);
	HRESULT	Initialize_TileTexture();
	void	Check_TileHead(int iIndex);

public:
	bool m_bGrid;
private:
	vector<TILE*>		m_vecTile;
	vector<MAPOBJ*>		m_vecObj;
	CToolView*			m_pMainView;
	
};

