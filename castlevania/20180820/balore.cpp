#include "stdafx.h"
#include "balore.h"
#include "room.h"
#include "player.h"
#include "animation.h"


HRESULT balore::init()
{
	m_pPlayer = g_mainGame.getPlayer();
	m_imgEye= IMAGEMANAGER->addImage("image/eye.bmp", "image/eye.bmp", 29, 29, true, RGB(84, 109, 142));
	m_imgHead= IMAGEMANAGER->addImage("image/head.bmp", "image/head.bmp", 864, 65,8 ,1, true, RGB(84, 109, 142));


	m_imgRHand = IMAGEMANAGER->addImage("image/Rhand.bmp", "image/Rhand.bmp", 100, 100, true, RGB(84, 109, 142));
	m_imgRarm = IMAGEMANAGER->addImage("image/Rarm.bmp", "image/Rarm.bmp", 100, 100, true, RGB(84, 109, 142));
	m_imgLHand = IMAGEMANAGER->addImage("image/Lhand.bmp", "image/Lhand.bmp", 100, 100, true, RGB(84, 109, 142));
	m_imgLarm = IMAGEMANAGER->addImage("image/Larm.bmp", "image/Larm.bmp", 100, 100, true, RGB(84, 109, 142));

	m_imgLaser= IMAGEMANAGER->addImage("image/Laser.bmp", "image/Laser.bmp", 300, 300, true, RGB(84, 109, 142));

	m_imgFire= IMAGEMANAGER->addImage("image/fire.bmp", "image/fire.bmp", 162, 65,6,1, true, RGB(84, 109, 142));
	m_pCImg = IMAGEMANAGER->addImage("숫자", "image/숫자.bmp", 96, 40, 12, 4, true, RGB(255, 0, 255));

	m_imgFlash= IMAGEMANAGER->addImage("image/flash.bmp", "image/flash.bmp", 63, 64, true, RGB(84, 109, 142));


	m_bIsAlive = true;

	m_fMapX = 220*3;
	m_fMapY = 50*3;

	m_fLHandMapY=m_fLArmMapY  =m_fY+ 150;
	m_fLHandMapX= m_fLArmMapX = 950;
	m_fRHandMapY =m_fRArmMapY = m_fY + 150;
	m_fRHandMapX= m_fRArmMapX = 400;

	m_nWhereSee = 0;

	m_nPhase = 1;

	m_nPattern = 1;

	m_fRArmAngle =m_fLArmAngle = 0;

	m_nLaserX = 0;

	m_nHitDmg = 0;

	m_bIsUp = true;

	m_bIsLeft = true;

	m_bIsPatternEnd = true;

	if (m_nPhase ==1)
	{
		m_bIsLaser = false;
	}
	else
	{
		m_bIsLaser = true;

	}

	m_bIsLeftLaser = true;

	m_ani = new animation[14];

	m_fStartCount = 0;

	for (int i = 0; i < 14; i++)
	{
		m_ani[i].init(162, 65, 27, 65);
		m_ani[i].setPlayFrame(0, 6);
		m_ani[i].setFPS(20);


	}

	m_rectEye = RectMakeCenter(-100, -100, 1, 1);

	m_mStatus = { "발로어",200,70,800,800,0,0,200,MonsterStatus::IDLE };

	m_nFlashRotate = 0;

	return S_OK;
}

void balore::release()
{
}	

void balore::update()
{
	Damagehit();
	if (!m_bIsAlive)
		return;

	if (m_mStatus.curHP < 400)
	{
		if (m_nPhase == 1)
		{
			m_bIsLaser = true;
		}
		m_nPhase = 2;
	}
	if (m_mStatus.curHP <= 0)
	{
		m_bIsAlive = false;
		
	}

	m_fX = m_fMapX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_fY = m_fMapY - ROOMMANAGER->getCurrRoom()->getPosMap().y;

	if (m_pPlayer->getFx() + ROOMMANAGER->getCurrRoom()->getPosMap().x < 220 * 3)
	{
		m_nWhereSee = 3;
	}
	else if (m_pPlayer->getFx() + ROOMMANAGER->getCurrRoom()->getPosMap().x < 290 * 3)
	{
		m_nWhereSee = 1;
	}
	else
	{
		m_nWhereSee = 2;

	}

	switch (m_nPhase)
	{
		case 1:
			phase1Update();
			break;

		case 2:

			phase2Update();

			break;

		default:
			break;
	}
   	m_fAngle = (MY_UTIL::getAngle(m_fMapX, m_fY - m_imgHead->getFrameHeight() / 2 + 30, m_nLaserX , START_Y))*180/PI;
	//(m_pPlayer->getRc().left )
	
	chackCollition();

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		m_mStatus.curHP -= 300;
	}

}

