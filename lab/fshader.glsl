#version 120

varying vec4 color;

void main()
{
	gl_FragColor = color;
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
