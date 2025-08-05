

// Request GLSL 3.3
#version 330

// Inputs from vertex shader
// Tex coord
in vec2 fragTexCoord;

// This corresponds to the output color to the color buffer
layout(location = 0) out vec4 outColor;

// Different textures from G-buffer
uniform sampler2D uGDiffuse;
uniform sampler2D uGNormal;
uniform sampler2D uGWorldPos;

// Create a struct for directional light
struct DirectionalLight
{
	// Direction of light
	vec3 mDirection;
	// Diffuse color
	vec3 mDiffuseColor;
	// Specular color
	vec3 mSpecColor;
};

// Uniforms for lighting
// Camera position (in world space)
uniform vec3 uCameraPos;
// Ambient light level
uniform vec3 uAmbientLight;
// Directional Light
uniform DirectionalLight uDirLight;

uniform sampler2DShadow uShadowMap;
uniform mat4 uLightViewProj;

float ComputeShadow(vec4 worldPos)
{
    vec4 lightSpacePos = worldPos * uLightViewProj;
    vec3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
    projCoords = projCoords * 0.5 + 0.5;

    // 範囲外チェック
    if (projCoords.x < 0.0 || projCoords.x > 1.0 ||
        projCoords.y < 0.0 || projCoords.y > 1.0 ||
        projCoords.z < 0.0 || projCoords.z > 1.0)
    {
        return 1.0; // ライト視錐台外 → 明るい
    }

    float shadow = 0.0;
    float bias = 0.005;
    float texelSize = 1.0 / 1024.0; // シャドウマップのサイズに合わせる

    // 3x3 PCFサンプリング
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            vec2 offset = vec2(x, y) * texelSize;
            shadow += texture(uShadowMap, vec3(projCoords.xy + offset, projCoords.z - bias));
        }
    }

    shadow /= 9.0; // サンプル数で割る（3x3=9）

    return shadow;
}

void main()
{
	vec3 gbufferDiffuse = texture(uGDiffuse, fragTexCoord).xyz;
	vec3 gbufferNorm = texture(uGNormal, fragTexCoord).xyz;
	vec3 gbufferWorldPos = texture(uGWorldPos, fragTexCoord).xyz;
	// Surface normal
	vec3 N = normalize(gbufferNorm);
	// Vector from surface to light
	vec3 L = normalize(-uDirLight.mDirection);
	// Vector from surface to camera
	vec3 V = normalize(uCameraPos - gbufferWorldPos);
	// Reflection of -L about N
	vec3 R = normalize(reflect(-L, N));

	// Compute phong reflection
	vec3 Phong = uAmbientLight;
	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		vec3 Diffuse = uDirLight.mDiffuseColor * NdotL;
		float shadow = ComputeShadow(vec4(gbufferWorldPos, 1.0));
		shadow = clamp(shadow, 0.0, 1.0);
		Phong += Diffuse * shadow; // ← shadowを掛けるのは拡散光のみに限定
	}


	// Clamp light between 0-1 RGB values
	Phong = clamp(Phong, 0.0, 1.0);

	// Final color is texture color times phong light (alpha = 1)
	outColor = vec4(gbufferDiffuse * Phong, 1.0);
}
