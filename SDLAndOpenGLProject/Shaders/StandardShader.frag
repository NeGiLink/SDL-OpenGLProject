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

in vec3 FragPos;    // ���_�V�F�[�_�[����󂯎�郏�[���h���W
in vec3 Normal;     // ���_�V�F�[�_�[����󂯎��@��
in vec2 TexCoord;   // UV���W

uniform vec3 ambientColor;   // ����
uniform vec3 diffuseColor;   // �g�U�F
uniform vec3 specularColor;  // ���ʔ���
uniform sampler2D texture1;  // �e�N�X�`��

void main()
{
    vec3 ambient = ambientColor;  // ��������
    vec3 diffuse = diffuseColor * texture(texture1, TexCoord).rgb;  // �g�U������
    vec3 specular = specularColor;  // ���ʔ��ˁi���j

    vec3 finalColor = ambient + diffuse + specular;
    FragColor = vec4(finalColor, 1.0);
}
