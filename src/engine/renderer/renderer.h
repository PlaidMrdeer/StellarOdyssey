#ifndef RENDERER_H
#define RENDERER_H

#include "../core.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace stellar {

struct Vertex {
    glm::vec3 position;
    // 后续可以添加更多属性，如：
    // glm::vec3 normal;
    // glm::vec2 texCoord;
    // glm::vec4 color;
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
    
    void draw_vertices(const std::vector<Vertex>& vertices);
    void set_shader(std::shared_ptr<Shader> shader) { shader_ = shader; }

private:
    unsigned int VAO_, VBO_;
    std::shared_ptr<Shader> shader_;
    std::vector<Vertex> vertex_buffer_;
    
    static const size_t MAX_VERTICES = 1000;  // 可以根据需要调整
};

} // namespace stellar

#endif // RENDERER_H 