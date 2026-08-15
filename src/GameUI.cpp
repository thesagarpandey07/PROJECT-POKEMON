#include "GameUI.h"

string GameUI::findPokemonImagePath(const string& pokemonName)
{
    static const unordered_map<string, string> imageFiles =
    {
        {"Alakazam",  "../graphics/Alakazam.png"},
        {"Arcanine",  "../graphics/Arcanine.png"},
        {"Blastoise", "../graphics/Blastoise.png"},
        {"Charizard", "../graphics/Charizard.png"},
        {"Dragonite", "../graphics/Dragonite.png"},
        {"Espeon",    "../graphics/Espeon.png"},
        {"Flareon",   "../graphics/Flareon.png"},
        {"Gengar",    "../graphics/Gengar.png"},
        {"Golem",     "../graphics/Golem.png"},
        {"Gyarados",  "../graphics/Gyarados.png"},
        {"Jolteon",   "../graphics/Jolteon.png"},
        {"Lapras",    "../graphics/Lapras.png"},
        {"Leafeon",   "../graphics/Leafeon.png"},
        {"Machamp",   "../graphics/Machamp.png"},
        {"Ninetales", "../graphics/Ninetales.png"},
        {"Pikachu",   "../graphics/Pikachu.png"},
        {"Snorlax",   "../graphics/Snorlax.png"},
        {"Umbreon",   "../graphics/Umbreon.png"},
        {"Vaporeon",  "../graphics/Vaporeon.png"},
        {"Venusaur",  "../graphics/Venusaur.png"}
    };

    auto it = imageFiles.find(pokemonName);

    if (it == imageFiles.end())
        return "";

    string path = it->second;

    if (FileExists(path.c_str()))
        return path;

    return "";
}

Texture2D* GameUI::getPokemonTexture(const string& pokemonName)
{
    if (pokemonName.empty())
        return nullptr;

    auto cached = pokemonTextures.find(pokemonName);
    if (cached != pokemonTextures.end())
    {
        if (IsTextureValid(cached->second))
            return &cached->second;

        return nullptr;
    }

    string path = findPokemonImagePath(pokemonName);

    if (path.empty())
        return nullptr;

    Texture2D texture = LoadTexture(path.c_str());

    if (!IsTextureValid(texture))
        return nullptr;

    pokemonTextures[pokemonName] = texture;
    pokemonTexturePaths[pokemonName] = path;

    return &pokemonTextures[pokemonName];
}

void GameUI::drawPokemonImage(const string& pokemonName, Rectangle destination, bool flipHorizontal)
{
    Texture2D* texture = getPokemonTexture(pokemonName);

    if (texture == nullptr)
        return;

    Rectangle source{
        flipHorizontal ? (float)texture->width : 0.0f,
        0.0f,
        flipHorizontal ? -(float)texture->width : (float)texture->width,
        (float)texture->height
    };

    DrawTexturePro(
        *texture,
        source,
        destination,
        Vector2{0, 0},
        0.0f,
        WHITE
    );
}

void GameUI::unloadPokemonTextures()
{
    for (auto& entry : pokemonTextures)
    {
        if (IsTextureValid(entry.second))
            UnloadTexture(entry.second);
    }

    pokemonTextures.clear();
    pokemonTexturePaths.clear();
}

void GameUI::drawButton(Rectangle r, const string& text, bool disabled)
{
    Color fill = disabled ? Color{70, 75, 85, 255} : Color{42, 54, 78, 255};
    DrawRectangleRec(r, fill);
    DrawRectangleLinesEx(r, 2, Color{18, 22, 32, 255});
    int textWidth = MeasureText(text.c_str(), 20);      
    DrawText(text.c_str(), (int)(r.x + (r.width - textWidth) / 2),(int)(r.y + (r.height - 20) / 2), 20, WHITE);
}

void GameUI::initGraphics()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pokemon Battle Arena");
    SetTargetFPS(60);
}

bool GameUI::windowOpen()
{
    return IsWindowReady() && !WindowShouldClose();
}

void GameUI::closeGraphics()
{
    unloadPokemonTextures();

    if (IsWindowReady())
        CloseWindow();
}

void GameUI::showFileError()
{
    showMessage("Error opening pokemon.txt or Type_Multiplier.txt");
}

