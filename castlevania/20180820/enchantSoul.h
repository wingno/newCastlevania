#pragma once
#include "soul.h"
class enchantSoul :public soul
{
public:
	virtual void init(int cType, int cCount, int cIdx, int cAtt, int cDef, int cStr,
		int cInt, int cCon, int cLuc, int cHp, int cMp,int useMp, string cName, string cExplanation);
	virtual void release();
	virtual void update();
	virtual void render();

	enchantSoul();
	~enchantSoul();
};

