#pragma once

#include "Include.h"

class CTimeMgr
{
	DECLARE_SINGLETON(CTimeMgr)

private:
	CTimeMgr();
	~CTimeMgr();

public:
	float			Get_TimeDelta() {	return m_fTimeDelta;	}

public:
	void			Initialize();
	void			Update();

private:
	LARGE_INTEGER			m_CurTime;
	LARGE_INTEGER			m_OldTime;
	LARGE_INTEGER			m_OriginTime;
	LARGE_INTEGER			m_CpuTick;

	float					m_fTimeDelta;
};

//GetTickCount()										QueryPerformanceCounter()
//
//os 생성(윈도우 구동되는 시점부터 시간 값이 증가)				하드웨어 생성(컴퓨터가 부팅되는 시점부터 시간 값이 증가)
//1 / 1000 초											1 / 1,000,000 초
//사용 용이함												진입 장벽이 있음
//														상대적으로 보안성이 뛰어남