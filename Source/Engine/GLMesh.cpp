#include "stdafx.h"
#include "GLMesh.h"

#include "GLEffect.h"
#include "EInputLayout.h"
#include "OpenGLExtensions.h"

struct VertexInput
{
	float x, y, z;
	float u, v;
};

namespace wendy
{
	CGLMesh::CGLMesh()
		: myVertexCount(0)
		, myIndexCount(0)
		, myVertexArrayID(0u)
		, myVertexBufferID(0u)
		, myIndexBufferID(0u)
	{
	}

	CGLMesh::CGLMesh(CGLMesh& aCopy)
		: myVertexCount(aCopy.myVertexCount)
		, myIndexCount(aCopy.myIndexCount)
		, myVertexArrayID(aCopy.myVertexArrayID)
		, myVertexBufferID(aCopy.myVertexBufferID)
		, myIndexBufferID(aCopy.myIndexBufferID)
	{
		aCopy.myVertexCount = 0;
		aCopy.myIndexCount = 0;
		aCopy.myVertexArrayID = 0;
		aCopy.myVertexBufferID = 0;
		aCopy.myIndexBufferID = 0;
	}

	CGLMesh::~CGLMesh()
	{
		Destroy();
	}

	CGLMesh& CGLMesh::operator=(CGLMesh& aCopy)
	{
		Destroy();

		myVertexCount = aCopy.myVertexCount;
		aCopy.myVertexCount = 0;

		myIndexCount = aCopy.myIndexCount;
		aCopy.myIndexCount = 0;

		myVertexArrayID = aCopy.myVertexArrayID;
		aCopy.myVertexArrayID = 0;

		myVertexBufferID = aCopy.myVertexBufferID;
		aCopy.myVertexBufferID = 0;

		myIndexBufferID = aCopy.myIndexBufferID;
		aCopy.myIndexBufferID = 0;

		return *this;
	}

	bool CGLMesh::Init()
	{
		myVertexCount = 4;
		myIndexCount = 6;

		VertexInput vertices[4];
		unsigned int indices[6];

		// Top left.
		vertices[0].x = 0.0f;
		vertices[0].y = 0.0f;
		vertices[0].z = 0.0f;

		vertices[0].u = 0.0f;
		vertices[0].v = 0.0f;

		// Bottom left.
		vertices[1].x = 0.0f;
		vertices[1].y = 1.0f;
		vertices[1].z = 0.0f;

		vertices[1].u = 0.0f;
		vertices[1].v = 1.0f;

		// Top right.
		vertices[2].x = 1.0f;
		vertices[2].y = 1.0f;
		vertices[2].z = 0.0f;

		vertices[2].u = 1.0f;
		vertices[2].v = 1.0f;

		// Bottom right.
		vertices[3].x = 1.0f;
		vertices[3].y = 0.0f;
		vertices[3].z = 0.0f;

		vertices[3].u = 1.0f;
		vertices[3].v = 0.0f;

		//for (int i = 0; i < 4; i++)
		//{
		//	vertices[i].x *= 0.5f;
		//	vertices[i].y *= 0.5f;
		//}

		indices[0] = 0;  // Top left.
		indices[1] = 1;  // Bottom left.
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

		return true;
	}

	bool CGLMesh::Init(const CU::StaticArray<SSpriteVertex, 4>& aVertices)
	{
		myVertexCount = aVertices.Size();
		myIndexCount = 6;

		unsigned int indices[6];

		indices[0] = 0;  // Top left.
		indices[1] = 1;  // Bottom left.
		indices[2] = 3;  // Bottom right.
		indices[3] = 3;  // Bottom right.
		indices[4] = 1;  // Top left.
		indices[5] = 2;  // Top right.

		glGenVertexArrays(1, &myVertexArrayID);
		glBindVertexArray(myVertexArrayID);

		glGenBuffers(1, &myVertexBufferID);

		glBindBuffer(GL_ARRAY_BUFFER, myVertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, myVertexCount * sizeof(SSpriteVertex), aVertices.AsVoidPointer(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0); //position
		glEnableVertexAttribArray(1); //uv

		// Specify the location and format of the position portion of the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, myVertexBufferID);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(SSpriteVertex), 0);

		// Specify the location and format of the color portion of the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, myVertexBufferID);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(SSpriteVertex), (unsigned char*)0 + (4 * sizeof(float)));

		glGenBuffers(1, &myIndexBufferID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIndexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, myIndexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		return true;
	}

	void CGLMesh::Render()
	{
		glBindVertexArray(myVertexArrayID);
		glDrawElements(GL_TRIANGLES, myIndexCount, GL_UNSIGNED_INT, 0);
	}

	void CGLMesh::Destroy()
	{
		if (myVertexBufferID != 0)
		{
			glDisableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDeleteBuffers(1, &myVertexBufferID);
			myVertexBufferID = 0;
		}

		if (myIndexBufferID != 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glDeleteBuffers(1, &myIndexBufferID);
			myIndexBufferID = 0;
		}

		if (myVertexArrayID != 0)
		{
			glBindVertexArray(0);
			glDeleteVertexArrays(1, &myVertexArrayID);
			myVertexArrayID = 0;
		}
	}
}
