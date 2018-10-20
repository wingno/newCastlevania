#pragma once
#include "scene.h"

class menuProgressBar;
class soul;

class menuScene :public scene
{
private:
	enum SceneState
	{
		MENU,SOUL_SET, EQUIT, ITEM
	};
	struct seleter
	{
		int Select;
		int SelectMover;
		bool isLeft;
		float speed;
	};


	image*	m_imgMenu;
	image*	m_imgEquit;
	image*	m_imgSoulSet;
	image*	m_imgUseItem;

	image*	m_imgRArrow;
	image*	m_imgLArrow;

	image*	m_imgEmptySoul;

	image*	m_imgBSoul;
	image*	m_imgGSoul;
	image*	m_imgESoul;

	image*	m_imgItem;

	animation * m_pBSoulAni;
	animation * m_pGSoulAni;
	animation * m_pESoulAni;


	image*	m_imgSeleter;

	bool	m_bIsChangeScene;

	int m_nAlphaNum;

	int m_nSetStep;

	int m_nTypeSelcet;
	
	int m_nFinalSelectNum;

	int m_nShowStartNum;

	int m_nShowEndChacker;




	Status m_ChangeStatus;


	seleter m_seleter;

	SceneState m_state;

	player* m_pPlayer;
	menuProgressBar* m_pHpBar;
	menuProgressBar* m_pMpBar;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void menuRander(HDC hdc );
	void menuUpdate();
	void sourSetRander(HDC hdc);
	void sourSetupdate();
	void equitRander(HDC hdc);
	void equitupdate();
	void useItemRander(HDC hdc);
	void useItemupdate();


	void bsUpDate();
	void gsUpDate();
	void esUpDate();

	void hiUpDate();

	void biUpDate();

	void aiUpDate();

	void fontPrint(HDC hdc);

	void useItemFontPrint(HDC hdc);

	void clearInven();

	Status changeStatus(Status status, SoulSet soulSet,ItemSet item);

	menuScene();
	~menuScene();
};

