#pragma once

#include "Include.h"

class CObj; 
class CObjMgr final 
{
	DECLARE_SINGLETON(CObjMgr)

public:
	enum ID { TERRAIN, PLAYER, EFFECT, UI, END };

private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Terrain() { return m_listObject[TERRAIN].front(); }

public:
	void Add_Object(ID eID, CObj* pObject); 

public:
	void Update(); 
	void Late_Update(); 
	void Render(); 
	void Release(); 

private:
	list<CObj*>		m_listObject[END];
};

