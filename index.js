const BACKGROUND = "#181818FF";
const FOREGROUND = "#18FF18FF";

game.width = 800
game.height = 800
const ctx = game.getContext("2d");

function clear() {
    ctx.fillStyle = BACKGROUND;
    ctx.fillRect(0, 0, game.width, game.height);
}

function point({x, y}) {
    const s = 20;
    ctx.fillStyle = FOREGROUND;
    ctx.fillRect(x - s/2, y - s/2, 20, 20);
}

function screen(p) {
    return {
        x: (p.x + 1)/2 * game.width,
        y: (1 - (p.y + 1)/2) * game.height,
    }
}

function project({x, y, z}) {
    return {
        x: x/z,
        y: y/z,
    }
}

const FPS = 60;
let dz = 1;
let angle = 0;

function translateZ({x, y, z}) {
    return {x: x, y: y, z: z + dz};
}

function rotateXZ({x, y, z}, angle) {
    const cos = Math.cos(angle);
    const sin = Math.sin(angle);
    return {
        x: x * cos - z * sin,
        y: y,
        z: x * sin + z * cos,
    };
}

function line(p1, p2) {
    ctx.strokeStyle = FOREGROUND;
    ctx.beginPath();
    ctx.moveTo(p1.x, p1.y);
    ctx.lineTo(p2.x, p2.y);
    ctx.stroke();
}

const vs = [
    {x:  0.25,  y:  0.25,  z: 0.25 },
    {x: -0.25,  y:  0.25,  z: 0.25 },
    {x: -0.25,  y: -0.25,  z: 0.25 },
    {x:  0.25,  y: -0.25,  z: 0.25 },

    {x:  0.25,  y:  0.25,  z: -0.25 },
    {x: -0.25,  y:  0.25,  z: -0.25 },
    {x: -0.25,  y: -0.25,  z: -0.25 },
    {x:  0.25,  y: -0.25,  z: -0.25 },
];

const fs = [
    [0, 1, 2, 3],
    [4, 5, 6, 7],
    [0, 4],
    [1, 5],
    [2, 6],
    [3, 7],
];

function frame() {
    dt = 1/FPS;
    //dz += 1 * dt;
    angle += Math.PI*dt;
    clear();
    for (const f of fs) {
        for (let i = 0; i < f.length; ++i) {
            const a = vs[f[i]];
            const b = vs[f[(i + 1) % f.length]];
            line(
                screen(project(translateZ(rotateXZ(a, angle)))),
                screen(project(translateZ(rotateXZ(b, angle))))
            );
        }
    }
    setTimeout(frame, 1000/FPS);
}
setTimeout(frame, 1000/FPS);