void GameUI::showMessage(const string& message, float)
{
    if (!IsWindowReady() || WindowShouldClose()) return;

    BeginDrawing();
    drawScene();

    DrawRectangle(180, 245, 640, 95, Color{30, 39, 55, 248});
    DrawRectangleLinesEx(Rectangle{180, 245, 640, 95}, 3, Color{90, 115, 145, 255});
    DrawText(message.c_str(), 215, 280, 20, Color{225, 230, 238, 255});

    EndDrawing();

    WaitTime(0.65);
}

void GameUI::showGameIntro()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{20, 28, 45, 255});

        DrawCircle(500, 55, 27, Color{205, 60, 70, 255});
        DrawRectangle(473, 52, 54, 7, Color{235, 238, 244, 255});
        DrawCircle(500, 55, 9, Color{235, 238, 244, 255});
        DrawCircleLines(500, 55, 27, Color{12, 17, 27, 255});
        DrawCircleLines(500, 55, 8, Color{12, 17, 27, 255});

        DrawText("POKEMON", 330, 70, 55, Color{245, 247, 250, 255});
        DrawText("BATTLE ARENA", 275, 135, 45, Color{255, 190, 55, 255});

        DrawRectangle(180, 235, 640, 190, Color{35, 43, 58, 250});
        DrawRectangleLinesEx(Rectangle{180, 235, 640, 190}, 3, Color{95, 112, 140, 255});

        DrawText("2 Players", 400, 265, 25, Color{100, 180, 245, 255});
        DrawText("Each player receives 3 random Pokemon", 270, 310, 20, Color{220, 225, 235, 255});
        DrawText("Choose moves and switch Pokemon", 300, 345, 20, Color{220, 225, 235, 255});
        DrawText("Use type advantages to win", 330, 380, 20, Color{220, 225, 235, 255});

        drawButton(Rectangle{365, 470, 270, 60}, "START GAME");

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouse = GetMousePosition();
            Rectangle button{365, 470, 270, 60};

            if (CheckCollisionPointRec(mouse, button))
                break;
        }
    }
}

void GameUI::displayPokemonDetails(
    int id, string name, string type, int hp, int attack, int defense, int speed,
    string move1, string move1Type, int power1, int pp1,
    string move2, string move2Type, int power2, int pp2,
    string move3, string move3Type, int power3, int pp3,
    string move4, string move4Type, int power4, int pp4)
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{22, 29, 43, 255});

        DrawText(("Pokemon #" + to_string(id) + " - " + name).c_str(),
                 40, 30, 30, Color{100, 190, 245, 255});

        DrawText(("Type: " + type).c_str(), 40, 75, 20, Color{225, 230, 238, 255});
        DrawText(("HP: " + to_string(hp)).c_str(), 40, 110, 20, Color{225, 230, 238, 255});
        DrawText(("Attack: " + to_string(attack)).c_str(), 40, 145, 20, Color{225, 230, 238, 255});
        DrawText(("Defense: " + to_string(defense)).c_str(), 260, 110, 20, Color{225, 230, 238, 255});
        DrawText(("Speed: " + to_string(speed)).c_str(), 260, 145, 20, Color{225, 230, 238, 255});

        DrawText("MOVES", 40, 200, 25, Color{100, 190, 245, 255});

        string moves[4] = {
            "1. " + move1 + " [" + move1Type + "] Power:" + to_string(power1) + " PP:" + to_string(pp1),
            "2. " + move2 + " [" + move2Type + "] Power:" + to_string(power2) + " PP:" + to_string(pp2),
            "3. " + move3 + " [" + move3Type + "] Power:" + to_string(power3) + " PP:" + to_string(pp3),
            "4. " + move4 + " [" + move4Type + "] Power:" + to_string(power4) + " PP:" + to_string(pp4)
        };

        for (int i = 0; i < 4; ++i)
            DrawText(moves[i].c_str(), 50, 245 + i * 45, 18, Color{220, 225, 235, 255});

        drawButton(Rectangle{390, 520, 220, 55}, "CONTINUE");

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, Rectangle{390, 520, 220, 55}))
                break;
        }
    }
}

