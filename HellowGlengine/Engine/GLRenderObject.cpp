#include "stdafx.h"
#include "GLRenderObject.h"

#include "GLEffect.h"
#include "EInputLayout.h"
#include "OpenGLExtensions.h"

struct VertexInput
{
	float x, y, z;
	float u, v;
};

CGLRenderObject::CGLRenderObject()
	: myEffect(nullptr)
	, myVertexCount(0)
	, myIndexCount(0)
	, myVertexArrayID(0u)
	, myVertexBufferID(0u)
	, myIndexBufferID(0u)
{
}

CGLRenderObject::~CGLRenderObject()
{
	SAFE_DELETE(myEffect);

	glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);

	// Release the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &myVertexBufferID);

	// Release the index buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &myIndexBufferID);

	// Release the vertex array object.
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &myVertexArrayID);
}

bool CGLRenderObject::Init()
{
	myVertexCount = 4;
	myIndexCount = 6;

	VertexInput vertices[4];
	unsigned int indices[6];

	// Bottom left.
	vertices[0].x = -1.0f;
	vertices[0].y = -1.0f;
	vertices[0].z = 0.0f;

	vertices[0].u = 0.0f;
	vertices[0].v = 0.0f;

	// Top left.
	vertices[1].x = -1.0f;
	vertices[1].y = 1.0f;
	vertices[1].z = 0.0f;

	vertices[0].u = 0.0f;
	vertices[0].v = 1.0f;

	// Top right.
	vertices[2].x = 1.0f;
	vertices[2].y = 1.0f;
	vertices[2].z = 0.0f;

	vertices[0].u = 1.0f;
	vertices[0].v = 1.0f;

	// Bottom right.
	vertices[3].x = 1.0f;
	vertices[3].y = -1.0f;
	vertices[3].z = 0.0f;

	vertices[0].u = 1.0f;
	vertices[0].v = 0.0f;

	for (int i = 0; i < 4; i++)
	{
		vertices[i].x *= 0.5f;
		vertices[i].y *= 0.5f;
	}

	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top left.
	indices[2] = 3;  // Bottom right.
	indices[3] = 3;  // Bottom right.
	indices[4] = 1;  // Top left.
	indices[5] = 2;  // Top right.


	glGenVertexArrays(1, &myVertexArrayID);
	glBindVertexArray(myVertexArrayID);

	glGenBuffers(1, &myVertexBufferID);

	glBindBuffer(GL_ARRAY_BUFFER, myVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, myVertexCount * sizeof(VertexInput), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); //position
	glEnableVertexAttribArray(1); //uv



// Specify the location and format of the position portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, myVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexInput), 0);

	// Specify the location and format of the color portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, myVertexBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexInput), (unsigned char*)NULL + (3 * sizeof(float)));

	glGenBuffers(1, &myIndexBufferID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, myIndexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	//myEffect = new CGLEffect();
	//myEffect->Init("Shaders/VS_", "", "Shaders/FS_", eInputLayout::eInputLayout_ePos);

	return true;
}

void CGLRenderObject::Render()
{
	//myEffect->Activate();

	glBindVertexArray(myVertexArrayID);
	glDrawElements(GL_TRIANGLES, myIndexCount, GL_UNSIGNED_INT, 0);
}
