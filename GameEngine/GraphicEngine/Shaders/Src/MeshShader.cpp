#include <GraphicEngine/Shaders/Header/MeshShader.hpp>

namespace GraphicEngine::Shaders {

		const std::string MeshShader::POSITION = "in_position";
		const std::string MeshShader::NORMAL = "in_normal";
		const std::string MeshShader::TANGENT = "in_tangent";
		const std::string MeshShader::BITANGENT = "in_bitangent";
		const std::string MeshShader::TEXTURECOORD = "in_textureCoordinates";

		const std::string MeshShader::MODEL = "uni_mat_model";
		const std::string MeshShader::VIEW = "uni_mat_view";
		const std::string MeshShader::PROJECTION = "uni_mat_projection";
		const std::string MeshShader::NORMALMATRX = "uni_mat_normal";

		const std::string MeshShader::EMISSIVE = "uni_material.emissiveColor";
		const std::string MeshShader::AMBIENT = "uni_material.ambientColor";
		const std::string MeshShader::DIFFUSE = "uni_material.diffuseColor";
		const std::string MeshShader::SPECULAR = "uni_material.specularColor";
		const std::string MeshShader::SHININESS = "uni_material.shininess";

		const std::string MeshShader::DIFFUSETEXT = "uni_diffuseTexture";
		const std::string MeshShader::SPECULARTEXT = "uni_specularTexture";
		const std::string MeshShader::NORMALTEXT = "uni_normalTexture";
		const std::string MeshShader::ENVIRONMENTTEXT = "uni_skybox";

		const std::string MeshShader::VIEW_POSITION = "uni_viewerPosition";
		const std::string MeshShader::LIGHT_DIRECTION = "uni_light.direction";
		const std::string MeshShader::LIGHT_COLOR = "uni_light.color";
		const std::string MeshShader::CLIPPING_DISTANCE= "uni_clippingDistance";

#pragma region INITIALIZATION
		/* Init this shader */
		void MeshShader::initialise() {
			_inPosition = getAttributeLocation(POSITION);
			_inNormal = getAttributeLocation(NORMAL);
			_inTangent = getAttributeLocation(TANGENT);
			_inBitangent = getAttributeLocation(BITANGENT);
			_inTextureCoordinate = getAttributeLocation(TEXTURECOORD);

			_uniModelMatrix = getUniformLocation(MODEL);
			_uniViewMatrix = getUniformLocation(VIEW);
			_uniProjectionMatrix = getUniformLocation(PROJECTION);
			_uniNormalMatrix = getUniformLocation(NORMALMATRX);

			_uniEmissiveColor = getUniformLocation(EMISSIVE);
			_uniAmbientColor = getUniformLocation(AMBIENT);
			_uniDiffuseColor = getUniformLocation(DIFFUSE);
			_uniSpecularColor = getUniformLocation(SPECULAR);
			_uniShininess = getUniformLocation(SHININESS);

			_uniDiffuseTexture = getUniformLocation(DIFFUSETEXT);
			_uniSpecularTexture = getUniformLocation(SPECULARTEXT);
			_uniNormalTexture = getUniformLocation(NORMALTEXT);
			_uniEnvironmentTexture = getUniformLocation(ENVIRONMENTTEXT);

			_uniViewPos = getUniformLocation(VIEW_POSITION);
			_uniLightDir = getUniformLocation(LIGHT_DIRECTION);
			_uniLightColor = getUniformLocation(LIGHT_COLOR);
			_uniClippingDistance = getUniformLocation(CLIPPING_DISTANCE);
		}

		MeshShader::MeshShader() : ShaderProgram(defaultPhongVertex(), defaultPhongFragment()), _view(glm::mat4())  {
			initialise();
		}

		MeshShader::MeshShader(const Shader& p_vertex, const Shader& p_fragment)
			: ShaderProgram(p_vertex, p_fragment), _view(glm::mat4()){
			initialise();
		}

