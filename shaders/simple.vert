#version 330

in vec3 position;
in vec3 color;
out vec4 v_color;
uniform mat4 mvp_matrix;

void main(void)
{
    gl_Position = mvp_matrix * vec4(position, 1.0);
    v_color = vec4(color, 1.0);
}
