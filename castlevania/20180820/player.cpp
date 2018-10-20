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

	// 플레이어의 동작 프레임 값
	m_nCount = 0;
	m_nRCurrFrameX = 0;
	m_nRCurrFrameY = 0;

	m_nLCurrFrameX = 18;
	m_nLCurrFrameY = 0;

	m_nNCurrFrameX = 0;
	m_nNCurrFrameY = 0;

	// 플레이어의 속성 초기화
	m_fSpeed = 6.0f; //테스팅용으로 
	m_fJumP = 20.0f;
	m_fGravity = 10.0f;
	m_fSildeP = 10.0f;
	m_fBackP = 8.0f;
	m_nSildeC = 0;
	m_nBackC = 0;
	m_nJumC = 0;
	m_nJumMC = 0;
	m_nMotionC = 0;
	m_nSkReadyC = 0;
	m_nHitC = 0;
	m_nHitDivineC = 100;
	m_nNumC = 0;
	// 플레이어의 초기 위치 값
	m_fX = 800;
	//m_fY = 2000;
	m_fY = 2000;
	m_fDamageY = m_fY - 80;

	// 플레이어가 오른쪽 보고 있는 상태로 초기화
	m_bPlayerSee = 1;
	m_bPlayerReady = 1;

	// 플레이어의 공격 모션 초기화
	m_bPlayerAttack = 0;

	// 플레이어의 점프 모션 초기화 점프는 int형식으로 주어서 2단 점프를 구현
	m_nPlayerJump = 0;
	m_bPlayerJumpDown = 0;
	m_bPlayerJumpM = 0;
	m_bPlayerJumpAttack = 0;

	// 플레이어의 앉기 모션 초기화
	m_nPlayerDown = 0;
	m_bPlayerDownAt = 0;

	// 플레이어의 백대쉬 모션 초기화
	m_bPlayerBackDash = 0;

	// 플레이어의 슬라이딩 모션 초기화
	m_bPlayerSilde = 0;

	// 플레이어의 착지 모션 초기화
	m_bPlayerStand = 0;

	// 플레이어의 스킬대기 모션 초기화
	m_bPlayerSkReady = 0;

	// 플레이어의 피격 모션 초기화
	m_bPlayerHited = 0;
	m_bDivin = 0;
	m_bDamageShow = 0;

	// 플레이어의 죽음
	m_bPlayerDie = 0;

	m_nSwordAngle = 0;

	m_status = { 10,10,12,12,11,11,9,9, 10,10,6,6,320,320,80,80,0,84 };

	m_nGold = 0;

	m_rc = RectMakeCenter(m_fX, m_fY, (m_pImg->getFrameWidth() - 20) * 3, (m_pImg->getFrameHeight() - 20) * 3);
	m_Irc = RectMakeCenter(0, 0, 0, 0);

	m_xCameraOn = false;
	m_yCameraOn = false;

	m_bIsJump = false;

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


	m_bItem = 0;

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
	PlayerDie();
	if (m_bPlayerDie != 0)
	{
		return;
	}
	// 중력 적용
	mapRectCollision();
	
	m_fY += m_fGravity;
	
	if (m_nHitDmg != 0)
	{
		m_nNumC--;
	}

	// 키입력시 플레이어의 행동

	

	// 플레이어 스킬 준비 모션
	/*if (KEYMANAGER->isStayKeyDown(VK_UP) && m_bPlayerAttack == 0 && m_nHitDmg == 0 && m_nPlayerDown == 0 && m_bPlayerDownAt == 0 && m_bPlayerJumpAttack == 0 && m_bPlayerSkReady == 0 && m_bPlayerSilde == 0)
	{
		m_bPlayerSkReady = 1;
		m_nSkReadyC++;
		if (m_bPlayerSee == 1)
		{
			m_nRCurrFrameY = 1;
			if (m_nSkReadyC < 1)
			{
				m_nRCurrFrameX = 1;
			}
		}
		else if (m_bPlayerSee == 0)
		{
			m_nLCurrFrameY = 1;
			if (m_nSkReadyC < 1)
			{
				m_nLCurrFrameX = 17;
			}
		}
	}*/


	// 플레이어 좌우 이동
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_nPlayerDown == 0 && m_bPlayerBackDash == 0 && m_bPlayerAttack == 0 && m_nHitDmg == 0 && m_bPlayerSkAttack == 0)
	{
		m_bPlayerAttack = 0;
		m_bPlayerSee = 1;
		m_bPlayerSkReady = 0;
		if (m_nPlayerJump == 0)
		{
			m_nRCurrFrameY = 3;
		}
		m_fX += m_fSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && m_nPlayerDown == 0 && m_bPlayerBackDash == 0 && m_bPlayerAttack == 0 && m_nHitDmg == 0)
	{
		m_nRCurrFrameX = 0;
		m_nRCurrFrameY = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && m_nPlayerDown == 0 && m_bPlayerBackDash == 0 && m_bPlayerAttack == 0 && m_nHitDmg == 0 && m_bPlayerSkAttack == 0)
	{
		m_bPlayerAttack = 0;
		m_bPlayerSee = 0;
		m_bPlayerSkReady = 0;
		if (m_nPlayerJump == 0)
		{
			m_nLCurrFrameY = 3;
		}
		m_fX -= m_fSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && m_nPlayerDown == 0 && m_bPlayerBackDash == 0 && m_bPlayerAttack == 0 && m_nHitDmg == 0)
	{
		m_nLCurrFrameX = 18;
		m_nLCurrFrameY = 0;
	}

	if (KEYMANAGER->isOnceKeyDownNotuch('Z'))
	{
		m_bIsJump = true;
	}



	//if (KEYMANAGER->isOnceKeyUp(VK_UP) && m_nHitDmg == 0 && m_bPlayerAttack == 0)
	//{
	//	m_bPlayerSkReady = 0;
	//	if (m_bPlayerSee == 1)
	//	{
	//		m_nRCurrFrameY = 0;
	//		m_nRCurrFrameX = 0;
	//	}
	//	else if (m_bPlayerSee == 0)
	//	{
	//		m_nLCurrFrameY = 0;
	//		m_nLCurrFrameX = 18;
	//	}

	//}

	// 플레이어 점프
	if (KEYMANAGER->isStayKeyDown('Z') && m_bPlayerAttack == 0 && m_nHitDmg == 0 && m_nPlayerDown == 0)
	{
		if (m_bIsJump)
		{
			if (m_bPlayerSee == 1)
			{
				if (m_nPlayerJump <= 2)
				{
					m_nJumMC++;
					if (m_nJumMC < 2)
					{
						if (m_bPlayerReady == 1)
						{
							m_nRCurrFrameX = 2;
						}
					}
					m_bPlayerJumpM = 1;
					if (m_bPlayerJumpAttack == 0)
					{
						if (m_bPlayerReady == 1)
						{
							m_nRCurrFrameY = 6;
						}

					}
					if (m_nPlayerJump == 0)
					{
						m_nPlayerJump = 1;
					}
					m_nJumC++;
					m_fY -= m_fJumP;

					if (m_nJumC < 30 && m_nJumC > 10)
					{
						m_fJumP = 10;
					}
					else if (m_nJumC > 30)
					{
						m_fJumP--;
						if (m_fJumP <= 0)
						{
							m_fJumP = 0;
						}
					}
				}
			}

			else if (m_bPlayerSee == 0)
			{
				if (m_nPlayerDown == 0 && m_nPlayerJump <= 2)
				{
					m_nJumMC++;
					if (m_nJumMC < 2)
					{
						if (m_bPlayerReady == 1)
						{
							m_nLCurrFrameX = 16;
						}
					}
					m_bPlayerJumpM = 1;
					if (m_bPlayerJumpAttack == 0)
					{
						if (m_bPlayerReady == 1)
						{
							m_nLCurrFrameY = 6;
						}
					}
					if (m_nPlayerJump == 0)
					{
						m_nPlayerJump = 1;
					}
					m_nJumC++;
					m_fY -= m_fJumP;

					if (m_nJumC < 30 && m_nJumC > 10)
					{
						m_fJumP = 10;
					}
					else if (m_nJumC > 30)
					{
						m_fJumP--;
						if (m_fJumP <= 0)
						{
							m_fJumP = 0;
						}
					}
				}
			}
		}

	}


	//플레이어 슬라이딩
	if (KEYMANAGER->isOnceKeyDown('Z') && m_nPlayerDown == 1 && m_nPlayerJump == 0 && m_bPlayerSilde == 0)
	{
		if (m_bIsJump)
		{
			m_bPlayerSilde = 1;
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameX = 7;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameX = 12;
			}
		}
	}

	// 점프 동작 초기화
	if (KEYMANAGER->isOnceKeyUp('Z') && m_nPlayerJump <= 3 && m_nHitDmg == 0 && m_nPlayerDown == 0)
	{
		if (m_bIsJump)
		{
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameY = 6;
				m_nRCurrFrameX = 0;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameY = 6;
				m_nLCurrFrameY = 18;
			}
			m_nPlayerJump++;
			m_bPlayerJumpDown = 1;
			m_bPlayerJumpM = 0;
			m_nJumC = 0;
			m_fJumP = 20.0f;
			m_nJumMC = 0;
		}

	}

	// 플레이어 공격
	if (KEYMANAGER->isOnceKeyDown('X') && m_bPlayerAttack == 0 && m_bPlayerSilde == 0 && m_nHitDmg == 0)
	{
		if (m_nPlayerDown == 0 && m_bPlayerStand == 1 && m_bPlayerJumpM == 0 && m_bPlayerSkReady == 0)
		{
			m_bPlayerAttack = 1;
			m_bPlayerBackDash = 0;
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameX = 0;
				m_nNCurrFrameY = 0;
				if (m_ItemSet.hI->m_nIdx == 2)
				{
					m_nRCurrFrameY = 9;
				}
				else
				{
					m_nRCurrFrameY = 1;
				}
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameX = 18;
				m_nNCurrFrameY = 1;
				if (m_ItemSet.hI->m_nIdx == 2)
				{
					m_nLCurrFrameY = 9;
				}
				else
				{
					m_nLCurrFrameY = 1;
				}
			}
		}
		else if (m_nPlayerDown == 1 && m_bPlayerAttack == 0 && m_bPlayerDownAt == 0 && m_bPlayerStand == 1)
		{
			m_bPlayerDownAt = 1;
			m_nPlayerDown = 1;
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameX = 10;
				m_nRCurrFrameY = 11;
				m_nNCurrFrameY = 0;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameX = 8;
				m_nLCurrFrameY = 11;
				m_nNCurrFrameY = 1;
			}
		}
		else if (m_nPlayerJump != 0 && m_bPlayerStand == 0 && m_bPlayerJumpAttack == 0)
		{
			m_bPlayerJumpAttack = 1;
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameY = 7;
				m_nRCurrFrameX = 4;
				m_nNCurrFrameY = 0;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameY = 7;
				m_nLCurrFrameX = 14;
				m_nNCurrFrameY = 1;
			}
		}
		else if (m_bPlayerSkReady == 1 && m_bPlayerStand == 1)
		{
			m_bPlayerSkAttack = 1;
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameX = 2;
				m_nRCurrFrameY = 1;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameX = 16;
				m_nLCurrFrameY = 1;
			}
		}
	}

	// 플레이어 앉기
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && m_bPlayerAttack == 0 && m_bPlayerJumpAttack == 0 && m_bPlayerJumpM == 0 && m_bPlayerSilde == 0)
	{
		m_nPlayerDown = 1;
		if (m_bPlayerSee == 1)
		{
			m_nRCurrFrameY = 11;
		}
		else if (m_bPlayerSee == 0)
		{
			m_nLCurrFrameY = 11;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && m_bPlayerSilde == 0 && m_bPlayerDownAt == 0 && m_bPlayerAttack == 0 && m_bPlayerJumpAttack == 0 && m_bPlayerJumpM == 0)
	{
		m_nPlayerDown = 2;
	}

	// 플레이어 백대쉬
	if (KEYMANAGER->isOnceKeyDown('A') && m_bPlayerBackDash == 0 && m_nPlayerDown == 0 && m_nPlayerJump == 0)
	{
		m_bPlayerBackDash = 1;
		m_bPlayerAttack = 0;
		m_nNCurrFrameX = 0;
		m_nSwordAngle = 0;
		m_Irc = RectMakeCenter(-10, -10, 1, 1);
		if (m_bPlayerSee == 1)
		{
			m_nRCurrFrameX = 2;
			m_nRCurrFrameY = 4;
		}
		else if (m_bPlayerSee == 0)
		{
			m_nLCurrFrameX = 17;
			m_nLCurrFrameY = 4;
		}
	}


	// 플레이어가 우측 방향을 보고 있을 떄 프레임 모션 지정
	if (m_bPlayerSee == 1)
	{
		m_nCount++;
		// 플레이어 기본자세
		if (m_nRCurrFrameY == 0 && m_bPlayerStand == 1 && m_nHitDmg == 0 && m_bPlayerJumpAttack == 0)
		{
			if (m_nCount % 20 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 3)
				{
					m_nRCurrFrameX = 0;
					m_nCount = 0;
				}
			}
		}

		// 플레이어 이동자세
		if (m_nRCurrFrameY == 3 && m_bPlayerStand == 1)
		{
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > m_pImg->getMaxFrameX())
				{
					m_nRCurrFrameX = 3;
					m_nCount = 0;
				}
			}
		}

		// 플레이어 공격자세
		else if (m_bPlayerAttack == 1 && m_bPlayerStand == 1 && m_bPlayerSkAttack == 0)
		{
			PlayerStandAttack();
		}



		// 플레이어 점프 자세
		else if (m_nRCurrFrameY == 6 && m_bPlayerJumpM == 1 && m_bPlayerStand == 0 && m_nJumC < 30 && m_nHitDmg == 0 && m_bPlayerJumpAttack == 0)
		{
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				if (m_nRCurrFrameX == 2)
				{
					m_nRCurrFrameX = 0;
				}
				m_pImg->setFrameX(m_nRCurrFrameX);
			}
		}

		else if (m_nRCurrFrameY == 7 && m_nHitDmg == 0 && m_bPlayerJumpAttack == 1 && m_bPlayerStand == 0)
		{
			PlayerJumpAttack();
		}

		// 플레이어 떨어지는 자세
		else if (m_bPlayerStand == 0 && m_bPlayerJumpM == 0 && m_nHitDmg == 0 && m_bPlayerJumpAttack == 0 || m_nJumC >= 30)
		{
			m_nRCurrFrameY = 6;
			m_nRCurrFrameX = 7;
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				if (m_nRCurrFrameX == 8)
				{
					m_nRCurrFrameX = 7;
				}
			}
		}

		// 플레이어 앉기 자세
		else if (m_nRCurrFrameY == 11 && m_nPlayerDown == 1 && m_bPlayerSilde == 0 && m_bPlayerDownAt == 0)
		{
			if (m_nCount % 10 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 3)
				{
					m_nRCurrFrameX = 3;
					m_nRCurrFrameY = 11;
					m_nCount = 0;
				}
			}
		}
		else if (m_nRCurrFrameY == 11 && m_nPlayerDown == 2)
		{
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 5)
				{
					m_nPlayerDown = 0;
					m_nCount = 0;
					m_nRCurrFrameX = 0;
					m_nRCurrFrameY = 0;
				}
			}
		}

		// 플레이어 앉아 공격 자세
		else if (m_bPlayerDownAt == 1 && m_nRCurrFrameY == 11)
		{
			PlayerDownAttack();
		}

		// 플레이어 슬라이딩 자세
		else if (m_nRCurrFrameY == 11 && m_bPlayerSilde == 1 && m_nPlayerDown == 1)
		{
			if (m_nSildeC > 5)
			{
				m_nRCurrFrameX++;
				m_nSildeC = 0;
			}
			else
			{
				m_nSildeC++;
			}

			if (m_nRCurrFrameX <= 9)
			{
				m_fX += m_fSildeP;
			}

			if (m_nCount % 10 == 0)
			{
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 9)
				{
					m_nPlayerDown = 2;
					//m_nPlayerJump = 1;
					m_bPlayerSilde = 0;
					m_nRCurrFrameX = 9;
					m_nRCurrFrameY = 11;
					m_fSildeP = 10.0f;
					m_nSildeC = 0;
				}
			}
		}

		// 플레이어 백대쉬 자세
		else if (m_nRCurrFrameY == 4 && m_bPlayerBackDash == 1)
		{
			m_fX -= m_fBackP;
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 4)
				{
					m_bPlayerBackDash = 0;
					m_nRCurrFrameX = 0;
					m_nRCurrFrameY = 0;
				}
			}
		}
		// 플레이어 스킬모션 대기 자세
	/*	else if (m_bPlayerSkReady == 1 && m_nRCurrFrameY != 3 && m_bPlayerSkAttack == 0)
		{
			if (m_nCount % 5 == 0)
			{
				if (m_nRCurrFrameX < 3)
				{
					m_nRCurrFrameX++;
					m_pImg->setFrameX(m_nRCurrFrameX);
				}
			}
		}

		else if (m_bPlayerSkAttack == 1 && m_nRCurrFrameY == 1)
		{
			if (m_nCount % 4 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > m_pImg->getMaxFrameX() - 7)
				{
					m_nRCurrFrameX = 0;
					m_bPlayerSkAttack = 0;
					m_nRCurrFrameY = 0;
					m_nNCurrFrameX = 0;
					m_nCount = 0;
				}
			}
		}*/
	}


	// 플레이어가 좌측 방향을 보고 있을 떄 프레임 모션 지정
	else if (m_bPlayerSee == 0)
	{
		m_nCount++;

		// 플레이어 왼쪽 기본자세
		if (m_nLCurrFrameY == 0 && m_bPlayerStand == 1 && m_nHitDmg == 0 && m_bPlayerJumpAttack == 0)
		{
			if (m_nCount % 20 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 15)
				{
					m_nLCurrFrameX = 18;
				}
			}
		}

		// 플레이어 왼쪽 이동자세
		else if (m_nLCurrFrameY == 3 && m_bPlayerStand == 1)
		{
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 0)
				{
					m_nLCurrFrameX = 14;
				}
			}
		}

		// 플레이어 왼쪽 공격자세
		else if (m_bPlayerAttack == 1 && m_bPlayerStand == 1)
		{
			PlayerStandAttack();
		}

		// 플레이어 점프자세

		else if (m_nLCurrFrameY == 6 && m_bPlayerJumpM == 1 && m_bPlayerStand == 0 && m_nJumC < 30 && m_nHitDmg == 0 && m_bPlayerJumpAttack == 0)
		{
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				if (m_nRCurrFrameX == 16)
				{
					m_nLCurrFrameX = 17;
				}
				m_pImg2->setFrameX(m_nLCurrFrameX);
			}
		}
		else if (m_nLCurrFrameY == 7 && m_nHitDmg == 0 && m_bPlayerJumpAttack == 1 && m_bPlayerStand == 0)
		{
			PlayerJumpAttack();
		}


		// 플레이어 떨어지는 자세
		else if (m_bPlayerStand == 0 && m_bPlayerJumpM == 0 && m_nHitDmg == 0 && m_bPlayerJumpAttack != 1 || m_nJumC >= 30)
		{
			m_nLCurrFrameY = 6;
			m_nLCurrFrameX = 11;
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				if (m_nLCurrFrameX == 10)
				{
					m_nLCurrFrameX = 11;
				}
			}
		}

		// 플레이어 왼쪽 앉기 자세
		else if (m_nLCurrFrameY == 11 && m_nPlayerDown == 1 && m_bPlayerSilde == 0 && m_bPlayerDownAt == 0)
		{
			if (m_nCount % 10 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 15)
				{
					m_nLCurrFrameX = 15;
					m_nLCurrFrameY = 11;
					m_nCount = 0;
				}
			}
		}

		else if (m_nLCurrFrameY == 11 && m_nPlayerDown == 2)
		{
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 13)
				{
					m_nLCurrFrameX = 18;
					m_nLCurrFrameY = 0;
					m_nPlayerDown = 0;
					m_nCount = 0;
				}
			}
		}


		// 플레이어 앉아 공격 자세
		else if (m_bPlayerDownAt == 1 && m_nLCurrFrameY == 11)
		{
			PlayerDownAttack();
		}

		// 플레이어 슬라이딩 자세
		else if (m_nLCurrFrameY == 11 && m_bPlayerSilde == 1 && m_nPlayerDown == 1)
		{
			if (m_nSildeC > 5)
			{
				m_nLCurrFrameX--;
				m_nSildeC = 0;
			}
			else
			{
				m_nSildeC++;
			}
			if (m_nLCurrFrameX > 9)
			{
				m_fX -= m_fSildeP;
			}
			if (m_nCount % 10 == 0)
			{
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 9)
				{
					m_nLCurrFrameX = 9;
					m_nLCurrFrameY = 11;
					m_nPlayerDown = 2;
					m_bPlayerSilde = 0;
					m_fSildeP = 10.0f;
					m_nSildeC = 0;
				}
			}
		}

		// 플레이어 백대쉬 자세
		else if (m_nLCurrFrameY == 4 && m_bPlayerBackDash == 1)
		{
			m_fX += m_fBackP;
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 14)
				{
					m_bPlayerBackDash = 0;
					m_nLCurrFrameX = 18;
					m_nLCurrFrameY = 0;
				}
			}
		}
		// 플레이어 스킬 대기 자세
		/*else if (m_bPlayerSkReady == 1 && m_nLCurrFrameY != 3 && m_bPlayerSkAttack == 0)
		{
			if (m_nCount % 5 == 0)
			{
				if (m_nLCurrFrameX > 15)
				{
					m_nLCurrFrameX--;
					m_pImg2->setFrameX(m_nLCurrFrameX);
				}
			}
		}
		else if (m_bPlayerSkAttack == 1 && m_nLCurrFrameY == 1)
		{
			if (m_nCount % 4 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 7)
				{
					m_nLCurrFrameX = 18;
					m_bPlayerSkAttack = 0;
					m_nLCurrFrameY = 0;
					m_nNCurrFrameX = 0;
					m_nCount = 0;
				}
			}
		}*/
	}

	mapchackCollision();
	mapMove();
	hitMosion();
	ShowDamage();
	FallDown();
	PlayerRect();

	


}