void balore::headRender(HDC hdc)
{
	if (!m_bIsAlive)
		return;

	if (m_nPhase==1)
	{


		switch (m_nWhereSee)
		{
			case 1:
				m_imgEye->render(hdc, m_fX + 125, m_fY - m_imgHead->getFrameHeight() / 2 + 37 - ((START_Y - m_pPlayer->getFY()) / 15), 3);
				break;
			case 2:
				m_imgEye->render(hdc, m_fX + 122, m_fY - m_imgHead->getFrameHeight() / 2 + 52 - ((START_Y - m_pPlayer->getFY()) / 15), 3);
				break;
			case 3:
				m_imgEye->render(hdc, m_fX + 120, m_fY - m_imgHead->getFrameHeight() / 2 + 45 - ((START_Y - m_pPlayer->getFY()) / 15), 3);
				break;

			default:
				break;
		}
		
		m_imgHead->frameRender(hdc, m_fX - m_imgHead->getFrameWidth() / 2, m_fY - m_imgHead->getFrameHeight() / 2, m_nWhereSee, 1,3);

		

	}
	else if (m_nPhase == 2)
	{

		m_imgEye->render(hdc, m_fX , m_fY - m_imgHead->getFrameHeight() / 2 + 30, 3);

		m_imgHead->frameRender(hdc, m_fX - m_imgHead->getFrameWidth() / 2, m_fY - m_imgHead->getFrameHeight() / 2, 6, 1, 3);

		//m_imgLaser->rotateRender(hdc, -m_fAngle, m_fX - m_imgHead->getFrameWidth() / 2, m_fY - m_imgHead->getFrameHeight() / 2 + 52, 0.5f, 0.5f, 1);

		if (m_nFlashRotate%10 < 2)
		{
			m_imgFlash->rotateRender(hdc, m_nFlashRotate++,m_fX-100, m_fY - m_imgHead->getFrameHeight() / 2 -75,0.5,0.5,6 );

		}
		else
		{
			m_imgFlash->rotateRender(hdc, m_nFlashRotate++, m_fX - 140, m_fY - m_imgHead->getFrameHeight() / 2 - 110, 0.5, 0.5, 7);

		}


		
	}
	//Rectangle(hdc, m_rectEye.left, m_rectEye.top, m_rectEye.right, m_rectEye.bottom);
}

