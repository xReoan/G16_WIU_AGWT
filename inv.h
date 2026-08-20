#pragma once
#include "itemDatabase.h"
class inv
{
private:
	static int invinside[16];
	item* invitem[10];
	itemDatabase database;

public:
	inv();
	void OpenInv() const;
	void RecivedInv(int thing) const; //reciving something, checks if its full inside
	
};

