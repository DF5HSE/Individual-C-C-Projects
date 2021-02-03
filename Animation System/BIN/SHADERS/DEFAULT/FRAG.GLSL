#version 420

layout(location = 0) out vec4 OutColor;

layout(binding = 0) uniform sampler2D Texture0;
layout(binding = 1) uniform sampler2D Texture1;
layout(binding = 2) uniform sampler2D Texture2;
layout(binding = 3) uniform sampler2D Texture3;
layout(binding = 4) uniform sampler2D Texture4;
layout(binding = 5) uniform sampler2D Texture5;
layout(binding = 6) uniform sampler2D Texture6;
layout(binding = 7) uniform sampler2D Texture7;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Ph;
uniform float Trans;
uniform vec3 CamLoc;
uniform float Time;

uniform int IsTexture0;
uniform int IsTexture1;
uniform int IsTexture2;
uniform int IsTexture3;
uniform int IsTexture4;
uniform int IsTexture5;
uniform int IsTexture6;
uniform int IsTexture7;

in vec3 InPos;
in vec3 DrawPos;     
in vec2 DrawTexCoord;
in vec3 DrawNormal;  
in vec4 DrawColor;   

vec3 Shade( void )
{
  vec3 LightPos = vec3(0, 20, 50);
  vec3 L = normalize(LightPos - DrawPos);
  vec3 V = normalize(DrawPos - CamLoc);
  vec3 R = normalize(reflect(V, DrawNormal));
  vec3 Color = Ka;

  faceforward(DrawNormal, V, DrawNormal);
  
  vec3 colord = Kd;

  if (IsTexture0 == 1)
    colord *= texture2D(Texture0, DrawTexCoord).rgb;
  if (IsTexture1 == 1)
    colord *= texture2D(Texture1, DrawTexCoord).rgb;
  if (IsTexture2 == 1)
    colord *= texture2D(Texture2, DrawTexCoord).rgb;
  if (IsTexture3 == 1)
    colord *= texture2D(Texture3, DrawTexCoord).rgb;
  if (IsTexture4 == 1)
    colord *= texture2D(Texture4, DrawTexCoord).rgb;
  if (IsTexture5 == 1)
    colord *= texture2D(Texture5, DrawTexCoord).rgb;
  if (IsTexture6 == 1)
    colord *= texture2D(Texture6, DrawTexCoord).rgb;
  if (IsTexture7 == 1)
    colord *= texture2D(Texture7, DrawTexCoord).rgb;

  Color += clamp(colord * max(dot(DrawNormal, L), 0), 0, 1);

  /*
  float min = 0.001;
  if (Ks.r < min && Ks.g < min && Ks.b < min)
    discard;
  */
  Color += clamp(Ks * pow(max(dot(R, L), 0), Ph), 0, 1);

  return Color;
};


void main( void )
{  
  //if (InPos.y > sin(Time / 10) * 300)
    //discard;
  OutColor = vec4(Shade(), Trans);
  //OutColor = vec4(DrawNormal, 1);
}                         	


