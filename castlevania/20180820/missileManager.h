#pragma once
#include <vector>
#include "missile.h"
#include "enemyMissile.h"

class missileManager
{
private:
	std::vector<missile*>	m_vecMissile;
	std::vector<missile*>::iterator	m_iter;

	const char* m_szImageName;
	float		m_fRange;
	int			m_nMaxCount;



public:
	HRESULT init(const char* szImageName, float range, int maxCount);
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void fire(float x, float y, float angle, float speed,int kind);
	void fire(float x, float y);
	void move();

	inline std::vector<missile*> getVecMissile()
	{
		return m_vecMissile;
	}

	missileManager();
	~missileManager();
};

