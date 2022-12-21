#pragma once

#include <Wire.h>

class ExampleLayer : public Wire::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Wire::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Wire::Event& e) override;
private:
	Wire::ShaderLibrary m_ShaderLibrary;
	Wire::Ref<Wire::Shader> m_Shader;
	Wire::Ref<Wire::VertexArray> m_VertexArray;

	Wire::Ref<Wire::Shader> m_FlatColourShader;
	Wire::Ref<Wire::VertexArray> m_SquareVA;

	Wire::Ref<Wire::Texture2D> m_Texture, m_ChernoLogoTexture;

	Wire::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColour = { 0.2f, 0.3f, 0.8f };
};
