#pragma once
class Entity
{
public:
	Entity(int hp);
	int gethp();
	int getmaxhp();
	bool isalive();
private:
	int hp;
	int maxhp;
};

