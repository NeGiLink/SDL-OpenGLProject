#pragma once
#include "Math.h"
#include "Mesh.h"

//�V�F�[�_�[�̓ǂݍ��݃N���X
class Shader
{
public:
				Shader();
				~Shader();
	bool		Load(const string& vertName, const string& fragName);
	void		Unload();
	// ������A�N�e�B�u�V�F�[�_�[�v���O�����Ƃ��Đݒ肵�܂��B
	void		SetActive();
	// �}�g���b�N�X�� uniform ��ݒ�
	void		SetMatrixUniform(const char* name, const Matrix4& matrix);
	// �}�g���b�N�X uniform �̔z���ݒ�
	void		SetMatrixUniforms(const char* name, Matrix4* matrices, unsigned count);
	// Vector3�̃��j�t�H�[����ݒ�
	void		SetVectorUniform(const char* name, const Vector3& vector);
	void		SetVector2Uniform(const char* name, const Vector2& vector);
	// ���������_���̃��j�t�H�[����ݒ�
	void		SetFloatUniform(const char* name, float value);
	// �����̃��j�t�H�[����ݒ�
	void		SetIntUniform(const char* name, int value);

	void		SetMaterialColor(const Vector4& color);

	void		SetColorUniform(const char* name,const MaterialInfo info);

	void		SetMaterialUniform(const char* name, const Vector3& color);

	void		SetNoTexture();
private:
	// �w�肳�ꂽ�V�F�[�_�[�̃R���p�C�������݂܂�
	bool		CompileShader(const string& fileName,
		GLenum shaderType,
		GLuint& outShader);

	// �V�F�[�_�[������ɃR���p�C�����ꂽ���ǂ������e�X�g
	bool		IsCompiled(GLuint shader);
	// ���_/�t���O�����g�v���O�����������N����邩�ǂ������e�X�g
	bool		IsValidProgram();
private:
	// �V�F�[�_�[�I�u�W�F�N�gID��ۑ�����
	GLuint		mVertexShader;
	GLuint		mFragShader;
	GLuint		mShaderProgram;
	Vector4		mMaterialColor;
};
