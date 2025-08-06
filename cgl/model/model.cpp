#include <cgl/model/model.h>


// CGL::Model::Model(const std::vector<CGL::Mesh>& meshes)
//     : m_meshes(meshes)
// {
// }

void CGL::Model::draw(Shader &shader)
{
    // unsigned int diffuseNr  = 1;
    // unsigned int specularNr = 1;
    // unsigned int normalNr   = 1;
    // unsigned int heightNr   = 1;

    // for(unsigned int i = 0; i < m_textures.size(); i++) {
    //     glActiveTexture(GL_TEXTURE0 + i);

    //     CGL::Texture texture = m_textures[i];
    //     std::string number;
    //     std::string name = texture.type;

    //     if(name == "texture_diffuse")
    //         number = std::to_string(diffuseNr++);
    //     else if(name == "texture_specular")
    //         number = std::to_string(specularNr++);
    //     else if(name == "texture_normal")
    //         number = std::to_string(normalNr++);
    //     else if(name == "texture_height")
    //         number = std::to_string(heightNr++);

    //     shader.setInt((name + number).c_str(), i);
    //     glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    // }

    // for (auto& m: m_meshes) {
    //     m.draw(shader);
    // }

    // glActiveTexture(GL_TEXTURE0);
}
