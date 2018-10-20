#include "stdafx.h"
#include "zombie.h"
#include "room.h"
#include "SubObject.h"


HRESULT zombie::init(int startX, int startY)
{

	m_imgzombi = IMAGEMANAGER->addImage("M1", "MONSTER/NEWZOMBI.bmp", 140, 80, 7, 2, true, RGB(84, 109, 142));


	

	m_fZombieX = startX;
	m_fZombiey = startY;


	m_nZombieFX = 0;
	m_nZombieFY = 0;
	m_nZombiecount = 0;
	m_nZombieIDX = 0;

	m_bZombiestand = true;
	m_bZombieMove = false;
	m_bZombiedead = false;
	m_bAlive = true;

	m_rc = RectMakeCenter(m_fZombieX, m_fZombiey + 30, m_imgzombi->getWidth() - 85, m_imgzombi->getHeight() + 35);


	m_SubObject = new SubObject;
	m_SubObject->init();
	return S_OK;
}

void zombie::release()
{
}

void zombie::update()
{

	if (m_bAlive)
	{
		if (m_bZombiestand) //좀비나오는모습
		{
			m_nZombieIDX++;
			if (m_nZombieIDX % 12 == 0)
			{
				m_nZombieFX++;
				if (m_nZombieFX > 5)
				{

					m_nZombieFX = 5;
					m_bZombieMove = true;
					m_bZombiestand = false;

				}
			}
		}

		if (m_bZombieMove) //단순 이동모션
		{

			m_fZombieX -= 1;
			m_nZombieIDX++;
			m_nZombiecount ++;
			if (m_nZombieIDX % 40 == 0)

			{

				m_nZombieFX++;
				if (m_nZombieFX > 6)
				{
					m_nZombieFX = 5;


				}
			}

			if (m_nZombiecount == 300|| m_rc.left < 190-ROOMMANAGER->getCurrRoom()->getPosMap().x) //이동도중 카운트를 주어서 일정 카운트가되면 데드로 해당하는 모션행동
			{
				m_bZombieMove = false;
				m_bZombiestand = false;
				m_bZombiedead = true;
				m_nZombiecount = 0;
				m_nZombieFX = 0;
				m_nZombieFY = 1;

			}
		}


		if (m_bZombiedead) //좀비가 데드라고했지만 일정 이상 움직일경우 땅으로 들어가개 만듬
		{

			m_nZombieIDX++;
			if (m_nZombieIDX % 20 == 0)
			{
				m_nZombieFX++;
				if (m_nZombieFX > 5)
				{
					m_nZombieFX = 6;
					m_fZombieX = m_fZombieX + 200;


					m_bZombiedead = false;

				}
			}
			if (m_bZombiedead == false)
			{
				m_bZombiestand = true;
				m_nZombieFY = 0;
				m_nZombieFX = 0;
			}
		}

		m_rc = RectMakeCenter(m_fZombieX - ROOMMANAGER->getCurrRoom()->getPosMap().x, m_fZombiey + 30,
			m_imgzombi->getWidth() - 85, m_imgzombi->getHeight() + 35);
	}



	if (!m_bAlive)
	{
	
			m_SubObject->SetSubObjectNum(1);
			m_SubObject->SetSubObjectXY(m_fZombieX, m_fZombiey);
			m_SubObject->setAlive(true);
			m_SubObject->update();
	}



}

void zombie::render(HDC hdc)
{
	if (m_bAlive)
	{
		//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

		m_imgzombi->frameRender(hdc, m_fZombieX + 40 - m_imgzombi->getWidth() / 2  - ROOMMANAGER->getCurrRoom()->getPosMap().x, m_fZombiey - m_imgzombi->getHeight() / 2, m_nZombieFX, m_nZombieFY, 3);
	}
	m_SubObject->render(hdc);
}

zombie::zombie()
{
}


zombie::~zombie()
{
}
