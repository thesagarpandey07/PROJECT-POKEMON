#include "Battle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
    void Battle::game_intro()
    {
        ui.showGameIntro();
    }

    void Battle::display_battle_details(string player1, Pokemon& p1, string player2, Pokemon& p2)
    {
        ui.drawBattleScreen(
            player1, p1.getName(), p1.getHP(), p1.getMaxHP(),
            player2, p2.getName(), p2.getHP(), p2.getMaxHP()
        );
    }

    string Battle::get_attack_name(int num, Pokemon& p)
    {
        if (num == 1) return p.getMove1();
        if (num == 2) return p.getMove2();
        if (num == 3) return p.getMove3();
        if (num == 4) return p.getMove4();
        return "";
    }

    void Battle::display_attack(int num, Pokemon& p)
    {
        ui.displayAttackUsed(p.getName(), get_attack_name(num, p));
    }

    bool Battle::is_pokemon_fainted(Pokemon& p)
    {
        if (p.getHP() <= 0)
        {
            p.setHP(0);
            ui.displayFainted(p.getName());
            return true;
        }
        return false;
    }

    void Battle::attack(int move, Pokemon& attacker, Pokemon& defender)
    {
        float STAB = (attacker.getType() ==
            (move == 1 ? attacker.getMove1Type() :
             move == 2 ? attacker.getMove2Type() :
             move == 3 ? attacker.getMove3Type() :
                         attacker.getMove4Type())) ? 1.5f : 1.0f;

        string move_type;
        int power = 0;

        if (move == 1)
        {
            power = attacker.getPower1();
            move_type = attacker.getMove1Type();
            attacker.setPP1(max(0, attacker.getPP1() - 1));
        }
        else if (move == 2)
        {
            power = attacker.getPower2();
            move_type = attacker.getMove2Type();
            attacker.setPP2(max(0, attacker.getPP2() - 1));
        }
        else if (move == 3)
        {
            power = attacker.getPower3();
            move_type = attacker.getMove3Type();
            attacker.setPP3(max(0, attacker.getPP3() - 1));
        }
        else if (move == 4)
        {
            power = attacker.getPower4();
            move_type = attacker.getMove4Type();
            attacker.setPP4(max(0, attacker.getPP4() - 1));
        }

        int damage = (int)(((attacker.getAttack() * power) *
                            attacker.get_type_multiplier(move_type, defender.getType()) *
                            STAB) /
                           max(1, defender.getDefense()));

        defender.setHP(max(0, defender.getHP() - damage));
    }

    int Battle::switch_pokemon(Pokemon p[])
    {
        string names[3];
        int hps[3];

        for (int i = 0; i < 3; ++i)
        {
            names[i] = p[i].getName();
            hps[i] = p[i].getHP();
        }

        return ui.promptSwitchChoice(names, hps);
    }

    int Battle::check_speed(Pokemon& p1, Pokemon& p2)
    {
        return p1.getSpeed() > p2.getSpeed() ? 1 : 2;
    }

    int Battle::check_all_pp(Pokemon& p)
    {
        return (p.getPP1() == 0 && p.getPP2() == 0 &&
                p.getPP3() == 0 && p.getPP4() == 0) ? 0 : 1;
    }

    int Battle::check_pp(int move, Pokemon& p)
    {
        return p.pp_getter(move) > 0 ? 1 : 0;
    }