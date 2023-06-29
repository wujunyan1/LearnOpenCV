#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aCellCoord;


//uniform mat4 model;
//uniform mat4 modelInverse;
//uniform mat4 view;
//uniform mat4 projection;
//uniform vec3 viewPos;
uniform mat4 model;
uniform mat4 OP;
//uniform mat4 view;
//uniform mat4 ortho;

uniform float mapScale;
uniform vec2 mapSize;
uniform vec2 cellSize;
uniform sampler2D cellDatas;

uniform vec2 startIndex;
uniform vec2 startPos;

//uniform float v[4];
uniform vec2 textureCoords[48];

out vec2 TexCoord;
out vec4 WorldPos;
out float ap;
out vec3 cellCoord;

void main()
{
    vec3 pos = vec3((aPos.x + startPos.x) * mapScale, (aPos.y - startPos.y) / mapSize.y  * mapScale , (aPos.z + startPos.y ) * mapScale);
    WorldPos = model * vec4(pos, 1.0);
    gl_Position = OP * WorldPos;
    // TexCoord = aTexCoord; //aTexCoord;
    vec4 cellData = texture(cellDatas, (vec2(aCellCoord) + startIndex) / vec2(10, 10) );
    vec2 coord = textureCoords[int(cellData.a * 255)]; // textureCoords[int(cellData.a * 255)];
    ap = cellData.a;
    cellCoord = aCellCoord;

    // gl_Position.z = (mod(aCellCoord.x / mapSize.x, 2) + aCellCoord.y / mapSize.y) * gl_Position.w;
    TexCoord = aTexCoord * cellSize + coord;

    // gl_Position.z = (aPos.z - (aCellCoord.y * 48)) / (mapSize.y * 4) * gl_Position.w;
}