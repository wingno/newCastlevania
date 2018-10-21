#pragma once

#define GRAVITY 12
#define MOVE_SPEED 8

class bulletSoul;
class guardianSoul;
class enchantSoul;
class handItem;
class bodyItem;
class accessoryItem;
class ItemUse;

class ItemUse;

class player
{
private:
	enum PlayerState
	{
		IDLE,
		ATTACK,
		SKILL_READY,
		MOVE,
		HIT,
		SHEET,
		SHEET_ATTACK,
		SLIDE,
		JUMP,
		FALL,
		JUMPJUMP,
		JUMPATTACK,
		JUMPSATTACK,
		JUMPHIT

	};

	struct itemInven
	{
		std::vector<handItem*>	vecHandItem;
		std::vector<handItem*>::iterator	hiter;

		std::vector<bodyItem*>	vecBodyItem;
		std::vector<bodyItem*>::iterator	biter;

		std::vector<accessoryItem*>	vecAccessoryItem;
		std::vector<accessoryItem*>::iterator	aiter;

		std::vector<ItemUse*>	vecItemUse;
		std::vector<ItemUse*>::iterator	iiter;
	};



	struct soulInven
	{
		std::vector<bulletSoul*>	vecBulletSoul;
		std::vector<bulletSoul*>::iterator	biter;

		std::vector<guardianSoul*>	vecGuardianSoul;
		std::vector<guardianSoul*>::iterator	giter;

		std::vector<enchantSoul*>	vecEnchantSoul;
		std::vector<enchantSoul*>::iterator	eiter;
	};

	
	// 플레이어 이미지
	image *	 m_pImg;
	image *	 m_pImg2;
	image *	 m_pImg3;
	image *	 m_pImg4;
	image *  m_pCImg;


	animation* m_aniIdle;
	animation* m_aniLIdle;

	animation*	m_aniMove;
	animation*	m_aniLMove;

	
	// 플레이어 렉트
	SYNTHESIZE (RECT, m_rc, Rc);
	SYNTHESIZE(RECT, m_Irc, IRC);
	
	// 플레이어 속성 값

	SYNTHESIZE(Status ,m_status,State);
	SYNTHESIZE(int, m_nGold, Gold);

	SYNTHESIZE(int, m_nHitDmg, HitDmg);



	SYNTHESIZE( int,m_nHitDivineC, HitDivineC);




	SYNTHESIZE( float, m_fX,Fx);
	SYNTHESIZE(float, m_fY,FY);



	// 플레이어 프레임설정 속성




	// 플레이어가 보고 있는 방향 속성
	bool	m_bPlayerSee;
	bool	m_bIsSheetDown;




	SYNTHESIZE(bool,m_xCameraOn,XCameraOn);
	SYNTHESIZE(bool, m_yCameraOn, YCameraOn);

	int			m_nSwordAngle;

	PlayerState	m_PlayerState;

	soulInven	m_soulInven;
	SoulSet		m_soulSet;

	itemInven	m_ItemInven;
	ItemSet		m_ItemSet;



	SYNTHESIZE(bool, m_bIsRide, IsRide);
	SYNTHESIZE(bool, m_bIsLide, IsLide);


	//내가 만든 캐릭터

	float	m_fDamageY;

	bool	m_bIsGround;
	bool	m_bIsControll;



public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void mapMove();

	void mapchackCollision();

	void mapRectCollision();

	void hitCollision(int damge);

	void DamageImg(HDC hdc, int damge);

	Status changeStatus(Status status, SoulSet soulSet, ItemSet itemSet);

	void ShowDamage();

	void PlayerRect();

	void controller();

	void aniInit();



	void bossRectCollision(RECT collRc, int idx);


	
	

	Status* getPState() { return &m_status; }

	player();
	~player();
};

