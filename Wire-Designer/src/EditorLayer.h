#pragma once

#include <Wire.h>

namespace Wire {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Wire::Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Wire::Event& e) override;

		bool PrintSize(WindowResizeEvent& e);
	private:
		Wire::OrthographicCameraController m_CameraController;

		Wire::Ref<Wire::VertexArray> m_SquareVA;
		Wire::Ref<Wire::Shader> m_FlatColourShader;
		Wire::Ref<Wire::Framebuffer> m_Framebuffer;

		Wire::Ref<Wire::Texture2D> m_CheckerboardTexture;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 1280.0f, 720.0f };

		glm::vec4 m_SquareColour = { 0.2f, 0.3f, 0.8f, 1.0f };

	};

}
