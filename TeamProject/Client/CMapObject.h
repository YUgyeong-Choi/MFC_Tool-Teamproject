#pragma once
#include "Obj.h"
class CMapObject :
    public CObj
{
public:
    HRESULT Initialize(void) override;
    int Update(void) override;
    void Late_Update(void) override;
    void Render(void) override;
    void Release(void) override;

private:
    vector<MAPOBJ*> m_vecObject;
    HRESULT Load_Object(const TCHAR* pTilePath);
};



