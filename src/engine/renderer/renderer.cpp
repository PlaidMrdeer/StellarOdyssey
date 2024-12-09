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
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    
    glBindVertexArray(0);
    
    STELLAR_CORE_INFO("渲染器初始化完成");
}

void Renderer::begin_batch() {
    vertex_buffer_.clear();
}

void Renderer::end_batch() {
    flush();
}

void Renderer::flush() {
    if (vertex_buffer_.empty()) {
        STELLAR_CORE_WARN("顶点缓冲区为空");
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
    
    STELLAR_CORE_INFO("绘制了 {} 个顶点", vertex_buffer_.size());
    
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