#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/gl.h>
#include <iostream>
#include <fstream>
//#include <string>
//#include <thread>
#include <cmath>

// Opens file dog.txt and draws the vertices in it as a line strip
void drawDog() {
    float x,y;
    // Open file
    std::string filename = "dog.txt";
    std::ifstream inputFile(filename);
    glBegin(GL_LINE_STRIP);

    // >> extracts 2 floats from inputfile and stores in x and y
    while (inputFile >> x >> y) {
        glVertex2f(x, y);
    }

    glEnd();

    // Reset file pointer to the beginning
    //inputFile.clear();              // clear the end-of-file flag
    //inputFile.seekg(0, std::ios::beg); // set the file pointer to the beginning

    inputFile.close();
}

// Calculates transitions and rotations to apply and then calls drawDog()
void drawCircleOfDogs(int numDogs, float circleRadius, float rotation) {
    for (int i = 0; i < numDogs; ++i) {

        // Divides 360 by number of dogs then multiples by i (the number of dog being drawn)
        // ex: 360/8=45 * i gives the angle. (0,45,90,...)
        float angle = i * (360.0f / numDogs);

        // To calculate the postions dogs must be translated to
        // 30 is the center, + radius of circle.
        // x = r cos(theta), multiplied by pi and divided by 180 to convert from degrees to radians
        float x = 30 + circleRadius * cosf(angle * 3.1415926f / 180.0f);
        float y = 30 + circleRadius * sinf(angle * 3.1415926f / 180.0f);

        glPushMatrix(); // saves current model-view matrix onto stack
        glTranslatef(x, y, 0.0f); // translates to x,y position
        glRotatef(rotation, 0.0f, 0.0f, 1.0f); // Rotate around center
        drawDog(); // Assuming the dog coordinates are relative to its center
        glPopMatrix(); // undoes the translation and rotation for next loop
    }
}

int main(void) {
    float rotation=0.0f;

    GLFWwindow*window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1280, 1000, "Exercise 1", NULL, NULL);
    if (!window) {
        std::cout << "Window Creation Didn't work" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // reset transformations

    // Specifies the viewing volume to be (left, right, bottom, top) = (0, 60, 0, 60)
    // center will change if this is change, rn its 30 because right and top are 60.
    glOrtho(0, 60, 0, 60, -1, 1);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glColor3f(0.0f, 0.0f, 0.0f); // black drawing
    glPointSize(2.0f); //increasing pointer size, default is 1.0f

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        drawCircleOfDogs(8, 25.0f, rotation); // Draw 8 dogs in a circle with a radius of 25.0

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // rotation increased every loop
        rotation += 1.0f;

        // delay to slow down the rotation
        //std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 200 milliseconds delay
    }

    glfwTerminate();
    return 0;
}
