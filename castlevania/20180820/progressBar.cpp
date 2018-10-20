#include "stdafx.h"
#include "progressBar.h"
#include "player.h"
HRESULT progressBar::init(float x, float y,float width, float height)
{

	m_fX = x;
	m_fY = y;
	m_fWidth = width ;
	m_fWidthMp = width ;

	m_rc = RectMake(m_fX, m_fY,
		m_fWidth, height);

	
	m_imgHp = IMAGEMANAGER->addImage("HP",

			"image/object/HP.bmp", m_fWidth , height -10 , true, RGB(0, 128, 0));
	
		m_imgMp = IMAGEMANAGER->addImage("MP",
			"image/object/MP.bmp", m_fWidthMp, height -10 , true, RGB(0, 128, 0));


	m_imgeMenuProgress = IMAGEMANAGER->addImage("progressbar",
		"image/object/progressbar.bmp", 140, height, true, RGB(0, 128, 0));


	m_imgNum = IMAGEMANAGER->addImage("m_nMyHp",
		"image/숫자.bmp", 96, 40 , 12,4, true, RGB(255, 0, 255));
	m_imgNum1 = IMAGEMANAGER->addImage("m_nMyHp",
		"image/숫자.bmp", 96, 40, 12, 4, true, RGB(255, 0, 255));
	m_imgNum2 = IMAGEMANAGER->addImage("m_nMyHp",
		"image/숫자.bmp", 96, 40, 12, 4, true, RGB(255, 0, 255));
	m_imgNum3 = IMAGEMANAGER->addImage("m_nMyHp",
		"image/숫자.bmp", 96, 40, 12, 4, true, RGB(255, 0, 255));
	m_pPlayer = g_mainGame.getPlayer();

	m_nFrameY = 0;
	m_nFrameY1 = 0;
	m_nFrameY2 = 0;
	m_nFrameY3 = 0;

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{


}

void progressBar::render(HDC hdc)
{
	/*m_imgBg->render(hdc, 0, 0, 521 + m_posMap.x / 3, 1551 + m_posMap.y / 3, 400, 160, 3);*/
	/*Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);*/
	m_imgeMenuProgress->render(hdc, m_fX, m_fY,3);
	
	m_imgHp->render(hdc, m_fX +120 , m_fY + 19, 0, 0,
		m_fWidth, m_imgHp->getHeight());
	m_imgMp->render(hdc, m_fX + 120, m_fY + 34, 0, 0,
		m_fWidthMp, m_imgMp->getHeight());
	//채력 게이지 숫자표시
	HpGauge(hdc);

}

void progressBar::HpGauge(HDC hdc)
{

	m_nMyHp = m_pPlayer->getPState()->curHP;


	if (m_pPlayer->getPState()->curHP >= 10000)
	{
	
		m_imgNum3->frameRender(hdc, m_fX + 40, m_fY + 25, 9, m_nFrameY3, 2);
		m_imgNum2->frameRender(hdc, m_fX + 50, m_fY + 25, 9, m_nFrameY2, 2);
		m_imgNum1->frameRender(hdc, m_fX + 60, m_fY + 25, 9, m_nFrameY1, 2);
		m_imgNum->frameRender(hdc, m_fX + 70, m_fY + 25, 9, m_nFrameY, 2);
	}
	else if (m_pPlayer->getPState()->curHP < 10000 && m_pPlayer->getPState()->curHP >= 1000)
	{

		m_nMyHp = (m_pPlayer->getPState()->curHP / 1000);
		m_imgNum3->frameRender(hdc, m_fX + 40, m_fY + 25, m_nMyHp, m_nFrameY3, 2);
		m_nMyHp = (m_pPlayer->getPState()->curHP / 100) - ((m_pPlayer->getPState()->curHP / 1000) * 10);
		m_imgNum2->frameRender(hdc, m_fX + 50, m_fY + 25, m_nMyHp, m_nFrameY2, 2);
		m_nMyHp = (m_pPlayer->getPState()->curHP / 10) - ((m_pPlayer->getPState()->curHP / 100) * 10);
		m_imgNum1->frameRender(hdc, m_fX + 60, m_fY + 25, m_nMyHp, m_nFrameY1, 2);
		m_nMyHp = (m_pPlayer->getPState()->curHP % 10);
		m_imgNum->frameRender(hdc, m_fX + 70, m_fY + 25, m_nMyHp, m_nFrameY, 2);
	}
	else if (m_pPlayer->getPState()->curHP < 1000 && m_pPlayer->getPState()->curHP >= 100)
	{
		m_nMyHp = (m_pPlayer->getPState()->curHP / 100);
		m_imgNum2->frameRender(hdc, m_fX + 50, m_fY + 25, m_nMyHp, m_nFrameY2, 2);
		m_nMyHp = (m_pPlayer->getPState()->curHP / 10) - ((m_pPlayer->getPState()->curHP / 100) * 10);
		m_imgNum1->frameRender(hdc, m_fX + 60, m_fY + 25, m_nMyHp, m_nFrameY1, 2);
		m_nMyHp = (m_pPlayer->getPState()->curHP % 10);
		m_imgNum->frameRender(hdc, m_fX + 70, m_fY + 25, m_nMyHp, m_nFrameY, 2);
	}
	else if (m_pPlayer->getPState()->curHP < 100 && m_pPlayer->getPState()->curHP >= 10)
	{
		m_nMyHp = (m_pPlayer->getPState()->curHP / 10) - ((m_pPlayer->getPState()->curHP / 100) * 10);
		m_imgNum1->frameRender(hdc, m_fX + 60, m_fY + 25, m_nMyHp, m_nFrameY1, 2);
		m_nMyHp = (m_pPlayer->getPState()->curHP % 10);
		m_imgNum->frameRender(hdc, m_fX + 70, m_fY + 25, m_nMyHp, m_nFrameY, 2);
	}
	else
	{
		m_nMyHp = (m_pPlayer->getPState()->curHP % 10);
		m_imgNum->frameRender(hdc, m_fX + 70, m_fY + 25, m_nMyHp, m_nFrameY, 2);
	}

}


void progressBar::setGauge(float currGauge, float maxGauge
	, float currGaugemp, float maxGaugemp)
{

	m_fWidth = (currGauge / maxGauge) * m_imgHp->getWidth();
	m_fWidthMp = (currGaugemp / maxGaugemp) * m_imgMp->getWidth();

}

progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}
