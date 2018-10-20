#pragma once

#define START_Y 392
#define START_ARMY 150

class animation;

class balore
{
private:

	enum BaloreState
	{
		IDLE,
		ATTACK,
		ATTACK2,
		HIT
	};


	image* m_imgEye;
	image* m_imgHead;

	image* m_imgLHand;
	image* m_imgLarm;
	image* m_imgRHand;
	image* m_imgRarm;
	image* m_imgLaser;
	image* m_imgFire;
	image *  m_pCImg;
	image* m_imgFlash;


	RECT m_rectEye;


	RECT m_handUpRect[2];
	RECT m_handDownRect[2];

	RECT m_fireRect[14];

	animation* m_ani;


	SYNTHESIZE(MonsterStatus, m_mStatus, MStatus);

	SYNTHESIZE(bool, m_bIshit, Ishit);

	bool	m_bIsAlive;
	int		m_nPhase;
	int		m_nWhereSee;

	int		m_nPattern;

	int		m_nLaserX;

	int		m_nFlashRotate;


	
	player* m_pPlayer;

	float	m_fX;
	float	m_fY;

	float	m_fMapX;
	float	m_fMapY;

	float	m_fAngle;
	float	m_fDivineTime;
	float	m_fDamageY;

	float	m_fStartCount;


	float	m_fLArmMapY;
	float	m_fLArmMapX;
	float	m_fRArmMapY;
	float	m_fRArmMapX;

	float	m_fLArmY;
	float	m_fLArmX;
	float	m_fRArmY;
	float	m_fRArmX;

	float	m_fLHandMapY;
	float	m_fLHandMapX;
	float	m_fRHandMapY;
	float	m_fRHandMapX;

	float	m_fLHandY;
	float	m_fLHandX;
	float	m_fRHandY;
	float	m_fRHandX;

	float	m_fRArmAngle;
	float	m_fLArmAngle;

	

	int		m_nfireCount;

	bool	m_bIsUp;

	bool	m_bIsPatternEnd;

	bool	m_bIsLeft;

	bool	m_bIsLaser;

	bool	m_bIsLeftLaser;


	SYNTHESIZE(int, m_nHitDmg, HitDmg);


public:
	HRESULT init();
	void release();
	void update();
	void headRender(HDC hdc);
	void armRender(HDC hdc);


	void phase1Update();
	void phase2Update();
	void firePlay();
	void fireRender();
	void chackCollition();

	void Damagehit();

	void DamageImg(HDC hdc, int damage);

	balore();
	~balore();
};

