#include "character.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

Character::Character() {
	this->name = "";
	this->maxHp = 0;
	this->dmg = 0;
	this->attackcooldown = 0.0;
}

Character::Character(const std::string& name, const int maxHp, const int dmg, const double attackcooldown) : name(name), maxHp(maxHp), dmg(dmg), attackcooldown(attackcooldown)
{
	health = maxHp;
}

std::string Character::getName() const
{
	return name;
}

int Character::getHp() const
{
	return health;
}

int Character::getDmg() const
{
	return dmg;
}
double Character::getAttackCoolDown() const
{
	return attackcooldown;
}

int Character::getMaxHp() const
{
	return maxHp;
}

int Character::getXp() const
{
	return xp;
}

int Character::getLevel() const
{
	return level;
}

bool Character::isAlive() const
{
	if (this->getHp() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Character::fight(Character &c)
{
	if (c.isAlive())
	{
		this->attack(c);
		this->levelup();
	}
}

void Character::attack(Character &player)
{
	int act_xp = 0;
	if (player.getHp() - getDmg() > 0)
	{
		player.health -= getDmg();
		act_xp = getDmg();
	}
	else
	{
		act_xp = player.getHp();
		player.health = 0;
	}
	xp += act_xp;
}

void Character::levelup()
{
	int level_c = getXp() / 100;
	for (int i = 0; i < level_c; i++)
	{
		level++;
		dmg += round(getDmg()*0.1);
		maxHp += round(getMaxHp()*0.1);
		health = maxHp;
		xp -= 100;
		attackcooldown-=round(attackcooldown*0.1);
	}
}
Character* Character::takeDamage(Character& player, Character& enemy)
{
	double t1=0.0;
	double t2=0.0;
	while(enemy.isAlive() && player.isAlive()){
		if(t1<t2){
			player.fight(enemy);
			if(!enemy.isAlive()){
				return &player;
			}
			t1+=player.attackcooldown;
		}
		else if(t1>t2){
			enemy.fight(player);
			if(!player.isAlive()){
				return &enemy;
			}
			t2+=enemy.attackcooldown;
		}
		else{
			player.fight(enemy);
			if (!enemy.isAlive()){
				return &player;
			}
			t1+=player.attackcooldown;
			enemy.fight(player);
			if(!player.isAlive()){
				return &enemy;
			}
			t2+=enemy.attackcooldown;
		}
	}
	return nullptr;
}

std::ostream & operator<<(std::ostream & os, const Character &C) {
	os << C.getName() << ": HP: " << C.getHp() << ", MaxHP:" << C.getMaxHp() << ", DMG: " << C.getDmg() << ", XP: " << C.getXp() << ", Level: " << C.getLevel() << '\n';
	return os;
}

void Character::parseUnit(Character &C, std::string charSheetName)
{
	std::fstream charSheet(charSheetName);

	if (charSheet.fail())
	{
		std::string error("Couldn't open file");
		throw std::runtime_error(error);
	}

	std::string line;

	while (!charSheet.eof())
	{
		std::getline(charSheet, line);

		if ((C.getName() == "") && (line.find("name") != std::string::npos))
		{
			int end = line.rfind('"');
			int start = end;
			bool find = true;
			while (find)
			{
				start--;
				if (line[start] == '"')
				{
					find = false;
				}
			}
			int length = end - start - 1;
			C.name = line.substr(start + 1, length);
		}

		if ((C.getMaxHp() == 0) && (line.find("hp") != std::string::npos)) 
		{
			int start = line.rfind(':');
			int end = line.rfind(',');
			int length = end - start - 2;
			C.maxHp = std::stoi(line.substr(start + 2, length));
			C.health=C.maxHp;
		}


		if ((C.getDmg() == 0) && (line.find("dmg") != std::string::npos))
		{
			int start = line.rfind(':');
			int length = line.length() - start - 1;
			C.dmg = std::stoi(line.substr(start + 2, length));
		}
		if ((C.getAttackCoolDown() == 0) && (line.find("atc") != std::string::npos))
		{
			int start = line.rfind(':');
			int length = line.length() - start - 1;
			C.attackcooldown = std::stoi(line.substr(start + 2, length));
		}
	}
	charSheet.close();
}