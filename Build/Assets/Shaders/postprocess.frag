#version 430

#define INVERT_MASK    (1 << 0)
#define GREYSCALE_MASK (1 << 1)
#define COLORINT_MASK  (1 << 2)

in layout(location = 0) vec2 ftexcoord;
out layout(location = 0) vec4 ocolor;

uniform float blend = 1;
uniform uint params = 0;

layout(binding = 0) uniform sampler2D screenTexture;

float random(vec2 st) 
{
	return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec4 invert(in vec4 color)
{
	return vec4(vec3(1) - color.rgb, color.a);
}

vec4 greyscale(in vec4 color)
{
	return vec4(vec3(0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b), color.a);
}

void main()
{
	vec4 basecolor = texture(screenTexture, ftexcoord);
	vec4 postprocess = basecolor;

	if (bool(params & INVERT_MASK)) postprocess = invert(basecolor);
	if (bool(params & GREYSCALE_MASK)) postprocess = greyscale(basecolor);

	ocolor = mix(basecolor, postprocess, blend);
}
