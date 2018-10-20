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
	// vector�� ù ���Һ��� ������ ���ұ��� ��ȸ�ϸ� �� ���Ҹ� delete�Ѵ�
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		(*m_iter)->release();
		delete (*m_iter);
	}
	// vector ��ü�� �����Ѵ�
	m_vecEnemy.clear();
}

void enemyManager::update()
{

	// vector�� ù ���Һ��� ������ ���ұ��� ��ȸ�ϸ� �� ���Ҹ� update�Ѵ�
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{

		(*m_iter)->update();

		

		//m_bisSetting = (*m_iter)->getIsSetting();
	}


}

void enemyManager::render(HDC hdc)
{
	// vector�� ù ���Һ��� ������ ���ұ��� ��ȸ�ϸ� �� ���Ҹ� render�Ѵ�
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
