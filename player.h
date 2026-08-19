#pragma once
#include "entity.h"
#include "item.h"
#include "inv.h"
class player : public entity
{
private:
	inv inventory;
	int money;
	item* equippedweapon;
	item* equippedarmor;
	//if player owns the coords for movement put it here
public:
	player();
	int getmoney();
	void addmoney(int amount);
	bool spendmoney(int amount);
	item* getweapon();
	item* getarmor();
	void unequipweapon();
	void unequiparmor();
	void equipweapon(item* weapon);
	void equiparmor(item* armor);
};