void player::render(HDC hdc)
{
	if (m_pImg)
	{
		//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		// 플레이어가 오른쪽을 보고 있을때 이미지 랜더
		if (m_bPlayerSee == 1)
		{
			m_pImg->frameRender(hdc, m_fX - (m_pImg->getFrameWidth() * 3) / 2, m_fY - (m_pImg->getFrameHeight() * 3) / 2 - 10, m_nRCurrFrameX, m_nRCurrFrameY, 3);
			if (m_bItem)
			{
				if (m_ItemSet.hI->m_nIdx == 1)
				{
					if (m_bPlayerAttack)
					{
						m_pImg3->frameRender(hdc, m_fX - 30, m_fY - 70, m_nNCurrFrameX, m_nNCurrFrameY, 3);
					}
					else if (m_bPlayerDownAt)
					{
						m_pImg3->frameRender(hdc, m_fX - 30, m_fY - 35, m_nNCurrFrameX, m_nNCurrFrameY, 3);
					}
					else if (m_bPlayerJumpAttack)
					{
						m_pImg3->frameRender(hdc, m_fX - 30, m_fY - 65, m_nNCurrFrameX, m_nNCurrFrameY, 3);
					}
				}
				else if (m_ItemSet.hI->m_nIdx == 2)
				{
					if (m_bPlayerAttack)
					{
						m_pImg4->rotateRender(hdc, m_nSwordAngle, m_fX - 90, m_fY - 145, 0.5, 1, 3);
					}
					else if (m_bPlayerDownAt)
					{
						m_pImg4->rotateRender(hdc, m_nSwordAngle, m_fX - 95, m_fY - 110, 0.5, 1, 3);
					}
					else if (m_bPlayerJumpAttack)
					{
						m_pImg4->rotateRender(hdc, m_nSwordAngle, m_fX - 70, m_fY - 150, 0.5, 1, 3);
					}
				}
			}
		}

		// 플레이어가 왼쪽을 보고 있을때 이미지 랜더
		else if (m_bPlayerSee == 0)
		{
			m_pImg2->frameRender(hdc, m_fX - (m_pImg->getFrameWidth() * 3) / 2, m_fY - (m_pImg->getFrameHeight() * 3) / 2 - 10, m_nLCurrFrameX, m_nLCurrFrameY, 3);

			if (m_bItem)
			{
				if (m_ItemSet.hI->m_nIdx == 1)
				{
					if (m_bPlayerAttack)
					{
						m_pImg3->frameRender(hdc, m_fX - 200, m_fY - 70, m_nNCurrFrameX, m_nNCurrFrameY, 3);
					}
					else if (m_bPlayerDownAt)
					{
						m_pImg3->frameRender(hdc, m_fX - 200, m_fY - 35, m_nNCurrFrameX, m_nNCurrFrameY, 3);
					}
					else if (m_bPlayerJumpAttack)
					{
						m_pImg3->frameRender(hdc, m_fX - 200, m_fY - 65, m_nNCurrFrameX, m_nNCurrFrameY, 3);
					}
				}
				else if (m_ItemSet.hI->m_nIdx == 2)
				{
					if (m_bPlayerAttack)
					{
						m_pImg4->rotateRender(hdc, m_nSwordAngle, m_fX - 130, m_fY - 145, 0.5, 1, 3);
					}
					else if (m_bPlayerDownAt)
					{
						m_pImg4->rotateRender(hdc, m_nSwordAngle, m_fX - 128, m_fY - 110, 0.5, 1, 3);
					}
					else if (m_bPlayerJumpAttack)
					{
						m_pImg4->rotateRender(hdc, m_nSwordAngle, m_fX - 150, m_fY - 150, 0.5, 1, 3);
					}
				}
			}
		}
	}

	if (m_nHitDmg != 0)
	{
		DamageImg(hdc, m_nHitDmg);
	}


	//Rectangle(hdc, m_Irc.left, m_Irc.top, m_Irc.right, m_Irc.bottom);
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
	for (int y = m_rc.top; y <= m_rc.bottom; y++)
	{
		COLORREF color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			m_fX + ROOMMANAGER->getCurrRoom()->getPosMap().x,
			y + ROOMMANAGER->getCurrRoom()->getPosMap().y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if (!(r == 0 && g == 88 && b == 24))
		{
			if (y > m_fY)
			{
				m_fY--;
			}
			else if ((y < m_fY))
			{
				m_fY++;
			}
		}
		else
		{
			m_bPlayerStand = 0;
		}

		if (y == m_rc.bottom)
		{
			y++;

			color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
				m_fX + ROOMMANAGER->getCurrRoom()->getPosMap().x,
				y + ROOMMANAGER->getCurrRoom()->getPosMap().y);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (!(r == 0 && g == 88 && b == 24))
			{

				m_fY -= m_fGravity;
				m_bPlayerReady = false;

			}
			else
			{
				m_bPlayerReady = true;
			}

			color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
				m_fX + ROOMMANAGER->getCurrRoom()->getPosMap().x,
				m_rc.bottom + 30 + ROOMMANAGER->getCurrRoom()->getPosMap().y);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (!(r == 0 && g == 88 && b == 24))
			{
				m_bPlayerStand = 1;
				m_nPlayerJump = 0;
				m_bPlayerJumpM = 0;
				m_nJumC = 0;

				if (m_bPlayerJumpAttack != 0)
				{
					m_bPlayerJumpAttack = 0;
					m_nRCurrFrameY = 0;
					m_nRCurrFrameX = 0;
					m_nLCurrFrameY = 0;
					m_nLCurrFrameX = 18;
					m_nNCurrFrameX = 0;
					m_bItem = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
				}
				if (m_nRCurrFrameY == 6)
				{
					m_nRCurrFrameY = 0;
					m_nRCurrFrameX = 0;
				}
				else if (m_nLCurrFrameY == 6)
				{
					m_nLCurrFrameY = 0;
					m_nLCurrFrameX = 18;
				}
			}
		}
	}

	for (int x = m_rc.left; x < m_rc.right; x++)
	{
		COLORREF color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			x + ROOMMANAGER->getCurrRoom()->getPosMap().x,
			m_fY + ROOMMANAGER->getCurrRoom()->getPosMap().y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if (!(r == 0 && g == 88 && b == 24))
		{
			if (x > m_fX)
			{
				m_fX--;
			}
			else if ((x < m_fX))
			{
				m_fX++;
			}
		}
	}
}

