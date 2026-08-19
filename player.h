#pragma once
#include "Entity.h"
#include "item.h"
#include "inv.h"
#include "Room.h"
class Player : public Entity
{
private:
	inv inventory;
	int money;
	item* equippedweapon;
	item* equippedarmor;
    // Player's current position inside the room.
    int x;
    int y;

    // Direction the player is currently facing.
    //
    // W = Up
    // A = Left
    // S = Down
    // D = Right
    char facingDirection;
public:
	Player();
	int getmoney();
	void addmoney(int amount);
	bool spendmoney(int amount);
	item* getweapon();
	item* getarmor();
	void unequipweapon();
	void unequiparmor();
	void equipweapon(item* weapon);
	void equiparmor(item* armor);

    // Constructor.
    Player();

    // Attempts to move the player one space.
    //
    // The Room checks whether the destination
    // can actually be walked on.
    void move(char direction, Room* room);

    // Getter functions.
    int getX();
    int getY();

    char getFacingDirection();
};