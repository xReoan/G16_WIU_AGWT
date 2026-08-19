#include "player.h"
#include <iostream>
player::player() : entity(100) {
	money = 0;
	equippedweapon = nullptr;
	equippedarmor = nullptr;
}

int player::getmoney() {
	return money;
}

item* player::getweapon() {
	return equippedweapon;
}

item* player::getarmor() {
	return equippedarmor;
}

void player::equipweapon(item* weapon)
{
	if (weapon != nullptr && weapon->getitemcategory() == item::itemtype::weapon) {
		equippedweapon = weapon;
	}
}

void player::equiparmor(item* armor)
{
	if (armor != nullptr && armor->getitemcategory() == item::itemtype::armor) {
		equippedarmor = armor;
	}
}

void player::addmoney(int amount) {
	money += amount;
}

bool player::spendmoney(int amount) {
	if (money >= amount) {
		money -= amount;
		return true;
	}
	else {
		return false;
	}
}