#include <cgl/framebuffer.h>
#include <glad/glad.h>

CGL::FrameBuffer::FrameBuffer(int width, int height)
{
    glGenTextures(1, &m_texture);
    glGenFramebuffers(1, &m_fbo);
    glGenRenderbuffers(1, &m_rbo);

    rescale(width, height);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "FrameBuffer compliete error" << std::endl;
    }

    // float frameVertices[] = {
    //     -1.0f,  1.0f,  0.0f, 1.0f,
    //     -1.0f, -1.0f,  0.0f, 0.0f,
    //      1.0f, -1.0f,  1.0f, 0.0f,

    //     -1.0f,  1.0f,  0.0f, 1.0f,
    //      1.0f, -1.0f,  1.0f, 0.0f,
    //      1.0f,  1.0f,  1.0f, 1.0f
    // };

    // glGenVertexArrays(1, &vao);
    // glGenBuffers(1, &vbo);
    // glBindVertexArray(vao);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(frameVertices), &frameVertices, GL_STATIC_DRAW);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

CGL::FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_fbo);
}

void CGL::FrameBuffer::bind()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glStencilMask(0x00);
}

void CGL::FrameBuffer::setStencil(GLenum mode, unsigned char mask)
{
    glStencilFunc(mode, 1, 0xff);
    glStencilMask(mask);
}

void CGL::FrameBuffer::enableDepth(bool mode)
{
    if (mode)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}

void CGL::FrameBuffer::use()
{
    // glBindVertexArray(m_vao);
    // glBindTexture(GL_TEXTURE_2D, texture);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
}

void CGL::FrameBuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
}

unsigned int CGL::FrameBuffer::texture() const
{
    return m_texture;
}