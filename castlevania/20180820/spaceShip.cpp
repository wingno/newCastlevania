#include "stdafx.h"
#include "spaceShip.h"
#include "missileManager.h"
#include "progressBar.h"


HRESULT spaceShip::init()
{
	m_img = IMAGEMANAGER->addImage("spaceShip", "image/rocket.bmp",
		52, 64, true, RGB(255, 0, 255));
	//m_img->setX(WINSIZEX / 2 - m_img->getWidth() / 2);
	//m_img->setY(WINSIZEY / 2 - m_img->getHeight() / 2 + 200);

	m_fSpeed = 5.0f;
	m_fX = WINSIZEX / 2;// -m_img->getWidth() / 2;
	m_fY = WINSIZEY / 2 + 200;// -m_img->getHeight() / 2 + 200;

	//m_rc = RectMakeCenter(m_fX, m_fY, m_img->getWidth(), m_img->getHeight());

	// 미사일
	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init();

	// 체력바
	m_pHPBar = new progressBar;
	//m_pHPBar->init(m_fX - (m_img->getWidth() / 2),
	//	m_fY - (m_img->getHeight() / 2) - 10,
	//	53, 5);

	m_nCurrHP = m_nMaxHP = 100;

	return S_OK;
}

HRESULT spaceShip::init(int selectNum)
{
	if (selectNum == 0)
	{
		m_img = IMAGEMANAGER->addImage("spaceShip", "image/rocket.bmp",
			52, 64, true, RGB(255, 0, 255));
	}
	else
	{
		m_img = IMAGEMANAGER->addImage("spaceShipY", "image/rocketY.bmp",
			52, 64, true, RGB(255, 0, 255));
	}
	//m_img->setX(WINSIZEX / 2 - m_img->getWidth() / 2);
	//m_img->setY(WINSIZEY / 2 - m_img->getHeight() / 2 + 200);

	m_fSpeed = 5.0f;
	m_fX = WINSIZEX / 2;// -m_img->getWidth() / 2;
	m_fY = WINSIZEY / 2 + 200;// -m_img->getHeight() / 2 + 200;

	/*m_rc = RectMakeCenter(m_fX, m_fY, m_img->getWidth(), m_img->getHeight());*/

	// 미사일
	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init();

	//// 체력바
	//m_pHPBar = new progressBar;
	//m_pHPBar->init(m_fX - (m_img->getWidth() / 2),
	//	m_fY - (m_img->getHeight() / 2) - 10,
	//	53, 5);

	m_nCurrHP = m_nMaxHP = 100;

	return S_OK;
}

void spaceShip::release()
{
	delete m_pHPBar;
	delete m_pMissileMgr;
}

void spaceShip::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (m_pMissileMgr)
			m_pMissileMgr->fire(m_fX, m_fY);
	}


	if (KEYMANAGER->isStayKeyDown(VK_LEFT)
		&& (m_fX > 0))
	{
		//m_img->setX(m_img->getX() - m_fSpeed);
		m_fX -= m_fSpeed;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT)
		&& (m_fX + m_img->getWidth() < WINSIZEX))
	{
		//m_img->setX(m_img->getX() + m_fSpeed);
		m_fX += m_fSpeed;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP)
		&& (m_fY > 0))
	{
		//m_img->setY(m_img->getY() - m_fSpeed);
		m_fY -= m_fSpeed;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN)
		&& (m_fY + m_img->getHeight() < WINSIZEY))
	{
		//m_img->setY(m_img->getY() + m_fSpeed);
		m_fY += m_fSpeed;
	}


	//m_rc = RectMakeCenter(m_fX, m_fY,
	//	m_img->getWidth(), m_img->getHeight());

	if (m_pMissileMgr)
		m_pMissileMgr->update();

	//if (m_pHPBar)
	//{
	//	m_pHPBar->setX(m_fX - m_img->getWidth() / 2);
	//	m_pHPBar->setY(m_fY - m_img->getHeight() / 2 - 10);
	//	m_pHPBar->update();
	//}
}

void spaceShip::render(HDC hdc)
{
	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

	//m_img->render(hdc, m_fX - m_img->getWidth() / 2, m_fY - m_img->getHeight() / 2);
	/*m_img->alphaRender(hdc,
		m_fX - m_img->getWidth() / 2, m_fY - m_img->getHeight() / 2, 150);*/
	//m_fX - m_img->getWidth() / 2, m_fY - m_img->getHeight() / 2);

	if (m_pMissileMgr)
		m_pMissileMgr->render(hdc);

	if (m_pHPBar)
		m_pHPBar->render(hdc);
}

void spaceShip::damaged(int damage)
{
	m_nCurrHP -= damage;
	if (m_nCurrHP <= 0)
	{
		m_nCurrHP = 0;
	}

	//if (m_pHPBar)
	//{
	//	m_pHPBar->setGauge(m_nCurrHP, m_nMaxHP);
	//}
}


HRESULT spaceShip::restart()
{

	m_fX = WINSIZEX / 2;// -m_img->getWidth() / 2;
	m_fY = WINSIZEY / 2 + 200;// -m_img->getHeight() / 2 + 200;

	/*m_rc = RectMakeCenter(m_fX, m_fY, m_img->getWidth(), m_img->getHeight());
*/
/*
	m_nCurrHP = m_nMaxHP = 100;*/
	//if (m_pHPBar)
	//{
	//	m_pHPBar->setGauge(m_nCurrHP, m_nMaxHP);
	//}

	return S_OK;
}

spaceShip::spaceShip()
{
}


spaceShip::~spaceShip()
{
}