void balore::armRender(HDC hdc)
{
	if (m_nHitDmg != 0)
	{
		DamageImg(hdc, m_nHitDmg);
	}
	if (!m_bIsAlive)
		return;
	//if (m_nPhase == 1)
	//{
	//	m_imgHead->frameRender(hdc, m_fX - m_imgHead->getFrameWidth() / 2, m_fY - m_imgHead->getFrameHeight() / 2, m_nWhereSee, 1, 3);
	//}
	if (m_nPhase == 1)
	{
		m_imgRarm->rotateRender(hdc, -m_fRArmAngle, m_fRArmX, m_fRArmY - m_imgHead->getFrameHeight() / 2 + 52, 0.5f, 0.5f, 3);
		m_imgLarm->rotateRender(hdc, m_fLArmAngle, m_fLArmX, m_fLArmY - m_imgHead->getFrameHeight() / 2 + 52, 0.5f, 0.5f, 3);
		m_imgRHand->rotateRender(hdc, -m_fRArmAngle, m_fRHandX + 100, m_fRHandY - m_imgHead->getFrameHeight() / 2 + 52, 0.5f, 0.5f, 3);
		m_imgLHand->rotateRender(hdc, m_fLArmAngle, m_fLHandX - 100, m_fLHandY - m_imgHead->getFrameHeight() / 2 + 52, 0.5f, 0.5f, 3);

		for(int i=0 ; i<2;i++)
		{

			//Rectangle(hdc, m_handDownRect[i].left, m_handDownRect[i].top, m_handDownRect[i].right, m_handDownRect[i].bottom);

			//Rectangle(hdc, m_handUpRect[i].left, m_handUpRect[i].top, m_handUpRect[i].right, m_handUpRect[i].bottom);
		}
	}

	if (m_bIsLaser)
	{
		if (m_nLaserX>700)
		{
			m_imgLaser->rotateRender(hdc, -m_fAngle, m_fX - 715 - (m_nLaserX < 800 ? (m_nLaserX / 30) : (800 / 30)), (m_fY - m_imgHead->getFrameHeight() / 2 - 715) + (m_nLaserX < 1000 ? (m_nLaserX / 15) : (1000 / 15)), 0.1f, 0.5f, 6);
		}
		else
		{
			m_imgLaser->rotateRender(hdc, -m_fAngle, m_fX - 715 - (m_nLaserX < 800 ? (m_nLaserX / 30) : (800 / 30)), (m_fY - m_imgHead->getFrameHeight() / 2 - 715), 0.1f, 0.5f, 6);
		}

	}
	else
	{

		//m_imgFire->render(hdc,300- m_imgFire->getFrameWidth()/2 ,START_Y- m_imgFire->getFrameHeight()/2 -120,3);
		for (int i = 0; i < 14; i++)
		{
			if(m_ani[i].getIsPlaying())
 			m_imgFire->aniRender(hdc, 200 + ((27*3) * i) - ROOMMANAGER->getCurrRoom()->getPosMap().x, START_Y - m_imgFire->getFrameHeight() / 2 - 120, &(m_ani[i]), 3);


			//Rectangle(hdc, m_fireRect[i].left, m_fireRect[i].top, m_fireRect[i].right, m_fireRect[i].bottom);
		}
	}



	
}

