#pragma once
#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer {
public:
    Renderer();
    ~Renderer() = default;
    void window_resize(const int width, const int height);
private:
    /* Empty */
};

#endif /* RENDERER */
