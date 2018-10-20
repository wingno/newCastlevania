#include "stdafx.h"
#include "RoomObject.h"
#include "room.h"
#include "SubObject.h"

HRESULT RoomObject::init(int nFX, int nFY, int ObjNum)
{
	//오브잭트
	
	m_imgObj = IMAGEMANAGER->addImage("candle", "image/object/candle.bmp", 198, 23, 11, 1, true, RGB(0, 64, 128));
	m_imgObj1 = IMAGEMANAGER->addImage("minifire", "image/object/minifire.bmp", 56, 20, 4, 1, true, RGB(0, 64, 128));
	m_imgObj2 = IMAGEMANAGER->addImage("soulob", "image/object/soulobject.bmp", 200, 46, 10, 1, true, RGB(0, 64, 128));


	//오브잭트
	m_bObjStand = true;
	//파괴 여부를 채크
	m_bObjDestruction = false;
	m_bObjDestructionMove = false;
	//위치
	m_nFX = nFX;
	m_nFY = nFY;
	//오브잭트 번호
	m_nObjNum = ObjNum;
	//프레임 
	m_nObjFrameX = 0;
	m_nObjFrameY = 0;

	m_nObjIdx = 0;
	m_nObjCount = 0;

	m_rc = RectMakeCenter(m_nFX + 26,  m_nFY + 45, m_imgObj->getWidth() / 4 - 3, m_imgObj->getHeight() * 2);

	m_SubObject = new SubObject;
	m_SubObject->init();


	return S_OK;
}

void RoomObject::release()
{
}

void RoomObject::update()
{
	ObjectCode();
	



	m_rc = RectMakeCenter(m_nFX + 26 - ROOMMANAGER->getCurrRoom()->getPosMap().x,  m_nFY + 45- ROOMMANAGER->getCurrRoom()->getPosMap().y,
		 m_imgObj->getWidth() / 4 - 3, m_imgObj->getHeight() * 2);



}

void RoomObject::render(HDC hdc)
{
	if (m_bObjStand||
		m_bObjDestruction||
		m_bObjDestructionMove)
	{
		//Rectangle(hdc, m_rc.left, m_rc.top,m_rc.right, m_rc.bottom);
		
		switch (m_nObjNum)
		{
		case 0: //촛불
			m_imgObj->frameRender(hdc, m_nFX - ROOMMANAGER->getCurrRoom()->getPosMap().x,
				m_nFY - ROOMMANAGER->getCurrRoom()->getPosMap().y
				, m_nObjFrameX, m_nObjFrameY, 3);
			break;
		case 1:
			m_imgObj1->frameRender(hdc, m_nFX - ROOMMANAGER->getCurrRoom()->getPosMap().x,
				m_nFY - ROOMMANAGER->getCurrRoom()->getPosMap().y
				, m_nObjFrameX, m_nObjFrameY, 3);
			break;
		case 2:
			m_imgObj2->frameRender(hdc, m_nFX - ROOMMANAGER->getCurrRoom()->getPosMap().x,
				m_nFY - ROOMMANAGER->getCurrRoom()->getPosMap().y
				, m_nObjFrameX, m_nObjFrameY, 3);
			break;

		}
	}
	



	m_SubObject->render(hdc);
	
}

void RoomObject::ObjectCode()
{
	
	



	switch (m_nObjNum)
	{
	case 0: //촛불
		
		//기본동작
		if (m_bObjStand)
		{
			m_nObjIdx++;
			if (m_nObjIdx % 7 == 0)
			{
				m_nObjFrameX++;
				if (m_nObjFrameX > 5)
				{
					m_nObjFrameX = 0;
				}
			}

			if (m_bObjStand == false)
			{
				m_bObjDestruction = true;
			}
		}


		if (m_bObjDestruction)
		{

			m_nObjIdx++;
			if (m_nObjIdx % 3 == 0)
			{
				m_nObjFrameX++;
				if (m_nObjFrameX > 8)
				{
					m_nObjFrameX = 8;
					if (m_nObjFrameX = 8)
					{
						 m_nFY -= 4;
						m_nObjCount++;

						if (m_nObjCount == 5)
						{
							m_nObjFrameX = 8;
							m_bObjDestruction = false;
							m_bObjDestructionMove = true;

						}

					}
				}
			}

		}
		// 죽을떄 취하는모션
		if (m_bObjDestructionMove)
		{

			m_nObjIdx++;
			if (m_nObjIdx % 5 == 0)
			{
				m_nObjFrameX++;
				if (m_nObjFrameX > 10)
				{
					m_nObjNum = 0;
			
					m_bObjDestructionMove = false;
					m_SubObject->SetSubObjectXY(m_nFX, m_nFY);
					m_SubObject->setAlive(true);
					
				}
			}

		}

		
		break;

	case 1: //휏불
	
		//기본동작
		if (m_bObjStand)
		{
			m_nObjIdx++;
			if (m_nObjIdx % 5 == 0)
			{
				m_nObjFrameX++;
				if (m_nObjFrameX > 3)
				{
					m_nObjFrameX = 0;

				}
			}
			
		}

		if (!m_bObjStand)
		{
			m_nObjIdx++;
			if (m_nObjIdx % 5 == 0)
			{
				m_nObjFrameX++;
				if (m_nObjFrameX > 3)
				{
					m_nObjFrameX = 0;

				}
			}

		}
		break;
	case 2: 
		if (m_bObjStand)
		{
			m_nObjIdx++;
			if (m_nObjIdx % 3 == 0)
			{
				m_nObjFrameX++;
				if (m_nObjFrameX > 9)
				{
					m_nObjFrameX = 0;

				}

			}
			
			
		}

		if (m_bObjStand == false)
		{
			m_bObjDestructionMove = false;
			m_bObjDestruction = false;
		}

		break;
		default:
		break;
	}


	if (m_bObjDestructionMove == false && m_bObjStand == false && m_bObjDestruction == false)
	{

		m_SubObject->update();

	}

	


}




RoomObject::RoomObject()
{


}


RoomObject::~RoomObject()
{
}