		MeshShader::MeshShader(const std::filesystem::path& p_vertexPath, const std::filesystem::path& p_fragmentPath)
			: ShaderProgram(p_vertexPath, p_fragmentPath), _view(glm::mat4()) {
			initialise();
		}
#pragma endregion

#pragma region COPY
		MeshShader::MeshShader(MeshShader&& p_other):ShaderProgram(std::move(p_other))
		{
			_inPosition = p_other._inPosition;
			_inNormal = p_other._inNormal;
			_inTangent = p_other._inTangent;
			_inBitangent = p_other._inBitangent;
			_inTextureCoordinate = p_other._inTextureCoordinate;

			_uniModelMatrix = p_other._uniModelMatrix;
			_uniViewMatrix = p_other._uniViewMatrix;
			_uniProjectionMatrix = p_other._uniProjectionMatrix;
			_uniNormalMatrix = p_other._uniNormalMatrix;

			_uniEmissiveColor = p_other._uniEmissiveColor;
			_uniAmbientColor = p_other._uniAmbientColor;
			_uniDiffuseColor = p_other._uniDiffuseColor;
			_uniSpecularColor = p_other._uniSpecularColor;
			_uniShininess = p_other._uniShininess;

			_uniDiffuseTexture = p_other._uniDiffuseTexture;
			_uniSpecularTexture = p_other._uniSpecularTexture;
			_uniNormalTexture = p_other._uniNormalTexture;
			_uniEnvironmentTexture = p_other._uniEnvironmentTexture;

			_uniViewPos = p_other._uniViewPos;
			_uniLightDir = p_other._uniLightDir;
			_uniLightColor = p_other._uniLightColor;
			_uniClippingDistance = p_other._uniClippingDistance;

			_view = p_other._view;
		}

		MeshShader& MeshShader::operator= (MeshShader&& p_other)
		{
			ShaderProgram::operator=(std::move(p_other));

			if (isValid()) {
				_inPosition = p_other._inPosition;
				_inNormal = p_other._inNormal;
				_inTangent = p_other._inTangent;
				_inBitangent = p_other._inBitangent;
				_inTextureCoordinate = p_other._inTextureCoordinate;

				_uniModelMatrix = p_other._uniModelMatrix;
				_uniViewMatrix = p_other._uniViewMatrix;
				_uniProjectionMatrix = p_other._uniProjectionMatrix;
				_uniNormalMatrix = p_other._uniNormalMatrix;

				_uniEmissiveColor = p_other._uniEmissiveColor;
				_uniAmbientColor = p_other._uniAmbientColor;
				_uniDiffuseColor = p_other._uniDiffuseColor;
				_uniSpecularColor = p_other._uniSpecularColor;
				_uniShininess = p_other._uniShininess;

				_uniDiffuseTexture = p_other._uniDiffuseTexture;
				_uniSpecularTexture = p_other._uniSpecularTexture;
				_uniNormalTexture = p_other._uniNormalTexture;
				_uniEnvironmentTexture = p_other._uniEnvironmentTexture;

				_uniViewPos = p_other._uniViewPos;
				_uniLightDir = p_other._uniLightDir;
				_uniLightColor = p_other._uniLightColor;
				_uniClippingDistance = p_other._uniClippingDistance;

				_view = p_other._view;
			}

			return (*this);
		}
#pragma endregion

