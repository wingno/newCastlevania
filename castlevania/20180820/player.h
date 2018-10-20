#pragma once


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


	
	// 플레이어 렉트
	SYNTHESIZE (RECT, m_rc, Rc);
	SYNTHESIZE(RECT, m_Irc, IRC);
	
	// 플레이어 속성 값

	SYNTHESIZE(Status ,m_status,State);
	SYNTHESIZE(int, m_nGold, Gold);

	SYNTHESIZE(int, m_nHitDmg, HitDmg);


	float	m_fJumP;

	float	m_fSildeP;

	float	m_fBackP;

	int		m_nSildeC;

	int		m_nBackC;

	int		m_nJumC;

	int		m_nJumMC;
	
	float	m_fSpeed;

	int		m_nMotionC;

	int		m_nSkReadyC;

	int		m_nHitC;

	SYNTHESIZE( int,m_nHitDivineC, HitDivineC);

	int		m_nNumC;


	SYNTHESIZE( float, m_fX,Fx);
	SYNTHESIZE(float, m_fY,FY);

	// 플레이어 프레임설정 속성
	int		m_nRCurrFrameX;
	int		m_nRCurrFrameY;

	int		m_nLCurrFrameX;
	int		m_nLCurrFrameY;
	int		m_nCount;

	float	m_fGravity;

	int		m_nNCurrFrameX;
	int		m_nNCurrFrameY;

	bool	m_bItem;

	// 플레이어가 보고 있는 방향 속성
	bool	m_bPlayerSee;
	bool	m_bPlayerReady;

	// 플레이어의 공격 모션
	SYNTHESIZE( bool,	m_bPlayerAttack, PlayerAttack);

	// 플레이어의 점프 모션
	int		m_nPlayerJump;
	bool	m_bPlayerJumpM;
	bool	m_bPlayerJumpDown;
	SYNTHESIZE(bool, m_bPlayerJumpAttack, PlayerJumpAttack);

	// 플레이어의 앉기 모션
	int		m_nPlayerDown;
	SYNTHESIZE(bool, m_bPlayerDownAt, PlayerDownAt);

	// 플레이어의 슬라이딩 모션
	bool	m_bPlayerSilde;

	// 플레이어의 백대쉬 모션
	bool	m_bPlayerBackDash;

	// 플레이어의 피격 모션
	bool	m_bPlayerHited;
	bool	m_bDivin;
	bool	m_bDamageShow;

	// 데미지의 속성
	float	m_fDamageY;

	// 플레이어의 착지 모션
	SYNTHESIZE(bool, m_bPlayerStand, PlayerStand);

	// 플레이어 죽음
	SYNTHESIZE(bool, m_bPlayerDie, PlayerDie);

	bool	m_bPlayerSkReady;
	bool	m_bPlayerSkAttack;

	SYNTHESIZE(bool, m_bIsJump, IsJump);


	SYNTHESIZE(bool,m_xCameraOn,XCameraOn);
	SYNTHESIZE(bool, m_yCameraOn, YCameraOn);

	int			m_nSwordAngle;

	soulInven	m_soulInven;
	SoulSet		m_soulSet;

	itemInven	m_ItemInven;
	ItemSet		m_ItemSet;



	SYNTHESIZE(bool, m_bIsRide, IsRide);
	SYNTHESIZE(bool, m_bIsLide, IsLide);


public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	
	void hitMosion();

	void mapMove();

	void mapchackCollision();

	void mapRectCollision();

	void hitCollision(int damge);

	void DamageImg(HDC hdc, int damge);

	Status changeStatus(Status status, SoulSet soulSet, ItemSet itemSet);

	void ShowDamage();

	void FallDown();

	void PlayerRect();

	void PlayerStandAttack();

	void PlayerDownAttack();
	
	void PlayerJumpAttack();

	void PlayerDie();

	void bossRectCollision(RECT collRc, int idx);


	
	

	Status* getPState() { return &m_status; }

	player();
	~player();
};

