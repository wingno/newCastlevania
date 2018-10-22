#include "stdafx.h"
#include "player.h"
#include "room.h"
#include "bulletSoul.h"
#include "guardianSoul.h"
#include "enchantSoul.h"
#include "handItem.h"
#include "bodyItem.h"
#include "accessoryItem.h"
#include "ItemUse.h"
#include "animation.h"

HRESULT player::init()
{
	// 플레이어의 오른쪽 보고 있을떄의 이미지 0부터 프레임 시작
	m_pImg = IMAGEMANAGER->addImage("player", "image/playerMotion.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));

	// 플레이어의 왼쪽 보고 있을떄의 이미지 18부터 프레임 시작
	m_pImg2 = IMAGEMANAGER->addImage("player2", "image/playerMotion2.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));

	// 발뭉
	m_pImg3 = IMAGEMANAGER->addImage("발뭉", "image/발뭉.bmp", 720, 48, 9, 2, true, RGB(255, 0, 255));

	// 크라우 솔루스
	m_pImg4 = IMAGEMANAGER->addImage("크라우솔루스", "image/크라우솔루스.bmp", 110, 110, true, RGB(255, 0, 255));

	// 숫자 이미지
	m_pCImg = IMAGEMANAGER->addImage("숫자", "image/숫자.bmp", 96, 40, 12, 4, true, RGB(255, 0, 255));

	m_bIsRide = false;


	// 플레이어의 초기 위치 값
	m_fX = 800;
	m_fY = 1000;

	// 플레이어가 오른쪽 보고 있는 상태로 초기화
	m_bPlayerSee = 1;

	// 플레이어의 공격 모션 초기화

	// 플레이어의 점프 모션 초기화 점프는 int형식으로 주어서 2단 점프를 구현

	// 플레이어의 앉기 모션 초기화

	// 플레이어의 백대쉬 모션 초기화

	// 플레이어의 슬라이딩 모션 초기화

	// 플레이어의 착지 모션 초기화

	// 플레이어의 스킬대기 모션 초기화

	// 플레이어의 피격 모션 초기화

	// 플레이어의 죽음

	m_nSwordAngle = 0;

	m_status = { 10,10,12,12,11,11,9,9, 10,10,6,6,320,320,80,80,0,84 };

	m_nGold = 0;

	m_rc = RectMakeCenter(m_fX, m_fY, (m_pImg->getFrameWidth() - 20) * 3, (m_pImg->getFrameHeight() - 20) * 3);
	m_Irc = RectMakeCenter(0, 0, 0, 0);

	m_xCameraOn = false;
	m_yCameraOn = false;

	m_bIsControll = true;


	bulletSoul* baseBSoul = new bulletSoul;
	baseBSoul->init(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "------", "---");

	bulletSoul* testBSoul = new bulletSoul;
	testBSoul->init(0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 8, "해골사수", "마법의 활을 쏜다");


	m_soulInven.vecBulletSoul.push_back(baseBSoul);
	m_soulInven.vecBulletSoul.push_back(testBSoul);



	guardianSoul* baseGSoul = new guardianSoul;
	baseGSoul->init(1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "------", "---");

	guardianSoul* testGSoul = new guardianSoul;
	testGSoul->init(1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 10, "메두사 헤드", "공중에서 정지가 가능하다.");

	m_soulInven.vecGuardianSoul.push_back(baseGSoul);
	m_soulInven.vecGuardianSoul.push_back(testGSoul);


	enchantSoul* baseESoul = new enchantSoul;
	baseESoul->init(2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "------", "---");

	enchantSoul* testESoul = new enchantSoul;
	testESoul->init(2, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, "좀비", "CON +2");

	m_soulInven.vecEnchantSoul.push_back(baseESoul);
	m_soulInven.vecEnchantSoul.push_back(testESoul);



	handItem* baseHItem = new handItem;
	baseHItem->init(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "------", "---");

	handItem* testHItem = new handItem;
	testHItem->init(0, 1, 1, 100, 0, 0, 0, 0, 0, 0, 0, "발뭉", "용을 살해한 검");

	handItem* test2HItem = new handItem;
	test2HItem->init(0, 1, 2, 99, 0, 7, 7, 7, 0, 0, 0, "크라우-솔루스", "빛나는 검날을 가진 검");



	m_ItemInven.vecHandItem.push_back(baseHItem);
	m_ItemInven.vecHandItem.push_back(testHItem);
	m_ItemInven.vecHandItem.push_back(test2HItem);


	bodyItem* baseBItem = new bodyItem;
	baseBItem->init(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "------", "---");

	bodyItem* testBItem = new bodyItem;
	testBItem->init(0, 1, 1, 0, 5, 0, 0, 0, 0, 0, 0, "평상복", "평소에 자주 입는 옷");

	bodyItem* testBItem1 = new bodyItem;
	testBItem1->init(0, 1, 5, 0, 33, 6, 6, 6, 6, 0, 0, "드라큘라 옷", "드라큘라의 마력이 깃든 옷");



	m_ItemInven.vecBodyItem.push_back(baseBItem);
	m_ItemInven.vecBodyItem.push_back(testBItem);
	m_ItemInven.vecBodyItem.push_back(testBItem1);


	accessoryItem* baseAItem = new accessoryItem;
	baseAItem->init(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "------", "---");

	accessoryItem* testAItem = new accessoryItem;
	testAItem->init(0, 1, 1, 0, 2, 0, 0, 0, 0, 0, 0, "머플러", "따뜻한 머플러");

	accessoryItem* testAItem1 = new accessoryItem;
	testAItem1->init(0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, "펜던트", "펜던트");

	accessoryItem* testAItem2 = new accessoryItem;
	testAItem2->init(0, 1, 5, 0, 6, 2, 2, 2, 0, 0, 0, "마왕의 반지", "마왕이 몸에 지니고 있던 반지");


	m_ItemInven.vecAccessoryItem.push_back(baseAItem);
	m_ItemInven.vecAccessoryItem.push_back(testAItem);
	m_ItemInven.vecAccessoryItem.push_back(testAItem1);
	m_ItemInven.vecAccessoryItem.push_back(testAItem2);


	ItemUse* testuItem = new ItemUse;
	testuItem->init(0, 1, 0, 0, 0, 0, 0, 0, 0, 100, 0, "포션", "체력을 100 회복한다.");
	ItemUse* testuItem1 = new ItemUse;
	testuItem1->init(0, 2, 1, 0, 0, 0, 0, 0, 0, 400, 0, "하이포션", "체력을 400 회복한다.");
	ItemUse* testuItem2 = new ItemUse;
	testuItem2->init(0, 2, 2, 0, 0, 0, 0, 0, 0, 999999, 0, "엑스포션", "체력을 완전히 회복한다.");
	ItemUse* testuItem3 = new ItemUse;
	testuItem3->init(0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 100, "마인드 업", "마나를 100회복한다");
	ItemUse* testuItem4 = new ItemUse;
	testuItem4->init(0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 200, "마인드 하이업", "마나를 200회복한다.");
	ItemUse* testuItem5 = new ItemUse;
	testuItem5->init(0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 999999, "마나 프리즘", "마나가 완전히 회복된다.");
	ItemUse* testuItem6 = new ItemUse;
	testuItem6->init(0, 6, 6, 0, 0, 0, 0, 0, 0, -200, 0, "썩은 고기", "썩은 고기 먹으면 안될것 같다.");

	m_ItemInven.vecItemUse.push_back(testuItem);
	m_ItemInven.vecItemUse.push_back(testuItem1);
	m_ItemInven.vecItemUse.push_back(testuItem2);
	m_ItemInven.vecItemUse.push_back(testuItem3);
	m_ItemInven.vecItemUse.push_back(testuItem4);
	m_ItemInven.vecItemUse.push_back(testuItem5);
	m_ItemInven.vecItemUse.push_back(testuItem6);




	m_soulSet.bS = baseBSoul;
	m_soulSet.gS = baseGSoul;
	m_soulSet.eS = baseESoul;

	m_ItemSet.hI = testHItem;
	m_ItemSet.bI = baseBItem;
	m_ItemSet.aI = baseAItem;

	
	m_status = changeStatus(m_status, m_soulSet, m_ItemSet);


	m_nHitDmg = 0;

	m_PlayerState = FALL;

	m_bIsGround = false;


	aniInit();

	return S_OK;
}

void player::release()
{
	for (int i=0; i< m_soulInven.vecBulletSoul.size(); i++)
	{
		m_soulInven.vecBulletSoul[i]->release();
		delete (m_soulInven.vecBulletSoul[i]);
	}
	m_soulInven.vecBulletSoul.clear();

	for (int i = 0; i < m_soulInven.vecGuardianSoul.size(); i++)
	{
		m_soulInven.vecGuardianSoul[i]->release();
		delete (m_soulInven.vecGuardianSoul[i]);
	}
	m_soulInven.vecGuardianSoul.clear();

	for (int i = 0; i < m_soulInven.vecEnchantSoul.size(); i++)
	{
		m_soulInven.vecEnchantSoul[i]->release();
		delete (m_soulInven.vecEnchantSoul[i]);
	}
	m_soulInven.vecEnchantSoul.clear();

	for (int i = 0; i < m_ItemInven.vecHandItem.size(); i++)
	{
		m_ItemInven.vecHandItem[i]->release();
		delete (m_ItemInven.vecHandItem[i]);
	}
	m_ItemInven.vecHandItem.clear();


	for (int i = 0; i < m_ItemInven.vecBodyItem.size(); i++)
	{
		m_ItemInven.vecBodyItem[i]->release();
		delete (m_ItemInven.vecBodyItem[i]);
	}
	m_ItemInven.vecBodyItem.clear();

	for (int i = 0; i < m_ItemInven.vecAccessoryItem.size(); i++)
	{
		m_ItemInven.vecAccessoryItem[i]->release();
		delete (m_ItemInven.vecAccessoryItem[i]);
	}
	m_ItemInven.vecAccessoryItem.clear();

	for (int i = 0; i < m_ItemInven.vecItemUse.size(); i++)
	{
		m_ItemInven.vecItemUse[i]->release();
		delete (m_ItemInven.vecItemUse[i]);
	}
	m_ItemInven.vecItemUse.clear();
}

void player::update()
{

	m_fY += GRAVITY;

	

	switch (m_PlayerState)
	{	
	case player::IDLE:
		m_aniIdle->frameUpdate(TIMEMANAGER->getElapsedTime());
		m_aniLIdle->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (m_bPlayerSee)
		{
			if(!m_aniIdle->getIsPlaying())
				m_aniIdle->start();
			m_aniLIdle->stop();
		}
		else
		{
			if (!m_aniLIdle->getIsPlaying())
			{
				m_aniLIdle->start();
			}
			m_aniIdle->stop();
		}




		if (!m_bIsGround)
		{
			m_PlayerState = FALL;
		}
		break;
	case player::ATTACK:
		break;
	case player::SKILL_READY:
		break;
	case player::MOVE:

		m_aniMove->frameUpdate(TIMEMANAGER->getElapsedTime());
		m_aniLMove->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (m_bPlayerSee)
		{
			if (!m_aniMove->getIsPlaying())
				m_aniMove->start();
			m_aniLMove->stop();

			if (m_aniMove->getNowPlayFrame()==75)
			{
				m_aniMove->setNowPlayIdx(2);
			}

		}
		else
		{
			if (!m_aniLMove->getIsPlaying())
			{
				m_aniLMove->start();
			}
			m_aniMove->stop();

			if (m_aniLMove->getNowPlayFrame() == 57)
			{
				m_aniLMove->setNowPlayIdx(2);
			}
		}


		m_PlayerState = IDLE;

		if (!m_bIsGround)
		{
			m_PlayerState = FALL;
		}

		break;
	case player::HIT:
		break;
	case player::SHEET:
		break;
	case player::SHEET_ATTACK:
		break;
	case player::SLIDE:
		break;
	case player::JUMP:
		m_aniJump->frameUpdate(TIMEMANAGER->getElapsedTime());
		m_aniLJump->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (m_bPlayerSee)
		{
			if (!m_aniJump->getIsPlaying())
				m_aniJump->start();
			m_aniLJump->stop();
		}
		else
		{
			if (!m_aniLJump->getIsPlaying())
			{
				m_aniLJump->start();
			}
			m_aniJump->stop();
		}


		if (!m_bIsGround)
		{
			m_PlayerState = IDLE;
		}


		break;
	case player::FALL:
		if (m_bIsGround)
		{
			m_PlayerState = IDLE;
		}


		break;
	case player::JUMPJUMP:
		break;
	case player::JUMPATTACK:
		break;
	case player::JUMPSATTACK:
		break;
	case player::JUMPHIT:
		break;
	default:
		break;
	}


	m_fMapX = (m_fX + ROOMMANAGER->getCurrRoom()->getPosMap().x);
	m_fMapY = (m_fY + ROOMMANAGER->getCurrRoom()->getPosMap().y);


	if (m_bIsGround)
	{
		m_nMaxJump = m_fMapY - 200;
	}
	else
	{
		if (m_PlayerState == JUMPJUMP)
			m_nMaxDoubleJump= m_fMapY - 200;
	}

	controller();

	PlayerRect();
	mapchackCollision();
	mapMove();

}

void player::render(HDC hdc)
{
	Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

	Rectangle(hdc, m_fX, m_fY, m_rc.right, m_rc.bottom);


	switch (m_PlayerState)
	{
	case player::IDLE:
		if (m_bPlayerSee)
		{
			m_pImg->aniRender(hdc, m_fX - (m_pImg->getFrameWidth() * 3) / 2, m_fY - ((m_pImg->getFrameHeight() * 3) / 2) - 10, m_aniIdle, 3);
		}
		else
		{
			m_pImg2->aniRender(hdc, m_fX - (m_pImg->getFrameWidth() * 3) / 2, m_fY - ((m_pImg2->getFrameHeight() * 3) / 2) - 10, m_aniLIdle, 3);
		}
		break;
	case player::ATTACK:
		break;
	case player::SKILL_READY:
		break;
	case player::MOVE:
		if (m_bPlayerSee)
		{
			m_pImg->aniRender(hdc, m_fX - (m_pImg->getFrameWidth() * 3) / 2, m_fY - ((m_pImg->getFrameHeight() * 3) / 2) - 10, m_aniMove, 3);
		}
		else
		{
			m_pImg2->aniRender(hdc, m_fX - (m_pImg->getFrameWidth() * 3) / 2, m_fY - ((m_pImg2->getFrameHeight() * 3) / 2) - 10, m_aniLMove, 3);
		}
		break;
	case player::HIT:
		break;
	case player::SHEET:
		break;
	case player::SHEET_ATTACK:
		break;
	case player::SLIDE:
		break;
	case player::JUMP:
		break;
	case player::FALL:
		break;
	case player::JUMPJUMP:
		break;
	case player::JUMPATTACK:
		break;
	case player::JUMPSATTACK:
		break;
	case player::JUMPHIT:
		break;
	default:
		break;
	}
	//m_pImg->frameRender(hdc, m_fX- (m_pImg->getFrameWidth() * 3) / 2, m_fY- ((m_pImg->getFrameHeight() * 3) / 2) -10, 0, 0, 3);



}


void player::mapMove()
{

	if (m_fX > (WINSIZEX / 2) - 6 && m_fX < (WINSIZEX / 2) + 6)
	{
		m_xCameraOn = true;
		m_fX = WINSIZEX / 2;
	}

	if (m_fY > (WINSIZEY / 2) + 75 - 10 && m_fY < (WINSIZEY / 2) + 75 + 10)
	{
		m_yCameraOn = true;
		m_fY = WINSIZEY / 2 + 75;
	}


	if (m_xCameraOn)
	{
		if (m_fX < WINSIZEX / 2)
		{
			ROOMMANAGER->mapMove(m_fX - WINSIZEX / 2, 0);
			m_fX = WINSIZEX / 2;
		}
		else if (m_fX > WINSIZEX / 2)
		{
			ROOMMANAGER->mapMove(m_fX - WINSIZEX / 2, 0);
			m_fX = WINSIZEX / 2;
		}
	}
	if (m_yCameraOn)
	{
		if (m_fY < WINSIZEY / 2 + 75)
		{
			ROOMMANAGER->mapMove(0, m_fY - 75 - WINSIZEY / 2);
			m_fY = WINSIZEY / 2 + 75;
		}
		else if (m_fY > WINSIZEY / 2 + 75)
		{
			ROOMMANAGER->mapMove(0, m_fY - 75 - WINSIZEY / 2);
			m_fY = WINSIZEY / 2 + 75;
		}
	}
}

void player::mapchackCollision()
{

   	int rectHarfHeight= (m_rc.bottom-m_rc.top)/2;
	int rectHarfWidth = (m_rc.right - m_rc.left) / 2;

	for (int y = 0; y <= rectHarfHeight; y++)
	{
		COLORREF color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			m_fX + ROOMMANAGER->getCurrRoom()->getPosMap().x,
			(m_fY+y) + ROOMMANAGER->getCurrRoom()->getPosMap().y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if (!(r == 0 && g == 88 && b == 24))
		{

    		m_fY = (m_fY + y) - ((m_pImg->getFrameHeight() * 3) / 4);
			PlayerRect();
			m_bIsGround = true;
			break;

		}
		else
		{
			m_bIsGround = false;
		}


		color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
		m_fX + ROOMMANAGER->getCurrRoom()->getPosMap().x,
		(m_fY - y) + ROOMMANAGER->getCurrRoom()->getPosMap().y);

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);


		if (!(r == 0 && g == 88 && b == 24))
		{

			m_fY = (m_fY - y) + ((m_pImg->getFrameHeight() * 3) / 4);
			PlayerRect();

			break;

		}


	}
	for (int x = 0; x <= rectHarfWidth; x++)
	{
		COLORREF color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			(m_fX +x) + ROOMMANAGER->getCurrRoom()->getPosMap().x,
			(m_fY) + ROOMMANAGER->getCurrRoom()->getPosMap().y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if (!(r == 0 && g == 88 && b == 24))
		{

			m_fX = (m_fX + x) - ((m_pImg->getFrameWidth() * 3) / 4);
			PlayerRect();
			break;

		}


		color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			(m_fX - x) + ROOMMANAGER->getCurrRoom()->getPosMap().x,
			(m_fY) + ROOMMANAGER->getCurrRoom()->getPosMap().y);

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);


		if (!(r == 0 && g == 88 && b == 24))
		{

			m_fX = (m_fX - x) + ((m_pImg->getFrameWidth() * 3) / 4);
			PlayerRect();

			break;

		}

	}
}

