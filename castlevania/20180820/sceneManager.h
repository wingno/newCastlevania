#pragma once
#include "singletonBase.h"

class scene;

class sceneManager :public singletonBase<sceneManager>
{
private:
	map<string, scene*>	m_mapScenes;
	map<string, scene*>::iterator	m_iter;

	map<string, scene*>	m_mapLoadingScenes;
	map<string, scene*>::iterator	m_iterLoading;


	static scene*	m_pCurrScene;	// 현재 씬
	static scene*	m_pNextScene;	// 전환 대기 중인 씬
	static scene*	m_pLoadingScene;	// 로딩 씬	


										// 현재 씬					한번 실행이 되면 메모리에 올라가서 프로그램이 끝나기 전까지 안내려옴
										// 전환 대기 중인 씬		전역변수와 메모리에 올라갔을떄의 상황은 비슷하지만 접근 권한은 지역성이 존재함(static)
										//로딩 씬				그래서 다른 클래스에서 스태틱으로 같은 이름으로 사용할 수 없게 된다.(에러 터짐)

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	//일반 씬
	scene* addScene(string sceneName, scene* pScene);
	HRESULT changeScene(string sceneName);

	// Loading 과정 포함
	scene* addLoadingScene(string loadingSceneName, scene* pScene);
	HRESULT changeScene(string nextSceneName, string loadingSceneName);

	friend DWORD CALLBACK loadingThraed(LPVOID prc);
	//friend: 캡슐화 한것을 깨는 예외

	sceneManager();
	~sceneManager();
};