void player::mapRectCollision()
{
	for (int i = 0; i < ROOMMANAGER->getCurrRoom()->getRectNum(); i++)
	{

		RECT rc;

		if (IntersectRect(&rc, &m_rc, &(ROOMMANAGER->getCurrRoom()->getRectObj()[i])))
		{
			m_bPlayerStand = 1;
			m_nPlayerJump = 0;

			if (m_bPlayerJumpAttack != 0)
			{
				m_bPlayerJumpAttack = 0;
				m_nRCurrFrameY = 0;
				m_nRCurrFrameX = 0;
				m_nLCurrFrameY = 0;
				m_nLCurrFrameX = 18;
				m_nNCurrFrameX = 0;
				m_bItem = 0;
				m_Irc = RectMakeCenter(-10, -10, 1, 1);
			}
			if (m_nRCurrFrameY == 6)
			{
				m_nRCurrFrameY = 0;
				m_nRCurrFrameX = 0;
			}
			else if (m_nLCurrFrameY == 6)
			{
				m_nLCurrFrameY = 0;
				m_nLCurrFrameX = 18;
			}
		}


		for (int i = 0; i < ROOMMANAGER->getCurrRoom()->getRectNum(); i++)
		{
			if (ROOMMANAGER->getCurrRoom()->getRectObj()[i].top + 13 > m_rc.bottom &&
				ROOMMANAGER->getCurrRoom()->getRectObj()[i].top - 7 < m_rc.bottom
				&& (m_rc.right > ROOMMANAGER->getCurrRoom()->getRectObj()[i].left &&
					m_rc.left < ROOMMANAGER->getCurrRoom()->getRectObj()[i].right))
			{

				m_fY = (ROOMMANAGER->getCurrRoom()->getRectObj()[i].top - 50);


				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					m_fY +=30;
					PlayerRect();
				}

			}

		

		}
	}
}

