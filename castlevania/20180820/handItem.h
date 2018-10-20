#pragma once
#include "item.h"
class handItem :
	public item
{

public:
	virtual void init(int cType, int cCount, int cIdx, int cAtt, int cDef, int cStr,
		int cInt, int cCon, int cLuc, int cHp, int cMp, string cName, string cExplanation);
	virtual void release();
	virtual void update();
	virtual void render();


	handItem();
	~handItem();
};

