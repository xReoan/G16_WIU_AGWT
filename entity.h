#pragma once
class entity
{
public:
	entity(int hp);
	int gethp();
	int getmaxhp();
	bool isalive();
private:
	int hp;
	int maxhp;
};

