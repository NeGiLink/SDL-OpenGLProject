

// Request GLSL 3.3
#version 330 core
layout (location = 0) in vec3 aPos;      // 頂点位置
layout (location = 1) in vec3 aNormal;   // 法線
layout (location = 2) in vec2 aTexCoord; // UV座標

out vec3 FragPos;   // フラグメント位置（ワールド座標）
out vec3 Normal;    // 法線
out vec2 TexCoord;  // UV座標

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoord = aTexCoord;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
