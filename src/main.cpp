#include <raylib.h>
#include <string>

int main() 
{
    constexpr int screenWidth = 640;
    constexpr int screenHeight = 480;
    
    InitWindow(screenWidth, screenHeight, "RPG Writer");
    InitAudioDevice();
    SetTargetFPS(30);


    Texture2D fightButton = LoadTexture("assets/images/ui/bt/fight.png");
    Texture2D actButton = LoadTexture("assets/images/ui/bt/act.png");
    Texture2D itemButton = LoadTexture("assets/images/ui/bt/item.png");
    Texture2D mercyButton = LoadTexture("assets/images/ui/bt/mercy.png");
    Texture2D hpName = LoadTexture("assets/images/ui/spr_hpname_0.png");
    Font uiFont = LoadFont("assets/fonts/Mars_Needs_Cunnilingus.ttf");
    Texture2D playerImage = LoadTexture("assets/images/ut-heart.png");
    Sound moveSound = LoadSound("assets/sound/sfx/menumove.wav");

    Vector2 player = {0, 446};
    int buttonOn = 0;
    std::string battleState = "buttons";

    const Vector2 buttonPositions[] = {
        {32, 432}, {185, 432}, {345, 432}, {500, 432}
    };

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

            DrawTextEx(uiFont, "Chara   LV 1", (Vector2){30, 400}, 24, 0, WHITE);

            for (int i = 0; i < 4; ++i) {
                DrawTextureRec(buttons[i], 
                               (Rectangle){110.0f * (buttonOn == i), 0.0f, 110.0f, 42.0f}, 
                               buttonPositions[i], 
                               WHITE);
            }

            DrawTexture(hpName, 240, 400, WHITE);
            DrawTexture(playerImage, player.x, player.y, {255, 0, 0, 255});
        EndDrawing();
    }
    
    UnloadTexture(fightButton);
    UnloadTexture(actButton);
    UnloadTexture(itemButton);
    UnloadTexture(mercyButton);
    UnloadTexture(hpName);
    UnloadTexture(playerImage);
    UnloadFont(uiFont);
    UnloadSound(moveSound);
    
    CloseWindow();
}