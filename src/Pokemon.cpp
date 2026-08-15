#include "Pokemon.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

    int Pokemon::getSkipTurn() const { return skip_turn; }
    void Pokemon::setSkipTurn(int s) { skip_turn = s; }

    int Pokemon::getId() const { return id; }

    int Pokemon::getMaxHP() const { return max_hp; }
    void Pokemon::setMaxHP(int value) { max_hp = value; }

    string Pokemon::getName() const { return name; }
    void Pokemon::setName(string value) { name = value; }

    string Pokemon::getType() const { return type; }
    void Pokemon::setType(string value) { type = value; }

    int Pokemon::getHP() const { return hp; }
    void Pokemon::setHP(int value) { hp = value; }

    int Pokemon::getAttack() const { return attack; }
    void Pokemon::setAttack(int value) { attack = value; }

    int Pokemon::getDefense() const { return defense; }
    void Pokemon::setDefense(int value) { defense = value; }

    int Pokemon::getSpeed() const { return speed; }
    void Pokemon::setSpeed(int value) { speed = value; }

    int Pokemon::getPP1() const { return pp1; }
    void Pokemon::setPP1(int value) { pp1 = value; }

    int Pokemon::getPP2() const { return pp2; }
    void Pokemon::setPP2(int value) { pp2 = value; }

    int Pokemon::getPP3() const { return pp3; }
    void Pokemon::setPP3(int value) { pp3 = value; }

    int Pokemon::getPP4() const { return pp4; }
    void Pokemon::setPP4(int value) { pp4 = value; }

    void Pokemon::setPower1(int value) { power1 = value; }
    int Pokemon::getPower1() const { return power1; }

    void Pokemon::setPower2(int value) { power2 = value; }
    int Pokemon::getPower2() const { return power2; }

    void Pokemon::setPower3(int value) { power3 = value; }
    int Pokemon::getPower3() const { return power3; }

    void Pokemon::setPower4(int value) { power4 = value; }
    int Pokemon::getPower4() const { return power4; }

    void Pokemon::setMove1(string value) { move1 = value; }
    string Pokemon::getMove1() const { return move1; }
    void Pokemon::setMove1Type(string value) { move1Type = value; }
    string Pokemon::getMove1Type() const { return move1Type; }

    void Pokemon::setMove2(string value) { move2 = value; }
    string Pokemon::getMove2() const { return move2; }
    void Pokemon::setMove2Type(string value) { move2Type = value; }
    string Pokemon::getMove2Type() const { return move2Type; }

    void Pokemon::setMove3(string value) { move3 = value; }
    string Pokemon::getMove3() const { return move3; }
    void Pokemon::setMove3Type(string value) { move3Type = value; }
    string Pokemon::getMove3Type() const { return move3Type; }

    void Pokemon::setMove4(string value) { move4 = value; }
    string Pokemon::getMove4() const { return move4; }
    void Pokemon::setMove4Type(string value) { move4Type = value; }
    string Pokemon::getMove4Type() const { return move4Type; }

    void Pokemon::get_data_from_file(int poke_id)
    {
        ifstream file("../Data_Files/pokemon.txt");

        if (!file)
        {
            ui.showFileError();
            return;
        }

        string line;
        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string temp;

            getline(ss, temp, ',');
            id = stoi(temp);

            if (id != poke_id)
                continue;

            getline(ss, name, ',');
            getline(ss, type, ',');

            getline(ss, temp, ',');
            hp = stoi(temp);
            max_hp = hp;

            getline(ss, temp, ',');
            attack = stoi(temp);

            getline(ss, temp, ',');
            defense = stoi(temp);

            getline(ss, temp, ',');
            speed = stoi(temp);

            getline(ss, move1, ',');
            getline(ss, move1Type, ',');
            getline(ss, temp, ',');
            power1 = stoi(temp);
            getline(ss, temp, ',');
            pp1 = stoi(temp);

            getline(ss, move2, ',');
            getline(ss, move2Type, ',');
            getline(ss, temp, ',');
            power2 = stoi(temp);
            getline(ss, temp, ',');
            pp2 = stoi(temp);

            getline(ss, move3, ',');
            getline(ss, move3Type, ',');
            getline(ss, temp, ',');
            power3 = stoi(temp);
            getline(ss, temp, ',');
            pp3 = stoi(temp);

            getline(ss, move4, ',');
            getline(ss, move4Type, ',');
            getline(ss, temp, ',');
            power4 = stoi(temp);
            getline(ss, temp);
            pp4 = stoi(temp);

            break;
        }
    }

    void Pokemon::display()
    {
        ui.displayPokemonDetails(
            id, name, type, hp, attack, defense, speed,
            move1, move1Type, power1, pp1,
            move2, move2Type, power2, pp2,
            move3, move3Type, power3, pp3,
            move4, move4Type, power4, pp4
        );
    }

    float Pokemon::get_type_multiplier(string attackType, string defenseType)
    {
        ifstream file("../Data_Files/Type_Multiplier.txt");

        if (!file)
        {
            ui.showFileError();
            return 1.0f;
        }

        string line;
        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string atkType, defType, temp;

            getline(ss, atkType, ',');
            getline(ss, defType, ',');
            getline(ss, temp, ',');

            float multiplier = stof(temp);

            if (atkType == attackType && defType == defenseType)
                return multiplier;
        }

        return 1.0f;
    }

    int Pokemon::pp_getter(int move) const
    {
        if (move == 1) return pp1;
        if (move == 2) return pp2;
        if (move == 3) return pp3;
        if (move == 4) return pp4;
        return 0;
    }
