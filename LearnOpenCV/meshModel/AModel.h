#pragma once

// https://github.com/assimp/assimp.git
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../math/Math.h"
#include "AMesh.h"
#include "ABaseMesh.h"
#include "AUIMesh.h"
#include "../file/ImageLoad.h"
#include "../file/FilePathManager.h"

#include "../render/Texture.h"

namespace Core
{
	class AModel
	{
	public:
		AModel();

		// constructor, expects a filepath to a 3D model.
		AModel(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
		{
            modelId = Math::getUid();
			loadModel(path);
		}

        ~AModel();

        std::vector<ABaseMesh*> getMeshs() { return meshes; };
        AMesh* addMesh(std::vector<AMesh::Vertex> vertices, std::vector<unsigned int> indices, std::vector<Render::Texture> textures);
        ABaseMesh* addMesh(std::string meshName, std::vector<AMesh::Vertex> vertices, std::vector<unsigned int> indices, std::vector<Render::Texture> textures);
        AUIMesh* createNewUIMesh();
        AUIMesh* addBaseUIMesh(std::string name);

        ABaseMesh* getMesh(std::string meshName)
        {
            for (auto mesh : meshes)
            {
                if (mesh->id == meshName)
                {
                    return mesh;
                }
            }
            return nullptr;
        }

        Math::Obb& getObb() { return obb; };

	private:
        // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
        void loadModel(std::string const& path)
        {
            // modelId = Math::getUid();
            printf("loadModel %d %s \n", modelId, path.c_str());
            std::string s = std::string(FilePathManager::getRootPath());
            // read file via ASSIMP
            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(s + path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
            // check for errors
            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
            {
                printf("ERROR::ASSIMP:: %s", importer.GetErrorString());
                return;
            }
            // retrieve the directory path of the filepath
            directory = path.substr(0, path.find_last_of('/'));

            std::vector<Math::Vector3> points;
            // process ASSIMP's root node recursively
            processNode(scene->mRootNode, scene, points);

            obb = Math::Obb(points);


        }

        // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
        void processNode(aiNode* node, const aiScene* scene, std::vector<Math::Vector3>& points)
        {
            // process each mesh located at the current node

            printf("mNumMeshes %d\n", node->mNumMeshes);
            for (unsigned int i = 0; i < node->mNumMeshes; i++)
            {
                // the node object only contains indices to index the actual objects in the scene. 
                // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
                aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                meshes.push_back(processMesh(meshes.size(), mesh, scene, points));
            }
            // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
            for (unsigned int i = 0; i < node->mNumChildren; i++)
            {
                processNode(node->mChildren[i], scene, points);
            }

        }

        AMesh* processMesh(unsigned int index, aiMesh* mesh, const aiScene* scene, std::vector<Math::Vector3>& points)
        {
            // data to fill
            std::vector<AMesh::Vertex> vertices;
            std::vector<unsigned int> indices;
            std::vector<Render::Texture> textures;

            // walk through each of the mesh's vertices
            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                AMesh::Vertex vertex;
                Math::Vector3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
                // positions
                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z;
                vertex.Position = vector;
                points.push_back(vertex.Position);
                // normals
                if (mesh->HasNormals())
                {
                    vector.x = mesh->mNormals[i].x;
                    vector.y = mesh->mNormals[i].y;
                    vector.z = mesh->mNormals[i].z;
                    vertex.Normal = vector;
                }
                // texture coordinates
                if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
                {
                    Math::Vector2 vec;
                    // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                    // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                    vec.x = mesh->mTextureCoords[0][i].x;
                    vec.y = mesh->mTextureCoords[0][i].y;
                    vertex.TexCoords = vec;
                    // tangent
                    vector.x = mesh->mTangents[i].x;
                    vector.y = mesh->mTangents[i].y;
                    vector.z = mesh->mTangents[i].z;
                    vertex.Tangent = vector;
                    // bitangent
                    vector.x = mesh->mBitangents[i].x;
                    vector.y = mesh->mBitangents[i].y;
                    vector.z = mesh->mBitangents[i].z;
                    vertex.Bitangent = vector;
                }
                else
                    vertex.TexCoords = { 0.0f, 0.0f };

                vertices.push_back(vertex);
            }
            // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
            for (unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                // retrieve all indices of the face and store them in the indices vector
                for (unsigned int j = 0; j < face.mNumIndices; j++)
                    indices.push_back(face.mIndices[j]);
            }
            // process materials
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
            // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
            // Same applies to other texture as the following list summarizes:
            // diffuse: texture_diffuseN
            // specular: texture_specularN
            // normal: texture_normalN

            // 1. diffuse maps
            std::vector<Render::Texture> diffuseMaps = loadMaterialTextures(scene, material, aiTextureType_DIFFUSE, "material.diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            // 2. specular maps
            std::vector<Render::Texture> specularMaps = loadMaterialTextures(scene, material, aiTextureType_SPECULAR, "material.specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            // 3. ambient maps
            std::vector<Render::Texture> ambientMaps = loadMaterialTextures(scene, material, aiTextureType_AMBIENT, "material.ambient");
            textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());
            // 4. normal maps
            std::vector<Render::Texture> normalMaps = loadMaterialTextures(scene, material, aiTextureType_NORMALS, "material.normal");
            textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
            // 5. height maps
            std::vector<Render::Texture> heightMaps = loadMaterialTextures(scene, material, aiTextureType_HEIGHT, "material.height");
            textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

            //mesh->mName
            aiString meshName = mesh->mName;
            if (meshName.length == 0)
            {
                meshName = std::to_string(index);
            }
            // return a mesh object created from the extracted mesh data
            return new AMesh( Math::stringFormat("%d|%s", modelId, meshName.C_Str()), vertices, indices, textures);
        }

        // checks all material textures of a given type and loads the textures if they're not loaded yet.
        // the required info is returned as a Texture struct.
        std::vector<Render::Texture> loadMaterialTextures(const aiScene* scene, aiMaterial* mat, aiTextureType type, std::string typeName)
        {
            printf("loadMaterialTextures  %d %s \n", mat->GetTextureCount(type), typeName.c_str());
            std::vector<Render::Texture> textures;
            for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
            {
                aiString str;
                mat->GetTexture(type, i, &str);
                printf("load image %s \n", str.C_Str());

                if (str.data[0] == '*') {
                    std::string textureName = std::string(str.data);
                    std::string subName = textureName.substr(1, textureName.length() - 1);
                    int textureId = std::stoi(subName);
                    const aiTexture* aitexture = scene->mTextures[i];

                    Image* image = ImageLoad::LoadImageByMemory(directory + "/" + subName, aitexture);

                    Render::Texture texture;
                    texture.image = image;
                    texture.imageName = str.C_Str();
                    texture.uniformName = typeName;
                    textures.push_back(texture);
                }
                else 
                {
                    Image* image = ImageLoad::LoadImage(directory + "/" + str.C_Str()); // TextureFromFile(str.C_Str(), this->directory);

                    Render::Texture texture;
                    texture.image = image;
                    texture.imageName = str.C_Str();
                    texture.uniformName = typeName;
                    textures.push_back(texture);
                }

            }
            return textures;
        }

        void updateObb();

	private:
		std::vector<ABaseMesh*>    meshes;
		std::string directory;
        unsigned int modelId;
		bool gammaCorrection;
        Math::Obb obb;
	};

    class AModelFactory
    {
    public:
        static AModel* createModel(std::string path);
        static AModel* createCustomModel();

    private: 
        static std::map<std::string, AModel*>* models;
    };
}
