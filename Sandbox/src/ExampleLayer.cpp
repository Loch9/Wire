#include "ExampleLayer.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), m_CameraController(1280.0f / 720.0f)
{
	m_VertexArray = Wire::VertexArray::Create();

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	Wire::Ref<Wire::VertexBuffer> vertexBuffer = Wire::VertexBuffer::Create(vertices, sizeof(vertices));
	Wire::BufferLayout layout = {
		{ Wire::ShaderDataType::Float3, "a_Position" },
		{ Wire::ShaderDataType::Float4, "a_Colour" }
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	Wire::Ref<Wire::IndexBuffer> indexBuffer = Wire::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_SquareVA = Wire::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	Wire::Ref<Wire::VertexBuffer> squareVB = Wire::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ Wire::ShaderDataType::Float3, "a_Position" },
		{ Wire::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Wire::Ref<Wire::IndexBuffer> squareIB = Wire::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
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
			
			layout(location = 0) out vec4 colour;

			in vec3 v_Position;
			in vec4 v_Colour;

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

	m_FlatColourShader = Wire::Shader::Create("FlatColour", flatColourShaderVertexSrc, flatColourShaderFragmentSrc);

	auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

	m_Texture = Wire::Texture2D::Create("assets/textures/Checkerboard.png");
	m_ChernoLogoTexture = Wire::Texture2D::Create("assets/textures/ChernoLogo.png");

	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnAttach() 
{
}

void ExampleLayer::OnDetach() 
{
}

void ExampleLayer::OnUpdate(Wire::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Wire::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
	Wire::RenderCommand::Clear();

	Wire::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	m_FlatColourShader->Bind();
	m_FlatColourShader->SetFloat3("u_Colour", m_SquareColour);

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
	m_ChernoLogoTexture->Bind();
	Wire::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	// Triangle
	// Wire::Renderer::Submit(m_Shader, m_VertexArray);

	Wire::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Colour", glm::value_ptr(m_SquareColour));
	ImGui::End();
}

void ExampleLayer::OnEvent(Wire::Event& e)
{
	m_CameraController.OnEvent(e);
}
