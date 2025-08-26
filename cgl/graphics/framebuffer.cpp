#include <cgl/graphics/framebuffer.h>
#include <cgl/graphics/texture/texture.h>
#include <glad/glad.h>
#include <iostream>

const char* framebufferStatusToString(GLenum status) {
    switch(status) {
    case GL_FRAMEBUFFER_COMPLETE: return "Complete";
    case GL_FRAMEBUFFER_UNDEFINED: return "Undefined";
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: return "Incomplete attachment";
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: return "Missing attachment";
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: return "Incomplete draw buffer";
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: return "Incomplete read buffer";
    case GL_FRAMEBUFFER_UNSUPPORTED: return "Unsupported";
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: return "Incomplete multisample";
    case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: return "Incomplete layer targets";
    default: return "Unknown error";
    }
}

CGL::FrameBuffer::FrameBuffer()
{
    glGenTextures(1, &m_texture);
    glGenFramebuffers(1, &m_fbo);
    m_currentFramebuffer = m_fbo;

    glGenRenderbuffers(1, &m_rbo);

    rescale(cglCoreContext().width(), cglCoreContext().height());

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "FrameBuffer compliete error: " << framebufferStatusToString(glCheckFramebufferStatus(GL_FRAMEBUFFER)) << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    CGL_CheckErros();
}

CGL::FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_fbo);
    glDeleteTextures(1, &m_texture);
    glDeleteRenderbuffers(1, &m_rbo);
}

void CGL::FrameBuffer::bind()
{
    CGL_CheckErros();
    glBindFramebuffer(GL_FRAMEBUFFER, m_currentFramebuffer);
    CGL_CheckErros();
    cglCoreContext().setStencilEnable(true);
    cglCoreContext().setStencilMask(true);
    cglCoreContext().setStencilFunction(CGL::CoreContext::BufferCheckFunction::Less);
    cglCoreContext().setDepthEnable(true);
    cglCoreContext().setDepthWriteMode(true);
    cglCoreContext().setDepthFunction(CGL::CoreContext::BufferCheckFunction::Less);
    cglCoreContext().setBuffersToClear(CGL::CoreContext::BuffersToClear::All);
    cglCoreContext().update();
    CGL_CheckErros();
}

void CGL::FrameBuffer::unbind()
{
    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete: " << framebufferStatusToString(fboStatus) << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}

void CGL::FrameBuffer::detach()
{
    glDeleteFramebuffers(1, &m_fbo);
    m_fbo = 0;
    m_currentFramebuffer = 0;
}

void CGL::FrameBuffer::rescale(int width, int height)
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
}

unsigned int CGL::FrameBuffer::texture() const
{
    return m_texture;
}

void CGL::FrameBuffer::bindDefaultFramebuffer()
{
    m_currentFramebuffer = 0;
}

void CGL::FrameBuffer::bindCustomFramebuffer()
{
    m_currentFramebuffer = m_fbo;
}
