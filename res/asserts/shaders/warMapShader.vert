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

uniform vec2 mapSize;
uniform vec2 cellSize;
uniform sampler2D cellDatas;

//uniform float v[4];
uniform vec2 textureCoords[48];

out vec2 TexCoord;
out vec4 WorldPos;

void main()
{
    WorldPos = model * vec4(aPos, 1.0);
    gl_Position = OP * WorldPos;
    // TexCoord = aTexCoord; //aTexCoord;
    vec4 cellData = texture(cellDatas, vec2(aCellCoord));
    vec2 coord = textureCoords[int(cellData.a * 255)];

    gl_Position.z = (mod(aCellCoord.x / mapSize.x, 2) + aCellCoord.y / mapSize.y) * gl_Position.w;
    TexCoord = aTexCoord * cellSize + coord;

    gl_Position.z = aPos.z / mapSize.y;
}