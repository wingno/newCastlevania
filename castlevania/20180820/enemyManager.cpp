#include "stdafx.h"
#include "enemyManager.h"
#include "spaceShip.h"


HRESULT enemyManager::init()
{


	m_vecEnemy.reserve(10);
	return S_OK;
}

void enemyManager::release()
{
	// vector의 첫 원소부터 마지막 원소까지 순회하며 각 원소를 delete한다
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		(*m_iter)->release();
		delete (*m_iter);
	}
	// vector 자체를 삭제한다
	m_vecEnemy.clear();
}

void enemyManager::update()
{

	// vector의 첫 원소부터 마지막 원소까지 순회하며 각 원소를 update한다
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{

		(*m_iter)->update();

		

		//m_bisSetting = (*m_iter)->getIsSetting();
	}


}

void enemyManager::render(HDC hdc)
{
	// vector의 첫 원소부터 마지막 원소까지 순회하며 각 원소를 render한다
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		
			(*m_iter)->render(hdc);


	}
}

void enemyManager::setEnemy(int baseX,int baseY, EnemyKind kind)
{
	enemy* pEnemy;
	pEnemy = NULL;
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		if ((*m_iter) != NULL)
		{
			if (!(*m_iter)->getIsAlive())
			{
				pEnemy = (*m_iter);
			}
		}

	}
	if (pEnemy == NULL)
	{


		pEnemy = new enemy;
		m_vecEnemy.push_back(pEnemy);
	}



	pEnemy->init( PointMake(baseX, baseY),kind);






}






enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}
