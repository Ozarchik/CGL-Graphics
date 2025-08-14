#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cgl/shader.h>
#include <cgl/vertex.h>
#include <cgl/mesh/common/meshbuffer.h>
#include <cgl/rendercontext.h>
#include <cgl/stb_image.h>


namespace CGL {

struct BoundingBox {
    glm::vec3 min;
    glm::vec3 max;
};

class Mesh {
public:
    explicit Mesh(const std::vector<Vertex>& vertices = {}, const std::vector<unsigned int>& indices = {});

    virtual ~Mesh() = default;
    virtual void setup();
    virtual void draw(Shader& Shader);
    virtual CGL::BoundingBox boundingBox() const;

    void setPrimitiveType(GLenum type);

protected:
    CGL::MeshBuffer m_buffer;
    CGL::PrimitiveData m_primitiveData;
};
}
