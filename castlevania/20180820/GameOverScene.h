#pragma once
#include "scene.h"
class GameOverScene : public scene
{
private:
	image* m_imgBackGround;
	image* m_imgGameOwer;

	//백그라운드 이미지 위치 및 인덱스
	int m_nAlpa, m_nIndx;
	//문구 위치
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

