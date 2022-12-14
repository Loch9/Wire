#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	WR_PROFILE_FUNCTION();

	m_CheckerboardTexture = Wire::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	WR_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Wire::Timestep ts)
{
	WR_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);
	// Render
	{
		WR_PROFILE_SCOPE("Renderer Prep");
		Wire::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
		Wire::RenderCommand::Clear(); 
	}

	{
		WR_PROFILE_SCOPE("Renderer Draw");
		Wire::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Wire::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), {0.8f, 0.2f, 0.3f, 1.0f});
		Wire::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Wire::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f, {1.0f, 0.9f, 0.9f, 1.0f});
		Wire::Renderer2D::EndScene(); 
	}
}

void Sandbox2D::OnImGuiRender()
{
	WR_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Colour", glm::value_ptr(m_SquareColour));
	ImGui::End();
}

void Sandbox2D::OnEvent(Wire::Event& e)
{
	m_CameraController.OnEvent(e);
}
