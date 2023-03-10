#include "CoreFramework.h"

GPUMesh* ModelLoader::loadMesh(GPUContext* context, std::string file)
{

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	std::vector<Vertex> vertices;
	std::vector<int> indices;

	if (scene->HasMeshes()) {
		for (int index = 0; index < scene->mNumMeshes; index++) {
			aiMesh* mesh = scene->mMeshes[index];
			int indexOffset = vertices.size() / 8;
			for (int i = 0; i < mesh->mNumVertices; i++) {
				int indice = i;

				Vertex vertex;

				vertex.position.x = mesh->mVertices[indice].x;
				vertex.position.y = mesh->mVertices[indice].y;
				vertex.position.z = mesh->mVertices[indice].z;

				if (mesh->HasTextureCoords(0)) {
					vertex.texCoord.x = mesh->mTextureCoords[0][indice].x;
					vertex.texCoord.y = 1.0f - mesh->mTextureCoords[0][indice].y;
				}
				else {
					vertex.texCoord.x = 0.0f;
					vertex.texCoord.y = 0.0f;
				}

				vertex.normal.x = mesh->mNormals[indice].x;
				vertex.normal.y = mesh->mNormals[indice].y;
				vertex.normal.z = mesh->mNormals[indice].z;

				vertices.push_back(vertex);
			}
			for (int i = 0; i < mesh->mNumFaces; i++) {
				indices.push_back(indexOffset + mesh->mFaces[i].mIndices[2]);
				indices.push_back(indexOffset + mesh->mFaces[i].mIndices[1]);
				indices.push_back(indexOffset + mesh->mFaces[i].mIndices[0]);
			}
		}
	}
	return context->createMesh(&vertices[0], vertices.size(), &indices[0], indices.size());
}
