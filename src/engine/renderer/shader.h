#ifndef SHADER_H
#define SHADER_H

#include "../core.h"
#include <string>
#include <glm/glm.hpp>

namespace stellar {

class STELLAR_API Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void use();
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setFloat(const std::string& name, float value) const;

private:
    unsigned int ID;
    void checkCompileErrors(unsigned int shader, const std::string& type);
};

} // namespace stellar

#endif // SHADER_H 