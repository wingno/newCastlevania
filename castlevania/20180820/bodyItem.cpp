#include "stdafx.h"
#include "bodyItem.h"


void bodyItem::init(int cType, int cCount, int cIdx, int cAtt, int cDef, int cStr, int cInt, int cCon, int cLuc, int cHp, int cMp, string cName, string cExplanation)
{
	item::init(cType, cCount, cIdx, cAtt, cDef, cStr, cInt, cCon, cLuc, cHp, cMp, cName, cExplanation);
}

void bodyItem::release()
{
}

void bodyItem::update()
{
}

void bodyItem::render()
{
}

bodyItem::bodyItem()
{
}


bodyItem::~bodyItem()
{
}
