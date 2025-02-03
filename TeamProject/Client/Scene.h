#pragma once

class CScene abstract
{
public:
	explicit CScene();
	virtual ~CScene();

public:
	virtual HRESULT Ready_Scene()PURE; 
	virtual void Update_Scene()PURE;
	virtual void Late_Update_Scene()PURE;
	virtual void Render_Scene()PURE;
	virtual void Release_Scene()PURE;
};

