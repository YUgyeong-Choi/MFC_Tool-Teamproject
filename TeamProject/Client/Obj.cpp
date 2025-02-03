#include "pch.h"
#include "Obj.h"
//#include "TimeMgr.h"

D3DXVECTOR3 CObj::m_vScroll{};

CObj::CObj()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	m_tInfo.vLook = { 1.f, 0.f, 0.f };
}

CObj::~CObj()
{
}


