#pragma once
#include <string>
//using namespace std;
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
	item(std::string name, std::string description, itemtype itemcategory, combattype combatcategory, int attackvalue, int defensevalue, int healvalue, int duration, int price);
	std::string getname();
	std::string getdescription();
	itemtype getitemcategory();
	combattype getcombatcategory();
	int getattackvalue();
	int getdefensevalue();
	int gethealvalue();
	int getduration();
	int getprice();
private:
	std::string itemname;
	std::string itemdescription;
	itemtype itemcategory;	
	combattype combatcategory;	
	int attackvalue;
	int defensevalue;
	int healvalue;
	int duration;
	int price;
};

