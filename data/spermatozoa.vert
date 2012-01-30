void main(void) {
	vec3 position = vec3(gl_ModelViewMatrix * gl_Vertex);
	vec3 normal = gl_NormalMatrix * gl_Normal;
	vec3 lightVec = gl_LightSource[0].position.xyz - position;
	float dis = length(lightVec);
	lightVec = normalize(lightVec);
	float attenuation = 1.0 / (gl_LightSource[0].constantAttenuation +
	gl_LightSource[0].linearAttenuation * dis +
	gl_LightSource[0].quadraticAttenuation * dis * dis);
	float diffuse = dot(lightVec, normal);
	gl_FrontColor = gl_FrontLightProduct[0].ambient;
	if (diffuse > 0.0) {
		diffuse = clamp(1.0 - diffuse, 0.0, 1.0);
		diffuse = diffuse*diffuse;
		gl_FrontColor += gl_FrontLightProduct[0].diffuse * diffuse * attenuation;
	}
	gl_Position = gl_ProjectionMatrix * vec4(position, 1.0);
}
