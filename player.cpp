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
#include "Player.h"

// Creates the player near the bottom
// centre of the room.
Player::Player()
{
    x = 25;
    y = 17;

    // Player begins facing upward.
    facingDirection = 'W';
}

// Attempts to move the player one position.
void Player::move(char direction, Room* room)
{
    // newX and newY represent the position
    // the player is TRYING to move to.
    int newX = x;
    int newY = y;

    // Move Up.
    if (direction == 'W' || direction == 'w')
    {
        facingDirection = 'W';
        newY = newY - 1;
    }

    // Move Down.
    else if (direction == 'S' || direction == 's')
    {
        facingDirection = 'S';
        newY = newY + 1;
    }

    // Move Left.
    else if (direction == 'A' || direction == 'a')
    {
        facingDirection = 'A';
        newX = newX - 1;
    }

    // Move Right.
    else if (direction == 'D' || direction == 'd')
    {
        facingDirection = 'D';
        newX = newX + 1;
    }

    // COLLISION DETECTION
    //
    // Only update the player's actual position
    // if the Room says the destination is walkable.
    if (room->isWalkable(newX, newY) == true)
    {
        x = newX;
        y = newY;
    }
}

// Returns player's x-coordinate.
int Player::getX()
{
    return x;
}

// Returns player's y-coordinate.
int Player::getY()
{
    return y;
}

// Returns the direction the player is facing.
char Player::getFacingDirection()
{
    return facingDirection;
}
