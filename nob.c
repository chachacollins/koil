#define NOB_IMPLEMENTATION
#include "nob.h"

int build_tools(Nob_Cmd cmd)
{
    if (!nob_mkdir_if_not_exists("build")) return false;
    if (!nob_mkdir_if_not_exists("build/tools")) return false;
    nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-o", "build/tools/obj2c", "obj2c.c");
    return nob_cmd_run(&cmd);
}

int build_demos(Nob_Cmd cmd)
{
    if (!nob_mkdir_if_not_exists("build")) return false;
    if (!nob_mkdir_if_not_exists("build/demos")) return false;
    nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-o", "build/demos/cube", "koil.c", "-lraylib", "-lm");
    if (!nob_cmd_run(&cmd)) return 1;

    nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-DTEAPOT", "-o", "build/demos/teapot", "koil.c", "-lraylib", "-lm");
    if (!nob_cmd_run(&cmd)) return 1;

    nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-DCUP", "-o", "build/demos/cup", "koil.c", "-lraylib", "-lm");
    if (!nob_cmd_run(&cmd)) return 1;

    nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-DPENGER", "-o", "build/demos/penger", "koil.c", "-lraylib", "-lm");
    if (!nob_cmd_run(&cmd)) return 1;
}

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);
    Nob_Cmd cmd = {0};
    if(!build_tools(cmd)) return 1;
    if(!build_demos(cmd)) return 1;
    return 0;
}
