#include "stdafx.h"
#include "ItemUse.h"


void ItemUse::init(int cType, int cCount, int cIdx, int cAtt, int cDef, int cStr, int cInt, int cCon, int cLuc, int cHp, int cMp, string cName, string cExplanation)
{
	item::init(cType, cCount, cIdx, cAtt, cDef, cStr, cInt, cCon, cLuc, cHp, cMp, cName, cExplanation);

	if (cIdx == 0)
	{

		m_imgIcon = IMAGEMANAGER->addImage("image/item.bmp", "image/item.bmp", 360, 18, 20, 1, true, RGB(0, 64, 128));

	}

		
	
}


void ItemUse::release()
{
}

void ItemUse::update()
{
}

void ItemUse::render()
{
}

ItemUse::ItemUse()
{
}


ItemUse::~ItemUse()
{
}
