#version 330

in vec4 vertex;
out vec4 v_color;

uniform mat4 mtv_matrix;

void main(void)
{
    gl_Position = mtv_matrix * vertex;
    v_color = vec4(1.0, 1.0, 1.0, 1.0);
}
