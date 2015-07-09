#ifndef _HERO_MESSAGE_UTIL_H
#define _HERO_MESSAGE_UTIL_H
#include "HeroMessage.h"
#include "json\rapidjson.h"
#include "json\document.h"
#include "cocos2d.h"
#include <map>

using namespace std;

class  HeroMessageUtil
{
public:
	static HeroMessageUtil* getInstance();
	HeroMessage getMessageById(int id);
	map<int, HeroMessage> getHeroMessageMap();
	HeroMessageUtil();
	~HeroMessageUtil();
private:
	void initHeroMsgMap();
private:
	static HeroMessageUtil* m_instance;
	map<int, HeroMessage> heroMsgMap;
};
#endif//_HERO_MESSAGE_UTIL_H