/**
 * @file main.c
 * @brief Main entry point for the Solar System in C simulation.
 */

#include "src/common.h"
#include "src/stars.h"
#include "src/planets.h"

/**
 * @brief Draw a sphere with simple vertex color variation for texture-like effect
 * @param radius Sphere radius
 * @param slices Number of horizontal slices
 * @param stacks Number of vertical stacks
 * @param r Red component (0..1)
 * @param g Green component (0..1)
 * @param b Blue component (0..1)
 */
void draw_textured_sphere(float radius, int slices, int stacks, float r, float g, float b) {
    for (int i = 0; i <= stacks; i++) {
        float lat0 = M_PI * (-0.5 + (float)(i - 1) / stacks);
        float z0 = radius * sin(lat0);
        float zr0 = radius * cos(lat0);

        float lat1 = M_PI * (-0.5 + (float)i / stacks);
        float z1 = radius * sin(lat1);
        float zr1 = radius * cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++) {
            float lng = 2.0f * M_PI * (float)(j - 1) / slices;
            float x = cos(lng);
            float y = sin(lng);

            float v = ((rand() % 20) / 100.0f) - 0.1f;
            glColor3f(r * (1.0f + v), g * (1.0f + v), b * (1.0f + v));
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);

            v = ((rand() % 20) / 100.0f) - 0.1f;
            glColor3f(r * (1.0f + v), g * (1.0f + v), b * (1.0f + v));
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
}

/**
 * @brief GLFW callback for window resize
 * @param window Pointer to GLFW window
 * @param width New window width
 * @param height New window height
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)width / height;
    gluPerspective(45.0, aspect, 0.1, 200.0);

    glMatrixMode(GL_MODELVIEW);
}

/**
 * @brief Program entry point
 */
int main() {
    // Initialize GLFW
    if (!glfwInit()) { printf("GLFW init failed\n"); return -1; }

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Solar System in C", NULL, NULL);
    if (!window) { printf("Window creation failed\n"); glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = 1;
    if (glewInit() != GLEW_OK) { printf("GLEW init failed\n"); return -1; }

    // OpenGL setup
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize planets and stars
    init_planets();
    init_stars();

    framebuffer_size_callback(window, 1280, 720);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // Orbiting camera
        float camX = camera_distance * sin(camera_angle);
        float camZ = camera_distance * cos(camera_angle);
        gluLookAt(camX, 10.0f, camZ, 0, 0, 0, 0, 1, 0);
        camera_angle += 0.0018f;

        // Draw background stars
        draw_stars();

        // Draw Sun (bright emissive)
        glPushMatrix();
        GLfloat sun_emission[] = {2.5f, 2.2f, 0.8f, 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, sun_emission);
        draw_textured_sphere(1.2f, 30, 30, 1.0f, 1.0f, 0.4f);
        GLfloat no_emission[] = {0, 0, 0, 1};
        glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
        glPopMatrix();

        GLfloat light_pos[] = {0, 0, 0, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

        // Draw planets
        for (int i = 0; i < NUM_PLANETS; i++) {
            Planet* p = &planets[i];
            float x = p->radius * cos(p->angle);
            float z = p->radius * sin(p->angle);

            glPushMatrix();
            glTranslatef(x, 0, z);
            draw_textured_sphere(p->size, 20, 20, p->color[0], p->color[1], p->color[2]);

            if (i == 5) { // Saturn's ring
                glColor3f(0.8f, 0.75f, 0.55f);
                draw_ring(p->size * 1.6f, p->size * 3.0f, 50);
            }

            glPopMatrix();
            p->angle += p->speed;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
