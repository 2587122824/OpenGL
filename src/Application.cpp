#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "vender/imgui/imgui.h"
#include "vender/imgui/imgui_impl_glfw.h"
#include "vender/imgui/imgui_impl_opengl3.h"
#include "vender/imgui/imgui_impl_opengl3.h"
#include "model.h"

//灯光默认位置
glm::vec3 lightPos(-1.0f, 0.9f, -0.5f);
//摄像机对象
Camera camera1(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;
float lastX = 400, lastY = 300;//鼠标初始位置
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
GLFWwindow* createWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
    }
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    return window;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
    // 关闭应用程序(按下esc键时)
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    //移动摄像机
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera1.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera1.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera1.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera1.ProcessKeyboard(RIGHT, deltaTime);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
        return;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
    //std::cout << xoffset << "," << yoffset << std::endl;

    lastX = xpos;
    lastY = ypos;
    camera1.ProcessMouseMovement(xoffset, yoffset);

};
//监听滚轮
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera1.ProcessMouseScroll(yoffset);
}
int main() {
    //创建窗口
    auto window = createWindow();
    //环境常量因子
     float ambientStrength = 0.1;
    
    //绑定事件
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    //着色器
    Shader shader("res/shaders/basic.shader");
    shader.use();
    shader.setUniform1i("slot1", 0);
    shader.setUniform1i("slot2", 1);
    shader.setUniform4f("u_color", glm::vec4(1.0f, 0.5f, 0.31f, 1.0f));
    shader.setUniform4f("lightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)* ambientStrength);
    //灯光着色器
    Shader lightShader("res/shaders/light.shader");
    lightShader.use();
    lightShader.setUniform1i("slot1", 0);
    lightShader.setUniform1i("slot2", 1);
    

    //加载模型
    Model backpack("res/objects/backpack/backpack.obj");

    //设置线框模式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //硬件支持最大顶点属性数量
    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    //变化矩阵
   /* glm::mat4 transform = glm::mat4(1.0f);
    shader.setUniformMatrix4fv("transform", transform);*/

    shader.use();
    //模型矩阵
    glm::mat4 model = glm::mat4(1.0f);//初始化赋值为单位矩阵！
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
    shader.setUniformMatrix4fv("model", model);
    //视图矩阵
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.5f));
    shader.setUniformMatrix4fv("view", view);
    //投影矩阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective<float>(glm::radians(45.0f), 800 / 600, 0.1f, 100.0f);
    shader.setUniformMatrix4fv("projection", projection);

    //开启深度测试
    glEnable(GL_DEPTH_TEST);

    //隐藏鼠标光标
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   
    //imgUI
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    #ifdef __EMSCRIPTEN__
        ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
    #endif
        const char* glsl_version = "#version 130";
        ImGui_ImplOpenGL3_Init(glsl_version);
    // Our state
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    //渲染循环前检查错误
    if (glGetError() != GL_NO_ERROR) {
        std::cerr << "OpenGL 初始化错误" << std::endl;
        return 0;
    }
    //GAME LOOP
    while (!glfwWindowShouldClose(window))
    {
        //清除屏幕、深度缓冲
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        

        //函数检查有没有触发什么事件（比如键盘输入、鼠标移动等），然后调用对应的回调函数（可以通过回调方法手动设置）
        glfwPollEvents();
        //渲染命令
        shader.use();
         //随时间旋转
        model = glm::rotate(model, ((float)deltaTime * 1) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 1.0f));
        shader.setUniformMatrix4fv("model", model);
        view = camera1.GetViewMatrix();
        shader.setUniformMatrix4fv("view", view);
        projection = glm::perspective(glm::radians(camera1.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
        shader.setUniformMatrix4fv("projection", projection);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        shader.setUniformMatrix4fv("model", model);
        backpack.Draw(shader);
        std::cout << glGetError() << "错误代码" << std::endl;
        //交换缓冲
        glfwSwapBuffers(window);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}