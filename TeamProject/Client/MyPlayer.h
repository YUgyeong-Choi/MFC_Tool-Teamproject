#pragma once

#include "Obj.h"
#include "CSingleTexture.h"
class CMyPlayer :public CObj
{
private:
	enum PLAYERLOOK{LEFT, RIGHT, UP, DOWN, PLAYERLOOK_END };
public:
	CMyPlayer();
	virtual ~CMyPlayer() { Release(); }
public:
	HRESULT Initialize(void) override;
	int Update(void) override;
	void Late_Update(void) override;
	void Move_Frame();
	void Render(void) override;
	void Release(void) override;
private:
	void KeyInput();
	void LoadPlayerData();
	void ChangeColor();
private:
	//플레이어 이미지 데이터
	map<wstring, CTexture*>		m_playerImage;
	int m_hairIndex;
	UNITDATA tData;

	float m_fSpeed;
	INFO m_tInfo;

	PLAYERLOOK m_playerLook;
	bool m_bPlayerWalk;
	FRAME		m_tFrame;
};

