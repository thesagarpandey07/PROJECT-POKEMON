#include "Player.h"
#include "Special_Attack.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

    int generate_random_number()
    {
        return rand() % 20 + 1;
    }
    int Player::getPokemonindex() const { return pokemon_index; }
    void Player::setPokemonindex(int index) { pokemon_index = index; }

    void Player::give_random_pokemon_to_players(string, Pokemon p[])
    {
        for (int i = 0; i < 3; ++i)
        {
            int pokemon_id = generate_random_number();
            p[i].get_data_from_file(pokemon_id);
            p[i].setSkipTurn(0);
        }
    }

    int Player::check_win(Pokemon p[])
    {
        return (p[0].getHP() <= 0 &&
                p[1].getHP() <= 0 &&
                p[2].getHP() <= 0) ? 1 : 0;
    }

    int Player::select_move(string playerName, Pokemon attacker[], Pokemon defender[],
                    Battle& b, Player& defending_player)
    {
        Pokemon& active = attacker[pokemon_index];

        string moves[4] = {
            active.getMove1(),
            active.getMove2(),
            active.getMove3(),
            active.getMove4()
        };

        int pp[4] = {
            active.getPP1(),
            active.getPP2(),
            active.getPP3(),
            active.getPP4()
        };

        int opponentIndex = defending_player.getPokemonindex();

        int move = ui.promptMoveSelection(
            playerName,
            active.getName(),
            active.getHP(),
            active.getMaxHP(),
            moves,
            pp,
            playerName == "Player 1" ? "Player 2" : "Player 1",
            defender[opponentIndex].getName(),
            defender[opponentIndex].getHP(),
            defender[opponentIndex].getMaxHP()
        );

        if (move < 0)
            return 1;

        if (move == 0)
        {
            int newIndex = b.switch_pokemon(attacker);

            if (attacker[newIndex].getHP() > 0)
            {
                pokemon_index = newIndex;
                ui.showMessage(playerName + " switched to " +
                               attacker[pokemon_index].getName());
            }

            return 0;
        }

        if (!b.check_pp(move, active))
        {
            ui.showNoPPLeft();
            return select_move(playerName, attacker, defender, b, defending_player);
        }

        Special_Attack sp;
        string attackName = b.get_attack_name(move, active);

        sp.use_special_attack(attackName, active,
                              defender[defending_player.getPokemonindex()]);

        b.display_attack(move, active);
        b.attack(move, active, defender[defending_player.getPokemonindex()]);

        if (b.is_pokemon_fainted(defender[defending_player.getPokemonindex()]))
        {
            if (check_win(defender))
                return 1;

            int newIndex = b.switch_pokemon(defender);
            defending_player.setPokemonindex(newIndex);
        }

        return 0;
    }

    int Player::player_turn(string playerName, Pokemon attacker[], Pokemon defender[],
                    Battle& b, Player& defending_player)
    {
        b.display_battle_details(
            playerName, attacker[pokemon_index],
            playerName == "Player 1" ? "Player 2" : "Player 1",
            defender[defending_player.getPokemonindex()]
        );

        return select_move(playerName, attacker, defender, b, defending_player);
    }

