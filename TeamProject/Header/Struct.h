#pragma once

#include "Enum.h"

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;
	D3DXVECTOR2		vSize;

	D3DXMATRIX		matWorld;

}INFO;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;   // 컴 객체

	D3DXIMAGE_INFO			tImgInfo;	// 구조체

}TEXINFO;


typedef struct tagTileObject
{
	bool			bExist;
	BYTE			byDrawID;	// 몇 번 타일 이미지, 유형 갯수 만큼 배열 추가
	TILETERRAIN		eTileTerrain;		// 지형 (흙 모래 ... )
}TILEOBJ;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;				// 타일의 중점 좌표
	D3DXVECTOR2 vSize;				// 타일의 가로, 세로 사이즈

	BYTE		byOption;			// 0, 1번(장애물)
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
	D3DXVECTOR2 vSize;	
	D3DXVECTOR2 vTileSize;		// 가로 세로 몇 칸 짜리 크기 오브젝트인지
								// 오브젝트 타일 계산 기준: LT?
	
	int			iTileIndex;		// 설치 된 타일 인덱스 번호
	MAPOBJTYPE	eObjType;		// 오브젝트 종류 (기능성 가구, 생활 가구, 장식 오브젝트)
	BYTE		byDrawID;		// 오브젝트 번호
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