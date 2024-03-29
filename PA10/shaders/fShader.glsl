#version 330

          smooth in vec2 texture;
          smooth in vec4 color;

          out vec4 frag_color;

          uniform sampler2D gSampler;

          void main(void)
          {
             frag_color = color * texture2D(gSampler, texture.xy);
          }
