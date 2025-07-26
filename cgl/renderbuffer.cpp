#include <cgl/renderbuffer.h>
#include <glad/glad.h>

CGL::RenderBuffer::RenderBuffer()
{
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
}
