varying vec2 texture_coord_i;

uniform sampler2D texture;

void main(void)
{
    gl_FragColor = texture2D(texture, texture_coord_i);
}
