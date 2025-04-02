// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330
// Inputs from vertex shader
// Tex coord
in vec2 fragTexCoord;
// Normal (in world space)
in vec3 fragNormal;
// Position (in world space)
in vec3 fragWorldPos;

// This corresponds to the outputs to the G-buffer
layout(location = 0) out vec4 outDiffuse;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out vec3 outWorldPos;

// This is used for the texture sampling
uniform sampler2D uTexture;

// ŠÂ‹«Œõ
uniform vec3 ambientColor;   
// ŠgUF
uniform vec3 diffuseColor;   
// ‹¾–Ê”½Ë
uniform vec3 specularColor;  

void main()
{
	// ŠÂ‹«Œõ¬•ª
    vec3 ambient = ambientColor;  
	// ŠgUŒõ¬•ª
    vec3 diffuse = diffuseColor * texture(uTexture, fragTexCoord).rgb;  
	// ‹¾–Ê”½Ëi‰¼j
    vec3 specular = specularColor;  

    vec3 finalColor = ambient + diffuse + specular;

	// Diffuse color is sampled from texture
	outDiffuse = vec4(finalColor, 1.0);
	//outDiffuse = vec4(texture(uTexture, fragTexCoord).xyz, 1.0);

	// Normal/world pos are passed directly along
	outNormal = fragNormal;
	outWorldPos = fragWorldPos;
}
