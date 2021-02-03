#version 420
layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;

uniform mat4 WVP;
uniform mat4 World;
uniform mat4 InvTrans;
uniform float Time;

out vec3 DrawPos;
out vec2 DrawTexCoord;
out vec3 DrawNormal;  
out vec4 DrawColor;   
out vec3 InPos;

void main( void )
{               
  gl_Position = WVP * vec4(InPosition, 1);

  InPos = InPosition;
  DrawPos = vec3(World * vec4(InPosition, 1));
  DrawTexCoord = InTexCoord;
  DrawNormal = mat3(InvTrans) * InNormal;
  DrawNormal = normalize(DrawNormal);
  DrawColor = InColor;
}
