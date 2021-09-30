#include "FrameBuffer.h"
#include "GlInclude.h"
#include "Window.h"

void FrameBuffer::Init() {
	// create fbo
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// create texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_COLOR_ATTACHMENT0, windowsSize.x, windowsSize.y, 0, GL_COLOR_ATTACHMENT0, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	// create rbo
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowsSize.x, windowsSize.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo));
	
	// unbound
	if (!FrameBufferComplete()) {
		PRINT_DEBUG("FRAME BUFFER ERROR");
	};
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FrameBuffer::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::DeleteBuffers() {
	if (texture) {
		glDeleteTextures(1, &texture);
		texture = 0;
	}
	if (depth) {
		glDeleteRenderbuffers(1, &depth);
		depth = 0;
	}
	if (stencil) {
		glDeleteRenderbuffers(1, &stencil);
		stencil = 0;
	}
	if (rbo) {
		glDeleteRenderbuffers(1, &rbo);
		rbo = 0;
	}
	if (fbo) {
		glDeleteFramebuffers(1, &fbo);
		fbo = 0;
	}
}

bool FrameBuffer::FrameBufferComplete() {
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

FrameBuffer::FrameBuffer() {
	windowsSize = Window::GetSingleton()->GetSize();
}

FrameBuffer::~FrameBuffer() {
}
