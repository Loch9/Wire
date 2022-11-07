#include <Wire.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Wire::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Wire::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		Wire::Ref<Wire::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Wire::VertexBuffer::Create(vertices, sizeof(vertices)));
		Wire::BufferLayout layout = {
			{ Wire::ShaderDataType::Float3, "a_Position" },
			{ Wire::ShaderDataType::Float4, "a_Colour" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Wire::Ref<Wire::IndexBuffer> indexBuffer;
		indexBuffer.reset(Wire::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Wire::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Wire::Ref<Wire::VertexBuffer> squareVB;
		squareVB.reset(Wire::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Wire::ShaderDataType::Float3, "a_Position" },
			{ Wire::ShaderDataType::Float2, "a_TexCoord" },
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Wire::Ref<Wire::IndexBuffer> squareIB;
		squareIB.reset(Wire::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Colour;

			void main()
			{
				v_Position = a_Position;
				v_Colour = a_Colour;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			in vec3 v_Position;
			in vec4 v_Colour;

			layout(location = 0) out vec4 colour;

			void main()
			{
				colour = vec4(v_Position * 0.5 + 0.5, 1.0);
				colour = v_Colour;
			}
		)";

		m_Shader = Wire::Shader::Create("VertexPosColour", vertexSrc, fragmentSrc);

		std::string flatColourShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColourShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 colour;

			in vec3 v_Position;

			uniform vec3 u_Colour;

			void main()
			{
				colour = vec4(u_Colour, 1.0);
			}
		)";

		m_FlatColourShader = Wire::Shader::Create("FlasColour", flatColourShaderVertexSrc, flatColourShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Wire::Texture2D::Create("assets/textures/Checkerboard.png");
		m_WireLogoTexture = Wire::Texture2D::Create("assets/textures/WireLogo.png");

		std::dynamic_pointer_cast<Wire::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Wire::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Wire::Timestep ts) override
	{
		if (Wire::Input::IsKeyPressed(WR_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Wire::Input::IsKeyPressed(WR_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Wire::Input::IsKeyPressed(WR_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Wire::Input::IsKeyPressed(WR_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Wire::Input::IsKeyPressed(WR_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Wire::Input::IsKeyPressed(WR_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Wire::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
		Wire::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Wire::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Wire::OpenGLShader>(m_FlatColourShader)->Bind();
		std::dynamic_pointer_cast<Wire::OpenGLShader>(m_FlatColourShader)->UploadUniformFloat3("u_Colour", m_SquareColour);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Wire::Renderer::Submit(m_FlatColourShader, m_SquareVA, transform);
			}
		}
		
		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Wire::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_WireLogoTexture->Bind();
		Wire::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Wire::Renderer::Submit(m_Shader, m_VertexArray);

		Wire::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Colour", glm::value_ptr(m_SquareColour));
		ImGui::End();
	}

	void OnEvent(Wire::Event& event) override
	{

	}
private:
	Wire::ShaderLibrary m_ShaderLibrary;
	Wire::Ref<Wire::Shader> m_Shader;
	Wire::Ref<Wire::VertexArray> m_VertexArray;

	Wire::Ref<Wire::Shader> m_FlatColourShader;
	Wire::Ref<Wire::VertexArray> m_SquareVA;

	Wire::Ref<Wire::Texture2D> m_Texture, m_WireLogoTexture;

	Wire::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0;

	float m_CameraMoveSpeed = 5;
	float m_CameraRotationSpeed = 180;

	glm::vec3 m_SquareColour = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Wire::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Wire::Application* Wire::CreateApplication()
{
	return new Sandbox();
}