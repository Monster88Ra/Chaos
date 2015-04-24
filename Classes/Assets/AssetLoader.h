#ifndef _ASSETLOADER_H
#define _ASSETLOADER_H

#include "cocos2d.h"

USING_NS_CC;

class AssetLoader:public Object
{
public:
	static Sprite* createSprite(const std::string &name);
private:
	static AssetLoader* getInstance();
	bool init();

	bool fileExists(const std::string &filename);
	std::string getTexturePlist(const std::string &name);
	std::string getTextureImage(const std::string &name);

private:
	Dictionary *_fileDict;
	//精灵表到_fileDict
	Dictionary* _texturePlistDict;
	//plist到 _fileDict
    Dictionary* _textureImageDict;    
};
#endif//AssetLoader.h