void player::mapRectCollision()
{
	for (int i = 0; i < ROOMMANAGER->getCurrRoom()->getRectNum(); i++)
	{

		RECT rc;

	


		for (int i = 0; i < ROOMMANAGER->getCurrRoom()->getRectNum(); i++)
		{
			if (ROOMMANAGER->getCurrRoom()->getRectObj()[i].top + 13 > m_rc.bottom &&
				ROOMMANAGER->getCurrRoom()->getRectObj()[i].top - 7 < m_rc.bottom
				&& (m_rc.right > ROOMMANAGER->getCurrRoom()->getRectObj()[i].left &&
					m_rc.left < ROOMMANAGER->getCurrRoom()->getRectObj()[i].right))
			{

				m_fY = (ROOMMANAGER->getCurrRoom()->getRectObj()[i].top - 50);
				m_bIsGround = true;
				


				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					m_fY +=30;
					PlayerRect();
				}
				break;
			}
			else
			{
				m_bIsGround = false;
			}

		

		}
	}
}

void player::hitCollision(int damage)
{

}

void player::DamageImg(HDC hdc, int damage)
{
	int Num = 0;
	if (damage >= 10000)
	{
		m_pCImg->frameRender(hdc, m_fX, m_fDamageY, 9, 2, 3);
		m_pCImg->frameRender(hdc, m_fX + 15, m_fDamageY, 9, 2, 3);
		m_pCImg->frameRender(hdc, m_fX + 30, m_fDamageY, 9, 2, 3);
		m_pCImg->frameRender(hdc, m_fX + 45, m_fDamageY, 9, 2, 3);
		m_pCImg->frameRender(hdc, m_fX + 60, m_fDamageY, 9, 2, 3);
	}
	else if (damage < 10000 && damage >= 1000)
	{

		Num = (damage / 1000);
		m_pCImg->frameRender(hdc, m_fX, m_fDamageY, Num, 2, 3);
		Num = (damage / 100) - ((damage / 1000) * 10);
		m_pCImg->frameRender(hdc, m_fX + 15, m_fDamageY, Num, 2, 3);
		Num = (damage / 10) - ((damage / 100) * 10);
		m_pCImg->frameRender(hdc, m_fX + 30, m_fDamageY, Num, 2, 3);
		Num = (damage % 10);
		m_pCImg->frameRender(hdc, m_fX + 45, m_fDamageY, Num, 2, 3);
	}
	else if (damage < 1000 && damage >= 100)
	{
		Num = (damage / 100);
		m_pCImg->frameRender(hdc, m_fX, m_fDamageY, Num, 2, 3);
		Num = (damage / 10) - ((damage / 100) * 10);
		m_pCImg->frameRender(hdc, m_fX + 15, m_fDamageY, Num, 2, 3);
		Num = (damage % 10);
		m_pCImg->frameRender(hdc, m_fX + 30, m_fDamageY, Num, 2, 3);
	}
	else if (damage < 100 && damage >= 10)
	{
		Num = (damage / 10) - ((damage / 100) * 10);
		m_pCImg->frameRender(hdc, m_fX, m_fDamageY, Num, 2, 3);
		Num = (damage % 10);
		m_pCImg->frameRender(hdc, m_fX + 15, m_fDamageY, Num, 2, 3);
	}
	else
	{
		Num = (damage % 10);
		m_pCImg->frameRender(hdc, m_fX, m_fDamageY, Num, 2, 3);
	}

}

