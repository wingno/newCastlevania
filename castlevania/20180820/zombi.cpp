#include "stdafx.h"
#include "zombi.h"
#include "room.h"


HRESULT zombi::init(int startX, int startY)
{

	m_zombi = IMAGEMANAGER->addImage("M1", "MONSTER/NEWZOMBI.bmp", 140, 80, 7, 2, true, RGB(84, 109, 142));

	


	zombiX = startX;
		//350
	zombiy = startY;
	zombiFX, zombiFY = 0;
	
	zombistand = true;
	zombimove = false;
	zombidead = false;

	//Alive = true;


	m_rc = RectMakeCenter(zombiX, zombiy + 30, m_zombi->getWidth() - 85, m_zombi->getHeight() + 35);

	
	return S_OK;
}

void zombi::release()
{
	//얼라이브를 추가할예정이였고 얼라이브가 false가되면 릴리즈해주는형식으로 만들려고했음

}

void zombi::update()
{
	MOVE();
	
}

void zombi::render(HDC hdc)
{
	
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

		m_zombi->frameRender(hdc, zombiX + 40 - m_zombi->getWidth() / 2, zombiy - m_zombi->getHeight() / 2, zombiFX, zombiFY, 3);
	
}

void zombi::MOVE()
{//if (Alive)
	
	
	if (zombistand) //좀비나오는모습
	{

		zombiIDX++;
		if (zombiIDX % 12 == 0)
		{

			zombiFX++;
			if (zombiFX > 5)
			{

				zombiFX = 5;
				zombimove = true;
				zombistand = false;

			}
		}
	}

	if (zombimove) //단순 이동모션
	{

		zombiX -= 1;
		m_rc.right -= 0.5;
		m_rc.left -= 0.5;

		zombiIDX++;
		zombicount += 1;
		if (zombiIDX % 40
			== 0)

		{

			zombiFX++;
			if (zombiFX > 6)
			{
				zombiFX = 5;


			}
		}

		if (zombicount == 500 || m_rc.left < 170) //이동도중 카운트를 주어서 일정 카운트가되면 데드로 해당하는 모션행동
		{
			zombimove = false;
			zombistand = false;
			zombidead = true;
			zombicount = 0;
			zombiFX = 0;
			zombiFY = 1;

		}
	}


	if (zombidead) //좀비가 데드라고했지만 일정 이상 움직일경우 땅으로 들어가개 만듬
	{

		zombiIDX++;
		if (zombiIDX % 20 == 0)
		{
			zombiFX++;
			if (zombiFX > 5)
			{
				zombiFX = 6;
				zombiX = zombiX + 200;
				m_rc.left = m_rc.left + 200;
				m_rc.right = m_rc.right + 200;

				zombidead = false;

			}


		}
		if (zombidead == false)
		{
			zombistand = true;
			zombiFY = 0;
			zombiFX = 0;
		}




	}

}

zombi::zombi()
{
}


zombi::~zombi()
{
}
