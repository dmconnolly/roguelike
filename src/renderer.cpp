#include "glbinding/gl/functions.h"
#include "glbinding/gl/enum.h"

#include "renderer.hpp"

Renderer::Renderer(const glm::ivec2 window_size) :
    window_size(window_size)
{
    gl::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gl::glViewport(0, 0, window_size.x, window_size.y);
    gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0);
}

void Renderer::window_resize(const glm::ivec2 window_size) {
    this->window_size = window_size;
    gl::glViewport(0, 0, window_size.x, window_size.y);
}
