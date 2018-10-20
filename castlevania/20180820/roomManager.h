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


	SYNTHESIZE(room*,m_pCurrRoom,CurrRoom);	// ���� ��
	room*	m_pNextRoom;	// ��ȯ ��� ���� ��

	SYNTHESIZE( enemyManager*,	m_pEnemyMgr,EnemyMgr);
	SYNTHESIZE( player*	, m_pPlayer,Player);

	
	




										// ���� ��					�ѹ� ������ �Ǹ� �޸𸮿� �ö󰡼� ���α׷��� ������ ������ �ȳ�����
										// ��ȯ ��� ���� ��		���������� �޸𸮿� �ö������� ��Ȳ�� ��������� ���� ������ �������� ������(static)
										//�ε� ��				�׷��� �ٸ� Ŭ�������� ����ƽ���� ���� �̸����� ����� �� ���� �ȴ�.(���� ����)

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	//�Ϲ� ��
	room* addRoom(string sceneName, room* pScene);
	HRESULT changeRoom(string sceneName);

	void mapMove(float fx,float fy);

	//friend: ĸ��ȭ �Ѱ��� ���� ����
	roomManager();
	~roomManager();
};

