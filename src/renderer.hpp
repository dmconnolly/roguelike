#pragma once
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "glm/glm.hpp"

class Renderer {
public:
    Renderer(const glm::ivec2 window_size);
    ~Renderer() = default;
    void window_resize(const glm::ivec2 window_size);

private:
    glm::ivec2 window_size;
};

#endif /* RENDERER */
