#pragma once

#include <Wire.h>

class Sandbox2D : public Wire::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Wire::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Wire::Event& e) override;
private:
	Wire::OrthographicCameraController m_CameraController;
	
	Wire::Ref<Wire::VertexArray> m_SquareVA;
	Wire::Ref<Wire::Shader> m_FlatColourShader;

	Wire::Ref<Wire::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColour = { 0.2f, 0.3f, 0.8f, 1.0f };
};