#pragma once
#include "scene.h"

class loadingScene : public scene
{
private:


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	loadingScene();
	~loadingScene();
};

