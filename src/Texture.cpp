#include "Texture.h"
#include "vender/stb_image/stb_image.h" 
#include <string>
#include <iostream>
unsigned char* Texture::image_load(const std::string filepath)
{
    //��������
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imgData = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 3);
    if (imgData != NULL) {
        std::cout << "SUCCESS: img loaded" << std::endl;
    }
    else {
        std::cout << "FAIL: " << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
    }
	return imgData;
}

Texture::Texture(const std::string filepath, int slot)
{
    //�����������
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + slot); // �ڰ�����֮ǰ�ȼ�������Ԫ
    glBindTexture(GL_TEXTURE_2D, id);
    unsigned char* imgData = image_load(filepath);
    /*��һ������ָ��������Ŀ��(Target)������ΪGL_TEXTURE_2D��ζ�Ż������뵱ǰ�󶨵����������ͬһ��Ŀ���ϵ������κΰ󶨵�GL_TEXTURE_1D��GL_TEXTURE_3D���������ܵ�Ӱ�죩��
    �ڶ�������Ϊ����ָ���༶��Զ����ļ��������ϣ�������ֶ�����ÿ���༶��Զ����ļ���Ļ�������������0��Ҳ���ǻ�������
    ��������������OpenGL����ϣ����������Ϊ���ָ�ʽ�����ǵ�ͼ��ֻ��RGBֵ���������Ҳ��������ΪRGBֵ��
    ���ĸ��͵���������������յ�����Ŀ�Ⱥ͸߶ȡ�����֮ǰ����ͼ���ʱ�򴢴������ǣ���������ʹ�ö�Ӧ�ı�����
    �¸�����Ӧ�����Ǳ���Ϊ0����ʷ�������⣩�߿򣿡�
    ���ߵڰ˸�����������Դͼ�ĸ�ʽ���������͡�����ʹ��RGBֵ�������ͼ�񣬲������Ǵ���Ϊchar(byte)���飬���ǽ��ᴫ���Ӧֵ��
    ���һ��������������ͼ�����ݡ�*/
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);//�������������
    //�ͷ�ͼ���ڴ�
    stbi_image_free(imgData);
    glGenerateMipmap(GL_TEXTURE_2D);//���Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
    unbind();
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
