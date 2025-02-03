#pragma once

#include "Obj.h"
#include "CSingleTexture.h"
class CMyPlayer :public CObj
{
public:
	CMyPlayer();
	virtual ~CMyPlayer() { Release(); }
public:
	HRESULT Initialize(void) override;
	int Update(void) override;
	void Late_Update(void) override;
	void Render(void) override;
	void Release(void) override;
private:
	void KeyInput();
	void LoadPlayerData();
private:
	//플레이어 이미지 데이터
	map<wstring, CTexture*>		m_playerImage;

	float m_fSpeed;
	INFO m_tInfo;
};

