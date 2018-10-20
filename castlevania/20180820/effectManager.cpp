#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"


HRESULT effectManager::init()
{
	return S_OK;
}

void effectManager::release()
{
	m_iter = m_mapEffects.begin();
	for (; m_iter != m_mapEffects.end(); )
	{

		vecEffect::iterator iter;
		vector<effect*> vecE= m_iter->second;

		// m_mapEffects <key,value>
		// key :string / (iterator-> first)
		// value :vector<effect*> /(iterator->second)
		// m_iter : m_mapEffects을 구성하는 원소(pair : key,value)를 담고있는 메모리 주소(포인터)
		// value를 받아온다 vecE (여기에)
		//if(vecE!=NULL)

		// iter : vecE를 구성하는 원소를 담고 있는 메모리 주소
		for (iter = vecE.begin(); iter != vecE.end(); iter++)
		{
			// m_iter->second로 안되는 이유는 주소값이지 안에 값이 아니기 떄문에 
			
			if ((*iter))
			{
				(*iter)->release();
				SAFE_DELETE((*iter));
				
			}	
		}
		vecE.clear();

		// 이터레이터 자체로 넘겨야 이터레이터로 넘어옴
		m_iter = m_mapEffects.erase(m_iter);


	}
	m_mapEffects.clear();


}


void effectManager::update()
{
	for (m_iter = m_mapEffects.begin(); m_iter != m_mapEffects.end(); m_iter++)
	{
		vecEffect::iterator iter;
		//이펙트형 포인터를 원소로 갖는 벡터
		for (iter = m_iter->second.begin(); iter != m_iter->second.end(); iter++)
		{
			(*iter)->update();
		}

	}
}

void effectManager::render(HDC hdc)
{
	for (m_iter = m_mapEffects.begin(); m_iter != m_mapEffects.end(); m_iter++)
	{
		vecEffect::iterator iter;
		for (iter = m_iter->second.begin(); iter != m_iter->second.end(); iter++)
		{
			(*iter)->render(hdc);
		}

	}
}


void effectManager::addEffect(string effectName,
	const char * imageName, int imageWidth, int imageHeight,
	int frameWidth, int frameHeight, int fps,
	int bufferCount ,float elapsedTime/*=0.0f */)
{
	image* pImage = IMAGEMANAGER->addImage(effectName, imageName, imageWidth, imageHeight, true, RGB(255, 0, 255));

	vecEffect vecEffects;
	for (int i = 0; i < bufferCount; i++)
	{
		effect* pEffect = new effect;
		pEffect->init(pImage,
			frameWidth, frameHeight, fps, elapsedTime);

		vecEffects.push_back(pEffect);
	}

	m_mapEffects.insert(
		pair<string, vecEffect>(effectName, vecEffects));
}

void effectManager::play(string effectName, int x, int y)
{
	m_iter = m_mapEffects.find(effectName);

	if (m_iter!= m_mapEffects.end())
	{
		vecEffect::iterator iter;
		for (iter = m_iter->second.begin(); iter != m_iter->second.end(); iter++)
		{
			if ((*iter)->getIsAlive()) continue;

			(*iter)->startEffect(x, y);
			return;
		}
		
	}

	

}

effectManager::effectManager()
{
}


effectManager::~effectManager()
{
}