int GameUI::promptMoveSelection(
    const string& playerName,
    const string& pokemonName,
    int hp,
    int maxHP,
    const string moves[4],
    const int pp[4],
    const string& opponentPlayer,
    const string& opponentPokemon,
    int opponentHP,
    int opponentMaxHP)
{
    bool player1Turn = (playerName == "Player 1");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        drawScene();
        drawBattlePokemonSprites(
            player1Turn ? playerName : opponentPlayer,
            player1Turn ? pokemonName : opponentPokemon,
            player1Turn ? opponentPlayer : playerName,
            player1Turn ? opponentPokemon : pokemonName
        );

        drawBattleHUD(
            player1Turn ? playerName : opponentPlayer,
            player1Turn ? pokemonName : opponentPokemon,
            player1Turn ? hp : opponentHP,
            player1Turn ? maxHP : opponentMaxHP,
            player1Turn ? opponentPlayer : playerName,
            player1Turn ? opponentPokemon : pokemonName,
            player1Turn ? opponentHP : hp,
            player1Turn ? opponentMaxHP : maxHP
        );

        DrawRectangle(25, 515, 950, 170, Color{24, 31, 46, 248});
        DrawRectangleLinesEx(Rectangle{25, 515, 950, 170}, 3, Color{72, 105, 145, 255});

        string title = playerName + " - " + pokemonName + "'s turn";
        DrawText(title.c_str(), 35, 523, 19, Color{105, 195, 245, 255});
        DrawText("Choose an attack", 35, 548, 14, Color{155, 165, 180, 255});

        for (int i = 0; i < 4; ++i)
        {
            Rectangle r{
                35.0f + (i % 2) * 475.0f,
                570.0f + (i / 2) * 38.0f,
                445.0f,
                32.0f
            };

            bool disabled = pp[i] <= 0;
            bool hovered = CheckCollisionPointRec(GetMousePosition(), r);

            Color fill = disabled ? Color{60, 65, 75, 255}
                                  : (hovered ? Color{67, 91, 125, 255}
                                             : Color{40, 50, 68, 255});

            DrawRectangleRec(r, fill);
            DrawRectangleLinesEx(r, 2, Color{88, 120, 160, 255});

            string text = to_string(i + 1) + ". " + moves[i] +
                          "   PP: " + to_string(pp[i]);

            DrawText(text.c_str(), (int)r.x + 12, (int)r.y + 7, 14,
                     disabled ? Color{125, 130, 140, 255} : Color{230, 235, 242, 255});
        }

        Rectangle switchButton{390, 650, 220, 30};
        bool switchHover = CheckCollisionPointRec(GetMousePosition(), switchButton);

        DrawRectangleRec(
            switchButton,
            switchHover ? Color{210, 125, 55, 255}
                        : Color{48, 83, 125, 255}
        );
        DrawRectangleLinesEx(switchButton, 2, Color{15, 20, 30, 255});
        int switchTextWidth = MeasureText("SWITCH POKEMON", 14);
        DrawText("SWITCH POKEMON",
                 (int)(switchButton.x + (switchButton.width - switchTextWidth) / 2),
                 (int)(switchButton.y + (switchButton.height - 14) / 2),
                 14, WHITE);

        EndDrawing();

        int selectedMove = -1;

        if (IsKeyPressed(KEY_ONE) && pp[0] > 0) selectedMove = 1;
        if (IsKeyPressed(KEY_TWO) && pp[1] > 0) selectedMove = 2;
        if (IsKeyPressed(KEY_THREE) && pp[2] > 0) selectedMove = 3;
        if (IsKeyPressed(KEY_FOUR) && pp[3] > 0) selectedMove = 4;

        if (IsKeyPressed(KEY_S))
            return 0;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouse = GetMousePosition();

            for (int i = 0; i < 4; ++i)
            {
                Rectangle r{
                    35.0f + (i % 2) * 475.0f,
                    570.0f + (i / 2) * 38.0f,
                    445.0f,
                    32.0f
                };

                if (CheckCollisionPointRec(mouse, r) && pp[i] > 0)
                {
                    selectedMove = i + 1;
                    break;
                }
            }

            if (CheckCollisionPointRec(mouse, switchButton))
                return 0;
        }

        if (selectedMove != -1)
        {
            drawAttackAnimation(
                player1Turn ? playerName : opponentPlayer,
                player1Turn ? pokemonName : opponentPokemon,
                player1Turn ? hp : opponentHP,
                player1Turn ? maxHP : opponentMaxHP,
                player1Turn ? opponentPlayer : playerName,
                player1Turn ? opponentPokemon : pokemonName,
                player1Turn ? opponentHP : hp,
                player1Turn ? opponentMaxHP : maxHP,
                player1Turn,
                moves[selectedMove - 1]
            );

            return selectedMove;
        }
    }

    return -1;
}

