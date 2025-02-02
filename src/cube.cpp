#include "cube.h"
#include <string>
#include <iostream>

CGL::Cube::Cube(const unsigned int& size)
    : Mesh(glm::vec3(0.0, 0.0, 0.0)), m_size(size)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, texcoord));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, color));
    glEnableVertexAttribArray(3);
}

CGL::Cube::Cube(const TextureBase &texture, const unsigned int &size)
    : Mesh(), m_size(size)
{
    m_textures.push_back(texture);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    m_coordBuffer.setVector(vectices, CGL::VertexBufferType);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);

    m_normalBuffer.setVector(normals, CGL::VertexBufferType);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    m_texureBuffer.setVector(texes, CGL::VertexBufferType);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    m_colorBuffer.setVector(colors, CGL::VertexBufferType);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(3);
}


CGL::Cube::Cube(const glm::vec3& pos, const unsigned int &size)
    : Mesh(pos), m_size(size)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    m_coordBuffer.setVector(vectices, CGL::VertexBufferType);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);

    m_normalBuffer.setVector(normals, CGL::VertexBufferType);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    m_texureBuffer.setVector(texes, CGL::VertexBufferType);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    m_colorBuffer.setVector(colors, CGL::VertexBufferType);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(3);
}

CGL::Cube::Cube(const glm::vec3 &pos, const TextureBase &texture, const unsigned int &size)
    : Mesh(pos), m_size(size)
{
    m_textures.push_back(texture);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    m_coordBuffer.setVector(vectices, CGL::VertexBufferType);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);

    m_normalBuffer.setVector(normals, CGL::VertexBufferType);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    m_texureBuffer.setVector(texes, CGL::VertexBufferType);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    m_colorBuffer.setVector(colors, CGL::VertexBufferType);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(3);
}

CGL::Cube::Cube(const glm::vec3& pos, const std::vector<CGL::TextureBase>& textures, const unsigned int &size)
    : Mesh(pos), m_size(size)
{
    m_textures = textures;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    m_coordBuffer.setVector(vectices, CGL::VertexBufferType);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);

    m_normalBuffer.setVector(normals, CGL::VertexBufferType);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    m_texureBuffer.setVector(texes, CGL::VertexBufferType);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    m_colorBuffer.setVector(colors, CGL::VertexBufferType);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(3);
}

CGL::Cube::Cube(const std::vector<Vertex>& vertices, const std::vector<CGL::TextureBase>& textures, const std::vector<unsigned int>& indices)
    : Mesh(vertices, textures, indices)
{

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
}

CGL::Cube::~Cube()
{

}

void CGL::Cube::draw(Shader &Shader) 
{

    for(unsigned int i = 0; i < m_textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        // glUniform1i(glGetUniformLocation(Shader.id(), (std::string("meterial.") + m_textures[i].type).c_str()), i);
        // glUniform1i(glGetUniformLocation(Shader.id(), (m_textures[i].type).c_str()), i);

        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }

    
    // draw mesh
    glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
    glDrawArrays(m_primitiveType, 0, 36);
    // glDrawArraysInstanced(m_primitiveType, 0, 36, 100);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}
