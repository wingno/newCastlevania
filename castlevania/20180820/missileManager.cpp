#include "stdafx.h"
#include "missileManager.h"


HRESULT missileManager::init(const char* szImageName, float range, int maxCount)
{
	m_fRange = range;
	m_nMaxCount = maxCount;
	m_szImageName = szImageName;


	m_vecMissile.reserve(m_nMaxCount);



	return S_OK;
}

HRESULT missileManager::init()
{


	m_vecMissile.reserve(m_nMaxCount);



	return S_OK;
}

void missileManager::release()
{
	for (m_iter = m_vecMissile.begin();
		m_iter != m_vecMissile.end(); m_iter++)
	{
		delete (*m_iter);
	}
	m_vecMissile.clear();
}

void missileManager::update()
{
	for (m_iter = m_vecMissile.begin(); m_iter != m_vecMissile.end(); m_iter++)
	{
		(*m_iter)->update();
	}
}

void missileManager::render(HDC hdc)
{
	for (m_iter = m_vecMissile.begin(); m_iter != m_vecMissile.end(); m_iter++)
	{
		(*m_iter)->render(hdc);
	}
}

void missileManager::fire(float x, float y, float angle, float speed,int kind)
{

	missile* pMissile;
	pMissile = NULL;
	for (m_iter = m_vecMissile.begin(); m_iter != m_vecMissile.end(); m_iter++)
	{
		if ((*m_iter) != NULL)
		{
			if (!(*m_iter)->getIsFire())
			{
				pMissile = (*m_iter);
			}
		}

	}
	if (pMissile == NULL)
	{
		pMissile = new missile;
		
		m_vecMissile.push_back(pMissile);
	}

	pMissile->init(m_szImageName, speed, x, y, angle, 1000,kind);

	pMissile->fire(x, y);


}

void missileManager::fire(float x, float y)
{

	missile* pMissile;
	pMissile = NULL;
	for (m_iter = m_vecMissile.begin(); m_iter != m_vecMissile.end(); m_iter++)
	{
		if ((*m_iter) != NULL)
		{
			if (!(*m_iter)->getIsFire())
			{
				pMissile = (*m_iter);
			}
		}

	}
	if (pMissile == NULL)
	{
		pMissile = new missile;
		pMissile->init();
		m_vecMissile.push_back(pMissile);
	}


	pMissile->fire(x, y);

}

void missileManager::move()
{
}

missileManager::missileManager()
{
}


missileManager::~missileManager()
{
}
