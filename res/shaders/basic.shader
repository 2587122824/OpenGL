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
    //texture�����������������ɫ������һ��������������������ڶ��������Ƕ�Ӧ���������ꡣ
    //color = texture(slot1, TexCoord);
    //mix������Ҫ��������ֵ��Ϊ�������������Ǹ��ݵ����������������Բ�ֵ��
    // ���������ֵ��0.0�����᷵�ص�һ�����룻�����1.0���᷵�صڶ�������ֵ��
    // 0.2�᷵��80 % �ĵ�һ��������ɫ��20 % �ĵڶ���������ɫ����������������Ļ��ɫ��
    //color = mix(texture(slot1, TexCoord), texture(slot2, TexCoord), 0.7);
}
    