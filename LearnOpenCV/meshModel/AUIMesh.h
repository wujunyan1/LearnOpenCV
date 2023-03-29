#pragma once
#include "../math/Math.h"
#include "../file/Image.h"
#include "../render/RenderUIMesh.h"
#include "../render/Texture.h"
#include "ABaseMesh.h"

namespace Core
{
	class AUIMesh: public ABaseMesh
	{
		friend class AModel;
	public:
		struct Vertex {
			// position
			Math::Vector3 Position;
			// texCoords
			Math::Vector2 TexCoords;
		};

	public:
		AUIMesh(std::string uid = "");
		AUIMesh(std::string uid, std::vector<Vertex> vertices, std::vector<unsigned int> indices);
		~AUIMesh();

		virtual int getMeshType() { return AUIMesh::MeshType; };

		virtual Render::RenderBaseMesh* getRenderMesh()
		{
			return mesh;
		};

		void updateMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

		AUIMesh* clone();

		static AUIMesh* getBaseAUIMesh(std::string name) {
			auto it = baseAUIMesh.find(name);
			if (it != baseAUIMesh.end())
			{
				return it->second;
			}
			AUIMesh* base = new AUIMesh(name);
			baseAUIMesh.insert(std::pair<std::string, AUIMesh*>(name, base));
			return base;
		};

		static void initEngine();
	private:

		void bindRender();

	private:
		std::string id;

		// mesh Data
		std::vector<Vertex>       vertices;
		std::vector<unsigned int> indices;

		Render::RenderUIMesh* mesh;

	public:
		const static int MeshType = 2;

	private:
		static std::map<std::string, AUIMesh*> baseAUIMesh;
	};
}
