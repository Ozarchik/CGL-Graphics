#ifndef CGL_MESH_H
#define CGL_MESH_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cgl/graphics/shader.h>
#include <cgl/graphics/vertex/vertex.h>
#include <cgl/graphics/mesh/common/meshbuffer.h>
#include <cgl/core/rendercontext.h>
#include <stb/stb_image.h>


namespace cgl {

enum class MeshType {
    Mesh,
    Rectangle,
    Terrain,
    Sphere,
    Cube,
    Line
};

struct BoundingBox {
    glm::vec3 min;
    glm::vec3 max;
};

class Mesh {
public:
    explicit Mesh(const std::vector<Vertex>& vertices = {}, const std::vector<unsigned int>& indices = {});

    virtual ~Mesh() = default;

    Mesh(const Mesh& other) = delete;
    Mesh& operator=(const Mesh& other) = delete;

    virtual void setup();
    virtual void draw(Shader& Shader);
    virtual cgl::BoundingBox boundingBox() const;
    
    void setVAO(std::unique_ptr<VAOBuffer> &&vao);
    void setPrimitiveData(PrimitiveData data);
    void setPrimitiveType(RenderContext::Primitive type);

protected:
    cgl::MeshBuffer m_buffer;
    cgl::PrimitiveData m_primitiveData;
};
}

#endif
