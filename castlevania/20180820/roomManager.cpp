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
	// 맵의 모든 원소를 돌면서 확인
	for (m_iter = m_mapRooms.begin(); m_iter != m_mapRooms.end(); )
	{
		// 원소의 value( scene* )가 있으면
		if (m_iter->second != NULL)
		{
			// 확인하려는 씬이 현재 씬이면 release 호출
			if (m_iter->second == m_pCurrRoom)
				m_iter->second->release();

			// 메모리 해제
			SAFE_DELETE(m_iter->second);
			// 맵에서 삭제
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

	// 맵에서 바꾸고자하는 씬을 찾는다
	m_iter = m_mapRooms.find(sceneName);
	// 맵에서 바꾸고자하는 씬을 못 찾으면
	if (m_iter == m_mapRooms.end())	return E_FAIL;

	// 바꾸고자하는 씬과 현재씬이 같으면
	if (m_iter->second == m_pCurrRoom)	return S_OK;

	SAFE_DELETE(m_pEnemyMgr);
	m_pEnemyMgr = new enemyManager;
	m_pEnemyMgr->init();
	// 바꾸고자하는 씬을 찾았으면 초기화
	m_iter->second->setEnemyMgr(m_pEnemyMgr);
	if (SUCCEEDED(m_iter->second->init()))
	{
		m_iter->second->setPlayer(m_pPlayer);
		// 초기화 성공 시, 현재 씬을 release
		if (m_pCurrRoom)
			m_pCurrRoom->release();

		// 현재 씬을 바꾸고자하는 씬으로 교체
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

