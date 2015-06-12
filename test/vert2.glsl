attribute vec2 position;
attribute vec4 color;

varying vec4 color_i;

void main(void)
{
    gl_Position = vec4(position, 0, 1);
    color_i = color;
}
