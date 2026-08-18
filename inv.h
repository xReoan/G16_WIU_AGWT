#pragma once
class inv
{
	static char invinside[17][35];
public:
	void OpenInv() const;
	void RecivedInv(char thing) const; //reciving something, checks if its full inside
};

