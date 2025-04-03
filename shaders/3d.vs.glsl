#version 330 core

in vec3 ourColor;

uniform vec3 objectColor;

out vec4 FragColor;

void main() {
    // Combiner la couleur du vertex et la couleur de l'objet
    FragColor = vec4(objectColor * ourColor, 1.0);
}