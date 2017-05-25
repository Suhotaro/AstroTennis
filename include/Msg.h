#pragma once

#include <string>

class Msg
{
protected:
	int __ID;
public:
	Msg(int ID) : __ID(ID) {}
	virtual ~Msg() {}

	//$todo: using DER
	virtual std::string Serialize() = 0;
	virtual void Unserialize(std::string) = 0;
};