#include "cgl/shader.h"
#include <cgl/mesh/common/meshbuffer.h>

#include <glad/glad.h>

CGL::MeshBuffer::MeshBuffer(const std::vector<CGL::Vertex> &vertices, const std::vector<TextureBase> &textures, const std::vector<unsigned int> &indices)
    : vertices(vertices), textures(textures), indices(indices)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(CGL::Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, texcoord));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, color));

    glBindVertexArray(0);
}

void CGL::MeshBuffer::setTextures(const std::vector<TextureBase>& newTextures)
{
    textures = newTextures;
}

void CGL::MeshBuffer::bind(CGL::Shader* shader)
{
    glBindVertexArray(vao);

    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;

    for(unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        CGL::TextureBase texture = textures[i];
        std::string number;
        std::string name = texture.type;
        // std::cout << "texture type: " << name << std::endl;

        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);
        else if(name == "texture_normal")
            number = std::to_string(normalNr++);
        else if(name == "texture_height")
            number = std::to_string(heightNr++);
        else {
            name = "texture_diffuse";
            number = std::to_string(diffuseNr++);
        }


        if (shader) {
            // shader->setInt("texture_diffuse1", i);
            shader->setInt((name + number).c_str(), i);
        }

        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glActiveTexture(GL_TEXTURE0);

    // for(unsigned int i = 0; i < textures.size(); i++) {
    //     glActiveTexture(GL_TEXTURE0 + i);
    //     glBindTexture(GL_TEXTURE_2D, textures[i].id);
    // }
}

void CGL::MeshBuffer::unbind()
{
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
