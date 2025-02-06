#pragma once
#include "Obj.h"
#include "CTexture.h"
class CAnimal :public CObj
{
public:
	CAnimal();
	virtual ~CAnimal() { Release(); }
public:
	HRESULT Initialize(void) override;
	int Update(void) override;
	void Late_Update(void) override;
	void Render(void) override;
	void Release(void) override;
public:
	void Set_Data(ANIMALDATA temp);
private:
	void Move_Frame();
	void OnLoadData();
	void AddAnimalAsset(const wstring& type, int idleCnt, int walkCnt, int eatCnt, int sleepCnt, int sleepingCnt, int wakeupCnt);
private:
	ANIMAL m_eAnimal;
	INFO m_tInfo;
	float m_fSpeed;
	int iHp;
	FRAME		m_tFrame;

	map<wstring, CTexture*>		m_animalImage;
};

