#version 410 core

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;

out vec4 fColor;

void main()
{
    vec3 ambient = texture(material.diffuse, vTexCoord).rgb * light.ambient;

	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(lightPos - vFragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = texture(material.diffuse, vTexCoord).rgb * diff *  light.diffuse;

	vec3 viewDir = normalize(viewPos - vFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = material.specular * spec * light.specular;

	fColor = vec4(ambient + diffuse + specular, 1.0f);
}