#include <cgl/framebuffer.h>
#include <glad/glad.h>
#include <iostream>

CGL::FrameBuffer::FrameBuffer(CGL::CoreContext& context)
    : m_context(context)
{
    glGenTextures(1, &m_texture);
    glGenFramebuffers(1, &m_fbo);
    glGenRenderbuffers(1, &m_rbo);

    rescale(m_context.width(), m_context.height());

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "FrameBuffer compliete error" << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

CGL::FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_fbo);
    glDeleteTextures(1, &m_texture);
    glDeleteRenderbuffers(1, &m_rbo);
}

void CGL::FrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    m_context.setStencilEnable(true);
    m_context.setStencilMask(true);
    m_context.setStencilFunction(CGL::CoreContext::BufferCheckFunction::Less);

    m_context.setDepthEnable(true);
    m_context.setDepthWriteMode(true);
    m_context.setDepthFunction(CGL::CoreContext::BufferCheckFunction::Less);

    m_context.setBuffersToClear(CGL::CoreContext::BuffersToClear::All);
    m_context.update();
}

void CGL::FrameBuffer::unbind()
{
    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete: " << fboStatus << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}

void CGL::FrameBuffer::detach()
{
    glDeleteFramebuffers(1, &m_fbo);
}

void CGL::FrameBuffer::rescale(int width, int height)
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
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