int GameUI::promptSwitchChoice(const string names[3], const int hps[3])
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{21, 28, 42, 255});

        DrawText("SWITCH POKEMON", 330, 35, 30, Color{100, 190, 245, 255});

        for (int i = 0; i < 3; ++i)
        {
            Rectangle r{100 + i * 300.0f, 130, 250, 260};

            bool fainted = hps[i] <= 0;
            DrawRectangleRec(r, fainted ? Color{48, 52, 60, 255} : Color{35, 44, 60, 255});
            DrawRectangleLinesEx(r, 3, fainted ? Color{85, 88, 95, 255} : Color{80, 115, 155, 255});

            DrawText((to_string(i + 1) + ". " + names[i]).c_str(),
                     (int)r.x + 15, (int)r.y + 25, 21,
                     fainted ? Color{120, 125, 135, 255} : Color{230, 235, 242, 255});

            DrawText(("HP: " + to_string(hps[i])).c_str(),
                     (int)r.x + 15, (int)r.y + 75, 18,
                     fainted ? Color{120, 125, 135, 255} : Color{105, 205, 125, 255});

            if (fainted)
                DrawText("FAINTED", (int)r.x + 60, (int)r.y + 130, 22, RED);
            else
                DrawText("CLICK TO SELECT", (int)r.x + 30, (int)r.y + 170, 16, DARKGRAY);
        }

        DrawText("Press 1, 2 or 3, or click a Pokemon",
                 315, 540, 18, Color{160, 170, 185, 255});

        EndDrawing();

        if (IsKeyPressed(KEY_ONE) && hps[0] > 0) return 0;
        if (IsKeyPressed(KEY_TWO) && hps[1] > 0) return 1;
        if (IsKeyPressed(KEY_THREE) && hps[2] > 0) return 2;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouse = GetMousePosition();

            for (int i = 0; i < 3; ++i)
            {
                Rectangle r{100 + i * 300.0f, 130, 250, 260};

                if (CheckCollisionPointRec(mouse, r) && hps[i] > 0)
                    return i;
            }
        }
    }

    return 0;
}

void GameUI::drawScene()
{
    DrawRectangle(0, 0, SCREEN_WIDTH, 650, Color{190, 225, 245, 255});
    DrawRectangle(0, 0, SCREEN_WIDTH, 145, Color{125, 190, 235, 255});

    DrawCircle(820, 82, 48, Color{255, 225, 135, 255});
    DrawCircle(820, 82, 68, Color{255, 225, 135, 45});

    DrawCircle(115, 88, 25, Color{250, 252, 255, 230});
    DrawCircle(145, 75, 36, Color{255, 255, 255, 240});
    DrawCircle(180, 88, 27, Color{248, 251, 255, 230});

    DrawCircle(600, 80, 22, Color{250, 252, 255, 215});
    DrawCircle(630, 66, 34, Color{255, 255, 255, 230});
    DrawCircle(666, 82, 25, Color{248, 251, 255, 215});

    DrawRectangle(0, 190, SCREEN_WIDTH, 95, Color{220, 228, 238, 255});
    DrawRectangle(0, 175, SCREEN_WIDTH, 18, Color{86, 120, 155, 255});

    for (int x = 20; x < SCREEN_WIDTH; x += 110)
    {
        DrawRectangle(x, 190, 70, 60, Color{185, 198, 214, 255});
        DrawRectangle(x + 10, 200, 50, 40, Color{150, 177, 202, 255});
    }

    for (int x = 55; x < SCREEN_WIDTH; x += 180)
    {
        DrawRectangle(x, 215, 42, 48, Color{245, 105, 105, 255});
        DrawTriangle(
            {(float)x, 263},
            {(float)x + 21, 250},
            {(float)x + 42, 263},
            Color{245, 105, 105, 255}
        );

        DrawCircle(x + 21, 228, 10, Color{255, 235, 130, 255});
        DrawCircleLines(x + 21, 228, 10, Color{255, 255, 255, 220});
    }

    DrawRectangle(0, 265, SCREEN_WIDTH, 34, Color{170, 188, 207, 255});
    DrawRectangle(0, 299, SCREEN_WIDTH, 18, Color{125, 150, 177, 255});

    DrawRectangle(0, 317, SCREEN_WIDTH, SCREEN_HEIGHT - 317,
                  Color{232, 225, 195, 255});

    DrawRectangle(0, 317, SCREEN_WIDTH, 12, Color{205, 195, 160, 255});
    DrawRectangle(0, 470, SCREEN_WIDTH, 10, Color{218, 207, 173, 255});

    DrawEllipse(500, 455, 355, 150, Color{242, 236, 212, 255});
    DrawEllipseLines(500, 455, 355, 150, Color{155, 145, 120, 255});

    DrawLine(145, 455, 855, 455, Color{175, 163, 135, 255});

    DrawCircle(500, 455, 48, Color{250, 250, 247, 255});
    DrawCircleLines(500, 455, 48, Color{135, 130, 120, 255});

    DrawRectangle(452, 451, 96, 8, Color{135, 130, 120, 255});

    DrawCircle(500, 455, 17, Color{255, 255, 255, 255});
    DrawCircleLines(500, 455, 17, Color{110, 105, 95, 255});

    DrawEllipse(250, 355, 150, 48, Color{166, 205, 174, 255});
    DrawEllipseLines(250, 355, 150, 48, Color{92, 145, 107, 255});

    DrawEllipse(750, 475, 170, 55, Color{166, 205, 174, 255});
    DrawEllipseLines(750, 475, 170, 55, Color{92, 145, 107, 255});

    for (int x = 80; x <= 920; x += 120)
    {
        DrawCircle(x, 575, 5, Color{190, 179, 150, 140});
        DrawCircle(x, 575, 2, Color{255, 255, 255, 190});
    }
}

