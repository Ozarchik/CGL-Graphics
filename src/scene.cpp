#include "scene.h"


void CGL::Scene::render(ShaderProgram& shaderProgram)
{
    shaderProgram.use();

    for (const auto obj: m_meshes) {
        obj->draw(shaderProgram);
    }
}

void CGL::Scene::addMesh(Mesh* mesh)
{
    m_meshes.push_back(mesh);
}

void CGL::Scene::clear()
{
    for (auto mesh: m_meshes) {
        delete mesh;
    }

    m_meshes.clear();
}