void balore::phase1Update()
{

	m_fLArmY = m_fLArmMapY - ROOMMANAGER->getCurrRoom()->getPosMap().y;
	m_fRArmY = m_fRArmMapY - ROOMMANAGER->getCurrRoom()->getPosMap().y;
	m_fLArmX = m_fLArmMapX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_fRArmX = m_fRArmMapX - ROOMMANAGER->getCurrRoom()->getPosMap().x;


	m_fLHandY = m_fLHandMapY - ROOMMANAGER->getCurrRoom()->getPosMap().y;
	m_fRHandY = m_fRHandMapY - ROOMMANAGER->getCurrRoom()->getPosMap().y;
	m_fLHandX = m_fLHandMapX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_fRHandX = m_fRHandMapX - ROOMMANAGER->getCurrRoom()->getPosMap().x;

	if (m_bIsPatternEnd)
	{
		if (START_ARMY < m_fRArmMapY)
		{
			m_fRArmMapY--;
			m_fRHandMapY -= 1.2;
		}
		else if(START_ARMY > m_fRArmMapY)
		{
			m_fRArmMapY++;
			m_fRHandMapY += 1.2;
		}

		if (START_ARMY < m_fLArmMapY)
		{
			m_fLArmMapY--;
			m_fLHandMapY -= 1.2;
		}
		else if (START_ARMY > m_fLArmMapY)
		{
			m_fLArmMapY++;
			m_fLHandMapY += 1.2;
		}




		if (400 < m_fRHandMapX)
		{
			m_fRArmMapX--;
			m_fRHandMapX --;
		}
		else if (400 > m_fRHandMapX)
		{
			m_fRArmMapX++;
			m_fRHandMapX ++;
		}

		if (950 < m_fLHandMapX)
		{
			m_fLArmMapX--;
			m_fLHandMapX --;
		}
		else if (950 > m_fLHandMapX)
		{
			m_fLArmMapX++;
			m_fLHandMapX++;
		}

		if ((m_fRArmMapY == START_ARMY)&&( m_fLArmMapY == START_ARMY) && (m_fLHandMapX == 950) && (400 == m_fRHandMapX))
		{
			m_bIsPatternEnd = false;
		}

	}
	else
	{
		m_bIsPatternEnd = false;

		switch (m_nPattern)
		{
			case 0:

				if (m_bIsUp)
				{
					m_fRArmMapY -= 2;
					m_fRHandMapY -= 2.4;

					m_fLArmMapY -= 2;
					m_fLHandMapY -= 2.4;

					m_fLArmMapX++;
					m_fRArmMapX--;
					m_fLHandMapX++;
					m_fRHandMapX--;

					if (m_pPlayer->getIsLide())
					{
						m_pPlayer->setFx(m_pPlayer->getFx() +1);
					}

					if (m_pPlayer->getIsRide())
					{
						m_pPlayer->setFx(m_pPlayer->getFx() -1);
					}
				}
				else
				{
					m_fRArmMapY += 8;
					m_fRHandMapY += 9.6;

					m_fLArmMapY += 8;
					m_fLHandMapY += 9.6;

					m_fLArmMapX -= 4;
					m_fRArmMapX += 4;
					m_fLHandMapX -= 4;
					m_fRHandMapX += 4;

					if (m_pPlayer->getIsLide())
					{
						m_pPlayer->setFx(m_pPlayer->getFx() - 4);
					}

					if (m_pPlayer->getIsRide())
					{
						m_pPlayer->setFx(m_pPlayer->getFx() + 4);
					}
				}



				if (m_fRArmMapY < -20)
				{
					m_bIsUp = false;
				}
				else if (m_fRArmMapY > 250)
				{
					m_bIsUp = true;
					m_bIsPatternEnd = true;
					m_nPattern = 1;
				}

				break;

			case 1:

				if (m_bIsLeft)
				{
					//m_fRArmMapY -= 2;
					//m_fRHandMapY -= 2.4;

					//m_fLArmMapY -= 2;
					//m_fLHandMapY -= 2.4;

					m_fLArmMapX+=2;
					m_fRArmMapX-=2;
					m_fLHandMapX+=2;
					m_fRHandMapX-=2;

					if (m_pPlayer->getIsLide())
					{
						m_pPlayer->setFx(m_pPlayer->getFx() + 2);
					}

					if (m_pPlayer->getIsRide())
					{
						m_pPlayer->setFx(m_pPlayer->getFx() - 2);
					}

				}
				else
				{
					m_fRArmMapY -= 2;
					m_fRHandMapY -= 2.4;

					m_fLArmMapY += 2;
					m_fLHandMapY += 2.4;

					m_fLArmMapX -= 8;
					m_fRArmMapX += 8;
					m_fLHandMapX -= 8;
					m_fRHandMapX += 8;


					if (m_pPlayer->getIsLide())
					{
						m_pPlayer->setFx(m_pPlayer->getFx() - 8);
					}

					if (m_pPlayer->getIsRide())
					{
						m_pPlayer->setFx(m_pPlayer->getFx() + 8);
					}

				}



				if (m_fRArmMapX < 200)
				{
					m_bIsLeft = false;
				}
				else if (m_fRArmMapX > 600)
				{
					m_bIsLeft = true;
					m_bIsPatternEnd = true;
					m_nPattern = 0;
				}
				break;


			default:
				break;
		}

	}

	m_handDownRect[0] = RectMakeCenter(m_fLHandX, m_fLHandY+150, 120, 100);

	m_handDownRect[1] = RectMakeCenter(m_fRHandX+200, m_fRHandY+150, 120, 100);


	m_handUpRect[0] = RectMakeCenter(m_fLHandX, m_fLHandY + 100, 120, 50);

	m_handUpRect[1] = RectMakeCenter(m_fRHandX + 200, m_fRHandY + 100, 120, 50);


	switch (m_nWhereSee)
	{
	case 1:
		m_rectEye = RectMake(m_fX + 125, m_fY - m_imgHead->getFrameHeight() / 2 + 37 - ((START_Y - m_pPlayer->getFY()) / 15), 90, 90);
		//m_imgEye->render(hdc, m_fX + 125, m_fY - m_imgHead->getFrameHeight() / 2 + 37 - ((START_Y - m_pPlayer->getFY()) / 15), 3);
		break;
	case 2:
		m_rectEye = RectMake(m_fX + 122, m_fY - m_imgHead->getFrameHeight() / 2 + 52 - ((START_Y - m_pPlayer->getFY()) / 15), 90, 90);

		//m_imgEye->render(hdc, m_fX + 122, m_fY - m_imgHead->getFrameHeight() / 2 + 52 - ((START_Y - m_pPlayer->getFY()) / 15), 3);
		break;
	case 3:
		m_rectEye = RectMake(m_fX + 120, m_fY - m_imgHead->getFrameHeight() / 2 + 45 - ((START_Y - m_pPlayer->getFY()) / 15), 90, 90);

		//m_imgEye->render(hdc, m_fX + 120, m_fY - m_imgHead->getFrameHeight() / 2 + 45 - ((START_Y - m_pPlayer->getFY()) / 15), 3);
		break;

	default:
		break;
	}



	m_fRArmAngle = ((START_ARMY - m_fRArmMapY) * 10)*(PI / 180);
	m_fLArmAngle = ((START_ARMY - m_fLArmMapY) * 10)*(PI / 180);




}

