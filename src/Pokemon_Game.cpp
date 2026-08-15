#include <raylib.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "Pokemon.h"
#include "GameUI.h"
#include "Player.h"
#include "Special_Attack.h"
#include "Battle.h"

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

int main()
{
    srand((unsigned int)time(NULL));

    Pokemon p1[3], p2[3];
    Player player1, player2;
    Battle battle;
    GameUI ui;

    ui.initGraphics();

    if (!ui.windowOpen())
        return 0;

    battle.game_intro();

    player1.give_random_pokemon_to_players("Player 1", p1);
    player2.give_random_pokemon_to_players("Player 2", p2);

    ui.showMessage("Pokemon selected! Battle begins.", 1.0f);

    bool gameOver = false;
    string winner;

    while (!gameOver && ui.windowOpen())
    {
        int first = battle.check_speed(
            p1[player1.getPokemonindex()],
            p2[player2.getPokemonindex()]
        );

        Player* firstPlayer;
        Player* secondPlayer;
        Pokemon* firstTeam;
        Pokemon* secondTeam;
        string firstName;
        string secondName;

        if (first == 1)
        {
            firstPlayer = &player1;
            secondPlayer = &player2;
            firstTeam = p1;
            secondTeam = p2;
            firstName = "Player 1";
            secondName = "Player 2";
        }
        else
        {
            firstPlayer = &player2;
            secondPlayer = &player1;
            firstTeam = p2;
            secondTeam = p1;
            firstName = "Player 2";
            secondName = "Player 1";
        }

        if (firstTeam[firstPlayer->getPokemonindex()].getSkipTurn() > 0)
        {
            firstTeam[firstPlayer->getPokemonindex()].setSkipTurn(
                firstTeam[firstPlayer->getPokemonindex()].getSkipTurn() - 1
            );
        }
        else
        {
            if (firstPlayer->player_turn(
                    firstName, firstTeam, secondTeam,
                    battle, *secondPlayer))
            {
                gameOver = true;
                winner = firstName;
                break;
            }
        }

        if (secondPlayer->check_win(secondTeam))
        {
            gameOver = true;
            winner = firstName;
            break;
        }

        if (secondTeam[secondPlayer->getPokemonindex()].getSkipTurn() > 0)
        {
            secondTeam[secondPlayer->getPokemonindex()].setSkipTurn(
                secondTeam[secondPlayer->getPokemonindex()].getSkipTurn() - 1
            );
        }
        else
        {
            if (secondPlayer->player_turn(
                    secondName, secondTeam, firstTeam,
                    battle, *firstPlayer))
            {
                gameOver = true;
                winner = secondName;
                break;
            }
        }

        if (firstPlayer->check_win(firstTeam))
        {
            gameOver = true;
            winner = secondName;
            break;
        }
    }

    if (gameOver && ui.windowOpen())
        ui.showWinner(winner + " wins!");

    ui.closeGraphics();
    return 0;
}
