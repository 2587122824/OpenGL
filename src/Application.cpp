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

//�ƹ�Ĭ��λ��
glm::vec3 lightPos(-1.0f, 0.9f, -0.5f);
//���������
Camera camera1(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;
float lastX = 400, lastY = 300;//����ʼλ��
float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��
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
    // ���û�����ESC��,��������window���ڵ�WindowShouldClose����Ϊtrue
    // �ر�Ӧ�ó���(����esc��ʱ)
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    //�ƶ������
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
    float yoffset = lastY - ypos; // ע���������෴�ģ���Ϊy�����Ǵӵײ����������������
    //std::cout << xoffset << "," << yoffset << std::endl;

    lastX = xpos;
    lastY = ypos;
    camera1.ProcessMouseMovement(xoffset, yoffset);

};
//��������
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera1.ProcessMouseScroll(yoffset);
}
int main() {
    //��������
    auto window = createWindow();
    //������������
     float ambientStrength = 0.1;
    
    //���¼�
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    //��ɫ��
    Shader shader("res/shaders/basic.shader");
    shader.use();
    shader.setUniform1i("slot1", 0);
    shader.setUniform1i("slot2", 1);
    shader.setUniform4f("u_color", glm::vec4(1.0f, 0.5f, 0.31f, 1.0f));
    shader.setUniform4f("lightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)* ambientStrength);
    //�ƹ���ɫ��
    Shader lightShader("res/shaders/light.shader");
    lightShader.use();
    lightShader.setUniform1i("slot1", 0);
    lightShader.setUniform1i("slot2", 1);
    

    //����ģ��
    Model backpack("res/objects/backpack/backpack.obj");

    //�����߿�ģʽ
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //Ӳ��֧����󶥵���������
    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    //�仯����
   /* glm::mat4 transform = glm::mat4(1.0f);
    shader.setUniformMatrix4fv("transform", transform);*/

    shader.use();
    //ģ�;���
    glm::mat4 model = glm::mat4(1.0f);//��ʼ����ֵΪ��λ����
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
    shader.setUniformMatrix4fv("model", model);
    //��ͼ����
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.5f));
    shader.setUniformMatrix4fv("view", view);
    //ͶӰ����
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective<float>(glm::radians(45.0f), 800 / 600, 0.1f, 100.0f);
    shader.setUniformMatrix4fv("projection", projection);

    //������Ȳ���
    glEnable(GL_DEPTH_TEST);

    //���������
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

    //��Ⱦѭ��ǰ������
    if (glGetError() != GL_NO_ERROR) {
        std::cerr << "OpenGL ��ʼ������" << std::endl;
        return 0;
    }
    //GAME LOOP
    while (!glfwWindowShouldClose(window))
    {
        //�����Ļ����Ȼ���
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
        

        //���������û�д���ʲô�¼�������������롢����ƶ��ȣ���Ȼ����ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
        glfwPollEvents();
        //��Ⱦ����
        shader.use();
         //��ʱ����ת
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
        std::cout << glGetError() << "�������" << std::endl;
        //��������
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