void GameUI::drawPokemonBox(Rectangle r, Color mainColor, string label, string playerLabel,
                    int hp, int maxHP, bool enemySide)
{
    DrawRectangle((int)r.x + 5, (int)r.y + 6, (int)r.width, (int)r.height,
                  Color{0, 0, 0, 85});

    DrawRectangleRec(r, Color{29, 38, 54, 248});
    DrawRectangleLinesEx(r, 4, mainColor);

    DrawRectangle((int)r.x, (int)r.y, (int)r.width, 32, mainColor);
    DrawText(playerLabel.c_str(), (int)r.x + 12, (int)r.y + 6, 17, Color{245, 247, 250, 255});

    int textX = (int)r.x + 18;

    DrawText(label.c_str(), textX, (int)r.y + 42, 20, Color{235, 239, 245, 255});

    if (maxHP <= 0) maxHP = 1;

    float ratio = (float)hp / (float)maxHP;
    if (ratio < 0.0f) ratio = 0.0f;
    if (ratio > 1.0f) ratio = 1.0f;

    Color hpColor = Color{70, 190, 105, 255};
    if (ratio < 0.5f) hpColor = Color{225, 165, 70, 255};
    if (ratio < 0.2f) hpColor = Color{215, 75, 80, 255};

    Rectangle hpBar{
        (float)textX,
        r.y + 72.0f,
        245.0f,
        14.0f
    };

    DrawText("HP", textX, (int)r.y + 63, 12, DARKGRAY);

    DrawRectangleRec(hpBar, Color{62, 70, 82, 255});
    DrawRectangle(hpBar.x, hpBar.y,
                  hpBar.width * ratio, hpBar.height, hpColor);
    DrawRectangleLinesEx(hpBar, 2, Color{15, 20, 28, 255});

    DrawText(TextFormat("%d / %d", hp, maxHP),
             textX + 250, (int)r.y + 72, 12, Color{155, 165, 180, 255});
}

void GameUI::drawBattlePokemonSprites(string player1, string p1PokemonName,
                               string player2, string p2PokemonName)
{
    Texture2D* opponentTexture = getPokemonTexture(p2PokemonName);

    if (opponentTexture != nullptr)
    {
        Rectangle destination{
            35.0f, 155.0f, 300.0f, 200.0f
        };

        drawPokemonImage(p2PokemonName, destination, false);
    }
    else
    {
        DrawRectangle(55, 195, 245, 140, Color{174, 60, 70, 255});
        DrawRectangleLinesEx(Rectangle{55, 195, 245, 140}, 3, BLACK);
        DrawText(p2PokemonName.c_str(), 85, 250, 20, WHITE);
    }

    Texture2D* playerTexture = getPokemonTexture(p1PokemonName);

    if (playerTexture != nullptr)
    {
        Rectangle destination{
            650.0f, 195.0f, 290.0f, 195.0f
        };

        drawPokemonImage(p1PokemonName, destination, true);
    }
    else
    {
        DrawRectangle(680, 225, 235, 135, Color{58, 105, 165, 255});
        DrawRectangleLinesEx(Rectangle{680, 225, 235, 135}, 3, BLACK);
        DrawText(p1PokemonName.c_str(), 710, 280, 20, WHITE);
    }
}

