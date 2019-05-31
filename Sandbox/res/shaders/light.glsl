#shader vertex
 #version 330 core  

 layout(location = 0) in vec4 Pos;
 layout(location = 1) in vec2 TextureCoordinates;

 uniform mat4 model;
 uniform mat4 view;
 uniform mat4 projection;

 void main() {  
	 gl_Position = projection * view * model * Pos;
 };

#shader fragment
#version 330 core

out vec4 color;

uniform vec4 objectColor;

 void main() {
		color = objectColor;
 };