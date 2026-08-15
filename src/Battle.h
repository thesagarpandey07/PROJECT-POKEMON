#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include <string>
#include "GameUI.h"
#include "Pokemon.h"
using namespace std;
class Battle
{
private:
    GameUI ui;

public:
    void game_intro();

    void display_battle_details(string player1, Pokemon& p1, string player2, Pokemon& p2);

    string get_attack_name(int num, Pokemon& p);

    void display_attack(int num, Pokemon& p);
    bool is_pokemon_fainted(Pokemon& p);

    void attack(int move, Pokemon& attacker, Pokemon& defender);

    int switch_pokemon(Pokemon p[]);

    int check_speed(Pokemon& p1, Pokemon& p2);

    int check_all_pp(Pokemon& p);

    int check_pp(int move, Pokemon& p);
};
#endif