#pragma once
#include "scene.h"



class EndingScene : public scene
{
private:
	image* m_imgBackGround2;
	image* m_imgGameOwer2;

	//��׶��� �̹��� ��ġ �� �ε���
	int m_nAlpa, m_nIndx;
	//���� ��ġ
	int m_nX, m_nY, m_nGameAlpa;

	bool m_bRander2;



public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);


	EndingScene();
	~EndingScene();
};

