#pragma once
#include "scene.h"
#include "spaceShip.h"
class selectScene :public scene
{
private:
	image * m_pBG;
	image * m_pselect;


	

	POINT selecterPos[2];

	int m_seletNum;

	image* m_imgRocketR;
	image* m_imgRocketY;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);





	selectScene();
	~selectScene();
};

