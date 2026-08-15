#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "GameUI.h"
#include "Battle.h"
#include "Pokemon.h"
using namespace std;

class Player
{
private:
    int pokemon_index;
    GameUI ui;

public:
    Player(int index = 0) : pokemon_index(index) {}

    int getPokemonindex() const ;
    void setPokemonindex(int index) ;

    void give_random_pokemon_to_players(string, Pokemon p[]);

    int check_win(Pokemon p[]);

    int select_move(string playerName, Pokemon attacker[], Pokemon defender[],
                    Battle& b, Player& defending_player);

    int player_turn(string playerName, Pokemon attacker[], Pokemon defender[],
                    Battle& b, Player& defending_player);
};
#endif
