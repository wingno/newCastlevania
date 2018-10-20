#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init()
{
	m_imgIntro = IMAGEMANAGER->addImage("intro", "image/introcopy.bmp", 5280, 320, 22, 2, true, RGB(255, 0, 255));
	m_imgSelect = IMAGEMANAGER->addImage("select", "image/title.bmp", 75, 75, 1, 3, true, RGB(255, 0, 255));
	m_imgSelect2 = IMAGEMANAGER->addImage("menu", "image/since.bmp", 232, 16, 1, 1, true, RGB(255, 0, 255));
	title1 = true;
	title2 = false;
	m_nMenuX = 210;
	m_nMenuY = 350;
	
	nIdx = 0;
	m_nFcount = 0;
	m_nFrameX = 0;
	m_nFrameY = 0;

	menuX2 = -20;
	menuY2 = 430;
	m_rc = RectMakeCenter(m_nMenuX, m_nMenuY, m_imgSelect->getWidth() / 2, m_imgSelect->getHeight() / 2);
	m_rc = RectMakeCenter(menuX2, menuY2, m_imgSelect2->getWidth() / 2, m_imgSelect2->getHeight() / 2);

	m_nSpeed = 7;
	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{


	if (title1)
	{

		if (KEYMANAGER->isStayKeyDown('Z'))
		{
			m_nSpeed = 2;
		}
		if (KEYMANAGER->isOnceKeyUp('Z'))
		{
			m_nSpeed = 7;
		}
		nIdx++;
		if (nIdx % m_nSpeed == 0)
		{

			m_nFrameX++;
			if (m_nFrameX > 21)
			{
				m_nFcount++;
				m_nFrameX = 0;

				m_nFrameY = 1;

			}

		}


	}

	if (m_nFcount == 2)
	{
		m_nFrameX = 22;
		title1 = false;
		title2 = true;
		m_nFcount = 0;

	}



	if (title2)
	{


		if (m_nMenuFrameY < 1)
		{
			m_nMenuFrameY = 1;
		}
		if (m_nMenuFrameY > 2)
		{
			m_nMenuFrameY = 2;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			m_nMenuFrameY += 1;


		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			m_nMenuFrameY -= 1;

		}
		if (m_nMenuFrameY == 1)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				SCENEMANAGER->changeScene("battle");
			}
		}


	}




}

void titleScene::render(HDC hdc)
{
	if (title1)
	{
		m_imgIntro->frameRender(hdc, 0, 0, m_nFrameX, m_nFrameY, WINSIZEX, WINSIZEY);
	}

	if (title2)
	{

		m_imgSelect->frameRender(hdc, m_nMenuX, m_nMenuY, 0, m_nMenuFrameY, 3);
		m_imgSelect2->frameRender(hdc, menuX2, menuY2, 0, 0, 3);

	}

}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
