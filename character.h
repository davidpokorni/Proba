/**
 * \class Character
 * 
 * \brief Character class
 * 
 * \note This class is simulating the fight.
 * 
 * \author davidpokorni
 * 
 * \date 2020.10.8. 11:17:23
*/
#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>

class Character{
private:
    std::string name;///< This is the name of the character.
    int maxHp;///< This is the health points of the character.
    int dmg;///< This is the damage of the character.
    int health;///< This is the health variable for the levelup method.
    int xp = 0;///< This is the experience of the Character.
	int level = 1;///< This is the level of the Character
    double attackcooldown;/// < This is the attackspeed of the Character.
    /// This function is helps the level ups of the Character.
    void levelup();
    /// This function manages the healt points of the characters in a fight.
    void attack(Character &c/** [in] This is the created character*/);
    /// This function manage the level ups and experiences of the Character.
    void fight(Character &c/** [in] The Character who is fighting*/);
public:
    /// This is a basic constructor and reset the variables.
    Character(/**< [in] There's no parameter here.*/);
    /// This constructor is setting up the private variables.
    Character(const std::string& name/** [in] The name of the character.*/, const int maxHp/** [in] The healt points of the character*/, const int dmg/** [in] The damage of the character*/, const double attackcooldown/** [in] The attackspeed of the character*/);
    /// This constructor is return the name of the character.
    std::string getName(/**< [in] There's no parameter here.*/) const;
    /// This constructor is return the max hp of the character.
    int getMaxHp(/**< [in] There's no parameter here.*/) const;
    /// This contructor is return the hp for the levelup function.
    int getHp(/**< [in] There's no parameter here.*/) const;
    /// This constructor is return the damage of the character.
    int getDmg(/**< [in] There's no parameter here.*/) const;
    /// This constructor is return the attackspeed of the character.
    double getAttackCoolDown(/**< [in] There's no parameter here.*/) const;
    /// This constructor returns the experience of the Character.
    int getXp(/**< [in] There's no parameter here.*/) const;
    /// This contructor returns the actual level of the Character.
	int getLevel(/**< [in] There's no parameter here.*/) const;
    /// This function is chechking the hp of the characters. If it's 0, return false, else true.
    bool isAlive(/**< [in] There's no parameter here.*/) const;
    /// This function is making the fights, using in main.
    Character* takeDamage(Character& player/** [in] This character is the first fighter*/, Character& enemy/** [in] This character is the second fighter*/);
    ///This function manages the input datas from the .json file.
    static void parseUnit(Character &C/** [in] This is the cerated character*/, std::string charSheetName/** [i] This is a string for the .json file name*/);
    /// This is the friend of the class and overload the "cout".
    friend std::ostream & operator<<(std::ostream & os/** [in] This is an ostream referenc to the output*/, const Character &C/** [in] This is what the program print out*/);
};

#endif // !CHARACTER_H
