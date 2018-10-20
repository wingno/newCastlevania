#pragma once
#include "scene.h"
class scoreScene :public scene
{
private:
	image * m_pBG;
	int* m_pscore;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	inline void setIsScore(int* score) { m_pscore = score; }

	scoreScene();
	~scoreScene();
};

