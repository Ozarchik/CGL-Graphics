#pragma once

#include <glad/glad.h>
#include <vector>

namespace CGL {

enum BufferType {
    VertexBufferType = GL_ARRAY_BUFFER,
    ElementBufferType = GL_ELEMENT_ARRAY_BUFFER,
};

template <typename T>
struct Buffer {
public:
    Buffer() = default;
	Buffer(const std::vector<T>& array, BufferType type) {
		setVector(array, type);
	}

	void setVector(const std::vector<T>& array, BufferType type) {
		m_type = type;
		glGenBuffers(1, &m_id);

		glBindBuffer(m_type, m_id);
		glBufferData(m_type, array.size()*sizeof(T), array.data(), GL_STATIC_DRAW);
	}

public:
	GLuint m_id;
	BufferType m_type;
};
}
