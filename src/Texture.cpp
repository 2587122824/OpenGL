#include "Texture.h"
#include "vender/stb_image/stb_image.h" 
#include <string>
#include <iostream>
unsigned char* Texture::image_load(const std::string filepath)
{
    //加载纹理
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
    //设置纹理参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + slot); // 在绑定纹理之前先激活纹理单元
    glBindTexture(GL_TEXTURE_2D, id);
    unsigned char* imgData = image_load(filepath);
    /*第一个参数指定了纹理目标(Target)。设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
    第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
    第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们也把纹理储存为RGB值。
    第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
    下个参数应该总是被设为0（历史遗留问题）边框？。
    第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为char(byte)数组，我们将会传入对应值。
    最后一个参数是真正的图像数据。*/
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);//绑定纹理后再设置
    //释放图像内存
    stbi_image_free(imgData);
    glGenerateMipmap(GL_TEXTURE_2D);//这会为当前绑定的纹理自动生成所有需要的多级渐远纹理
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
