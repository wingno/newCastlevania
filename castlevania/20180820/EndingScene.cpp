#include "stdafx.h"
#include "EndingScene.h"


HRESULT EndingScene::init()
{
	m_imgBackGround2 = IMAGEMANAGER->addImage("endingBG", "image/endingBG.bmp", 512, 482);
	m_imgGameOwer2 = IMAGEMANAGER->addImage("ending", "image/ending.bmp", 500, 300, true, RGB(84, 109, 142));

	m_bRander2 = true;
	m_nAlpa = 0;
	m_nGameAlpa = 0;
	m_nX = 50;
	m_nY = 50;
	m_nIndx = 0;


	return S_OK;
}

void EndingScene::release()
{
}

void EndingScene::update()
{

		
	if (m_bRander2)
	{
		m_nIndx++;
		m_nAlpa = 70;
		if (m_nIndx == 100)
		{
			m_bRander2 = false;
			m_nIndx = 0;
		}
	}
	if (!m_bRander2)
	{

		m_nGameAlpa = 20;
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			SCENEMANAGER->changeScene("titleScene");
		}
	}


}

void EndingScene::render(HDC hdc)
{
	if (m_bRander2)
	{
		m_imgBackGround2->alphaRender(hdc, 0, 0, 0, 0, WINSIZEX + 5, WINSIZEY + 5, m_nAlpa, 1);

	}

	if (!m_bRander2)
	{
		m_imgGameOwer2->alphaRender(hdc, m_nX, m_nY, 0, 0, 500, 300, m_nGameAlpa, 1);
	}
}

EndingScene::EndingScene()
{
}


EndingScene::~EndingScene()
{
}
