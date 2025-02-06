#pragma once

#include "Enum.h"

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR2		vSize;
	D3DXVECTOR3		vLook;

	D3DXMATRIX		matWorld;

}INFO;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;   // �� ��ü

	D3DXIMAGE_INFO			tImgInfo;	// ����ü

}TEXINFO;


typedef struct tagTileObject
{
	bool			bExist;
	BYTE			byDrawID;	// �� �� Ÿ�� �̹���, ���� ���� ��ŭ �迭 �߰�
	TILETERRAIN		eTileTerrain;		// ���� (�� �� ... )
}TILEOBJ;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;				// Ÿ���� ���� ��ǥ
	D3DXVECTOR2 vSize;				// Ÿ���� ����, ���� ������

	BYTE		byOption;			// 0, 1��(��ֹ�)
	TILEOBJ		tObject[OPT_END];

	int			iIndex = 0;
	int			iParentIndex = 0;
}TILE;

typedef struct tagTileAddLook
{
	TILE* pTile;
	PLAYERLOOK eLook;
}TILEADDLOOK;

typedef struct tagMapObjectData
{
	D3DXVECTOR3	vPos;	
	
	int			iTileIndex;		// ��ġ �� Ÿ�� �ε��� ��ȣ
	MAPOBJTYPE	eObjType;		// ������Ʈ ���� (��ɼ� ����, ��Ȱ ����, ��� ������Ʈ)
	BYTE		byDrawID;		// ������Ʈ ��ȣ
}MAPOBJ;


typedef struct PlayerColorData {
	int iR;
	int iG;
	int iB;
}PLAYERRGB;

typedef	struct tagUnitData
{
	int		iHp;
	int		iAttack;
	PLAYERRGB eSkinRGB;
	PLAYERRGB eEyeRGB;
	PLAYERRGB eHairRGB;
	PLAYERRGB eShirtRGB;
	PLAYERRGB ePantRGB;
}UNITDATA;

typedef struct tagTexturePath
{
	wstring		wstrObjKey		= L"";
	wstring		wstrStateKey	= L"";
	wstring		wstrPath		= L"";
	int			iCount			= 0;

}IMGPATH;

typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	ULONGLONG	dwSpeed;
	ULONGLONG	dwTime;

}FRAME;

typedef struct tagAnimal {
	ANIMAL eAnimalType;
	int iSpawnX;
	int iSpawnY;
	int iHp;
}ANIMALDATA;