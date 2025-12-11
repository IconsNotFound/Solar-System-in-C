/**
 * @file planets.h
 * @brief Planet definitions, initialization, and ring rendering.
 */

#ifndef PLANETS_H
#define PLANETS_H

#include "common.h"

/**
 * @struct Planet
 * @brief Represents a planet in the solar system.
 */
typedef struct {
    float radius;   /**< Orbit radius from Sun */
    float angle;    /**< Current angle along orbit */
    float speed;    /**< Angular speed of orbit */
    float size;     /**< Planet radius */
    float color[3]; /**< RGB color */
} Planet;

/** Array holding all planets */
static Planet planets[NUM_PLANETS];

/** Camera parameters */
static float camera_angle = 0.0f;
static float camera_distance = 25.0f;

/**
 * @brief Initialize planet data with realistic colors and sizes.
 * The colors were chosen for visual appeal and differentiation.
 */
static void init_planets() {
    planets[0] = (Planet){2.0f, 0.0f, 0.05f, 0.22f, {0.72f, 0.72f, 0.72f}}; // Mercury
    planets[1] = (Planet){3.5f, 0.0f, 0.03f, 0.26f, {0.95f, 0.88f, 0.65f}}; // Venus
    planets[2] = (Planet){5.0f, 0.0f, 0.02f, 0.30f, {0.15f, 0.35f, 1.0f}};  // Earth
    planets[3] = (Planet){6.5f, 0.0f, 0.017f, 0.28f, {0.90f, 0.32f, 0.18f}}; // Mars
    planets[4] = (Planet){9.0f, 0.0f, 0.012f, 0.60f, {1.00f, 0.78f, 0.60f}}; // Jupiter
    planets[5] = (Planet){11.0f, 0.0f, 0.01f, 0.50f, {0.95f, 0.85f, 0.55f}}; // Saturn
    planets[6] = (Planet){13.0f, 0.0f, 0.008f, 0.40f, {0.55f, 0.86f, 1.00f}}; // Uranus
    planets[7] = (Planet){15.0f, 0.0f, 0.007f, 0.40f, {0.20f, 0.28f, 0.80f}}; // Neptune
    planets[8] = (Planet){17.0f, 0.0f, 0.005f, 0.18f, {0.82f, 0.76f, 0.70f}}; // Pluto
}

/**
 * @brief Draws a flat ring around a planet (e.g., Saturn)
 * @param innerR Inner radius of the ring
 * @param outerR Outer radius of the ring
 * @param segments Number of segments for smoothness
 */
static void draw_ring(float innerR, float outerR, int segments) {
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * M_PI * i / segments;
        float x = cos(theta);
        float z = sin(theta);
        glVertex3f(innerR * x, 0.0f, innerR * z);
        glVertex3f(outerR * x, 0.0f, outerR * z);
    }
    glEnd();
}

#endif // PLANETS_H
