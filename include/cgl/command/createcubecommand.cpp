#include <cgl/command/createcubecommand.h>
#include <cgl/resourcemanager.h>
#include <cgl/mesh/meshes3D.h>

CGL::CreateCubeCommand::CreateCubeCommand() {}

void CGL::CreateCubeCommand::execute(CGL::Scene& scene)
{
    CGL::Node* node = new CGL::Node(new CGL::Cube, CGL::ResourceManager::loadDefaultShader());
    scene.append(node);
}
