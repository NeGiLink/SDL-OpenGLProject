// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330 core
out vec4 FragColor;

in vec3 FragPos;    // 頂点シェーダーから受け取るワールド座標
in vec3 Normal;     // 頂点シェーダーから受け取る法線
in vec2 TexCoord;   // UV座標

uniform vec3 ambientColor;   // 環境光
uniform vec3 diffuseColor;   // 拡散色
uniform vec3 specularColor;  // 鏡面反射
uniform sampler2D texture1;  // テクスチャ

void main()
{
    vec3 ambient = ambientColor;  // 環境光成分
    vec3 diffuse = diffuseColor * texture(texture1, TexCoord).rgb;  // 拡散光成分
    vec3 specular = specularColor;  // 鏡面反射（仮）

    vec3 finalColor = ambient + diffuse + specular;
    FragColor = vec4(finalColor, 1.0);
}
