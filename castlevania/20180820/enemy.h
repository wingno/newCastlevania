#pragma once
class image;
class missileManager;
class player;
class animation;

#define AXE_ARMOR_RANGE 500
#define LIZARMAN_RANGE 300


class enemy
{
private:


	image * m_pImgRMotion;
	image * m_pImgLMotion;
	image *  m_pCImg;
	SYNTHESIZE (RECT,m_rc,Rc);
	RECT	m_chaserRc;
	SYNTHESIZE(RECT, m_attackRect, AttackRect);
	
	SYNTHESIZE (MonsterStatus, m_mStatus, MStatus);
	EnemyKind m_eKind;

	bool	m_bIsAlive;
	bool	m_bIsLeftSee;
	bool	m_bIsGround;
	bool	m_bIsMove;
	bool	m_bIsShot;
	bool	m_bIsWallTouch;
	SYNTHESIZE(bool,m_bIshit,Ishit);


	float	m_fX;
	float	m_fY;

	float	m_fMapX;
	float	m_fMapY;

	float	m_fSpeed;

	float	m_fAngle;
	float	m_fGravity;
	float	m_fElapsedTime;

	float	m_fDivineTime;

	int		m_nPattonNum;

	float	m_fDamageY;


	int		m_nTempDef;
	SYNTHESIZE(int, m_nHitDmg, HitDmg);


	int*	m_pLAni1;
	int*	m_pLAni2;
	int*	m_pRAni1;
	int*	m_pRAni2;
	




	// 미사일 매니저
	missileManager*	m_pMissileMgr;
	player* m_pPlayer;

	animation* m_aniL1;
	animation* m_aniL2;
	animation* m_aniR1;
	animation* m_aniR2;
	
	



public:
	HRESULT init( POINT position, EnemyKind eKind);	
	void release();
	void update();
	void render(HDC hdc);

	void move();
	void lizardMove();
	void fire();
	void attack();
	void defense();



	void ripperMapchackCollision();
	void axeAromorMapchackCollision();

	void ripperInit(POINT position, EnemyKind eKind);
	void ripperUpdate();
	void ripperMove();
	void ripperRender(HDC hdc);



	void axeArmorInit(POINT position, EnemyKind eKind);
	void axeArmorUpdate();
	void axeArmorShot();
	void axeArmorRender(HDC hdc);

	void lizardManInit(POINT position, EnemyKind eKind);
	void lizardManUpdate();
	void lizardManRender(HDC hdc);

	void Damagehit();

	void DamageImg(HDC hdc, int damage);

	inline missileManager* getMissileMgr()
	{ return m_pMissileMgr; }

	inline bool getIsAlive() { return m_bIsAlive; }
	inline void setIsAlive(bool isAlive) { m_bIsAlive = isAlive; }


	enemy();
	~enemy();
};

