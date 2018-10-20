#include "stdafx.h"
#include "accessoryItem.h"


void accessoryItem:: init(int cType, int cCount, int cIdx, int cAtt, int cDef, int cStr, int cInt, int cCon, int cLuc, int cHp, int cMp, string cName, string cExplanation)
{
	item::init(cType, cCount, cIdx, cAtt, cDef, cStr, cInt, cCon, cLuc, cHp, cMp, cName, cExplanation);
}

void accessoryItem::release()
{
}

void accessoryItem::update()
{
}

void accessoryItem::render()
{
}

accessoryItem::accessoryItem()
{
}


accessoryItem::~accessoryItem()
{
}
