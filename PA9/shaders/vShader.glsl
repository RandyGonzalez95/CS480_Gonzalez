#version 330

          layout (location = 0) in vec3 v_position;
          layout (location = 1) in vec2 uv;
          layout (location = 2) in vec3 normal;

          smooth out vec2 texture;

          uniform mat4 projectionMatrix;
          uniform mat4 viewMatrix;
          uniform mat4 modelMatrix;

          uniform vec4 LightPosition;

          out vec3 fN;
          out vec3 fE;
          out vec3 fL;

          void main(void)
          {
            fN = normal;
            fE = v_position.xyz;
            fL = LightPosition.xyz;


            vec4 v = vec4(v_position, 1.0);

            if( LightPosition.w != 0.0 )
            {
            fL = LightPosition.xyz  - v_position.xyz;
            }

            gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v;
            texture = uv;
          }