Status player::changeStatus(Status status, SoulSet soulSet, ItemSet itemSet)
{
	status.curStr = status.originStr + soulSet.eS->m_nChangeStr + soulSet.gS->m_nChangeStr + soulSet.bS->m_nChangeStr + itemSet.hI->m_nChangeStr + itemSet.bI->m_nChangeStr + itemSet.aI->m_nChangeStr;
	status.curCon = status.originCon + soulSet.eS->m_nChangeCon + soulSet.gS->m_nChangeCon + soulSet.bS->m_nChangeCon + itemSet.hI->m_nChangeCon + itemSet.bI->m_nChangeCon + itemSet.aI->m_nChangeCon;
	status.curInt = status.originInt + soulSet.eS->m_nChangeInt + soulSet.gS->m_nChangeInt + soulSet.bS->m_nChangeInt + itemSet.hI->m_nChangeInt + itemSet.bI->m_nChangeInt + itemSet.aI->m_nChangeInt;
	status.curLck = status.originLck + soulSet.eS->m_nChangeLck + soulSet.gS->m_nChangeLck + soulSet.bS->m_nChangeLck + itemSet.hI->m_nChangeLck + itemSet.bI->m_nChangeLck + itemSet.aI->m_nChangeLck;

	status.originAtt = status.curStr;
	status.originDef = status.curCon / 2;

	status.curAtt = status.originAtt + soulSet.eS->m_nChangeAtt + soulSet.gS->m_nChangeAtt + soulSet.bS->m_nChangeAtt + itemSet.hI->m_nChangeAtt + itemSet.bI->m_nChangeAtt + itemSet.aI->m_nChangeAtt;
	status.curDef = status.originDef + soulSet.eS->m_nChangeDef + soulSet.gS->m_nChangeDef + soulSet.bS->m_nChangeDef + itemSet.hI->m_nChangeDef + itemSet.bI->m_nChangeDef + itemSet.aI->m_nChangeDef;

	return status;
}