void GameUI::drawBattleHUD(string player1, string p1PokemonName, int p1HP, int p1MaxHP,
                   string player2, string p2PokemonName, int p2HP, int p2MaxHP)
{
    drawPokemonBox(
        Rectangle{15, 15, 360, 120},
        Color{174, 60, 70, 255},
        p2PokemonName, player2, p2HP, p2MaxHP, true
    );

    drawPokemonBox(
        Rectangle{615, 395, 360, 105},
        Color{58, 105, 165, 255},
        p1PokemonName, player1, p1HP, p1MaxHP, false
    );
}

void GameUI::drawAttackAnimation(
    string player1, string p1Pokemon, int p1HP, int p1MaxHP,
    string player2, string p2Pokemon, int p2HP, int p2MaxHP,
    bool player1Attacking, string moveName)
{
    const double animationTime = 0.85;
    double start = GetTime();

    while (!WindowShouldClose())
    {
        double elapsed = GetTime() - start;
        if (elapsed >= animationTime) break;

        float progress = (float)(elapsed / animationTime);

        BeginDrawing();
        drawScene();
        drawBattlePokemonSprites(player1, p1Pokemon, player2, p2Pokemon);
        drawBattleHUD(player1, p1Pokemon, p1HP, p1MaxHP,
                      player2, p2Pokemon, p2HP, p2MaxHP);

        Vector2 startPos = player1Attacking
            ? Vector2{820, 435}
            : Vector2{180, 200};

        Vector2 endPos = player1Attacking
            ? Vector2{180, 200}
            : Vector2{820, 435};

        float x = startPos.x + (endPos.x - startPos.x) * progress;
        float y = startPos.y + (endPos.y - startPos.y) * progress;

        DrawCircle(x, y, 14, Color{255, 245, 80, 255});
        DrawCircleLines(x, y, 24, Color{255, 130, 40, 255});

        if (progress > 0.68f)
        {
            float flash = (progress - 0.68f) / 0.32f;
            DrawCircle(endPos.x, endPos.y,
                       65.0f * flash,
                       Color{255, 80, 60, 120});
        }

        DrawRectangle(220, 565, 560, 62, Color{24, 31, 45, 248});
        DrawRectangleLinesEx(Rectangle{220, 565, 560, 62}, 3, Color{80, 105, 135, 255});

        string action = (player1Attacking ? player1 : player2) +
                        "'s " +
                        (player1Attacking ? p1Pokemon : p2Pokemon) +
                        " used " + moveName + "!";

        DrawText(action.c_str(), 250, 585, 19, Color{235, 239, 245, 255});

        EndDrawing();
    }
}

void GameUI::displayBattleDetails(string player1, string p1Name, int p1HP,
                          string player2, string p2Name, int p2HP)
{
    drawBattleScreen(player1, p1Name, p1HP, p1HP,
                     player2, p2Name, p2HP, p2HP);
}

void GameUI::displayAttackUsed(string pokemonName, string attackName)
{
    showMessage(pokemonName + " used " + attackName);
}

void GameUI::displayFainted(string pokemonName)
{
    showMessage(pokemonName + " fainted!", 1.5f);
}

void GameUI::showFaintedRetry()
{
    showMessage("That Pokemon has fainted. Choose another.");
}

void GameUI::showNoPPLeft()
{
    showMessage("No PP left for that move!");
}

void GameUI::displayPlayerTurn(string player, string pokemonName)
{
    showMessage(player + ": " + pokemonName + "'s turn", 0.6f);
}

void GameUI::displayPokemonStatus(string names[3], int hps[3])
{
    promptSwitchChoice(names, hps);
}

void GameUI::displayPlayerPokemonHeader(string) {}
void GameUI::displayGivenPokemon(int, string) {}
void GameUI::displayGivenPokemonListEnd() {}

