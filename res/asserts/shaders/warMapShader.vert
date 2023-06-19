#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aCellCoord;

out vec4 vertexColor;
uniform vec4 ourColor;

//uniform mat4 model;
//uniform mat4 modelInverse;
//uniform mat4 view;
//uniform mat4 projection;
//uniform vec3 viewPos;
uniform mat4 model;
uniform mat4 VP;
uniform mat4 view;
uniform mat4 proj;

uniform vec2 mapSize;
uniform vec2 cellSize;
uniform sampler2D cellDatas;

uniform vec2[] texCoords;


out vec2 TexCoord;
out vec4 WorldPos;

void main()
{
    WorldPos = model * vec4(aPos, 1.0);
    gl_Position = VP * WorldPos;
    // TexCoord = aTexCoord; //aTexCoord;
    vec4 cellData = texture(cellDatas, vec2(aCellCoord));
    vec2 coord = texCoords[int(cellData.a * 255)];

    TexCoord = aTexCoord * cellSize + coord;
}