

// Request GLSL 3.3
#version 330 core
layout (location = 0) in vec3 aPos;      // ���_�ʒu
layout (location = 1) in vec3 aNormal;   // �@��
layout (location = 2) in vec2 aTexCoord; // UV���W

out vec3 FragPos;   // �t���O�����g�ʒu�i���[���h���W�j
out vec3 Normal;    // �@��
out vec2 TexCoord;  // UV���W

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
