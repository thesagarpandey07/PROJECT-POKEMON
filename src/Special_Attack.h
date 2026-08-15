#ifndef SPECIALATTACK_H
#define SPECIALATTACK_H

#include <iostream>
#include <string>
#include "GameUI.h"
#include "Pokemon.h"
using namespace std;


class Special_Attack
{
private:
    GameUI ui;

public:
    void use_special_attack(string attack_name, Pokemon& attacker, Pokemon& defender);
};
#endif