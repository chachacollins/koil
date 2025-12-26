{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    xorg.libX11
    xorg.libXext
    xorg.libXrandr
    xorg.libXinerama
    xorg.libXcursor
    xorg.libXrender
    xorg.libXfixes
    xorg.libXi
    xorg.libXScrnSaver
    xorg.libXpresent
    xorg.libXv
    xorg.libXt
    xorg.libXmu
    xorg.libxcb
    xorg.xcbutil
    xorg.xcbutilwm
    xorg.xcbutilimage
    xorg.xcbutilkeysyms
    xorg.xcbutilrenderutil
    xorg.xcbutilcursor
    mesa
    libGL
    libGLU

    # X11 tools
    xorg.xrandr
    xorg.xset
    xorg.xinput
    xorg.xev

    zig
    raylib
  ];
}
