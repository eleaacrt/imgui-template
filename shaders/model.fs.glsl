#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform vec3 light2Pos;
uniform vec3 light2Color;

uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Ns;

uniform bool useTexture;
uniform sampler2D map_Kd;

void main() {

    vec3 diffuseColor = useTexture ? texture(map_Kd, TexCoords).rgb : Kd;

    // Ambient
    vec3 ambient = Ka * (lightColor * 0.25 + light2Color * 0.25);

    // Diffuse for light 1
    vec3 L1 = normalize(lightPos - FragPos);
    vec3 N = normalize(Normal);
    float diff1 = max(dot(L1, N), 0.0);
    vec3 diffuse1 = diff1 * diffuseColor * lightColor;

    // Diffuse for light 2
    vec3 L2 = normalize(light2Pos - FragPos);
    float diff2 = max(dot(L2, N), 0.0);
    vec3 diffuse2 = diff2 * diffuseColor * light2Color;

    // Specular for light 1
    vec3 V = normalize(viewPos - FragPos);
    vec3 H1 = normalize(L1 + V);
    float spec1 = pow(max(dot(N, H1), 0.0), Ns);
    vec3 specular1 = spec1 * Ks * lightColor;

    // Specular for light 2
    vec3 H2 = normalize(L2 + V);
    float spec2 = pow(max(dot(N, H2), 0.0), Ns);
    vec3 specular2 = spec2 * Ks * light2Color;

    // Combine results
    vec3 result = ambient + diffuse1 + diffuse2 + specular1 + specular2;
    FragColor = vec4(result, 1.0);
}