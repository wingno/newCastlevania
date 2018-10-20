#pragma once
#include "scene.h"
class GameOverScene : public scene
{
private:
	image* m_imgBackGround;
	image* m_imgGameOwer;

	//��׶��� �̹��� ��ġ �� �ε���
	int m_nAlpa, m_nIndx;
	//���� ��ġ
	int m_nX, m_nY, m_nGameAlpa;

	bool m_bRander;


public:


	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	GameOverScene();
	~GameOverScene();
};

