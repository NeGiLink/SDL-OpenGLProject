

// Request GLSL 3.3
#version 330
//メッシュ用のフラグシェーダー
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
//ライトの位置
uniform vec3 uLightPos;
//カメラの位置
uniform vec3 uViewPos;

void main()
{

	vec4 texColor = texture(uTexture, fragTexCoord);
	
	vec3 ambient = ambientColor * texColor.rgb;
	vec3 diffuse = diffuseColor * texColor.rgb;
	vec3 specular = specularColor * shininess;
	
	vec3 finalColor = ambient + diffuse + specular;
	
	// 不透明度 = マテリアルカラー × テクスチャアルファ
	outDiffuse = vec4(finalColor, uColor.a * texColor.a);
	
	// Normal/world pos are passed directly along
	outNormal = fragNormal;
	outWorldPos = fragWorldPos;

	//vec4 texColor = texture(uTexture, fragTexCoord);
    //vec3 normal = normalize(fragNormal);
    //vec3 lightDir = normalize(uLightPos - fragWorldPos);
    //vec3 viewDir = normalize(uViewPos - fragWorldPos);
    //vec3 reflectDir = reflect(-lightDir, normal);
    //
    //// ----- 環境光 -----
    //vec3 ambient = ambientColor;
    //
    //// ----- 拡散光（Lambert） -----
    //float diff = max(dot(normal, lightDir), 0.0);
    //vec3 diffuse = diff * diffuseColor * texColor.rgb;
    //
    //// ----- 鏡面反射光（Phong） -----
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    //vec3 specular = spec * specularColor;
    //
    //// ----- 合成 -----
    //vec3 finalColor = ambient + diffuse + specular;
    //
    //outDiffuse = vec4(finalColor, uColor.a * texColor.a);
    //outNormal = fragNormal;
    //outWorldPos = fragWorldPos;
}