void player::hitCollision(int damage)
{
	if (m_bDivin == 0)
	{
		m_bPlayerAttack = 0;
		m_bPlayerDownAt = 0;
		m_bPlayerSilde = 0;
		m_nPlayerDown = 0;
		m_bPlayerJumpAttack = 0;
		m_nNCurrFrameX = 0;
	/*	if (m_bPlayerStand == 0)
		{
			m_bPlayerHited = 1;
			m_bDivin = 1;
			if (m_nHitDivineC == 100)
			{
				m_status.curHP -= damage;

			}
		}*/
	
			m_bPlayerHited = 1;
			m_bDivin = 1;
			if (m_nHitDivineC == 100)
			{
				m_status.curHP -= damage;

			}
		
	}
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
	if (m_nHitDmg != 0)
	{
		m_bDamageShow = 1;
	}
	else
	{
		m_fDamageY = m_fY - 80;
	}

	if (m_bDamageShow == 1)
	{
		m_nNumC++;
		m_fDamageY--;
		if (m_nNumC >= 20)
		{
			m_nNumC = 0;
			m_bDamageShow = 0;
			m_fDamageY = m_fY - 80;
		}
	}
}

void player::FallDown()
{
}

void player::PlayerRect()
{
	if (m_nPlayerDown == 0)
	{
		m_rc = RectMakeCenter(m_fX, m_fY, (m_pImg->getFrameWidth() * 3) / 2, (m_pImg->getFrameHeight() * 3) / 2);
	}
	else if (m_nPlayerDown == 1)
	{
		m_rc = RectMakeCenter(m_fX, m_fY + 15, (m_pImg->getFrameWidth() * 3) / 2, ((m_pImg->getFrameHeight() * 3) / 2 - 30));
	}
}

