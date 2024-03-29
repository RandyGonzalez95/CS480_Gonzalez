#version 330

          layout (location = 0) in vec3 v_position;
          layout (location = 1) in vec2 uv;
          layout (location = 2) in vec3 normal;

          smooth out vec2 texture;
          smooth out vec4 color;

          uniform mat4 projectionMatrix;
          uniform mat4 viewMatrix;
          uniform mat4 modelMatrix;

          uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
          uniform vec4 LightPosition;
          float Shininess;

          void main(void)
          {
            vec4 v = vec4(v_position, 1.0);
            Shininess = 80.0f;

            // Transform vector position into eye coordinates
            vec3 pos = ((viewMatrix * modelMatrix) * v).xyz;

            vec3 L = normalize(LightPosition.xyz - pos);
            vec3 E = normalize(-pos);
            vec3 H = normalize(L + E);

            // Transform vertex normal into eye coordinates
            vec3 N = normalize((viewMatrix * modelMatrix)*vec4(normal,0.0)).xyz;

            vec4 ambient = AmbientProduct;

            float Kd = max(dot(L,N), 0.0);
            vec4 diffuse = Kd * DiffuseProduct;
            float Ks = pow(max(dot(N,H),0.0), Shininess);
            vec4 specular = Ks * SpecularProduct;

            if(dot(L,N)<0.0)
            {
              specular = vec4(0.0, 0.0, 0.0, 1.0);
            }

            gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v;
            texture = uv;
            color = ambient + diffuse + specular;
            color.a = 0.0;
          }
