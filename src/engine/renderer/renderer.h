#ifndef RENDERER_H
#define RENDERER_H

#include "../core.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace stellar {

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    
    Vertex(const glm::vec3& pos, const glm::vec4& col = glm::vec4(1.0f))
        : position(pos), color(col) {}
};

class Shader;

class STELLAR_API Renderer {
public:
    Renderer();
    ~Renderer();

    void init();
    void begin_batch();
    void end_batch();
    void flush();
    
    // 基础图形绘制函数
    void draw_triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, 
                      const glm::vec4& color = glm::vec4(1.0f));
    void draw_quad(const glm::vec3& position, const glm::vec2& size, 
                  const glm::vec4& color = glm::vec4(1.0f));
    void draw_vertices(const std::vector<Vertex>& vertices);

    void set_shader(std::shared_ptr<Shader> shader) { shader_ = shader; }

private:
    unsigned int VAO_, VBO_;
    std::shared_ptr<Shader> shader_;
    std::vector<Vertex> vertex_buffer_;
    
    static const size_t MAX_VERTICES = 1000;
};

} // namespace stellar

#endif // RENDERER_H 