void player::PlayerStandAttack()
{
	if (m_bPlayerSee == 1)
	{
		if (m_ItemSet.hI->m_nIdx == 0)
		{
			if (m_nCount % 4 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > m_pImg->getMaxFrameX() - 7)
				{
					m_nRCurrFrameX = 0;
					m_bPlayerAttack = 0;
					m_nRCurrFrameY = 0;
					m_nCount = 0;
				}
			}
		}
		else if (m_ItemSet.hI->m_nIdx == 1)
		{
			if (m_nCount % 4 == 0)
			{
				m_nRCurrFrameX++;
				if (m_nRCurrFrameX > 2)
				{
					m_bItem = 1;
					m_nNCurrFrameX++;


					if (m_nNCurrFrameX > 0 && m_nNCurrFrameX < 5)
					{
						m_Irc = RectMakeCenter(m_fX + 120, m_fY - 40, m_pImg3->getFrameWidth() * 2, m_pImg3->getFrameHeight() * 2);
					}
				}
				m_pImg->setFrameX(m_nRCurrFrameX);
				m_pImg3->setFrameX(m_nNCurrFrameX);
				if (m_nRCurrFrameX > m_pImg->getMaxFrameX() - 7)
				{
					m_nRCurrFrameX = 0;
					m_bPlayerAttack = 0;
					m_nRCurrFrameY = 0;
					m_nNCurrFrameX = 0;
					m_bItem = 0;
					m_nCount = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
				}
			}
		}
		else if (m_ItemSet.hI->m_nIdx == 2)
		{
			if (m_nSwordAngle <= 130)
			{
				m_Irc = RectMakeCenter(m_fX + 90, m_fY - 40, 145, 200);
				m_bItem = 1;
				m_nSwordAngle+=10;
			}
			else if (m_nSwordAngle >= 130)
			{
				if (m_nCount % 4 == 0)
				{
					m_nRCurrFrameX++;
					m_bItem = 0;
					m_pImg->setFrameX(m_nRCurrFrameX);
					if (m_nRCurrFrameX > 2)
					{
						m_nSwordAngle = 0;
						m_nRCurrFrameX = 0;
						m_bPlayerAttack = 0;
						m_nRCurrFrameY = 0;
						m_nCount = 0;
						m_Irc = RectMakeCenter(-10, -10, 1, 1);
					}
				}
			}
		}
	}
	else if (m_bPlayerSee == 0)
	{
		if (m_ItemSet.hI->m_nIdx == 0)
		{
			if (m_nCount % 4 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 7)
				{
					m_nLCurrFrameX = 18;
					m_bPlayerAttack = 0;
					m_nLCurrFrameY = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
				}
			}
		}
		else if (m_ItemSet.hI->m_nIdx == 1)
		{
			if (m_nCount % 4 == 0)
			{
				if (m_nCount % 4 == 0)
				{
					if (m_nLCurrFrameX < 17)
					{
						m_bItem = 1;
						m_nNCurrFrameX++;
						if (m_nNCurrFrameX > 0 && m_nNCurrFrameX < 5)
						{
							m_Irc = RectMakeCenter(m_fX - 110, m_fY - 40, m_pImg3->getFrameWidth() * 2, m_pImg3->getFrameHeight() * 2);
						}
					}
					m_nLCurrFrameX--;
					m_pImg3->setFrameX(m_nRCurrFrameX);
					m_pImg2->setFrameX(m_nLCurrFrameX);
					if (m_nLCurrFrameX < 7)
					{
						m_nLCurrFrameX = 18;
						m_bPlayerAttack = 0;
						m_nLCurrFrameY = 0;
						m_nNCurrFrameX = 0;
						m_Irc = RectMakeCenter(-10, -10, 1, 1);
					}
				}
			}
		}
		else if (m_ItemSet.hI->m_nIdx == 2)
		{
			if (m_nSwordAngle >= -130)
			{
				m_bItem = 1;
				m_nSwordAngle -= 10;
				m_Irc = RectMakeCenter(m_fX - 90, m_fY - 40, 145, 200);
			}
			else if (m_nSwordAngle <= -130)
			{
				if (m_nCount % 4 == 0)
				{
					m_nLCurrFrameX--;
					m_bItem = 0;
					m_pImg2->setFrameX(m_nLCurrFrameX);
					if (m_nLCurrFrameX < 15)
					{
						m_nSwordAngle = 0;
						m_nLCurrFrameX = 18;
						m_bPlayerAttack = 0;
						m_nLCurrFrameY = 0;
						m_nCount = 0;
						m_Irc = RectMakeCenter(-10, -10, 1, 1);
					}
				}
			}
		}
	}
}

