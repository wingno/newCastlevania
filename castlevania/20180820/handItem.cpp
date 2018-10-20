#include "stdafx.h"
#include "handItem.h"


void handItem::init(int cType, int cCount, int cIdx, int cAtt, int cDef, int cStr, int cInt, int cCon, int cLuc, int cHp, int cMp, string cName, string cExplanation)
{
	item::init(cType, cCount, cIdx, cAtt, cDef, cStr, cInt, cCon, cLuc, cHp, cMp, cName, cExplanation);

	
}

void handItem::release()
{
}

void handItem::update()
{
}

void handItem::render()
{
}

handItem::handItem()
{
}


handItem::~handItem()
{
}
