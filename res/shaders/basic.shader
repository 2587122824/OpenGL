#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color; 
layout (location = 2) in vec2 texCoord; 

out vec3 vertexColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(position.xyz, 1.0);
    vertexColor = color;
    //TexCoord = texCoord;

}

#shader fragment
#version 330 core
in vec3 vertexColor;
in vec2 TexCoord;
out vec4 color;
uniform vec4 u_color;
uniform vec4 lightColor;
uniform sampler2D slot1;
uniform sampler2D slot2;
void main()
{
    color = vec4(lightColor * u_color);
    //texture函数来采样纹理的颜色，它第一个参数是纹理采样器，第二个参数是对应的纹理坐标。
    //color = texture(slot1, TexCoord);
    //mix函数需要接受两个值作为参数，并对它们根据第三个参数进行线性插值。
    // 如果第三个值是0.0，它会返回第一个输入；如果是1.0，会返回第二个输入值。
    // 0.2会返回80 % 的第一个输入颜色和20 % 的第二个输入颜色，即返回两个纹理的混合色。
    //color = mix(texture(slot1, TexCoord), texture(slot2, TexCoord), 0.7);
}
    