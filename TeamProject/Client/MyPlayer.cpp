#include "pch.h"
#include "MyPlayer.h"
#include "KeyMgr.h"
#include "CDevice.h"

CMyPlayer::CMyPlayer()
{
}

HRESULT CMyPlayer::Initialize(void)
{
	LoadPlayerData();

	m_fSpeed = 3.f;
	m_tInfo.vPos = { 0.f,0.f,0.f };

	return E_NOTIMPL;
}

int CMyPlayer::Update(void)
{
	KeyInput();
	return 0;
}

void CMyPlayer::Late_Update(void)
{
}

void CMyPlayer::Render(void)
{
	D3DXMATRIX matScale, matTrans;

	const TEXINFO* pTexInfo = m_playerImage[L"skin_idlefront_1"]->Get_Texture();

	float fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matScale * matTrans;

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);


	D3DXVECTOR3 vTemp{ fCenterX, fCenterY, 0.f };

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,      
		&vTemp,     
		nullptr,      
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMyPlayer::Release(void)
{
	for (auto& pair : m_playerImage) {
		Safe_Delete(pair.second);  
	}
	m_playerImage.clear();
}

void CMyPlayer::KeyInput()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('W')) {
		m_tInfo.vDir = { 0.f, -1.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('S')) {
		m_tInfo.vDir = { 0.f, 1.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('A')) {
		m_tInfo.vDir = { -1.f, 0.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('D')) {
		m_tInfo.vDir = { 1.f, 0.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}
}

void CMyPlayer::LoadPlayerData()
{
	TCHAR szFullPath[MAX_PATH] = L"../Assets/Player2/";
	TCHAR pFilePathType[9][MAX_STR] = { L"eye", L"hair1", L"hair2", L"hair3", L"hair4", L"hair5", L"pant", L"shirt", L"skin" };
	TCHAR pFilePathState[3][MAX_STR] = { L"front", L"side", L"back" };

	//walk
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 6; ++k) {
				//传捞 back老锭
				if (i == 0 && j == 2) {
					continue;
				}

				wstring strName;
				wstring szFilePath;

				szFilePath = L"../Assets/Player2/" + wstring(pFilePathType[i]) + L"/walk/" + wstring(pFilePathState[j]) + L"/" + wstring(pFilePathState[j]) + L"_" + to_wstring(k + 1) + L".png";
				strName = wstring(pFilePathType[i]) + L"_walk" + wstring(pFilePathState[j]) + L"_" + to_wstring(k + 1);

				CTexture* pTexture = nullptr;
				pTexture = new CSingleTexture;
				pTexture->Insert_Texture(szFilePath.c_str(), L"Player", 1);

				m_playerImage.insert({ strName, pTexture });
			}
		}
	}
	

	//idle
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 3; ++j) {
			//传捞 back老锭
			if (i == 0 && j == 2) {
				continue;
			}

			wstring strName;
			wstring szFilePath;

			szFilePath = L"../Assets/Player2/" + wstring(pFilePathType[i]) + L"/idle/" + wstring(pFilePathState[j]) + L"/" + wstring(pFilePathState[j]) + L"_1.png";
			strName = wstring(pFilePathType[i]) + L"_idle" + wstring(pFilePathState[j]) + L"_1";

			CTexture* pTexture = nullptr;
			pTexture = new CSingleTexture;
			pTexture->Insert_Texture(szFilePath.c_str(), L"Player", 1);

			m_playerImage.insert({ strName, pTexture });
		}
	}
}
