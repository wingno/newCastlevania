#include "stdafx.h"
#include "SkeletonArcher.h"
#include"player.h"


HRESULT SkeletonArcher::init(int startX, int startY)
{

	m_Archer = IMAGEMANAGER->addImage("M2", "MONSTER/Skullbow.bmp", 480, 80, 12, 2, true, RGB(84, 109, 142));


	ArcherX = startX;
	Archery = startY;
	ArcherFX, ArcherFY = 0;


	

	Archermove = false;
	Archerstand = true;
	Archerdead = false;
	


	

	m_rc = RectMakeCenter(ArcherX  +10, Archery + 20 , m_Archer->getWidth() /5, m_Archer->getHeight() + 50);


	return S_OK;
}

void SkeletonArcher::release()
{
}

void SkeletonArcher::update()
{
	MOVE();
}

void SkeletonArcher::render(HDC hdc)
{

	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

	m_Archer->frameRender(hdc, ArcherX -60 , Archery - m_Archer->getHeight() / 2, ArcherFX, ArcherFY, 3);
}


void SkeletonArcher::MOVE()
{

	if (Archerstand) //해골궁수 서있는모습
	{
		ArcherFX = 0;
		Archercount++;
		BACKcount++;
	/*	if (BACKcount == 100)
		{
			Archermove = true;
			Archerstand = false;
			BACKcount == 0;
		}*/
		
		if (Archercount == 400)
		{
			Archerdead = true;
			ArcherFX = 3;
			Archerstand = false;
			Archermove = false;
			Archercount = 0;
		}
	}

	//if (Archermove) //단순 이동모션  //뒤로 이동하는 모션이라 주석처해놓음 충돌처리하기 편하개
	//{

	//	ArcherX += 1;
	//	m_rc.left += 1;
	//	m_rc.right += 1;
	//	ArcherIDX++;
	//	BACKcount++;
	//	
	//	if (ArcherIDX % 40
	//		== 0)
	//	{
	//		ArcherFX++;
	//		if (ArcherFX > 2)
	//		{
	//			ArcherFX = 1;

	//			if (BACKcount == 20)
	//			{
	//				Archermove = false;
	//				Archerstand = true;
	//				Archerdead = false;
	//				BACKcount == 0;
	//			}
	//		}
	//	}

	//}

	if (Archerdead) //해골궁수일경우는 어택임 
	{

		ArcherIDX++;
		if (ArcherIDX % 10 == 0)
		{
			ArcherFX++;
			if (ArcherFX > 11)
			{
				ArcherFX = 3;
				Archerdead = false;
				Archerstand = true;

			}
		}
		

	}
}



SkeletonArcher::SkeletonArcher()
{
}


SkeletonArcher::~SkeletonArcher()
{
}
