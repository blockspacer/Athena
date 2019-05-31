#shader vertex
 #version 330 core  

 layout(location = 0) in vec4 Pos;

 out vec4 texCoord;

 uniform mat4 transform;
 uniform mat4 model;
 uniform mat4 view;
 uniform mat4 projection;
 uniform mat4 scale;

 void main() {  
	// gl_Position = projection * view * model * transform * scale * Pos;
	 gl_Position = projection * view * model * Pos;
	texCoord = gl_Position;
 };

#shader fragment
#version 330 core

out vec4 color;

in vec4 texCoord;
uniform vec4 userColor;

uniform int IsTextureActive;
uniform sampler2D activeTexture;

 void main() {
		if (IsTextureActive != 0)
			color = texture(activeTexture, texCoord.xy);
		else
			color = userColor;
 };