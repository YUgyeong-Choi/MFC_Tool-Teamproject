#include "pch.h"
#include "MyPlayer.h"
#include "KeyMgr.h"
#include "CDevice.h"
#include "TimeMgr.h"
#include "CAstarMgr.h"

CMyPlayer::CMyPlayer()
{
}

HRESULT CMyPlayer::Initialize(void)
{
	LoadPlayerData();
	ChangeColor();

	m_fSpeed = 0.5f;
	m_tInfo.vPos = { 150.f,150.f,0.f };
	m_playerLook = DOWN;
	m_bPlayerWalk = false;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount64();

	return E_NOTIMPL;
}

int CMyPlayer::Update(void)
{
	D3DXMATRIX matScale, matTrans;

	if (m_playerLook == LEFT) {
		D3DXMatrixIdentity(&m_tInfo.matWorld);
		D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + m_vScroll.x,
			m_tInfo.vPos.y + m_vScroll.y - 10.f,
			0.f);
	}
	else {
		D3DXMatrixIdentity(&m_tInfo.matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + m_vScroll.x,
			m_tInfo.vPos.y + m_vScroll.y - 10.f,
			0.f);
	}


	m_tInfo.matWorld = matScale * matTrans;
	return 0;
}

void CMyPlayer::Late_Update(void)
{
	if (0.f > Get_Mouse().x)
		m_vScroll.x += 200.f * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (WINCX < Get_Mouse().x)
		m_vScroll.x -= 200.f * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (0.f > Get_Mouse().y)
		m_vScroll.y += 200.f * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (WINCY < Get_Mouse().y)
		m_vScroll.y -= 200.f * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		CAstarMgr::Get_Instance()->Start_Astar(m_tInfo.vPos, Get_Mouse() - CObj::m_vScroll);
	}

	Move_Astar();
	Move_Frame();
}

void CMyPlayer::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;

		m_tFrame.dwTime = GetTickCount64();
	}
}