void player::PlayerDownAttack()
{
	if (m_bPlayerSee == 1)
	{
		if (m_ItemSet.hI->m_nIdx == 0)
		{
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 14)
				{
					m_nCount = 0;
					m_nRCurrFrameX = 10;
					m_bPlayerDownAt = 0;
					m_nPlayerDown = 2;
					m_nMotionC = 0;
					m_bItem = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
				}
			}
		}
		else if (m_ItemSet.hI->m_nIdx == 1)
		{
			if (m_nCount % 5 == 0)
			{
				m_nMotionC++;
				if (m_nMotionC < 3 || m_nMotionC > 5)
				{
					m_nRCurrFrameX++;
				}

				if (m_nRCurrFrameX < 14)
				{
					m_bItem = 1;
					m_nNCurrFrameX++;
					if (m_nNCurrFrameX > 3 && m_nNCurrFrameX < 5)
					{
						m_Irc = RectMakeCenter(m_fX + 120, m_fY - 10, m_pImg3->getFrameWidth() * 2, m_pImg3->getFrameHeight() * 2);
					}
				}

				m_pImg->setFrameX(m_nRCurrFrameX);
				m_pImg3->setFrameX(m_nNCurrFrameX);
				if (m_nRCurrFrameX > 14)
				{
					m_nCount = 0;
					m_nRCurrFrameX = 10;
					m_nNCurrFrameX = 0;
					m_bPlayerDownAt = 0;
					m_nPlayerDown = 2;
					m_nMotionC = 0;
					m_bItem = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
				}
			}
		}
		else if (m_ItemSet.hI->m_nIdx == 2)
		{
			if (m_nSwordAngle <= 130)
			{
				m_Irc = RectMakeCenter(m_fX + 90, m_fY - 40, 145, 200);
				m_bItem = 1;
				m_nSwordAngle += 10;
			}
			else if (m_nSwordAngle >= 130)
			{
				if (m_nCount % 4 == 0)
				{
					m_nRCurrFrameX++;
					m_bItem = 0;
					m_pImg->setFrameX(m_nRCurrFrameX);
					if (m_nRCurrFrameX > 2)
					{
						m_nSwordAngle = 0;
						m_nRCurrFrameX = 10;
						m_bPlayerDownAt = 0;
						m_nPlayerDown = 2;
						m_nCount = 0;
						m_Irc = RectMakeCenter(-10, -10, 1, 1);
					}
				}
			}
		}
	}
	else if(m_bPlayerSee == 0)
	{
		if (m_ItemSet.hI->m_nIdx == 0)
		{
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 4)
				{
					m_nCount = 0;
					m_nLCurrFrameX = 8;
					m_bPlayerDownAt = 0;
					m_nPlayerDown = 2;
				}
			}
		}
		else if (m_ItemSet.hI->m_nIdx == 1)
		{
			if (m_nCount % 5 == 0)
			{
				m_nMotionC++;
				if (m_nMotionC < 3 || m_nMotionC > 5)
				{
					m_nLCurrFrameX--;
				}

				if (m_nLCurrFrameX > 4)
				{
					m_bItem = 1;
					m_nNCurrFrameX++;
					if (m_nNCurrFrameX > 3 && m_nNCurrFrameX < 5)
					{
						m_Irc = RectMakeCenter(m_fX - 110, m_fY - 10, m_pImg3->getFrameWidth() * 2, m_pImg3->getFrameHeight() * 2);
					}
				}
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 4)
				{
					m_nCount = 0;
					m_nLCurrFrameX = 8;
					m_nNCurrFrameX = 0;
					m_bPlayerDownAt = 0;
					m_nPlayerDown = 2;
					m_nMotionC = 0;
					m_bItem = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
				}
			}
		}
		else if (m_ItemSet.hI->m_nIdx == 2)
		{
			if (m_nSwordAngle >= -130)
			{
				m_bItem = 1;
				m_nSwordAngle -= 10;
				m_Irc = RectMakeCenter(m_fX - 90, m_fY - 40, 145, 200);
			}
			else if (m_nSwordAngle <= -130)
			{
				if (m_nCount % 4 == 0)
				{
					m_nLCurrFrameX--;
					m_bItem = 0;
					m_pImg2->setFrameX(m_nLCurrFrameX);
					if (m_nLCurrFrameX < 15)
					{
						m_nSwordAngle = 0;
						m_nLCurrFrameX = 8;
						m_bPlayerDownAt = 0;
						m_nPlayerDown = 2;
						m_nCount = 0;
						m_Irc = RectMakeCenter(-10, -10, 1, 1);
					}
				}
			}
		}
	}
}

