#include "stdafx.h"
#include "GameOverScene.h"


HRESULT GameOverScene::init()
{
	m_imgBackGround = IMAGEMANAGER->addImage("GameOverBG","image/GameOverBG.bmp", 431, 161, true, RGB(84,109, 142));
	m_imgGameOwer = IMAGEMANAGER->addImage("GameOverE", "image/GameOverE.bmp", 500, 98, true, RGB(84,109, 142));
	
	m_bRander = true;
	m_nAlpa = 0;
	m_nGameAlpa = 0;
	m_nX = 80;
	m_nY = 90;
	m_nIndx = 0;
	return S_OK;
}

void GameOverScene::release()
{
}

void GameOverScene::update()
{
	if (m_bRander)
	{
		m_nIndx++;
		m_nAlpa = 100;
		if (m_nIndx == 100)
		{
			m_bRander = false;
			m_nIndx = 0;
		}
	}
	if (!m_bRander)
	{

		m_nGameAlpa = 20;
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			SCENEMANAGER->changeScene("titleScene");
		}
	}

}

void GameOverScene::render(HDC hdc)
{
	if (m_bRander)
	{
		m_imgBackGround->alphaRender(hdc, -5, -5, 0, 0, WINSIZEX + 5, WINSIZEY + 5, m_nAlpa,1);
	
	}

	if (!m_bRander)
	{
		m_imgGameOwer->alphaRender(hdc, m_nX, m_nY, 0, 0, 500, 98, m_nGameAlpa,1);
	}
}

GameOverScene::GameOverScene()
{
}


GameOverScene::~GameOverScene()
{
}