void balore::phase2Update()
{

	m_handDownRect[0] = RectMakeCenter(-100, -100, 1, 1);

	m_handDownRect[1] = RectMakeCenter(-100, -100, 1, 1);


	m_handUpRect[0] = RectMakeCenter(-100, -100, 1, 1);

	m_handUpRect[1] = RectMakeCenter(-100, -100, 1, 1);

	if (m_bIsLaser)
	{
		if (m_bIsLeftLaser)
		{
			if (m_nLaserX < 1300)
			{
				m_nLaserX += 20;

			}
			else
			{
				m_bIsLaser = false;
			}

		}

	}
	else
	{	
		firePlay();
	}
	m_rectEye = RectMake(m_fX, m_fY - m_imgHead->getFrameHeight() / 2 + 37 - ((START_Y - m_pPlayer->getFY()) / 15), 90, 90);

}

void balore::firePlay()
{
	for (int i = 0; i < 14; i++)
	{

		m_ani[i].frameUpdate(TIMEMANAGER->getElapsedTime());
		
	}

	if (m_fStartCount == 0)
	{
		m_ani[0].start();
	}
	for (int i = 1; i < 14; i++)
	{
		if (m_ani[i-1].getNowPlayFrame() == 1)
		{
			m_ani[i].start();
		}

		if (m_ani[i].getNowPlayFrame() > 1 && m_ani[i].getIsPlaying())
		{
			m_fireRect[i] = RectMake(200 + ((27 * 3) * i) - ROOMMANAGER->getCurrRoom()->getPosMap().x, START_Y - m_imgFire->getFrameHeight() / 2 , 27 * 3, 65 );
		}
		else
		{
			m_fireRect[i] = RectMake(-200, -200, 1, 1);
		}
	}


	




	m_fStartCount += TIMEMANAGER->getElapsedTime();




	bool isAllFalse = true;
	for (int i = 0; i < 14; i++)
	{

		
		isAllFalse= m_ani[i].getIsPlaying();

		if (isAllFalse)
		{
			isAllFalse = false;
			break;
		}

		isAllFalse = true;

	}

	if (isAllFalse)
	{
		m_fStartCount = 0;
		m_bIsLaser = true;
		m_bIsLeftLaser = true;
		m_nLaserX = 0;
	}

}

void balore::fireRender()
{
}

