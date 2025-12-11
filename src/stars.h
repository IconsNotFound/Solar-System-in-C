/**
 * @file stars.h
 * @brief Background stars initialization and rendering.
 */

#ifndef STARS_H
#define STARS_H

#include "common.h"

/** Star positions */
static float stars[NUM_STARS][3];

/** Star motion offsets for subtle wobble */
static float star_offsets[NUM_STARS];

/**
 * @brief Initialize star positions in a sphere around the camera
 * and assign small offsets for subtle motion effect.
 */
static void init_stars() {
    for (int i = 0; i < NUM_STARS; i++) {
        float theta = (rand() % 6283) / 1000.0f;  // 0..2pi
        float phi = (rand() % 3141) / 1000.0f;    // 0..pi
        float r = 30.0f; // fixed distance behind planets

        stars[i][0] = r * sin(phi) * cos(theta);
        stars[i][1] = r * sin(phi) * sin(theta);
        stars[i][2] = r * cos(phi);

        star_offsets[i] = (rand() % 1000) / 50000.0f; // motion factor
    }
}

/**
 * @brief Draw all stars with slight motion and faded white color.
 */
static void draw_stars() {
    glDisable(GL_LIGHTING);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_STARS; i++) {
        float dx = sin(glfwGetTime() * star_offsets[i]) * 0.1f;
        float dy = cos(glfwGetTime() * star_offsets[i]) * 0.1f;

        // Slightly dimmed white for realism
        glColor3f(0.6f, 0.6f, 0.6f);
        glVertex3f(stars[i][0] + dx, stars[i][1] + dy, stars[i][2]);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

#endif // STARS_H
