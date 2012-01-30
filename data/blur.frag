uniform vec2 textureSize;
uniform sampler2DRect texture;
vec4 getColor(float dx, float dy) {
	vec2 pos = gl_TexCoord[0].st + vec2(dx, dy);
	return texture2DRect(texture, pos);
}
void main(void) {
	vec4 sum = getColor(0.0, 0.0);
	sum += getColor(1.0, 0.0);
	sum += getColor(-1.0, 0.0);
	sum += getColor(0.0, 1.0);
	sum += getColor(0.0, -1.0);
	gl_FragColor = gl_Color * 0.2 * sum;
}