void player::ShowDamage()
{

}


void player::PlayerRect()
{

	m_rc = RectMakeCenter(m_fX, m_fY, (m_pImg->getFrameWidth() * 3) / 2, (m_pImg->getFrameHeight() * 3) / 2);
	

}

void player::controller()
{
	if (m_bIsControll)
	{
		if (m_bIsGround)
		{
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				m_fX += MOVE_SPEED;
				m_PlayerState = MOVE;
				m_bPlayerSee = true;
			}
			if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				m_aniMove->stop();
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				m_fX -= MOVE_SPEED;
				m_PlayerState = MOVE;
				m_bPlayerSee = false;
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
			{
				m_aniLMove->stop();
			}


			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				m_PlayerState = JUMP;
				m_fY -= ((m_fMapY - m_nMaxJump) / 12) + GRAVITY;
			}




		}
		else
		{
			if (KEYMANAGER->isStayKeyDown('Z'))
			{
				if (m_fMapY > m_nMaxJump)
				{
					m_fY -= ((m_fMapY - m_nMaxJump) / 12)+GRAVITY;
				}
				else
				{
					m_PlayerState = FALL;
				}
			}
			if (KEYMANAGER->isOnceKeyUp('Z'))
			{
				if (m_PlayerState == JUMP || m_PlayerState == JUMPJUMP)
					m_PlayerState = FALL;
			}
		}

	}


}

