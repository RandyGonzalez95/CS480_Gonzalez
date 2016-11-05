#version 330

    layout (location = 0) in vec3 v_position;
    layout (location = 1) in vec2 uv;
    layout (location = 2) in vec3 normal;

    smooth out vec2 texture;
    smooth out vec4 color;

    uniform vec4 DiffuseProduct;
    uniform vec4 LightPosition;

    uniform mat4 projectionMatrix;
    uniform mat4 viewMatrix;
    uniform mat4 modelMatrix;

    void main(void)
    {

      vec4 v = vec4(v_position, 1.0);
    	float attenuation = 1.0;
    	vec3 normalDirection = normalize( normal );
    	vec3 lightDirection = normalize( vec3(LightPosition) );

    	if( DiffuseProduct[3] == 0.0f ){
    		attenuation == 1.0;
    		lightDirection = normalize( vec3(LightPosition) );
    	}
    	else if ( DiffuseProduct[3] == 1.0 ){
    		lightDirection = normalize( vec3(LightPosition) - v_position );
    		attenuation = 1.0;
    	}
    	else if ( DiffuseProduct[3] == 2.0 ){
    		lightDirection = normalize( vec3(LightPosition) - v_position );
    		float clampedCosine = max( 0.0, dot(-lightDirection, vec3(LightPosition) ) );
    	}

    	vec3 diffuseReflection = attenuation * vec3(DiffuseProduct) * max(0.0, dot(normalDirection, lightDirection));

      gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v;
    	texture = uv;
    	color = vec4( diffuseReflection, 1.0 );
    }
