#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <cgl/shader.h>
#include <cgl/vertex.h>
#include <cgl/mesh/common/meshbuffer.h>
#include <cgl/mesh/common/meshglobals.h>
#include <cgl/mesh/common/meshcontroller.h>
#include <cgl/stb_image.h>


namespace CGL {
class Mesh {
    friend class MeshContoller;

public:
    explicit Mesh(const std::vector<Vertex>& vertices = {}, const std::vector<unsigned int>& indices = {});

    virtual ~Mesh() = default;
    virtual void setup();
    virtual void draw(Shader& Shader);

    void setPrimitiveType(GLenum type);

protected:
    CGL::MeshBuffer m_buffer;
    GLenum m_primitiveType = GL_TRIANGLES;
    CGL::ColorRenderMode m_colorRenderMode;
    CGL::MeshController m_controller;
};
}
