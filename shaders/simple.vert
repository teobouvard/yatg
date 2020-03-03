#version 330

in vec3 v_position;
out vec4 v_color;

uniform mat4 mvp_matrix;

void main(void)
{
    gl_Position = mvp_matrix * vec4(v_position, 1.0);
    v_color = vec4(1.0, 1.0, 1.0, 1.0);
}
