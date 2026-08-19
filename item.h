#pragma once
#include <string>
using namespace std;
class item
{
public:
	enum class itemtype {
		weapon,
		armor,
		consumable
	};
	enum class combattype {
		melee,
		projectile,
		none
	};
	item(string name, string description, itemtype itemcategory, combattype combatcategory, int attackvalue, int defensevalue, int healvalue, int duration, int price);
	string getname();
	string getdescription();
	itemtype getitemcategory();
	combattype getcombatcategory();
	int getattackvalue();
	int getdefensevalue();
	int gethealvalue();
	int getduration();
	int getprice();
private:
	string itemname;
	string itemdescription;
	itemtype itemcategory;	
	combattype combatcategory;	
	int attackvalue;
	int defensevalue;
	int healvalue;
	int duration;
	int price;
};