		void MeshShader::renderMesh(const Buffers::VertexArrayObject& p_meshVAO, const Materials::PhongMaterial& p_material) {
			setMaterial(p_material);
			glEnableClientState(GL_VERTEX_ARRAY);
			p_meshVAO.bind();
			glDrawElements(GL_TRIANGLES, (GLsizei)p_meshVAO.eboSize(), GL_UNSIGNED_INT, 0);
			handleGLerror("MeshShader::renderMesh()");
			p_meshVAO.unbind();
			glDisableClientState(GL_VERTEX_ARRAY);
		}

#pragma region GETTERS
		Buffers::VertexArrayObject* MeshShader::getMeshVAO(const PSceneGraph::Mesh& p_mesh)
		{
			std::vector<std::pair<GLint, const Buffers::VertexBufferObject*>> vbos;
			if (_inPosition != -1) {
				vbos.push_back(std::pair <GLint, const Buffers::VertexBufferObject* >(_inPosition, p_mesh.getVerticesVbo())); 
			}
			if (_inNormal != -1) { 
				vbos.push_back(std::pair <GLint, const Buffers::VertexBufferObject* >(_inNormal,p_mesh.getNormalsVbo())); 
			}
			if (_inTangent != -1) {
				vbos.push_back(std::pair <GLint, const Buffers::VertexBufferObject* >(_inTangent,p_mesh.getTagentsVbo())); 
			}
			if (_inBitangent != -1) { 
				vbos.push_back(std::pair <GLint, const Buffers::VertexBufferObject* >(_inBitangent,p_mesh.getBitangentsVbo())); 
			}
			if (_inTextureCoordinate != -1) { 
				vbos.push_back(std::pair <GLint, const Buffers::VertexBufferObject* >(_inTextureCoordinate,p_mesh.getTextureCoordinatesVbo()));
			}

			return new Buffers::VertexArrayObject(vbos, p_mesh.getIndices().value());
		}
#pragma endregion

#pragma region SETTERS
		void MeshShader::setMaterial(const Materials::PhongMaterial& p_material) const
		{
			// The material properties
			if (_uniEmissiveColor != -1) { 
				setUniform(_uniEmissiveColor, p_material.getEmissive()); }
			if (_uniAmbientColor != -1) { 
				setUniform(_uniAmbientColor, p_material.getAmbient()); }
			if (_uniDiffuseColor != -1) {
				setUniform(_uniDiffuseColor, p_material.getDiffuse()); }
			if (_uniSpecularColor != -1) { 
				setUniform(_uniSpecularColor, p_material.getSpecular()); }
			if (_uniShininess != -1) { 
				setUniform(_uniShininess, p_material.getShininess()); }

			// The textures
			if (_uniDiffuseTexture != -1 && p_material.getDiffuseTexture() != nullptr)
			{
				p_material.getDiffuseTexture()->associateWithTextureUnit(0);
				setUniform(_uniDiffuseTexture, 0);
			}
			if (_uniSpecularTexture != -1 && p_material.getSpecularTexture() != nullptr)
			{
				p_material.getSpecularTexture()->associateWithTextureUnit(1);
				setUniform(_uniSpecularTexture, 1);
			}
			if (_uniNormalTexture != -1 && p_material.getNormalTexture() != nullptr)
			{
				p_material.getNormalTexture()->associateWithTextureUnit(2);
				setUniform(_uniNormalTexture, 2);
			}
		}

		void MeshShader::setTransforms(const glm::mat4& p_model, const glm::mat4& p_view, const glm::mat4& p_projection)
		{
			if (_uniModelMatrix != -1) { setUniform(_uniModelMatrix, p_model); }
			if (_uniViewMatrix != -1) { 
				_view = p_view;
				setUniform(_uniViewMatrix, p_view); 
			}
			if (_uniProjectionMatrix != -1) { setUniform(_uniProjectionMatrix, p_projection); }
			
			if (_uniNormalMatrix != -1)
			{
				glm::mat3 normal = glm::transpose(inverse(glm::mat3(p_view) * glm::mat3(p_model)));
				setUniform(_uniNormalMatrix, normal);
			}
		}

		void MeshShader::setModelTransform(const glm::mat4& p_model) {
			if (_uniModelMatrix != -1) { setUniform(_uniModelMatrix, p_model); }
			if (_uniNormalMatrix != -1)
			{
				glm::mat3 normal = glm::transpose(inverse(glm::mat3(_view) * glm::mat3(p_model)));
				setUniform(_uniNormalMatrix, normal);
			}
		}

		void MeshShader::setViewTransform(const glm::mat4& p_view) {
			if (_uniViewMatrix != -1) {
				_view = p_view;
				setUniform(_uniViewMatrix, p_view);
			}
		}

		void MeshShader::setProjectionTransform(const glm::mat4& p_projection) {
			if (_uniProjectionMatrix != -1) { setUniform(_uniProjectionMatrix, p_projection); }
		}

		void MeshShader::setLights(glm::vec3 p_direction, glm::vec3 p_color) {
			if (_uniLightDir != -1) {
				setUniform(_uniLightDir, p_direction);}
			if (_uniLightColor != -1) { 
				setUniform(_uniLightColor, p_color); }
		}

		void MeshShader::setViewPosition(glm::vec3 p_position) {
			if (_uniViewPos != -1) setUniform(_uniViewPos, p_position);
		}

		void MeshShader::setClippingDistance(float p_distance) {
			if (_uniClippingDistance != -1) setUniform(_uniClippingDistance, p_distance);
		}

		void MeshShader::setEnvTexture(Textures::CubeMap* p_texture) {
			int textureUnit = 0;
			if (_uniDiffuseTexture != -1) textureUnit++;
			if (_uniSpecularTexture != -1) textureUnit++;
			if(_uniNormalTexture != -1) textureUnit++;
			if (_uniEnvironmentTexture != -1 && p_texture != nullptr) {
				p_texture->associateWithTextureUnit(textureUnit);
				setUniform(_uniEnvironmentTexture, textureUnit);
			}
		}
#pragma endregion
}