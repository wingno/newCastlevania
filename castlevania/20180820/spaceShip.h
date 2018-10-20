#pragma once

class missileManager;
class progressBar;

class spaceShip
{
private:
	image * m_img;
	RECT	m_rc;
	float	m_fSpeed;
	float	m_fX;
	float	m_fY;


	missileManager*	m_pMissileMgr;

	progressBar*	m_pHPBar;
	int				m_nCurrHP;
	int				m_nMaxHP;

	int				m_nselectNum;

public:
	HRESULT init();
	HRESULT init(int selectNum);
	void release();
	void update();
	void render(HDC hdc);

	inline RECT getRect() { return m_rc; }
	inline float getX() { return m_fX; }
	inline float getY() { return m_fY; }

	//inline progressBar* getHPBar() { return m_pHPBar; }
	inline void setCurrHP(int hp) { m_nCurrHP = hp; }
	//inline void damaged(int damage) { m_nCurrHP -= damage; }

	inline void setSelectNum(int selectNum) { m_nselectNum = selectNum; }

	void damaged(int damage);

	inline missileManager* getMissileMgr()
	{
		return m_pMissileMgr;
	}

	HRESULT restart();

	spaceShip();
	~spaceShip();
};

