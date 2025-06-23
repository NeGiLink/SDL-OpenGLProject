

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

// 環境光
uniform vec3 ambientColor;   
// 拡散色
uniform vec3 diffuseColor;   
// 鏡面反射
uniform vec3 specularColor;

uniform float shininess;

uniform vec4 uColor;
void main()
{
	vec4 texColor = texture(uTexture, fragTexCoord);
	
	vec3 ambient = ambientColor;
	vec3 diffuse = diffuseColor * texColor.rgb;
	vec3 specular = specularColor * shininess;
	
	vec3 finalColor = ambient + diffuse + specular;
	
	// 不透明度 = マテリアルカラー × テクスチャアルファ
	outDiffuse = vec4(finalColor, uColor.a * texColor.a);

	// Normal/world pos are passed directly along
	outNormal = fragNormal;
	outWorldPos = fragWorldPos;
}