void player::PlayerJumpAttack()
{
	if (m_bPlayerSee == 1)
	{
		if (m_ItemSet.hI->m_nIdx == 0)
		{
			if (m_nCount % 6 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 8)
				{
					m_bPlayerJumpAttack = 0;
					m_nRCurrFrameX = 0;
					m_nCount = 0;
					//m_nRCurrFrameY = 6;
				}
			}
		}
		else if (m_ItemSet.hI->m_nIdx == 1)
		{
			if (m_nCount % 2 == 0)
			{
				if (m_nRCurrFrameX > 5)
				{
					m_bItem = 1;
					m_nNCurrFrameX++;
					if (m_nNCurrFrameX > 0 && m_nNCurrFrameX < 5)
					{
						m_Irc = RectMakeCenter(m_fX + 120, m_fY - 40, m_pImg3->getFrameWidth() * 2, m_pImg3->getFrameHeight() * 2);
					}
				}
			}
			if (m_nCount % 6 == 0)
			{
				m_nRCurrFrameX++;

				m_pImg->setFrameX(m_nRCurrFrameX);
				m_pImg3->setFrameX(m_nNCurrFrameX);
				if (m_nRCurrFrameX > 8)
				{
					m_bPlayerJumpAttack = 0;
					m_nRCurrFrameX = 0;
					m_nNCurrFrameX = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
					m_nCount = 0;
					m_bItem = 0;
					m_nRCurrFrameY = 6;
				}
			}
		}
		else if (m_ItemSet.hI->m_nIdx == 2)
		{
			if (m_nSwordAngle <= 130)
			{
				m_Irc = RectMakeCenter(m_fX + 90, m_fY - 40, 145, 200);
				m_bItem = 1;
				m_nSwordAngle += 10;
			}
			else if (m_nSwordAngle >= 130)
			{
				if (m_nCount % 4 == 0)
				{
					m_nRCurrFrameX++;
					m_bItem = 0;
					m_pImg->setFrameX(m_nRCurrFrameX);
					if (m_nRCurrFrameX > 2)
					{
						m_nSwordAngle = 0;
						m_nRCurrFrameX = 10;
						m_bPlayerJumpAttack = 0;
						m_nCount = 0;
						m_Irc = RectMakeCenter(-10, -10, 1, 1);
					}
				}
			}
		}
	}
	else if (m_bPlayerSee == 0)
	{
		if (m_ItemSet.hI->m_nIdx == 0)
		{
			if (m_nCount % 6 == 0)
			{
				m_nLCurrFrameX--;

				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 11)
				{
					m_bPlayerJumpAttack = 0;
					m_nLCurrFrameX = 18;
					m_nCount = 0;
				}
			}
		}
		else if (m_ItemSet.hI->m_nIdx == 1)
		{
			if (m_nCount % 2 == 0)
			{
				if (m_nLCurrFrameX < 13)
				{
					m_bItem = 1;
					m_nNCurrFrameX++;
					if (m_nNCurrFrameX > 0 && m_nNCurrFrameX < 5)
					{
						m_Irc = RectMakeCenter(m_fX - 120, m_fY - 40, m_pImg3->getFrameWidth() * 2, m_pImg3->getFrameHeight() * 2);
					}
				}
			}
			if (m_nCount % 6 == 0)
			{
				m_nLCurrFrameX--;

				m_pImg2->setFrameX(m_nLCurrFrameX);
				m_pImg3->setFrameX(m_nNCurrFrameX);
				if (m_nLCurrFrameX < 11)
				{
					m_bPlayerJumpAttack = 0;
					m_nLCurrFrameX = 18;
					m_nNCurrFrameX = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
					m_nCount = 0;
					m_bItem = 0;
					//m_nRCurrFrameY = 6;
				}
			}
		}
		else if (m_ItemSet.hI->m_nIdx == 2)
		{
			if (m_nSwordAngle >= -130)
			{
				m_bItem = 1;
				m_nSwordAngle -= 10;
				m_Irc = RectMakeCenter(m_fX - 90, m_fY - 40, 145, 200);
			}
			else if (m_nSwordAngle <= -130)
			{
				if (m_nCount % 4 == 0)
				{
					m_nLCurrFrameX--;
					m_bItem = 0;
					m_pImg2->setFrameX(m_nLCurrFrameX);
					if (m_nLCurrFrameX < 15)
					{
						m_nSwordAngle = 0;
						m_nLCurrFrameX = 8;
						m_bPlayerJumpAttack = 0;
						m_nCount = 0;
						m_Irc = RectMakeCenter(-10, -10, 1, 1);
					}
				}
			}
		}
	}
}

