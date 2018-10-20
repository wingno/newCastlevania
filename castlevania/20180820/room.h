#pragma once
#include "enemyManager.h"

class player;
//class enemyManager;
class room
{
protected:
	typedef struct tagMemDCInfo
	{
		HDC		hMemDC;	// ȭ�鿡 ��, ��, ���� ���� �׸� �� �ʿ��� ������ �����ϴ� ��ü
						// �׸��� �׸� �� �ʿ��� �޸� ���� �Ҵ�(��ȭ�� ����)
		HBITMAP	hBitmap;	// �̹������� �ε忡 ���Ǵ� ��ü
		HBITMAP hOldBitmap;
		int		nWidth;		// �̹��� �ʺ�
		int		nHeight;	// �̹��� ����


		tagMemDCInfo()
		{
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBitmap = NULL;
			nWidth = 0;
			nHeight = 0;
		}//

		//void init();

		//~tagImageInfo() {}
	} MEM_INFO, *LPMEM_INFO;

	SYNTHESIZE(enemyManager*, m_pEnemyMgr, EnemyMgr);
	SYNTHESIZE(player*, m_pPlayer, Player);
	

	SYNTHESIZE(LPMEM_INFO, m_pMemDCInfo, MemDCInfo);

	SYNTHESIZE(RECT*, m_rectObj,RectObj);
	SYNTHESIZE(RECT*, m_rectGate, RectGate);
	SYNTHESIZE(int, m_nRectNum, RectNum);

	image* m_imgBg;
	image* m_imgMap;

	SYNTHESIZE(POINT, m_posMap, PosMap);
	POINT m_posBG;



public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	
	inline float getX() { return m_posMap.x; }
	inline float getY() { return m_posMap.y; }
	void MapMove(float fx,float fy);


	room();
	~room();
};