void GameUI::showHypnosisEffect(string name)
{
    showMessage(name + " fell asleep! Speed decreased.");
}

void GameUI::showRecoverEffect(string name)
{
    showMessage(name + " recovered 70 HP!");
}

void GameUI::showConfuseRayEffect(string name)
{
    showMessage(name + " became confused! Attack decreased.");
}

void GameUI::showDragonDanceEffect(string name)
{
    showMessage(name + "'s Attack and Speed increased!");
}

void GameUI::showRestEffect(string name)
{
    showMessage(name + " rested and recovered HP.");
}

void GameUI::showMoonlightEffect(string name)
{
    showMessage(name + " restored HP using Moonlight!");
}

void GameUI::showSwordsDanceEffect(string name)
{
    showMessage(name + "'s Attack sharply rose!");
}

void GameUI::showSolarBeamEffect(string name)
{
    showMessage(name + " is charging Solar Beam.");
}

void GameUI::showHyperBeamEffect(string name)
{
    showMessage(name + " used Hyper Beam and must recharge.");
}

void GameUI::showOutrageEffect(string name)
{
    showMessage(name + " went into an Outrage!");
}

void GameUI::showRolloutEffect(string name)
{
    showMessage(name + " started Rollout!");
}

void GameUI::showSkullBashEffect(string name)
{
    showMessage(name + " is charging Skull Bash.");
}

void GameUI::showFutureSightEffect(string name)
{
    showMessage(name + " will not attack for 2 turns.");
}

void GameUI::showWinner(string message)
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{20, 28, 45, 255});

        DrawCircle(500, 75, 30, Color{205, 60, 70, 255});
        DrawRectangle(470, 71, 60, 8, Color{235, 238, 244, 255});
        DrawCircle(500, 75, 10, Color{235, 238, 244, 255});
        DrawCircleLines(500, 75, 30, Color{12, 17, 27, 255});
        DrawCircleLines(500, 75, 9, Color{12, 17, 27, 255});

        DrawText("BATTLE OVER", 350, 120, 40, Color{245, 247, 250, 255});
        DrawText(message.c_str(), 280, 230, 30, Color{255, 190, 55, 255});

        drawButton(Rectangle{350, 350, 300, 65}, "CLOSE GAME");

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, Rectangle{350, 350, 300, 65}))
                break;
        }
    }
}

void GameUI::drawBattleScreen(string player1, string p1PokemonName, int p1HP, int p1MaxHP,
                      string player2, string p2PokemonName, int p2HP, int p2MaxHP,
                      string message)
{
    if (!IsWindowReady() || WindowShouldClose()) return;

    BeginDrawing();
    drawScene();
    drawBattlePokemonSprites(player1, p1PokemonName, player2, p2PokemonName);
    drawBattleHUD(player1, p1PokemonName, p1HP, p1MaxHP,
                  player2, p2PokemonName, p2HP, p2MaxHP);

    DrawRectangle(235, 565, 530, 62, Color{24, 31, 45, 248});
    DrawRectangleLinesEx(Rectangle{235, 565, 530, 62}, 3, Color{80, 105, 135, 255});

    if (!message.empty())
        DrawText(message.c_str(), 265, 585, 19, Color{235, 239, 245, 255});
    else
        DrawText("Choose a move or press S to switch Pokemon.",
                 285, 585, 16, DARKGRAY);

    EndDrawing();
}

void GameUI::drawHPBar(int x, int y, int width, int height, int hp, int maxHP)
{
    if (maxHP <= 0) maxHP = 1;

    float ratio = (float)hp / (float)maxHP;
    if (ratio < 0.0f) ratio = 0.0f;
    if (ratio > 1.0f) ratio = 1.0f;

    Color color = GREEN;
    if (ratio < 0.5f) color = ORANGE;
    if (ratio < 0.2f) color = RED;

    DrawRectangle(x, y, width, height, LIGHTGRAY);
    DrawRectangle(x, y, (int)(width * ratio), height, color);
    DrawRectangleLines(x, y, width, height, BLACK);
}

void GameUI::waitForWindowClose()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{22, 29, 43, 255});
        DrawText("Press the window X to close.", 350, 300, 20, DARKGRAY);
        EndDrawing();
    }

    if (IsWindowReady())
        CloseWindow();
}