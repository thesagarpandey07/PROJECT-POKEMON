#ifndef GAMEUI_H
#define GAMEUI_H

#include <raylib.h>
#include <string>
#include <unordered_map>

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class GameUI
{
private:
    unordered_map<string, Texture2D> pokemonTextures;
    unordered_map<string, string> pokemonTexturePaths;

    string findPokemonImagePath(const string& pokemonName);
    Texture2D* getPokemonTexture(const string& pokemonName);
    void drawPokemonImage(const string& pokemonName, Rectangle destination, bool flipHorizontal);
    void unloadPokemonTextures();
    void drawButton(Rectangle r, const string& text, bool disabled = false);

public:
    void initGraphics();
    bool windowOpen();
    void closeGraphics();
    void showFileError();
    void showMessage(const string& message, float = 1.2f);
    void showGameIntro();
    void displayPokemonDetails(
        int id, string name, string type, int hp, int attack, int defense, int speed,
        string move1, string move1Type, int power1, int pp1,
        string move2, string move2Type, int power2, int pp2,
        string move3, string move3Type, int power3, int pp3,
        string move4, string move4Type, int power4, int pp4);
    int promptMoveSelection(
        const string& playerName,
        const string& pokemonName,
        int hp,
        int maxHP,
        const string moves[4],
        const int pp[4],
        const string& opponentPlayer,
        const string& opponentPokemon,
        int opponentHP,
        int opponentMaxHP);
    int promptSwitchChoice(const string names[3], const int hps[3]);
    void drawScene();
    void drawPokemonBox(Rectangle r, Color mainColor, string label, string playerLabel,
                        int hp, int maxHP, bool enemySide);
    void drawBattlePokemonSprites(string player1, string p1PokemonName,
                                   string player2, string p2PokemonName);
    void drawBattleHUD(string player1, string p1PokemonName, int p1HP, int p1MaxHP,
                       string player2, string p2PokemonName, int p2HP, int p2MaxHP);
    void drawAttackAnimation(
        string player1, string p1Pokemon, int p1HP, int p1MaxHP,
        string player2, string p2Pokemon, int p2HP, int p2MaxHP,
        bool player1Attacking, string moveName);
    void displayBattleDetails(string player1, string p1Name, int p1HP,
                              string player2, string p2Name, int p2HP);
    void displayAttackUsed(string pokemonName, string attackName);
    void displayFainted(string pokemonName);
    void showFaintedRetry();
    void showNoPPLeft();
    void displayPlayerTurn(string player, string pokemonName);
    void displayPokemonStatus(string names[3], int hps[3]);
    void displayPlayerPokemonHeader(string);
    void displayGivenPokemon(int, string);
    void displayGivenPokemonListEnd();
    void showHypnosisEffect(string name);
    void showRecoverEffect(string name);
    void showConfuseRayEffect(string name);
    void showDragonDanceEffect(string name);
    void showRestEffect(string name);
    void showMoonlightEffect(string name);
    void showSwordsDanceEffect(string name);
    void showSolarBeamEffect(string name);
    void showHyperBeamEffect(string name);
    void showOutrageEffect(string name);
    void showRolloutEffect(string name);
    void showSkullBashEffect(string name);
    void showFutureSightEffect(string name);
    void showWinner(string message);
    void drawBattleScreen(string player1, string p1PokemonName, int p1HP, int p1MaxHP,
                          string player2, string p2PokemonName, int p2HP, int p2MaxHP,
                          string message = "");
    void drawHPBar(int x, int y, int width, int height, int hp, int maxHP);
    void waitForWindowClose();
};

#endif // GAMEUI_H