void CMyPlayer::Render(void)
{

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	TCHAR pFilePathType[5][MAX_STR] = { L"skin", L"hair",L"pant", L"shirt", L"eye" };
	TCHAR pFilePathState[3][MAX_STR] = { L"front", L"side", L"back" };

	if (m_bPlayerWalk) {
		for (int i = 0; i < 5; ++i) {
			wstring strName;
			switch (m_playerLook)
			{
			case LEFT:
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex+1)+ L"_walkside_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_walkside_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				break;
			case RIGHT:
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex + 1) + L"_walkside_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_walkside_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				break;
			case UP:
				if (i == 4) {
					continue;
				}
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex + 1) + L"_walkback_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_walkback_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				break;
			case DOWN:
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex + 1) + L"_walkfront_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_walkfront_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				break;
			case PLAYERLOOK_END:
				break;
			default:
				break;
			}

			const TEXINFO* pTexInfo = m_playerImage[strName]->Get_Texture();

			float fCenterX = pTexInfo->tImgInfo.Width / 2.f;
			float fCenterY = pTexInfo->tImgInfo.Height / 2.f;

			D3DXVECTOR3 vTemp{ fCenterX, fCenterY, 0.f };

			switch (i)
			{
			case 0: //½ºÅ²
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eSkinRGB.iR, tData.eSkinRGB.iG, tData.eSkinRGB.iB));
				break;
			case 1: //¸Ó¸®
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eHairRGB.iR, tData.eHairRGB.iG, tData.eHairRGB.iB));
				break;
			case 2: //¹ÙÁö
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.ePantRGB.iR, tData.ePantRGB.iG, tData.ePantRGB.iB));
				break;
			case 3: //¼ÅÃ÷
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eShirtRGB.iR, tData.eShirtRGB.iG, tData.eShirtRGB.iB));
				break;
			case 4: //´«
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eEyeRGB.iR, tData.eEyeRGB.iG, tData.eEyeRGB.iB));
				break;
			default:
				break;
			}
		}
	}
	else {
		for (int i = 0; i < 5; ++i) {
			wstring strName;
			switch (m_playerLook)
			{
			case LEFT:
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex + 1) + L"_idleside_1";
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_idleside_1";
				}
				break;
			case RIGHT:
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex + 1) + L"_idleside_1";
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_idleside_1";
				}
				break;
			case UP:
				if (i == 4) {
					continue;
				}
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex + 1) + L"_idleback_1";
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_idleback_1";
				}
				break;
			case DOWN:
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex + 1) + L"_idlefront_1";
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_idlefront_1";
				}
				break;
			case PLAYERLOOK_END:
				break;
			default:
				break;
			}

			const TEXINFO* pTexInfo = m_playerImage[strName]->Get_Texture();

			float fCenterX = pTexInfo->tImgInfo.Width / 2.f;
			float fCenterY = pTexInfo->tImgInfo.Height / 2.f;

			D3DXVECTOR3 vTemp{ fCenterX, fCenterY, 0.f };

			switch (i)
			{
			case 0: //½ºÅ²
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eSkinRGB.iR, tData.eSkinRGB.iG, tData.eSkinRGB.iB));
				break;
			case 1: //¸Ó¸®
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eHairRGB.iR, tData.eHairRGB.iG, tData.eHairRGB.iB));
				break;
			case 2: //¹ÙÁö
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.ePantRGB.iR, tData.ePantRGB.iG, tData.ePantRGB.iB));
				break;
			case 3: //¼ÅÃ÷
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eShirtRGB.iR, tData.eShirtRGB.iG, tData.eShirtRGB.iB));
				break;
			case 4: //´«
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eEyeRGB.iR, tData.eEyeRGB.iG, tData.eEyeRGB.iB));
				break;
			default:
				break;
			}
		}
	}

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
		m_playerLook = UP;
		m_tInfo.vDir = { 0.f, -1.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		m_bPlayerWalk=true;

		m_vScroll.y += 200.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
	}else if (CKeyMgr::Get_Instance()->Key_Pressing('S')) {
		m_playerLook = DOWN;
		m_tInfo.vDir = { 0.f, 1.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		m_bPlayerWalk = true;

		m_vScroll.y -= 200.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
	}else if (CKeyMgr::Get_Instance()->Key_Pressing('A')) {
		m_playerLook = LEFT;
		m_tInfo.vDir = { -1.f, 0.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		m_bPlayerWalk = true;

		m_vScroll.x += 200.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
	}else if (CKeyMgr::Get_Instance()->Key_Pressing('D')) {
		m_playerLook = RIGHT;
		m_tInfo.vDir = { 1.f, 0.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		m_bPlayerWalk = true;

		m_vScroll.x -= 200.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
	}
	else {
		m_bPlayerWalk = false;
		m_tFrame.iFrameStart = 0;
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
				//´«ÀÌ backÀÏ¶§
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
			//´«ÀÌ backÀÏ¶§
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

void CMyPlayer::ChangeColor()
{
	HANDLE hFile = CreateFile(L"../Data/Player.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD	dwByte(0);

	while (true)
	{
		ReadFile(hFile, &tData.iHp, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &tData.iAttack, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &(tData.eSkinRGB), sizeof(PLAYERRGB), &dwByte, nullptr);
		ReadFile(hFile, &(tData.eHairRGB), sizeof(PLAYERRGB), &dwByte, nullptr);
		ReadFile(hFile, &(tData.eEyeRGB), sizeof(PLAYERRGB), &dwByte, nullptr);
		ReadFile(hFile, &(tData.eShirtRGB), sizeof(PLAYERRGB), &dwByte, nullptr);
		ReadFile(hFile, &(tData.ePantRGB), sizeof(PLAYERRGB), &dwByte, nullptr);
		ReadFile(hFile, &(m_hairIndex), sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
		{
			break;
		}
	}

	CloseHandle(hFile);
}

void CMyPlayer::Move_Astar()
{
	m_bPlayerWalk = false;
	list<TILEADDLOOK>& BestList = CAstarMgr::Get_Instance()->Get_BestList();

	if (!BestList.empty())
	{
		D3DXVECTOR3 vDir = BestList.front().pTile->vPos - m_tInfo.vPos;

		float       fDistance = D3DXVec3Length(&vDir);

		D3DXVec3Normalize(&vDir, &vDir);

		m_tInfo.vPos += vDir * 300.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
		m_playerLook = BestList.front().eLook;
		m_bPlayerWalk = true;

		if (3.f >= fDistance)
			BestList.pop_front();
	}
}