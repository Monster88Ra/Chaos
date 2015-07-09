#include "HeroMessageUtil.h"
#include "cocos2d.h"
USING_NS_CC;

#define RETURN_IF(cond)           if((cond)) return

HeroMessageUtil* HeroMessageUtil::m_instance = nullptr;

HeroMessageUtil::HeroMessageUtil(){
	initHeroMsgMap();
}

void HeroMessageUtil::initHeroMsgMap(){
	std::string  jsonStr = cocos2d::FileUtils::getInstance()->getStringFromFile("JsonFiles/HeroMessage.json");
	rapidjson::Document _mDoc;

	std::string mstr = jsonStr;
	RETURN_IF(NULL == mstr.c_str() || !mstr.compare(""));
	_mDoc.Parse<0>(mstr.c_str());
	RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
	const rapidjson::Value &pArr = _mDoc["json"];

	CCLOG("Size = %d", pArr.Capacity());

	for (int i = 0; i<pArr.Capacity(); ++i){
		HeroMessage h;
		const rapidjson::Value &temp = pArr[i];
		int id = temp["id"].GetInt();
		h.id = temp["id"].GetInt();
		h.heroName = temp["HeroName"].GetInt();
		h.lifeValue = temp["HeroLifeValue"].GetInt();
		h.magicValue = temp["HeroMagicValue"].GetInt();
		h.damageStrength = temp["HeroDamageStrength"].GetInt();
		h.moveSpeed = temp["HeroMoveSpeed"].GetInt();
		
		h.bodyBoxOriginX = temp["HeroBodyBoxOriginX"].GetDouble();
		h.bodyBoxOriginY = temp["HeroBodyBoxOriginY"].GetDouble();
		h.bodyBoxSizeX = temp["HeroBodyBoxSizeX"].GetDouble();
		h.bodyBoxSizeY = temp["HeroBodyBoxSizeY"].GetDouble();

		h.hitBoxOriginX = temp["HeroHitBoxOriginX"].GetDouble();
		h.hitBoxOriginY = temp["HeroHitBoxOriginY"].GetDouble();
		h.hitBoxSizeX = temp["HeroHitBoxSizeX"].GetDouble();
		h.hitBoxSizeY = temp["HeroHitBoxSizeY"].GetDouble();

		heroMsgMap.insert(make_pair(id, h));

		//CCLOG("h : %s", h.r_png.c_str());
	}
	CCLOG("MapSize = %d", heroMsgMap.size());
	return;
}


HeroMessageUtil::~HeroMessageUtil(){
	CC_SAFE_DELETE(m_instance);
}

HeroMessageUtil* HeroMessageUtil::getInstance(){
	if (m_instance == nullptr){
		m_instance = new HeroMessageUtil();
	}
	return m_instance;
}

map<int, HeroMessage> HeroMessageUtil::getHeroMessageMap(){
	return heroMsgMap;
}

HeroMessage HeroMessageUtil::getMessageById(int id){
	auto it = heroMsgMap.find(id);
	CCASSERT(it != heroMsgMap.end(), "can't get hero msg of the id");
	return (*it).second;
}