void balore::chackCollition()
{
	for (int i = 0 ; i < 2; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayer->getRc(), &m_handDownRect[i]))
		{
			int damage = m_mStatus.curAtt - m_pPlayer->getState().curDef;

			if (damage < 1)
			{
				damage = 1;
			}

			if (m_pPlayer->getHitDivineC() == 100)
			{
				m_pPlayer->setHitDmg(damage);
				m_pPlayer->hitCollision(damage);


			}
		}

		m_pPlayer->bossRectCollision(m_handUpRect[i],i);

	}

	for (int i = 0; i < 14; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayer->getRc(), &m_fireRect[i]))
		{
			int damage = m_mStatus.curAtt+30 - m_pPlayer->getState().curDef;

			if (damage < 1)
			{
				damage = 1;
			}

			if (m_pPlayer->getHitDivineC() == 100)
			{
				m_pPlayer->setHitDmg(damage);
				m_pPlayer->hitCollision(damage);


			}
		}
	}

	RECT rc;
	if (IntersectRect(&rc, &m_pPlayer->getIRC(), &m_rectEye))
	{
		//(*iter)->setIsAlive(false);


		int damage = m_pPlayer->getState().curAtt - m_mStatus.curDef;

		if (damage < 1)
		{
			damage = 1;
		}

		if (!(m_bIshit))
			m_nHitDmg=damage;


	}
}


void balore::Damagehit()
{
	if (m_nHitDmg != 0)
	{
		m_fDamageY--;
		m_bIshit = true;
		if (m_fDivineTime == 0)
		{
			m_mStatus.curHP -= m_nHitDmg;
		}


		if (m_fDivineTime > 0.5)
		{
			m_nHitDmg = 0;

		}

		m_fDivineTime += TIMEMANAGER->getElapsedTime();
	}
	else
	{
		m_bIshit = false;
		m_fDamageY = m_fMapY - 30;


		m_fDivineTime = 0;
	}


}

void balore::DamageImg(HDC hdc, int damage)
{
	int Num = 0;

	int fx = m_fX + 100;

	if (damage >= 10000)
	{
		m_pCImg->frameRender(hdc, m_fMapX, m_fDamageY, 9, 2, 3);
		m_pCImg->frameRender(hdc, m_fMapX + 15, m_fDamageY, 9, 2, 3);
		m_pCImg->frameRender(hdc, m_fMapX + 30, m_fDamageY, 9, 2, 3);
		m_pCImg->frameRender(hdc, m_fMapX + 45, m_fDamageY, 9, 2, 3);
		m_pCImg->frameRender(hdc, m_fMapX + 60, m_fDamageY, 9, 2, 3);
	}
	else if (damage < 10000 && damage >= 1000)
	{

		Num = (damage / 1000);
		m_pCImg->frameRender(hdc, m_fMapX, m_fDamageY, Num, 2, 3);
		Num = (damage / 100) - ((damage / 1000) * 10);
		m_pCImg->frameRender(hdc, m_fMapX + 15, m_fDamageY, Num, 2, 3);
		Num = (damage / 10) - ((damage / 100) * 10);
		m_pCImg->frameRender(hdc, m_fMapX + 30, m_fDamageY, Num, 2, 3);
		Num = (damage % 10);
		m_pCImg->frameRender(hdc, m_fMapX + 45, m_fDamageY, Num, 2, 3);
	}
	else if (damage < 1000 && damage >= 100)
	{
		Num = (damage / 100);
		m_pCImg->frameRender(hdc, fx, m_fDamageY, Num, 2, 3);
		Num = (damage / 10) - ((damage / 100) * 10);
		m_pCImg->frameRender(hdc, fx + 15, m_fDamageY, Num, 2, 3);
		Num = (damage % 10);
		m_pCImg->frameRender(hdc, fx + 30, m_fDamageY, Num, 2, 3);
	}
	else if (damage < 100 && damage >= 10)
	{
		Num = (damage / 10) - ((damage / 100) * 10);
		m_pCImg->frameRender(hdc, fx, m_fDamageY, Num, 2, 3);
		Num = (damage % 10);
		m_pCImg->frameRender(hdc, fx + 15, m_fDamageY, Num, 2, 3);
	}
	else
	{
		Num = (damage % 10);
		m_pCImg->frameRender(hdc, fx, m_fDamageY, Num, 2, 3);
	}

}


balore::balore()
{
}


balore::~balore()
{
}
