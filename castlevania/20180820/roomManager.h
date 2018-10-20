#pragma once
#include "singletonBase.h"

class player;
class enemyManager;
class room;
class zombi;

class roomManager :public singletonBase<roomManager>
{
private:
	map<string, room*>				m_mapRooms;
	map<string, room*>::iterator	m_iter;


	SYNTHESIZE(room*,m_pCurrRoom,CurrRoom);	// 현재 씬
	room*	m_pNextRoom;	// 전환 대기 중인 씬

	SYNTHESIZE( enemyManager*,	m_pEnemyMgr,EnemyMgr);
	SYNTHESIZE( player*	, m_pPlayer,Player);

	
	




										// 현재 씬					한번 실행이 되면 메모리에 올라가서 프로그램이 끝나기 전까지 안내려옴
										// 전환 대기 중인 씬		전역변수와 메모리에 올라갔을떄의 상황은 비슷하지만 접근 권한은 지역성이 존재함(static)
										//로딩 씬				그래서 다른 클래스에서 스태틱으로 같은 이름으로 사용할 수 없게 된다.(에러 터짐)

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	//일반 씬
	room* addRoom(string sceneName, room* pScene);
	HRESULT changeRoom(string sceneName);

	void mapMove(float fx,float fy);

	//friend: 캡슐화 한것을 깨는 예외
	roomManager();
	~roomManager();
};

