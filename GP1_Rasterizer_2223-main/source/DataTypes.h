#pragma once
#include "Math.h"
#include "vector"

namespace dae
{
	struct Vertex
	{
		Vector3 position{};
		ColorRGB color{colors::White};
		Vector2 uv{}; 
		Vector3 normal{}; 
		Vector3 tangent{}; 
		//Vector3 viewDirection{}; //W4
	};

	struct Vertex_Out
	{
		Vector4 position{};
		ColorRGB color{ colors::White };
		Vector2 uv{};
		Vector3 normal{};
		Vector3 tangent{};
		//Vector3 viewDirection{};
	};

	struct BoundingBox
	{
		int minX;
		int minY;
		int maxX;
		int maxY;
	};

	enum class PrimitiveTopology
	{
		TriangeList,
		TriangleStrip
	};

	enum class RenderMode
	{
		FinalColor,
		DepthBuffer
	};

	struct Mesh
	{
		std::vector<Vertex> vertices{};
		std::vector<uint32_t> indices{};
		PrimitiveTopology primitiveTopology{ PrimitiveTopology::TriangleStrip };

		std::vector<Vertex_Out> vertices_out{};
		Matrix worldMatrix{};
	};



	struct Triangle
	{
		Vertex_Out vertices[3]{};
		Vector2 edges[3]{};
		float recipTotalArea{};
		float weights[3]{};


		Vector2 GetVector2Pos(int idx) const 
		{ 
			return { vertices[idx].position.x, vertices[idx].position.y };
		};
	};

	struct TriangleMesh
	{
		std::vector<Triangle> triangles{};
		Matrix worldMatrix{};
	};
}