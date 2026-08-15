#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <string>
#include "GameUI.h"
using namespace std;

class Pokemon
{
private:
    int id = 0;
    string name;
    string type;

    int hp = 0;
    int max_hp = 0;
    int attack = 0;
    int defense = 0;
    int speed = 0;

    string move1, move1Type;
    int power1 = 0, pp1 = 0;

    string move2, move2Type;
    int power2 = 0, pp2 = 0;

    string move3, move3Type;
    int power3 = 0, pp3 = 0;

    string move4, move4Type;
    int power4 = 0, pp4 = 0;

    int skip_turn = 0;
    GameUI ui;

public:
    Pokemon(int turn = 0) : skip_turn(turn) {}

    int getSkipTurn() const ;
    void setSkipTurn(int s = 0) ;
    int getId() const ;
    int getMaxHP() const ;
    void setMaxHP(int value) ;

    string getName() const ;
    void setName(string value) ;

    string getType() const ;
    void setType(string value) ;
    int getHP() const ;
    void setHP(int value) ;

    int getAttack() const ;
    void setAttack(int value) ;

    int getDefense() const ;
    void setDefense(int value) ;

    int getSpeed() const ;
    void setSpeed(int value) ;

    int getPP1() const ;
    void setPP1(int value) ;

    int getPP2() const ;
    void setPP2(int value) ;

    int getPP3() const ;
    void setPP3(int value) ;

    int getPP4() const ;
    void setPP4(int value) ;

    void setPower1(int value) ;
    int getPower1() const ;
    void setPower2(int value) ;
    int getPower2() const ;

    void setPower3(int value) ;
    int getPower3() const ;

    void setPower4(int value) ;
    int getPower4() const ;
    void setMove1(string value) ;
    string getMove1() const ;
    void setMove1Type(string value) ;
    string getMove1Type() const ;

    void setMove2(string value) ;
    string getMove2() const ;
    void setMove2Type(string value) ;
    string getMove2Type() const ;
    void setMove3(string value) ;
    string getMove3() const ;
    void setMove3Type(string value) ;
    string getMove3Type() const ;

    void setMove4(string value) ;
    string getMove4() const ;
    void setMove4Type(string value) ;
    string getMove4Type() const ;

    void get_data_from_file(int poke_id);
    void display();

    float get_type_multiplier(string attackType, string defenseType);

    int pp_getter(int move) const;
};
#endif