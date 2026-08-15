#include "Special_Attack.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
void Special_Attack::use_special_attack(string attack_name, Pokemon& attacker, Pokemon& defender)
    {
        if (attack_name == "Hypnosis")
        {
            defender.setSpeed(max(10, defender.getSpeed() - 25));
            defender.setSkipTurn(2);
            ui.showHypnosisEffect(defender.getName());
        }
        else if (attack_name == "Recover")
        {
            attacker.setHP(min(attacker.getMaxHP(), attacker.getHP() + 70));
            ui.showRecoverEffect(attacker.getName());
        }
        else if (attack_name == "Confuse Ray")
        {
            defender.setAttack(max(20, defender.getAttack() - 20));
            ui.showConfuseRayEffect(defender.getName());
        }
        else if (attack_name == "Dragon Dance")
        {
            attacker.setAttack(attacker.getAttack() + 30);
            attacker.setSpeed(attacker.getSpeed() + 20);
            ui.showDragonDanceEffect(attacker.getName());
        }
        else if (attack_name == "Rest")
        {
            attacker.setHP(min(attacker.getMaxHP(), attacker.getHP() + 120));
            attacker.setSpeed(max(10, attacker.getSpeed() - 15));
            attacker.setSkipTurn(2);
            ui.showRestEffect(attacker.getName());
        }
        else if (attack_name == "Moonlight")
        {
            attacker.setHP(min(attacker.getMaxHP(), attacker.getHP() + 90));
            ui.showMoonlightEffect(attacker.getName());
        }
        else if (attack_name == "Swords Dance")
        {
            attacker.setAttack(attacker.getAttack() + 40);
            ui.showSwordsDanceEffect(attacker.getName());
        }
        else if (attack_name == "Solar Beam")
        {
            attacker.setSkipTurn(1);
            ui.showSolarBeamEffect(attacker.getName());
        }
        else if (attack_name == "Hyper Beam")
        {
            attacker.setSkipTurn(1);
            ui.showHyperBeamEffect(attacker.getName());
        }
        else if (attack_name == "Outrage")
        {
            attacker.setSkipTurn(2);
            ui.showOutrageEffect(attacker.getName());
        }
        else if (attack_name == "Rollout")
        {
            attacker.setSkipTurn(4);
            ui.showRolloutEffect(attacker.getName());
        }
        else if (attack_name == "Skull Bash")
        {
            attacker.setSkipTurn(1);
            ui.showSkullBashEffect(attacker.getName());
        }
        else if (attack_name == "Future Sight")
        {
            attacker.setSkipTurn(2);
            ui.showFutureSightEffect(attacker.getName());
        }
    }
