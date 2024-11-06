#include <raylib.h>
#include <string>

int main() 
{
    constexpr int screenWidth = 640;
    constexpr int screenHeight = 480;
    InitWindow(screenWidth, screenHeight, "raylib undertale");
    InitAudioDevice();
    SetTargetFPS(30);


    Texture2D fightButton = LoadTexture("assets/images/ui/bt/fight.png");
    Texture2D actButton = LoadTexture("assets/images/ui/bt/act.png");
    Texture2D itemButton = LoadTexture("assets/images/ui/bt/item.png");
    Texture2D mercyButton = LoadTexture("assets/images/ui/bt/mercy.png");
    Texture2D referenceImage = LoadTexture("assets/images/refs/main.png");
    Texture2D hpName = LoadTexture("assets/images/ui/spr_hpname_0.png");
    Font uiFont = LoadFont("assets/fonts/Mars_Needs_Cunnilingus.ttf");
    Font determination = LoadFont("assets/fonts/determination-mono.ttf");
    Texture2D playerImage = LoadTexture("assets/images/ut-heart.png");
    Sound moveSound = LoadSound("assets/sound/sfx/menumove.wav");

    Vector2 player = {0, 446};
    int buttonOn = 0;
    std::string battleState = "buttons";

    const Vector2 buttonPositions[] = {
        {32, 432}, {185, 432}, {345, 432}, {500, 432}
    };

    struct ArenaParams {
        int x = 32;
        int y = 250;
        int w = 575;
        int h = 140;
    };

    struct PlayerStats {
        int hp = 20.0f;
        int maxhp = 20.0f;
        std::string name = "Chara";
    };

    ArenaParams arena;
    PlayerStats playerStats;

    Texture2D buttons[] = {fightButton, actButton, itemButton, mercyButton};

    while (!WindowShouldClose())
    {
        if(battleState == "buttons") {
            if (IsKeyPressed(KEY_RIGHT)) {
                buttonOn = (buttonOn + 1) % 4;
                PlaySound(moveSound);
            }
            if (IsKeyPressed(KEY_LEFT)) {
                buttonOn = (buttonOn + 3) % 4;
                PlaySound(moveSound);
            }
            
            player.x = buttonPositions[buttonOn].x + 8;
            player.y = 446;
        }

        BeginDrawing();

            ClearBackground(BLACK);
            
            DrawTexture(referenceImage, 0, 0, {255, 255, 255, 0});
            
            DrawTextEx(uiFont, (playerStats.name + "   LV 1").c_str(), (Vector2){30, 400}, 24, 0, WHITE);
            if(playerStats.hp<10) {
                DrawTextEx(uiFont, ("0" + std::to_string(playerStats.hp) + " / " + std::to_string(playerStats.maxhp)).c_str(), (Vector2){290.0f + (playerStats.maxhp * 1.2), 400}, 24, 0, WHITE);
            }
            else {
                DrawTextEx(uiFont, (std::to_string(playerStats.hp) + " / " + std::to_string(playerStats.maxhp)).c_str(), (Vector2){290.0f + (playerStats.maxhp * 1.2), 400}, 24, 0, WHITE);
            }
           

            for (int i = 0; i < 4; ++i) {
                DrawTextureRec(buttons[i], 
                               (Rectangle){110.0f * (buttonOn == i), 0.0f, 110.0f, 42.0f}, 
                               buttonPositions[i], 
                               WHITE);
            }

            DrawTexture(hpName, 240, 400, WHITE);

            DrawRectangle(arena.x, arena.y, arena.w, arena.h, WHITE);
            DrawRectangle(arena.x + 5, arena.y + 5, arena.w - 10, arena.h - 10, BLACK);
            DrawRectangle(275.0f, 400.0f, playerStats.maxhp * 1.2, 21.0f, {200, 0, 0, 255});
            DrawRectangle(275.0f, 400.0f, playerStats.hp * 1.2, 21.0f, YELLOW);

            DrawTextEx(determination, "* The fact that the text looks\n\n  horrible makes me very angry.", (Vector2){52, 274}, 28, 0, WHITE);

            DrawTexture(playerImage, player.x, player.y, {255, 0, 0, 255});

        EndDrawing();
    }
    
    UnloadTexture(fightButton);
    UnloadTexture(actButton);
    UnloadTexture(itemButton);
    UnloadTexture(mercyButton);
    UnloadTexture(hpName);
    UnloadTexture(playerImage);
    UnloadTexture(referenceImage);
    UnloadFont(uiFont);
    UnloadFont(determination);
    UnloadSound(moveSound);
    
    CloseWindow();
}
