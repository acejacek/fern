/*
 * https://github.com/acejacek/fern
 */

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#define WIDTH 900
#define HEIGHT 900

typedef struct {
    float x, y;
    size_t prob1, prob2, prob3;
} Params;

// original
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

Params p1(void)
{
    return (Params){4.0f, 10.4f, 1, 1+85, 1+85+7 };
}

// modified
Vector2 f5(Vector2* p)
{
    return (Vector2){0.00f,
                     0.20f * p->y - 0.12f};
}

Vector2 f6(Vector2* p)
{
    return (Vector2){ 0.845f * p->x + 0.035f * p->y,
                     -0.035f * p->x + 0.820f * p->y + 1.60f};
}

Vector2 f7(Vector2* p)
{
    return (Vector2){0.200f * p->x - 0.31f * p->y,
                     0.255f * p->x + 0.245f * p->y + 0.29f};
}

Vector2 f8(Vector2* p)
{
    return (Vector2){-0.15f * p->x + 0.24f * p->y,
                      0.255f * p->x + 0.20f * p->y + 0.68f};
}

Params p2(void)
{
    return (Params){3.5f, 8.8f, 1, 1+85, 1+85+7 };
}

// modified 2
Vector2 f9(Vector2* p)
{
    return (Vector2){0.00f,
                     0.25f * p->y - 0.14f};
}

Vector2 f10(Vector2* p)
{
    return (Vector2){ 0.85f * p->x + 0.02f * p->y,
                     -0.02f * p->x + 0.83f * p->y + 1.00f};
}

Vector2 f11(Vector2* p)
{
    return (Vector2){0.09f * p->x - 0.28f * p->y,
                     0.30f * p->x + 0.11 * p->y + 0.60f};
}

Vector2 f12(Vector2* p)
{
    return (Vector2){-0.09f * p->x + 0.28f * p->y,
                      0.30f * p->x + 0.09f * p->y + 0.70f};
}

Params p3(void)
{
    return (Params){3.0f, 6.0f, 2, 2+84, 2+85+7 };
}

// fishbone
Vector2 f13(Vector2* p)
{
    return (Vector2){0.00f,
                     0.25f * p->y - 0.40f};
}

Vector2 f14(Vector2* p)
{
    return (Vector2){ 0.950f * p->x + 0.002f * p->y - 0.002f,
                     -0.002f * p->x + 0.930f * p->y + 0.50f};
}

Vector2 f15(Vector2* p)
{
    return (Vector2){0.035f * p->x - 0.11f * p->y - 0.050f,
                     0.270f * p->x + 0.01f * p->y + 0.005f};
}

Vector2 f16(Vector2* p)
{
    return (Vector2){-0.04f * p->x + 0.11f * p->y + 0.047f,
                      0.27f * p->x + 0.01f * p->y + 0.060f};
}

Params p4(void)
{
    return (Params){5.0f, 8.0f, 2, 2+84, 2+84+7 };
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Barnsley Fern");
    SetTargetFPS(60);
    Vector2 point = Vector2Zero();   // coords in fern space
    Vector2 pixel;                   // coords in screen space

    Vector2 (*transformate[])(Vector2*) = 
        { f1, f2, f3, f4,
          f5, f6, f7, f8,
          f9, f10, f11, f12,
          f13, f14, f15, f16,
        };

    Params (*get_param[])(void) = {p1, p2, p3, p4};

    const size_t limit = sizeof(get_param) / sizeof(get_param[0]);

    size_t base = 0;
    size_t f;

    Params p = (*get_param[base])();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ||
                IsKeyPressed(KEY_SPACE))
        {
            ++base;
            if (base >= limit ) base = 0;
            p = (*get_param[base])();
            point = Vector2Zero();
            ClearBackground(BLACK);
        }

        for (size_t i = 0; i < 1000; ++i)
        {
            // remap ponts to scren
            pixel.x = Remap(point.x, -p.x, p.x, 0.0f, WIDTH);
            pixel.y = Remap(point.y, 0.0f, p.y, HEIGHT, 0.0f);

            DrawPixelV(pixel, GREEN);

            const int r = GetRandomValue(0, 99);
            if (r < p.prob1)
                f = 0;
            else if (r < p.prob2)
                f = 1;
            else if (r < p.prob3)
                f = 2;
            else
                f = 3;

            point = (*transformate[(base << 2) + f])(&point);  // base * 4 + f
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
