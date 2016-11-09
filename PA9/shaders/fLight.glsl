#version 330

          in vec3 fN;
          in vec3 fE;
          in vec3 fL;

          uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
          uniform vec4 LightPosition;
          float Shininess;


          smooth in vec2 texture;

          out vec4 frag_color;

          vec4 light;

          uniform sampler2D gSampler;

          void main(void)
          {
            Shininess = 80.0f;

            vec3 N = normalize(fN);
            vec3 E = normalize(fE);
            vec3 L = normalize(fL);

            vec3 H = normalize( L + E );
            vec4 ambient = AmbientProduct;

            float Kd = max(dot(L, N), 0.0);
            vec4 diffuse = Kd*DiffuseProduct;

            float Ks = pow(max(dot(N, H), 0.0), Shininess);
            vec4 specular = Ks*SpecularProduct;

            if( dot(L, N) < 0.0 )
              specular = vec4(0.0, 0.0, 0.0, 1.0);

            light = ambient + diffuse + specular;
            light.a = 1.0;

            frag_color = light* texture2D(gSampler, texture.xy);
          }
