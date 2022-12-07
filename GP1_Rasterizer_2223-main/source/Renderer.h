#pragma once

#include <cstdint>
#include <vector>

#include "Camera.h"
#include "DataTypes.h"

struct SDL_Window;
struct SDL_Surface;

namespace dae
{
	class Texture;
	struct Mesh;
	struct Vertex;
	class Timer;
	class Scene;

	class Renderer final
	{
	public:
		Renderer(SDL_Window* pWindow);
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		void Update(Timer* pTimer);
		void Render();

		bool SaveBufferToImage() const;
		void CycleRenderMode();

	private:
		void RenderLoop();
		void PixelLoop(const Triangle& t, const BoundingBox& bb);

		SDL_Window* m_pWindow{};

		SDL_Surface* m_pFrontBuffer{ nullptr };
		SDL_Surface* m_pBackBuffer{ nullptr };
		uint32_t* m_pBackBufferPixels{};

		float* m_pDepthBufferPixels{};
		
		Mesh m_Mesh{};
		Camera m_Camera{};
		Matrix m_WorldMatrix{};
		Matrix m_ViewMatrix{};
		Matrix m_ProjectionMatrix{};

		Matrix m_WorldViewProjectionMatrix{ };
	
		RenderMode m_CurrentRenderMode{ RenderMode::DepthBuffer };

		Texture* m_pTexture{ nullptr };

		int m_Width{};
		int m_Height{};
		
		void InitializeMesh();
		void VertexTransformationFunction(Mesh& mesh); 
		void UpdateWorldViewProjectionMatrix(const Matrix& worldMatrix, const Matrix& viewMatrix, const Matrix& projectionMatrix);
		void ParseMesh(Mesh mesh, std::vector<Vertex>& vertices_out);
		
		bool IsVertexInFrustum(const Vertex_Out& v);
		bool IsTriangleInFrustum(const Triangle& t);
		bool IsPointInTri(Vector2 P, const Triangle& t, float(&weights)[3]) const;

		BoundingBox GenerateBoundingBox(const Triangle t) const;

		float Remap(float value, float rangeMin, float rangeMax);

	
	};
}
