#include "stdafx.h"
#include "missile.h"
#include "player.h"
#include "room.h"

//using namespace MY_UTIL;

HRESULT missile::init()
{
	m_fAngle = PI / 2;
	m_fRange = 500.0f;
	m_fSpeed = 5.0f;
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_fFiredX = 0.0f;
	m_fFiredY = 0.0f;
	m_isFire = false;

	//memset(&m_rc, 3, sizeof(m_rc));
	ZeroMemory(&m_rc, sizeof(m_rc));

	m_pImg = IMAGEMANAGER->findImage("enemy_missile_1");
	m_pPlayer = g_mainGame.getPlayer();

	return S_OK;
}

HRESULT missile::init(const char * szImageName, float speed,
	float x, float y, float angle, float range ,int kind)
{
	m_fAngle = angle;
	m_fRange = range;
	m_fSpeed = speed;
	m_fX = x;
	m_fY = y;
	m_fFiredX = x;
	m_fFiredY = y;
	m_isFire = false;

	m_nKind = kind;
	m_fRotateAngle = 0;

	m_fMapX = m_fX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_fMapY = m_fY - ROOMMANAGER->getCurrRoom()->getPosMap().y;

	//memset(&m_rc, 3, sizeof(m_rc));
	ZeroMemory(&m_rc, sizeof(m_rc));

	switch (kind)
	{
	case 0:
		m_pImg = IMAGEMANAGER->findImage("image/RipperL.bmp");
		m_nDmg = 30;
		break;
	case 1:
		m_pImg = IMAGEMANAGER->findImage("image/RipperR.bmp");
		m_nDmg = 30;
		break;
	case 2:
		m_pImg = IMAGEMANAGER->addImage("image/axe.bmp","image/axe.bmp",28,28,true,RGB(84,109,142));
		m_nDmg = 80;
		m_fRange = 300;
		m_bIsturn = false;
		break;
	default:
		break;
	}

	

	return S_OK;
}

void missile::release()
{
}

void missile::update()
{
	move();
}

void missile::render(HDC hdc)
{
	if (m_isFire)
	{
		//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		if (m_nKind ==0)
		{
			m_pImg->render(hdc, m_fMapX - 8*3, m_fMapY - 4*3,176,8,16,8,3);
		}
		else if (m_nKind == 1)
		{
			m_pImg->render(hdc, m_fMapX - 8*3, m_fMapY - 4*3,0,8,16,8,3);
		}
		else
		{
			m_pImg->rotateRender(hdc , m_fRotateAngle+=15, (m_fMapX -( m_pImg->getWidth()*3) / 2)+10, m_fMapY - ((m_pImg->getHeight()*3) / 2)+10,0.5f,0.5f,3);
		}

	}
}

void missile::fire(float x, float y)
{
	if (!m_isFire)
	{
		m_isFire = true;
		// 시작 위치
		m_fFiredX = m_fX = x;
		m_fFiredY = m_fY = y;


		if (m_nKind < 2)
		{
			m_rc = RectMakeCenter(m_fX, m_fY,
				m_pImg->getFrameWidth()*3, 8*3);
		}
		else if(m_nKind==2)
		{
			m_rc = RectMakeCenter(m_fMapX, m_fMapY,
				m_pImg->getWidth()*3, m_pImg->getHeight()*3);
		}


		//// 플레이어의 위치를 알아야 각도를 구할 수 있다
		//if (m_pPlayer)
		//{
		//	m_fAngle = MY_UTIL::getAngle(
		//		m_fX, m_fY,
		//		m_pPlayer->getFx(), m_pPlayer->getFY());
		//}


	}
}

void missile::move()
{
	if (m_isFire)
	{
		m_fX += cosf(m_fAngle) * m_fSpeed;
		m_fY += -sinf(m_fAngle) * m_fSpeed;

		m_fMapX = m_fX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
		m_fMapY = m_fY - ROOMMANAGER->getCurrRoom()->getPosMap().y;

		if (m_nKind < 2)
		{
			m_rc = RectMakeCenter(m_fMapX, m_fMapY,
				m_pImg->getFrameWidth()*3, 8*3);

			if (m_fRange < MY_UTIL::getDistance(m_fFiredX, m_fFiredY, m_fX, m_fY))
			{
				m_isFire = false;
			}
		}
		else if(m_nKind==2)
		{
			m_rc = RectMakeCenter(m_fMapX, m_fMapY,
				m_pImg->getWidth()*3, m_pImg->getHeight()*3);

			if (m_fRange < MY_UTIL::getDistance(m_fFiredX, m_fFiredY, m_fX, m_fY))
			{
				if (m_bIsturn)
				{
					m_isFire = false;
				}
				else
				{
					m_fAngle += PI;
					m_bIsturn = true;
					m_fRange = 1000.0f;
				}

			}

		}


	}
}

missile::missile()
{
}


missile::~missile()
{
}
