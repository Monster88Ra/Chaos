#ifndef _HERO_MESSAGE_H
#define _HERO_MESSAGE_H
#include <string>
using namespace std;

class HeroMessage
{
public:
	int id;
	string heroName;
	int lifeValue;
	int magicValue;
	int damageStrength;
	int moveSpeed;

	float bodyBoxOriginX;
	float bodyBoxOriginY;
	float bodyBoxSizeX;
	float bodyBoxSizeY;

	float hitBoxOriginX;
	float hitBoxOriginY;
	float hitBoxSizeX;
	float hitBoxSizeY;
};
#endif//_HERO_MESSAGE_H