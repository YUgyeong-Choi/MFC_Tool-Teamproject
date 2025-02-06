#include "pch.h"
#include "Animal.h"
#include "CDevice.h"
#include "CSingleTexture.h"

CAnimal::CAnimal()
{
}

HRESULT CAnimal::Initialize(void)
{
	OnLoadData();

	m_fSpeed = 0.5f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount64();
	switch (m_eAnimal)
	{
	case COW:
		m_tFrame.iFrameEnd = 5;
		break;
	case TURTLE:
		m_tFrame.iFrameEnd = 4;
		break;
	case DODO:
		m_tFrame.iFrameEnd = 5;
		break;
	case ANIMAL_END:
		break;
	default:
		break;
	}
	m_eRender = R_MAPOBJ;

	return E_NOTIMPL;
}

void CAnimal::OnLoadData()
{
	AddAnimalAsset(L"dodo", 6, 8, 12, 6, 1, 5);
	AddAnimalAsset(L"cow", 6, 8, 16, 6, 1, 10);
	AddAnimalAsset(L"turtle", 5, 8, 13, 0, 0, 0);
}

void CAnimal::AddAnimalAsset(const wstring& type, int idleCnt, int walkCnt, int eatCnt, int sleepCnt, int sleepingCnt, int wakeupCnt)
{
	TCHAR szFullPath[MAX_PATH] = L"../Assets/Animal/";
	TCHAR pFilePathType[6][MAX_STR] = { L"idle", L"walk", L"eat", L"sleep", L"sleeping", L"wakeup" };
	TCHAR pFilePathState[3][MAX_STR] = { L"front", L"side", L"back" };
	int numImages = 0;

	for (int i = 0; i < 6; ++i) {
		switch (i)
		{
		case 0:
			numImages = idleCnt;
			break;
		case 1:
			numImages = walkCnt;
			break;
		case 2:
			numImages = eatCnt;
			break;
		case 3:
			numImages = sleepCnt;
			break;
		case 4:
			numImages = sleepingCnt;
			break;
		case 5:
			numImages = wakeupCnt;
			break;
		default:
			break;
		}
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < numImages; ++k) {
				wstring strName;
				wstring szFilePath;

				szFilePath = L"../Assets/Animal/" + type + L"/" + wstring(pFilePathType[i]) + L"/" + wstring(pFilePathState[j]) + L"/" + wstring(pFilePathState[j]) + L"_" + to_wstring(k + 1) + L".png";
				strName = type + wstring(pFilePathType[i]) + L"_" + wstring(pFilePathState[j]) + to_wstring(k + 1);

				CTexture* pTexture = nullptr;
				pTexture = new CSingleTexture;
				pTexture->Insert_Texture(szFilePath.c_str(), L"Animal", 1);

				m_animalImage.insert({ strName, pTexture });

			}
		}
	}
}

int CAnimal::Update(void)
{
	D3DXMATRIX matScale, matTrans;
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f);
	m_tInfo.matWorld = matScale * matTrans;
	return 0;
}

void CAnimal::Late_Update(void)
{
	Move_Frame();
}

void CAnimal::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;

		m_tFrame.dwTime = GetTickCount64();
	}
}

void CAnimal::Render(void)
{
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	wstring strName;
	switch (m_eAnimal)
	{
	case COW:
		strName = L"cowidle_front" + to_wstring(m_tFrame.iFrameStart + 1);
		break;
	case TURTLE:
		strName = L"turtleidle_front" + to_wstring(m_tFrame.iFrameStart + 1);
		break;
	case DODO:
		strName = L"dodoidle_front" + to_wstring(m_tFrame.iFrameStart + 1);
		break;
	case ANIMAL_END:
		break;
	default:
		break;
	}

	const TEXINFO* pTexInfo = m_animalImage[strName]->Get_Texture();

	float fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	D3DXVECTOR3 vTemp{ fCenterX, fCenterY, 0.f };

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&vTemp,
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CAnimal::Release(void)
{
	for (auto& pair : m_animalImage) {
		Safe_Delete(pair.second);
	}
	m_animalImage.clear();
}

void CAnimal::Set_Data(ANIMALDATA temp)
{
	m_tInfo.vPos = { (float)temp.iSpawnX, (float)temp.iSpawnY, 0.f };
	iHp = temp.iHp;
	m_eAnimal = temp.eAnimalType;
}
