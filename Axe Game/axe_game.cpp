#include "raylib.h"

int main()
{
    // window dimensions
    int width = 800, height = 450;
    InitWindow(width, height, "My Window");

    // Circle Coridnate
    int circle_x{width / 2}, circle_y{height / 2}, circle_radious = 25;

    // Circle edges
    int l_circle_x{circle_x - circle_radious};
    int r_circle_x{circle_x + circle_radious};
    int u_circle_y{circle_y - circle_radious};
    int b_circle_y{circle_y + circle_radious};

    // Axe Coordinates
    int axe_x{400}, axe_y{0}, direction{5}, axe_lenght{50};

    // Axe edges
    int l_axe_x{axe_x};
    int r_axe_x{axe_x + axe_lenght};
    int u_axe_y{axe_y};
    int b_axe_y{axe_y + axe_lenght};

    bool collision_with_axe = (b_axe_y >= u_circle_y) &&
                              (u_axe_y <= b_circle_y) &&
                              (l_axe_x <= r_circle_x) &&
                              (r_axe_x >= l_circle_x);

    SetTargetFPS(60);
    while (WindowShouldClose() != true)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (collision_with_axe)
        {
            DrawText("Game Over!", 400, 200, 20, RED);
        }
        else
        {
            // Game logic begins

            // Update the Edges
            l_circle_x = circle_x - circle_radious;
            r_circle_x = circle_x + circle_radious;
            u_circle_y = circle_y - circle_radious;
            b_circle_y = circle_y + circle_radious;

            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_lenght;
            u_axe_y = axe_y;
            b_axe_y = axe_y + axe_lenght;

            // Update collision_with_axe
            collision_with_axe = (b_axe_y >= u_circle_y) &&
                                 (u_axe_y <= b_circle_y) &&
                                 (l_axe_x <= r_circle_x) &&
                                 (r_axe_x >= l_circle_x);

            DrawCircle(circle_x, circle_y, circle_radious, BLUE);
            DrawRectangle(axe_x, axe_y, axe_lenght, axe_lenght, RED);

            // move the axe
            axe_y += direction;
            if (axe_y > height - 50 || axe_y < 0)
            {
                direction = -direction;
            }

            if (IsKeyDown(KEY_D) && circle_x < width - circle_radious)
            {
                circle_x += 10;
            }

            if (IsKeyDown(KEY_A) && circle_x > 0 + circle_radious)
            {
                circle_x -= 10;
            }

            // Game logic ends
        }

        EndDrawing();
    }
    return 0;
}