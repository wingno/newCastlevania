#pragma once
#include "scene.h"

class titleScene : public scene
{
private:
	image * m_imgIntro;
	int m_nFrameX, m_nFrameY, nIdx, m_nSpeed;
	int m_nFcount;

	image* m_imgSelect;
	image* m_imgSelect2;

	int m_nMenuX, m_nMenuY, m_nMenuFrameY;
	int menuX2, menuY2;

	bool title1, title2;
	RECT m_rc;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	titleScene();
	~titleScene();
};

