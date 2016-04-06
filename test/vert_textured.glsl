attribute vec2 position;
attribute vec2 texture_coord;
uniform float scale;

varying vec2 texture_coord_i;

void main(void)
{
    gl_Position = vec4(scale * position, 0, 1);
    texture_coord_i = texture_coord;
}
