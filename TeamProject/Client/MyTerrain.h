#pragma once

#include "Obj.h"

class CMyTerrain :	public CObj
{
public:
	CMyTerrain();
	virtual ~CMyTerrain();
public:
	vector<TILE*>& Get_VecTile() { return m_vecTile; }
	vector<list<TILE*>>& Get_VecAdj() { return m_vecAdj; }
public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
	void	Render_WallHead(void);

private:
	HRESULT		Load_Tile(const TCHAR* pTilePath);

	void Ready_Adjacency();

private:
	vector<TILE*>		m_vecTile;
	vector<list<TILE*>>	m_vecAdj;
};