void player::aniInit()
{
	m_aniIdle = new animation;
	m_aniIdle->init(855, 741, 45, 57);
	m_aniIdle->setPlayFrame(0, 4, false, true);
	m_aniIdle->setFPS(5);

	m_aniLIdle = new animation;
	m_aniLIdle->init(855, 741, 45, 57);
	m_aniLIdle->setPlayFrame(15, 19, true, true);
	m_aniLIdle->setFPS(5);

	m_aniMove = new animation;
	m_aniMove->init(855, 741, 45, 57);
	m_aniMove->setPlayFrame(57, 76, false, true);
	m_aniMove->setFPS(10);

	m_aniLMove = new animation;
	m_aniLMove->init(855, 741, 45, 57);
	m_aniLMove->setPlayFrame(57, 76, true, true);
	m_aniLMove->setFPS(10);

	m_aniJump = new animation;
	m_aniJump->init(855, 741, 45, 57);
	m_aniJump->setPlayFrame(114, 117, false, false);
	m_aniJump->setFPS(10);

	m_aniLJump = new animation;
	m_aniLJump->init(855, 741, 45, 57);
	m_aniLJump->setPlayFrame(130, 133, true, true);
	m_aniLJump->setFPS(10);

}

void player::bossRectCollision(RECT collRc, int idx)
{

}






player::player()
{
}


player::~player()
{
}
