#include "Shader.h"


Shader::Shader()
	: mShaderProgram(0)
	, mVertexShader(0)
	, mFragShader(0)
{

}

Shader::~Shader()
{

}

bool Shader::Load(const string& vertName, const string& fragName)
{
	// ���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[���R���p�C������
	if (!CompileShader(vertName,
		GL_VERTEX_SHADER,
		mVertexShader) ||
		!CompileShader(fragName,
			GL_FRAGMENT_SHADER,
			mFragShader))
	{
		return false;
	}

	// ���_
	// �t���O�V�F�[�_�[�������N����V�F�[�_�[�v���O�������쐬�B
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);

	// �v���O����������Ƀ����N�������Ƃ��m�F���Ă�������
	if (!IsValidProgram())
	{
		return false;
	}

	return true;
}

void Shader::Unload()
{
	// �v���O����/�V�F�[�_�[���폜����
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragShader);
}

void Shader::SetActive()
{
	// ���̃v���O�������A�N�e�B�u�Ȃ��̂Ƃ��Đݒ肵�܂�
	glUseProgram(mShaderProgram);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
	// ���̖��O��UniformLocation��������
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	// �s��f�[�^�����j�t�H�[���ɑ��M
	glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

void Shader::SetMatrixUniforms(const char* name, Matrix4* matrices, unsigned count)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	// �s��f�[�^�����j�t�H�[���ɑ��M
	glUniformMatrix4fv(loc, count, GL_TRUE, matrices->GetAsFloatPtr());
}

void Shader::SetVectorUniform(const char* name, const Vector3& vector)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	// �x�N�g���f�[�^�𑗐M
	glUniform3fv(loc, 1, vector.GetAsFloatPtr());
}

void Shader::SetVector4Uniform(const char* name, const Vector4& vector)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	// �x�N�g���f�[�^�𑗐M
	glUniform4fv(loc, 1, vector.GetAsFloatPtr());
}

void Shader::SetVector2Uniform(const char* name, const Vector2& vector)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	// �x�N�g���f�[�^�𑗐M
	glUniform2fv(loc, 1, vector.GetAsFloatPtr());
}

void Shader::SetFloatUniform(const char* name, float value)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	// ���������_�f�[�^�𑗐M
	glUniform1f(loc, value);
}

void Shader::SetIntUniform(const char* name, int value)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	// ���������_�f�[�^�𑗐M
	glUniform1i(loc, value);
}

void Shader::SetMaterialColor(const Vector4& color)
{
	mMaterialColor = color;
}

void Shader::SetColorUniform(const char* name, const MaterialInfo info)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, "ambientColor");
	glUniform3f(loc, info.Ambient.x, info.Ambient.y, info.Ambient.z);

	loc = glGetUniformLocation(mShaderProgram, "diffuseColor");
	glUniform3f(loc, info.Diffuse.x, info.Diffuse.y, info.Diffuse.z);

	loc = glGetUniformLocation(mShaderProgram, "specularColor");
	glUniform3f(loc, info.Specular.x, info.Specular.y, info.Specular.z);

	loc = glGetUniformLocation(mShaderProgram, "shininess");
	glUniform1f(loc, info.Shininess);

	loc = glGetUniformLocation(mShaderProgram, name);
	glUniform4fv(loc, 1, mMaterialColor.GetAsFloatPtr());
}

void Shader::SetMaterialUniform(const char* name, const Vector3& color)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	glUniform3f(loc, color.x, color.y, color.z);
}

void Shader::SetNoTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Shader::CompileShader(const string& fileName,
	GLenum shaderType,
	GLuint& outShader)
{
	// Open file
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		// ���ׂẴe�L�X�g�𕶎���ɓǂݍ���
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		// �w�肳�ꂽ�^�C�v�̃V�F�[�_�[���쐬���܂��B
		outShader = glCreateShader(shaderType);
		// �\�[�X������ݒ肵�āA�R���p�C�������݂�
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader))
		{
			SDL_Log("Failed to compile shader %s", fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s", fileName.c_str());
		return false;
	}

	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;
	// �R���p�C���󋵂��Ɖ��
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}

	return true;
}

bool Shader::IsValidProgram()
{

	GLint status;
	// �����N�̏�Ԃ��Ɖ��
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("GLSL Link Status:\n%s", buffer);
		return false;
	}

	return true;
}

