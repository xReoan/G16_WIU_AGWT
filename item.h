#pragma once
#include <string>
using namespace std;
class item
{
public:
	enum class itemtype {
		weapon,
		armor,
		consumable,
	};
	enum class combattype {
		melee,
		projectile,
		none,
	};
	item(string name, string description, itemtype itemcategory, combattype combatcategory, int value);
	string getname();
	string getdescription();
	int getvalue();
	itemtype getitemcategory();
	combattype getcombatcategory();
private:
	string name;
	string description;
	itemtype itemcategory;	
	combattype combatcategory;
	int value;	
};