void player::PlayerDie()
{
	if (m_status.curHP <= 0 && m_bPlayerDie == 0)
	{
		m_status.curHP = 0;
		m_bPlayerDie = 1;
		if (m_bPlayerSee == 1)
		{
			m_nRCurrFrameY = 5;
			m_nRCurrFrameX = 2;
		}
		else if (m_bPlayerSee == 0)
		{
			m_nLCurrFrameY = 5;
			m_nLCurrFrameX = 16;
		}
		
	}

	if (m_bPlayerDie == 1)
	{
		m_nCount++;
		if (m_nCount % 20 == 0)
		{
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameX++;
				if (m_nRCurrFrameX >= 6)
				{
					m_nRCurrFrameX = 6;
					m_nCount = 0;
				}
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameX--;
				if (m_nLCurrFrameX <= 12)
				{
					m_nLCurrFrameX = 12;
					m_nCount = 0;
				}
			}
		}
	}
}

void player::bossRectCollision(RECT collRc,int idx)
{



	RECT rc;

	if (IntersectRect(&rc, &m_rc, &collRc))
	{
		m_bPlayerStand = 1;
		m_nPlayerJump = 0;

		if (m_bPlayerJumpAttack != 0)
		{
			m_bPlayerJumpAttack = 0;
			m_nRCurrFrameY = 0;
			m_nRCurrFrameX = 0;
			m_nLCurrFrameY = 0;
			m_nLCurrFrameX = 18;
			m_nNCurrFrameX = 0;
			m_bItem = 0;
			m_Irc = RectMakeCenter(-10, -10, 1, 1);
		}
		if (m_nRCurrFrameY == 6)
		{
			m_nRCurrFrameY = 0;
			m_nRCurrFrameX = 0;
		}
		else if (m_nLCurrFrameY == 6)
		{
			m_nLCurrFrameY = 0;
			m_nLCurrFrameX = 18;
		}

		if (idx == 0)
		{
			m_bIsLide = true;

		}
		else
		{
			m_bIsRide = true;
		}
	}
	else
	{
		if (idx == 0)
		{
			m_bIsLide = false;

		}
		else
		{
			m_bIsRide = false;
		}
	}


		if (collRc.top + 13 > m_rc.bottom &&
			collRc.top - 7 < m_rc.bottom
			&& (m_rc.right > collRc.left &&
				m_rc.left < collRc.right))
		{

			m_fY = (collRc.top - 50);




		}



	
	
}



void player::hitMosion()
{
	if (m_bDivin == 1)
	{
		m_nHitDivineC--;
		if (m_nHitDivineC <= 0)
		{
			m_bDivin = 0;
			m_nHitDivineC = 100;
		}
	}
		
	if (m_nHitDmg != 0)
	{
		m_nHitC++;
	/*	if (m_bPlayerStand == 0)
		{
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameY = 5;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameY = 5;
			}
		}*/
	
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameY = 5;
				m_nRCurrFrameX = 0;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameY = 5;
				m_nLCurrFrameX = 18;
			}


		if (m_nHitC < 10 )
		{
			if (m_bPlayerSee == 1)
			{
				m_fX -= 7.0f;
			}
			else if (m_bPlayerSee == 0)
			{
				m_fX += 7.0f;
			}
		}
		else if (m_nHitC >= 10)
		{
			m_nHitC = 0;
			m_nHitDmg = 0;
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameY = 0;
				m_nRCurrFrameX = 0;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameY = 0;
				m_nLCurrFrameX = 18;
			}
		}
	}
}





player::player()
{
}


player::~player()
{
}
