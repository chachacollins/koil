#include <raylib.h>
#include <math.h>

#ifdef TEAPOT
#include "assets/utahTeapot.c"
#elif defined(CUP)
#include "assets/tsodinCupLowPoly.c"
#elif defined(PENGER)
#include "assets/penger.c"
#else
#include "assets/cube.c"
#endif

#define BACKGROUND  0x181818FF
#define FOREGROUND  0x18FF18FF
#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])

Vector2 project(Vector3 pos)
{
    return (Vector2) {
        .x = pos.x / pos.z,
        .y = pos.y / pos.z,
    };
}

Vector2 screen(Vector2 pos)
{
    return (Vector2) {
        .x = (pos.x + 1)/2       * GetScreenWidth(),
        .y = (1 - (pos.y + 1)/2) * GetScreenHeight(),
    };
}

Vector3 translate_z(Vector3 pos, float dz)
{
    return (Vector3) {
        .x = pos.x,
        .y = pos.y,
        .z = pos.z + dz,
    };
}

Vector3 rotate_xz(Vector3 pos, float angle)
{
    const float c = cos(angle);
    const float s = sin(angle);
    return (Vector3) {
        .x = pos.x * c - pos.z * s,
        .y =  pos.y,
        .z = pos.x * s + pos.z * c,
    };
}

void draw_point(Vector2 pos)
{
    Vector2 size = {20, 20};
    Vector2 dpos = {pos.x - size.x/2, pos.y - size.y/2};
    DrawRectangleV(dpos, size, GetColor(FOREGROUND));
}

void draw_line(Vector2 p1, Vector2 p2)
{
    DrawLineV(p1, p2, RAYWHITE);
}

int main(void)
{
    const int screen_width  = 800;
    const int screen_height = 800;
    float dz = 4;
    float angle = 0;
    InitWindow(screen_width, screen_height, "KOIL");
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f/GetFrameTime())), GetScreenWidth() - 220, 40, 20, GetColor(FOREGROUND));
        ClearBackground(GetColor(BACKGROUND));
        angle += PI*GetFrameTime();
        for(long unsigned int i = 0; i < ARRAY_SIZE(faces); ++i)
        {
            for(long unsigned int j = 0; j < ARRAY_SIZE(faces[i]); j++) 
            {
                const Vector3 b = vertices[faces[i][1]];
                const Vector3 a = vertices[faces[i][0]];
                draw_line(
                        screen(project(translate_z(rotate_xz(a, angle), dz))),
                        screen(project(translate_z(rotate_xz(b, angle), dz)))
                );
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
