#include "stdafx.h"
#include "roomManager.h"
#include "room.h"
#include "enemyManager.h"


roomManager::roomManager()
{
}


roomManager::~roomManager()
{
}

HRESULT roomManager::init()
{
	m_pEnemyMgr = new enemyManager;
	m_pEnemyMgr->init();
	return S_OK;
}

void roomManager::release()
{
	// ���� ��� ���Ҹ� ���鼭 Ȯ��
	for (m_iter = m_mapRooms.begin(); m_iter != m_mapRooms.end(); )
	{
		// ������ value( scene* )�� ������
		if (m_iter->second != NULL)
		{
			// Ȯ���Ϸ��� ���� ���� ���̸� release ȣ��
			if (m_iter->second == m_pCurrRoom)
				m_iter->second->release();

			// �޸� ����
			SAFE_DELETE(m_iter->second);
			// �ʿ��� ����
			m_iter = m_mapRooms.erase(m_iter);
		}
		else
		{
			m_iter++;
		}
	}
	m_mapRooms.clear();
	m_pEnemyMgr->release();
	SAFE_DELETE(m_pEnemyMgr);
	
}

void roomManager::update()
{

	m_pEnemyMgr->update();
	if (m_pCurrRoom)
		m_pCurrRoom->update();
}

void roomManager::render(HDC hdc)
{

	if (m_pCurrRoom)
		m_pCurrRoom->render(hdc);
	m_pEnemyMgr->render(hdc);
}

room * roomManager::addRoom(string roomName, room * pRoom)
{
	if (!pRoom)	return NULL;

	m_mapRooms.insert(pair<string, room*>(roomName, pRoom));

	return pRoom;
}

HRESULT roomManager::changeRoom(string sceneName)
{

	// �ʿ��� �ٲٰ����ϴ� ���� ã�´�
	m_iter = m_mapRooms.find(sceneName);
	// �ʿ��� �ٲٰ����ϴ� ���� �� ã����
	if (m_iter == m_mapRooms.end())	return E_FAIL;

	// �ٲٰ����ϴ� ���� ������� ������
	if (m_iter->second == m_pCurrRoom)	return S_OK;

	SAFE_DELETE(m_pEnemyMgr);
	m_pEnemyMgr = new enemyManager;
	m_pEnemyMgr->init();
	// �ٲٰ����ϴ� ���� ã������ �ʱ�ȭ
	m_iter->second->setEnemyMgr(m_pEnemyMgr);
	if (SUCCEEDED(m_iter->second->init()))
	{
		m_iter->second->setPlayer(m_pPlayer);
		// �ʱ�ȭ ���� ��, ���� ���� release
		if (m_pCurrRoom)
			m_pCurrRoom->release();

		// ���� ���� �ٲٰ����ϴ� ������ ��ü
		m_pCurrRoom = m_iter->second;
		return S_OK;
	}

	return E_FAIL;

}

void roomManager::mapMove(float fx, float fy)
{
	if (m_pCurrRoom)
		m_pCurrRoom->MapMove(fx,fy);
}

