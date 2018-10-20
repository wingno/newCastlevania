#pragma once
#include <vector>
#include "enemy.h"

class enemyManager
{
private:
	// std::vector ��� ���� : enemy*
	// ������ �˰� �ִ� �迭�� ���� ���·� ����ȴ�
	std::vector<enemy*>	m_vecEnemy;
	// <enemy* �� ���ҷ� ������ vector>�� ������ �ּҰ��� ��� ����
	std::vector<enemy*>::iterator	m_iter;




	bool m_bisAllClear;

	bool m_bisSetting;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);







	void setEnemy(int baseX, int baseY, EnemyKind kind);




	inline bool getisAllClear() { return m_bisAllClear; };

	inline bool getIsSetting() { return m_bisSetting; }

	inline std::vector<enemy*>	getVecEnemy() { return m_vecEnemy; }
	inline std::vector<enemy*>::iterator getIterEnemy() { return m_iter; }

	enemyManager();
	~enemyManager();
};

