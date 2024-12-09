#include "renderer.h"
#include "shader.h"
#include "../../tools/logger.h"
#include <glad/glad.h>

namespace stellar {

Renderer::Renderer() : VAO_(0), VBO_(0) {}

Renderer::~Renderer() {
    if (VAO_) glDeleteVertexArrays(1, &VAO_);
    if (VBO_) glDeleteBuffers(1, &VBO_);
}

void Renderer::init() {
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    
    STELLAR_CORE_INFO("VAO: {}, VBO: {}", VAO_, VBO_);

    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    
    // 预分配缓冲区
    glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

    // 设置顶点属性
    // 位置属性
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (void*)offsetof(Vertex, position));
    
    // 颜色属性
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (void*)offsetof(Vertex, color));
    
    glBindVertexArray(0);
    
    STELLAR_CORE_INFO("渲染器初始化完成");
}

void Renderer::draw_triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, 
                           const glm::vec4& color) {
    std::vector<Vertex> vertices = {
        Vertex(p1, color),
        Vertex(p2, color),
        Vertex(p3, color)
    };
    draw_vertices(vertices);
}

void Renderer::draw_quad(const glm::vec3& position, const glm::vec2& size, 
                        const glm::vec4& color) {
    float x = position.x;
    float y = position.y;
    float z = position.z;
    float w = size.x / 2.0f;
    float h = size.y / 2.0f;

    std::vector<Vertex> vertices = {
        // 第一个三角形
        Vertex(glm::vec3(x - w, y - h, z), color),
        Vertex(glm::vec3(x + w, y - h, z), color),
        Vertex(glm::vec3(x + w, y + h, z), color),
        
        // 第二个三角形
        Vertex(glm::vec3(x - w, y - h, z), color),
        Vertex(glm::vec3(x + w, y + h, z), color),
        Vertex(glm::vec3(x - w, y + h, z), color)
    };
    
    draw_vertices(vertices);
}

void Renderer::begin_batch() {
    vertex_buffer_.clear();
}

void Renderer::end_batch() {
    flush();
}

void Renderer::flush() {
    if (vertex_buffer_.empty()) {
        return;
    }
    
    if (!shader_) {
        STELLAR_CORE_ERROR("没有设置着色器程序！");
        return;
    }

    shader_->use();
    glBindVertexArray(VAO_);
    
    // 更新缓冲区数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 
                   vertex_buffer_.size() * sizeof(Vertex), 
                   vertex_buffer_.data());

    // 绘制
    glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_.size());
    
    glBindVertexArray(0);
    vertex_buffer_.clear();
}

void Renderer::draw_vertices(const std::vector<Vertex>& vertices) {
    if (vertex_buffer_.size() + vertices.size() > MAX_VERTICES) {
        flush();
    }
    
    vertex_buffer_.insert(vertex_buffer_.end(), vertices.begin(), vertices.end());
}

} // namespace stellar 