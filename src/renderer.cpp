#include "renderer.hpp"

Renderer::Renderer() {
    // Initialise OpenGL bindings
    glbinding::Binding::initialize();

    // Clear screen
    gl::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gl::glViewport(0, 0, width, height);
    gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0);
}

void Renderer::window_resize(const int width, const int height) {
    gl::glViewport(0, 0, width, height);
}
