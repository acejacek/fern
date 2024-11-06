/*
 * https://github.com/acejacek/fern
 */

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#define WIDTH 900
#define HEIGHT 900

Vector2 f1(Vector2* p)
{
    return (Vector2){0.00f,
                     0.16f * p->y};
}

Vector2 f2(Vector2* p)
{
    return (Vector2){ 0.85f * p->x + 0.04f * p->y,
                     -0.04f * p->x + 0.85f * p->y + 1.60f};
}

Vector2 f3(Vector2* p)
{
    return (Vector2){0.20f * p->x - 0.26f * p->y,
                     0.23f * p->x + 0.22f * p->y + 1.60f};
}

Vector2 f4(Vector2* p)
{
    return (Vector2){-0.15f * p->x + 0.28f * p->y,
                      0.26f * p->x + 0.24f * p->y + 0.44f};
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Barnsley Fern");
    SetTargetFPS(60);
    Vector2 point = {0.0f, 0.0f};  // coords in fern space
    Vector2 pixel;                 // coords in screen space

    Vector2 (*transformate[])(Vector2*) = { f1, f2, f3, f4 };
    size_t f;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        for (size_t i = 0; i < 1000; ++i)
        {
            // remap ponts to scren
            pixel.x = Remap(point.x, -4.0f, 4.0f, 0.0f, WIDTH);
            pixel.y = Remap(point.y, 0.0f, 10.0f, HEIGHT, 0.0f);

            DrawPixelV(pixel, GREEN);

            const int r = GetRandomValue(0,99);
            if (r < 1)
                f = 0;
            else if (r < 86)
                f = 1;
            else if (r < 93)
                f = 2;
            else
                f = 3;

            point = (*transformate[f])(&point);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
