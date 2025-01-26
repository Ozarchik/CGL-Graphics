#include "scene.h"


void CGL::Scene::render(Shader& Shader)
{
    Shader.use();

    for (const auto obj: m_meshes) {
        obj->draw(Shader);
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
