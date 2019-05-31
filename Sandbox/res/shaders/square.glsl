#shader vertex
 #version 330 core  

 layout(location = 0) in vec4 Pos;
 layout(location = 1) in vec3 fragNormal;
 layout(location = 2) in vec2 fragTexCoord;

 out vec2 texCoord;
 out vec3 Normal;
 out vec3 FragPos;

 uniform mat4 model;
 uniform mat4 view;
 uniform mat4 projection;

 void main() {  
	 gl_Position = projection * view * model * Pos;

	 ///setting up fragment shader options
	 texCoord = fragTexCoord;
	 Normal = mat3(model) * fragNormal;
	 FragPos = vec3(model * Pos);
 };

#shader fragment
#version 330 core

out vec4 color;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

/// lighting stuff
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec4 lightColor;
uniform vec4 objectColor;

/// texture
uniform int IsTextureActive;
uniform sampler2D activeTexture;

 void main() {
// vec3 lightPos = vec3(0.0);
 //vec4 lightColor = vec4(1.0);
	
		/// constant characteristic of material

			const float ambientStrength = 0.1;
			const float specularStrength = 0.5;
			const int specularContrast = 128;

		// ambient
			vec3 ambient = ambientStrength * lightColor.w * lightColor.xyz;

		//diffuse
			vec3 norm = normalize(Normal);
			vec3 lightDir = normalize(lightPos - FragPos);
			
			/// to eliminate light from back we use max func
			float diff = max(dot(norm, lightDir), 0.0);
			vec3 diffuse = diff * lightColor.xyz;

		// specular
			vec3 viewDir = normalize(viewPos - FragPos);
			vec3 reflectDir = reflect(-lightDir, norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularContrast);
			vec3 specular = specularStrength * spec * lightColor.xyz;

		if (IsTextureActive == 1)
			color = vec4(ambient + diffuse + specular, 1.0f) * texture(activeTexture, texCoord);
		else color = vec4(ambient + diffuse + specular, 1.0f)  * objectColor;
 };