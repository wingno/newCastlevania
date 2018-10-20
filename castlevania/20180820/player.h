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

	
	// �÷��̾� �̹���
	image *	 m_pImg;
	image *	 m_pImg2;
	image *	 m_pImg3;
	image *	 m_pImg4;
	image *  m_pCImg;


	
	// �÷��̾� ��Ʈ
	SYNTHESIZE (RECT, m_rc, Rc);
	SYNTHESIZE(RECT, m_Irc, IRC);
	
	// �÷��̾� �Ӽ� ��

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

	// �÷��̾� �����Ӽ��� �Ӽ�
	int		m_nRCurrFrameX;
	int		m_nRCurrFrameY;

	int		m_nLCurrFrameX;
	int		m_nLCurrFrameY;
	int		m_nCount;

	float	m_fGravity;

	int		m_nNCurrFrameX;
	int		m_nNCurrFrameY;

	bool	m_bItem;

	// �÷��̾ ���� �ִ� ���� �Ӽ�
	bool	m_bPlayerSee;
	bool	m_bPlayerReady;

	// �÷��̾��� ���� ���
	SYNTHESIZE( bool,	m_bPlayerAttack, PlayerAttack);

	// �÷��̾��� ���� ���
	int		m_nPlayerJump;
	bool	m_bPlayerJumpM;
	bool	m_bPlayerJumpDown;
	SYNTHESIZE(bool, m_bPlayerJumpAttack, PlayerJumpAttack);

	// �÷��̾��� �ɱ� ���
	int		m_nPlayerDown;
	SYNTHESIZE(bool, m_bPlayerDownAt, PlayerDownAt);

	// �÷��̾��� �����̵� ���
	bool	m_bPlayerSilde;

	// �÷��̾��� ��뽬 ���
	bool	m_bPlayerBackDash;

	// �÷��̾��� �ǰ� ���
	bool	m_bPlayerHited;
	bool	m_bDivin;
	bool	m_bDamageShow;

	// �������� �Ӽ�
	float	m_fDamageY;

	// �÷��̾��� ���� ���
	SYNTHESIZE(bool, m_bPlayerStand, PlayerStand);

	// �÷��̾� ����
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

