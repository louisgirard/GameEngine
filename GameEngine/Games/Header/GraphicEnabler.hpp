#pragma once

#include <GraphicEngine/Header/GraphicEnum.hpp>

#include <GraphicEngine/SceneBase/Header/Camera.hpp>

#include <GraphicEngine/Buffers/Header/VertexArrayObject.hpp>
#include <GraphicEngine/Buffers/Header/FrameBuffer.hpp>

#include <GraphicEngine/Shaders/Header/ShaderProgram.hpp>
#include <GraphicEngine/Shaders/Header/MeshShader.hpp>
#include <GraphicEngine/Shaders/Header/VFXShader.hpp>

#include <GraphicEngine/Textures/Header/CubeMap.hpp>
#include <GraphicEngine/Textures/Header/Texture2D.hpp>
#include <GraphicEngine/Buffers/Header/RenderBuffer.hpp>

#include <GraphicEngine/SceneBase/Header/BoundingBox.hpp>
#include <GraphicEngine/SceneBase/Header/SkyboxGeometry.hpp>
#include <GraphicEngine/SceneBase/Header/ScreenRenderQuad.hpp>

#include <GraphicEngine/SceneGraph/Header/Mesh.hpp>

#include <GraphicEngine/Servers/Header/SceneServer.hpp>
#include <GraphicEngine/Servers/Header/ShaderServer.hpp>
#include <GraphicEngine/Servers/Header/TextureServer.hpp>

namespace Games {

#pragma region ENUM

	using FBOAttachment = GraphicEngine::FBOAttachement;
	using FBOAttachmentType = GraphicEngine::FBOAttachmentType;
	using TextureInternalFormat = GraphicEngine::TextureInternalFormat;

#pragma endregion

	using Camera = GraphicEngine::SceneBase::Camera;

	using VAO = GraphicEngine::Buffers::VertexArrayObject;
	using FrameBuffer = GraphicEngine::Buffers::FrameBuffer;

	using ShaderProgram = GraphicEngine::Shaders::ShaderProgram;
	using MeshShader = GraphicEngine::Shaders::MeshShader;
	using VFXShader = GraphicEngine::Shaders::VFXShader;

	using RenderBuffer = GraphicEngine::Buffers::RenderBuffer;
	using Texture2D = GraphicEngine::Textures::Texture2D;
	using CubeMap = GraphicEngine::Textures::CubeMap;

	using BoundingBox = GraphicEngine::SceneBase::BoundingBox;
	using SkyboxGeometry = GraphicEngine::SceneBase::SkyboxGeometry;
	using ScreenRenderQuad = GraphicEngine::SceneBase::ScreenRenderQuad;

	using Mesh = GraphicEngine::PSceneGraph::Mesh;

	using SceneServer = GraphicEngine::Servers::SceneServer;
	using ShaderServer = GraphicEngine::Servers::ShaderServer;
	using TextureServer = GraphicEngine::Servers::TextureServer;
}