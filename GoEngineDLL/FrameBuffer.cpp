#include "FrameBuffer.h"
#include "GlInclude.h"
#include "Window.h"

void FrameBuffer::Init() {
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	// create a color attachment texture
	texture = new Texture();
	texture->CreateTexture(NULL,windowsSize.x, windowsSize.y, 3, "");
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->GetTextureID(), 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &depth);
	glBindRenderbuffer(GL_RENDERBUFFER, depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowsSize.x, windowsSize.y); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, attachments);
	if (!IsComplete())
		PRINT_DEBUG("ERROR ON FRAME BUFFER INIT");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLfloat vertices[] =
	{
		// Pos        // Tex

		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,

		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &fullscreenQuad_VAO);
	glBindVertexArray(fullscreenQuad_VAO);

	glGenBuffers(1, &fullscreenQuad_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, fullscreenQuad_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void FrameBuffer::InitGBuffer() {
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	// Create the gbuffer textures
	for (unsigned int i = 0; i < 3; i++) {
		Texture* texture = new Texture();
		texture->CreateTexture(NULL, windowsSize.x, windowsSize.y, 3, "");
		textures[i] = texture;
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures[i]->GetTextureID(), 0);
	}
	// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);
	// depth
	glBindTexture(GL_TEXTURE_2D, depth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, windowsSize.x, windowsSize.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT,NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth, 0);

	unsigned int drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, drawBuffers);

	// finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	multipleTextures = true;
}

void FrameBuffer::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FrameBuffer::BindWriting() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}

void FrameBuffer::BindReading() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
	if (!multipleTextures) { return; }
	for (int i = 0; i < 3; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[GBUFFER_TEXTURE_TYPE_POSITION + i]->GetTextureID());
	}
}

void FrameBuffer::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::DeleteBuffers() {
	if (texture) {
		delete texture;
	}
	if (depth) {
		glDeleteRenderbuffers(1, &depth);
		depth = 0;
	}
	if (fbo) {
		glDeleteFramebuffers(1, &fbo);
		fbo = 0;
	}
}

void FrameBuffer::BindTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
}

void FrameBuffer::BindTextures() {
	for (size_t i = 0; i < 3; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]->GetTextureID());
	}
}

bool FrameBuffer::IsComplete() {
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void FrameBuffer::SetReadBuffer(BufferTextureType type) {
	glReadBuffer(GL_COLOR_ATTACHMENT0 + type);
	glBlitFramebuffer(0, 0, windowsSize.x, windowsSize.y, 0, 0, windowsSize.x, windowsSize.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void FrameBuffer::ShowTexture(BufferTextureType type, int width, int height, int x, int y) {
	glReadBuffer(GL_COLOR_ATTACHMENT0 + type);
	glBlitFramebuffer(0, 0, windowsSize.x, windowsSize.y, x, y, windowsSize.x, windowsSize.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void FrameBuffer::DrawToScreen() {
	glBindVertexArray(fullscreenQuad_VAO);
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

Texture* FrameBuffer::GetTexture(BufferTextureType type) const {
	return textures[type];
}

Texture* FrameBuffer::GetTexture() const {
	return texture;
}

FrameBuffer::FrameBuffer() {
	windowsSize = Window::GetSingleton()->GetSize();
}

FrameBuffer::~FrameBuffer() {
}
