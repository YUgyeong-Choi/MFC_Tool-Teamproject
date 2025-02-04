#include "pch.h"
#include "MyPlayer.h"
#include "KeyMgr.h"
#include "CDevice.h"
#include "TimeMgr.h"

CMyPlayer::CMyPlayer()
{
}

HRESULT CMyPlayer::Initialize(void)
{
	LoadPlayerData();
	ChangeColor();

	m_fSpeed = 0.5f;
	m_tInfo.vPos = { 300.f,300.f,0.f };
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
	KeyInput();
	return 0;
}

void CMyPlayer::Late_Update(void)
{
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
	D3DXMATRIX matScale, matTrans;

	if (m_playerLook == LEFT) {
		D3DXMatrixIdentity(&m_tInfo.matWorld);
		D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + m_vScroll.x,
			m_tInfo.vPos.y + m_vScroll.y,
			0.f);
	}
	else {
		D3DXMatrixIdentity(&m_tInfo.matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + m_vScroll.x,
			m_tInfo.vPos.y + m_vScroll.y,
			0.f);
	}


	m_tInfo.matWorld = matScale * matTrans;

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	TCHAR pFilePathType[5][MAX_STR] = { L"skin", L"hair",L"pant", L"shirt", L"eye" };
	TCHAR pFilePathState[3][MAX_STR] = { L"front", L"side", L"back" };

	if (m_bPlayerWalk) {
		for (int i = 0; i < 5; ++i) {
			wstring strName;
			switch (m_playerLook)
			{
			case CMyPlayer::LEFT:
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex+1)+ L"_walkside_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_walkside_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				break;
			case CMyPlayer::RIGHT:
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex + 1) + L"_walkside_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_walkside_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				break;
			case CMyPlayer::UP:
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
			case CMyPlayer::DOWN:
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex + 1) + L"_walkfront_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_walkfront_" + to_wstring(m_tFrame.iFrameStart + 1);
				}
				break;
			case CMyPlayer::PLAYERLOOK_END:
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
			case 0: //스킨
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eSkinRGB.iR, tData.eSkinRGB.iG, tData.eSkinRGB.iB));
				break;
			case 1: //머리
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eHairRGB.iR, tData.eHairRGB.iG, tData.eHairRGB.iB));
				break;
			case 2: //바지
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.ePantRGB.iR, tData.ePantRGB.iG, tData.ePantRGB.iB));
				break;
			case 3: //셔츠
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eShirtRGB.iR, tData.eShirtRGB.iG, tData.eShirtRGB.iB));
				break;
			case 4: //눈
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
			case CMyPlayer::LEFT:
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex + 1) + L"_idleside_1";
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_idleside_1";
				}
				break;
			case CMyPlayer::RIGHT:
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex + 1) + L"_idleside_1";
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_idleside_1";
				}
				break;
			case CMyPlayer::UP:
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
			case CMyPlayer::DOWN:
				if (i == 1) {
					strName = wstring(pFilePathType[i]) + to_wstring(m_hairIndex + 1) + L"_idlefront_1";
				}
				else {
					strName = wstring(pFilePathType[i]) + L"_idlefront_1";
				}
				break;
			case CMyPlayer::PLAYERLOOK_END:
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
			case 0: //스킨
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eSkinRGB.iR, tData.eSkinRGB.iG, tData.eSkinRGB.iB));
				break;
			case 1: //머리
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eHairRGB.iR, tData.eHairRGB.iG, tData.eHairRGB.iB));
				break;
			case 2: //바지
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.ePantRGB.iR, tData.ePantRGB.iG, tData.ePantRGB.iB));
				break;
			case 3: //셔츠
				CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
					nullptr,
					&vTemp,
					nullptr,
					D3DCOLOR_ARGB(255, tData.eShirtRGB.iR, tData.eShirtRGB.iG, tData.eShirtRGB.iB));
				break;
			case 4: //눈
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
				//눈이 back일때
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
			//눈이 back일때
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

	//TCHAR pFilePathType[9][MAX_STR] = { L"eye", L"hair1", L"hair2", L"hair3", L"hair4", L"hair5", L"pant", L"shirt", L"skin" };
	//TCHAR pFilePathState[3][MAX_STR] = { L"front", L"side", L"back" };

	////idle
	//for (int i = 0; i < 9; ++i) {
	//	for (int j = 0; j < 3; ++j) {
	//		if (i == 0 && j == 2) {
	//			continue;
	//		}
	//		wstring strName;
	//		strName = wstring(pFilePathType[i]) + L"_idle" + wstring(pFilePathState[j]) + L"_1";

	//		D3DLOCKED_RECT lockedRect;
	//		HRESULT hr = m_playerImage[strName]->Get_Texture()->pTexture->LockRect(0, &lockedRect, NULL, D3DLOCK_DISCARD);
	//		if (FAILED(hr)) {
	//			return;
	//		}

	//		BYTE* pPixels = (BYTE*)lockedRect.pBits;
	//		for (int y = 0; y < m_playerImage[strName]->Get_Texture()->tImgInfo.Height; ++y) {
	//			for (int x = 0; x < m_playerImage[strName]->Get_Texture()->tImgInfo.Width; ++x) {
	//				// 픽셀의 인덱스 계산 (A8R8G8B8 포맷에서 Red, Green, Blue, Alpha 순서로 구성)
	//				int pixelIndex = (y * lockedRect.Pitch) + (x * 4); // A8R8G8B8 포맷은 4바이트

	//				// 원본 픽셀 색상 가져오기 (RGBA 순서)
	//				BYTE* pR = &pPixels[pixelIndex + 0];  // Red
	//				BYTE* pG = &pPixels[pixelIndex + 1];  // Green
	//				BYTE* pB = &pPixels[pixelIndex + 2];  // Blue
	//				BYTE* pA = &pPixels[pixelIndex + 3];  // Alpha

	//				// 색상 조정 (RGB 값 변경 가능)
	//				*pR = (*pR * tData.eEyeRGB.iR) / 255;
	//				*pG = (*pG * tData.eEyeRGB.iG) / 255;
	//				*pB = (*pB * tData.eEyeRGB.iB) / 255;
	//			}
	//		}

	//		m_playerImage[strName]->Get_Texture()->pTexture->UnlockRect(0);
	//	}
	//}
}
