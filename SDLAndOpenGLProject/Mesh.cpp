#include "Mesh.h"
#include "Shader.h"

namespace
{
	union Vertex
	{
		float f;
		uint8_t b[4];
	};
}

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

bool Mesh::Load(const string& fileName, Renderer* renderer, int index)
{
	// ファイルの拡張子を取得
	string extension = fileName.substr(fileName.find_last_of('.') + 1);

	// **FBX の場合**
	if (extension == "fbx")
	{
		return LoadFromFBX(fileName, renderer,index);
	}

	return false; 
}

int Mesh::CheckMeshIndex(const string& fileName, Renderer* renderer)
{
	int index = 0;
	std::ifstream fileCheck(fileName);
	if (!fileCheck) {
		SDL_Log("FBX file not found: %s", fileName.c_str());
		return false;
	}

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!scene || !scene->HasMeshes())
	{
		SDL_Log("Assimp Error: %s", importer.GetErrorString());
		return false;
	}

	index = scene->mNumMeshes;

	return index;
}

bool Mesh::LoadFromMeshBin(const string& fileName, Renderer* renderer, int index)
{
	string name = StringConverter::RemoveExtension(fileName);

	//1:バイナリ情報に変換した頂点、インデックスデータをbinファイルから取得
	string number = std::to_string(index);
	//fileNameからPath部分だけ取り除く
	string result = StringConverter::RemoveString(name, Model::ModelPath);

	string binaryFilePath = Model::BinaryFilePath + result + number + Model::BinaryPath;
	//バイナリファイルの確認
	std::ifstream in(binaryFilePath, std::ios::binary);
	if (!in) {
		SDL_Log("Failed to open mesh binary: %s", binaryFilePath.c_str());
		return false;
	}

	//バイナリデータの構造体宣言
	MeshBinHeader header;
	//宣言した構造体に読み込んだファイルの情報を読み込む
	in.read((char*)&header, sizeof(header));
	//Textureのタイプを代入
	VertexArray::Layout layout = (header.layoutType == 0) ?
		VertexArray::PosNormTex : VertexArray::PosNormSkinTex;

	// 要素数を計算（1頂点あたりのVertex数）
	size_t stride = (layout == VertexArray::PosNormTex) ? MeshLayout::MESH_VERTEXCOUNT : MeshLayout::SKINMESH_VERTEXCOUNT;
	std::vector<Vertex> vertices(header.vertexCount * stride);
	std::vector<uint32_t> indices(header.indexCount);

	in.read((char*)vertices.data(), sizeof(Vertex) * vertices.size());
	in.read((char*)indices.data(), sizeof(uint32_t) * indices.size());

	// 中心位置や半径を再利用したい場合
	AABB box = AABB(Vector3::Infinity, Vector3::NegInfinity);
	box.mMin = header.min;
	box.mMax = header.max;

	// AABBの中心とサイズからOBBを作る（回転なし）
	Vector3 center = (box.mMin + box.mMax) * 0.5f;
	Vector3 extents = (box.mMax - box.mMin) * 0.5f;
	Quaternion rotation = Quaternion::Identity; // 方向なし
	OBB obbBox = OBB(Vector3::Zero, Quaternion::Identity, Vector3::Zero);
	obbBox = OBB(center, rotation, extents);


	mBoxs.push_back(box); // AABB中心などに使える
	mOBBBoxs.push_back(obbBox);
	mRadiusArray.push_back(header.colliderRadius);

	VertexArray* va = new VertexArray(vertices.data(), header.vertexCount,
		layout, indices.data(), header.indexCount);
	mVertexArrays.push_back(va);

	//2:Assimpを使ってファイルからテクスチャとマテリアル情報を取得
	string assimpFilePath = name + ".fbx";
	//ファイルチェック
	std::ifstream fileCheck(assimpFilePath);
	if (!fileCheck)
	{
		SDL_Log("FBX file not found: %s", assimpFilePath.c_str());
		return false;
	}
	//モデル情報取得
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(assimpFilePath,
		aiProcess_Triangulate | aiProcess_FlipUVs |
		aiProcess_GenNormals | aiProcess_GlobalScale |
		aiProcess_MakeLeftHanded |
		aiProcess_FlipWindingOrder);
	//MeshCheck
	if (!scene || !scene->HasMeshes())
	{
		SDL_Log("Assimp Error: %s", importer.GetErrorString());
		return false;
	}

	aiMesh* mesh = scene->mMeshes[index];

	//テクスチャとマテリアルの情報を取得
		//テクスチャとマテリアルの読み込み
	std::unordered_map<string, Texture*> loadedTextures;
	string texFile = "MaterialTexure.png";
	for (unsigned int i = 0; i < scene->mNumMaterials; i++)
	{
		// メッシュに関連付けられたマテリアルを取得
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		aiString texturePath;
		//ファイルにFBXがあるか
		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
		{
			texFile = texturePath.C_Str();

			// 埋め込みテクスチャかどうかチェック
			if (texFile[0] == '.') {
				int embeddedIndex = std::atoi(texFile.c_str() + 1);
				if (embeddedIndex < scene->mNumTextures) {
					aiTexture* embeddedTex = scene->mTextures[embeddedIndex];

					Texture* newTex = new Texture();
					if (newTex->LoadFromAssimp(embeddedTex)) {
						loadedTextures[texFile] = newTex;
					}
					else {
						delete newTex;
					}
				}
			}
			// 通常の外部テクスチャ
			else {
				if (loadedTextures.find(texFile) == loadedTextures.end())
				{
					Texture* newTex = new Texture();
					if (newTex->Load(Model::ModelTexturePath + texFile))
					{
						loadedTextures[texFile] = newTex;
					}
					else {
						delete newTex;
					}
				}
			}

			if (loadedTextures.find(texFile) != loadedTextures.end())
			{
				mTextures.push_back(loadedTextures[texFile]);
			}
		}
		//ないならマテリアル用のテクスチャロード
		else
		{
			//マテリアル用のテクスチャ取得
			if (loadedTextures.find(texFile) == loadedTextures.end())
			{
				Texture* newTex = new Texture();
				if (newTex->Load(Model::ModelTexturePath + texFile))
				{
					loadedTextures[texFile] = newTex;
				}
				else {
					delete newTex;
				}
			}

			if (loadedTextures.find(texFile) != loadedTextures.end())
			{
				mTextures.push_back(loadedTextures[texFile]);
			}
		}

		MaterialInfo info
		{
				Vector4(0,0,0,0),
				Vector3(0,0,0),
				Vector3(0,0,0),
				Vector3(0,0,0),
				0
		};

		aiColor4D diffuseColor;
		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor))
		{

			info.Color = Vector4(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
		}

		// 拡散色（Diffuse Color）の取得
		aiColor3D diffuse(1.0f, 1.0f, 1.0f);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);

		// 環境光（Ambient Color）の取得
		aiColor3D ambient(0.2f, 0.2f, 0.2f);
		material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);

		// 鏡面反射（Specular Color）の取得
		aiColor3D specular(0.5f, 0.5f, 0.5f);
		material->Get(AI_MATKEY_COLOR_SPECULAR, specular);

		// シェーダーに値を送る（glUniform3f を使用）
		info.Ambient = Vector3(ambient.r, ambient.g, ambient.b);
		info.Diffuse = Vector3(diffuse.r, diffuse.g, diffuse.b);
		info.Specular = Vector3(specular.r, specular.g, specular.b);

		mMaterialInfo.push_back(info);

		float shininess = 0.0f;
		if (scene->HasMaterials())
		{

			if (AI_SUCCESS != material->Get(AI_MATKEY_SHININESS, shininess))
			{
				// デフォルト値を設定
				shininess = 100.0f;
			}
			shininess = shininess / 128.0f;

			info.Shininess = shininess;
		}
	}

	//読み込み成功
	return true;
}
/*
//独自フォーマット用読み込み関数
bool Mesh::LoadFromJSON(const string& fileName, Renderer* renderer, int index)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Mesh %s", fileName.c_str());
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		SDL_Log("Mesh %s is not valid json", fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the version
	if (ver != 1)
	{
		SDL_Log("Mesh %s not version 1", fileName.c_str());
		return false;
	}

	mShaderName = doc["shader"].GetString();

	// Set the vertex layout/size based on the format in the file
	VertexArray::Layout layout = VertexArray::PosNormTex;
	size_t vertSize = 8;

	string vertexFormat = doc["vertexformat"].GetString();
	if (vertexFormat == "PosNormSkinTex")
	{
		layout = VertexArray::PosNormSkinTex;
		// This is the number of "Vertex" unions, which is 8 + 2 (for skinning)s
		vertSize = 10;
	}

	MaterialInfo info
	{
			Vector4(1.0f,1.0f,1.0f,1.0f),
			Vector3(0,0,0),
			Vector3(0,0,0),
			Vector3(0,0,0),
			0
	};
	// Load textures
	const rapidjson::Value& textures = doc["textures"];
	if (!textures.IsArray() || textures.Size() < 1)
	{
		SDL_Log("Mesh %s has no textures, there should be at least one", fileName.c_str());
		return false;
	}

	float specPower = static_cast<float>(doc["specularPower"].GetDouble());
	info.Shininess = specPower / 128.0f;

	for (rapidjson::SizeType i = 0; i < textures.Size(); i++)
	{
		// Is this texture already loaded?
		string texName = textures[i].GetString();
		Texture* t = renderer->GetTexture(texName);
		if (t == nullptr)
		{
			// Try loading the texture
			t = renderer->GetTexture(texName);
			if (t == nullptr)
			{
				// If it's still null, just use the default texture
				t = renderer->GetTexture(Model::ModelTexturePath + "Default.png");
			}
		}
		mTextures.emplace_back(t);

		// 拡散色（Diffuse Color）の取得
		Vector3 diffuse(0.8f, 0.8f, 0.8f);

		// 環境光（Ambient Color）の取得
		Vector3 ambient(0.0f, 0.0f, 0.0f);

		// 鏡面反射（Specular Color）の取得
		Vector3 specular(0.2f, 0.2f, 0.2f);

		// シェーダーに値を送る（glUniform3f を使用）
		info.Ambient = ambient;
		info.Diffuse = diffuse;
		info.Specular = specular;

		mMaterialInfo.push_back(info);
	}

	// Load in the vertices
	const rapidjson::Value& vertsJson = doc["vertices"];
	if (!vertsJson.IsArray() || vertsJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no vertices", fileName.c_str());
		return false;
	}

	AABB box = AABB(Vector3::Infinity, Vector3::NegInfinity);

	vector<Vertex> vertices;
	vertices.reserve(vertsJson.Size() * vertSize);
	float radius = 0.0f;
	for (rapidjson::SizeType i = 0; i < vertsJson.Size(); i++)
	{
		// For now, just assume we have 8 elements
		const rapidjson::Value& vert = vertsJson[i];
		if (!vert.IsArray())
		{
			SDL_Log("Unexpected vertex format for %s", fileName.c_str());
			return false;
		}

		Vector3 pos(vert[0].GetDouble(), vert[1].GetDouble(), vert[2].GetDouble());
		radius = Math::Max(radius, pos.LengthSq());
		box.UpdateMinMax(pos);

		if (layout == VertexArray::PosNormTex)
		{
			Vertex v;
			// Add the floats
			for (rapidjson::SizeType j = 0; j < vert.Size(); j++)
			{
				v.f = static_cast<float>(vert[j].GetDouble());
				vertices.emplace_back(v);
			}
		}
		else
		{
			Vertex v;
			// Add pos/normal
			for (rapidjson::SizeType j = 0; j < 6; j++)
			{
				v.f = static_cast<float>(vert[j].GetDouble());
				vertices.emplace_back(v);
			}

			// Add skin information
			for (rapidjson::SizeType j = 6; j < 14; j += 4)
			{
				v.b[0] = vert[j].GetUint();
				v.b[1] = vert[j + 1].GetUint();
				v.b[2] = vert[j + 2].GetUint();
				v.b[3] = vert[j + 3].GetUint();
				vertices.emplace_back(v);
			}

			// Add tex coords
			for (rapidjson::SizeType j = 14; j < vert.Size(); j++)
			{
				v.f = vert[j].GetDouble();
				vertices.emplace_back(v);
			}
		}
	}

	// We were computing length squared earlier
	radius = Math::Sqrt(radius);

	// Load in the indices
	const rapidjson::Value& indJson = doc["indices"];
	if (!indJson.IsArray() || indJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no indices", fileName.c_str());
		return false;
	}

	vector<unsigned int> indices;
	indices.reserve(indJson.Size() * 3);
	for (rapidjson::SizeType i = 0; i < indJson.Size(); i++)
	{
		const rapidjson::Value& ind = indJson[i];
		if (!ind.IsArray() || ind.Size() != 3)
		{
			SDL_Log("Invalid indices for %s", fileName.c_str());
			return false;
		}

		indices.emplace_back(ind[0].GetUint());
		indices.emplace_back(ind[1].GetUint());
		indices.emplace_back(ind[2].GetUint());
	}

	mRadiusArray.push_back(radius);
	mBoxs.push_back(box);

	VertexArray* va = new VertexArray(vertices.data(), static_cast<unsigned>(vertices.size()) / vertSize,
		layout, indices.data(), static_cast<unsigned>(indices.size()));
	//頂点配列の作成
	mVertexArrays.push_back(va);

	SDL_Log("JSON file exists: %s", fileName.c_str());
	return true;
}
*/
//FBX用読み込み関数
bool Mesh::LoadFromFBX(const string& fileName, Renderer* renderer, int index)
{
	//ファイルチェック
	std::ifstream fileCheck(fileName);
	if (!fileCheck) 
	{
		SDL_Log("FBX file not found: %s", fileName.c_str());
		return false;
	}
	//モデル情報取得
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName,
		aiProcess_Triangulate |
		aiProcess_FlipUVs |
		aiProcess_GenNormals  |
		aiProcess_GlobalScale |
		aiProcess_MakeLeftHanded |
		aiProcess_FlipWindingOrder);
	//MeshCheck
	if (!scene || !scene->HasMeshes())
	{
		SDL_Log("Assimp Error: %s", importer.GetErrorString());
		return false;
	}

	//メッシュをロード
	aiMesh* mesh;
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	float radius = 0.0f;
	AABB box = AABB(Vector3::Infinity, Vector3::NegInfinity);
	OBB obbBox = OBB(Vector3::Zero,Quaternion::Identity,Vector3::Zero);

	mesh = scene->mMeshes[index];

	//頂点データの変換
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D pos = mesh->mVertices[i];
		aiVector3D norm = mesh->mNormals[i];

		aiVector3D uv = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : aiVector3D(0, 0, 0);


		Vector3 vertexPos(pos.x, pos.y, pos.z);
		radius = Math::Max(radius, vertexPos.LengthSq());
		box.UpdateMinMax(vertexPos);
		// AABBの中心とサイズからOBBを作る（回転なし）
		Vector3 center = (box.mMin + box.mMax) * 0.5f;
		Vector3 extents = (box.mMax - box.mMin) * 0.5f;
		Quaternion rotation = Quaternion::Identity; // 方向なし

		obbBox = OBB(center, rotation, extents);

		Vertex v;
		v.f = pos.x; vertices.push_back(v);

		v.f = pos.y; vertices.push_back(v);

		v.f = pos.z; vertices.push_back(v);

		v.f = norm.x; vertices.push_back(v);

		v.f = norm.y; vertices.push_back(v);

		v.f = norm.z; vertices.push_back(v);

		//頂点にウェイト追加、簡易のため複数メッシュの場合など不足あり(修正済み)
		if (mesh->HasBones())
		{
			Vertex boneIndex = { 0 };
			Vertex weight[4] = { 0,0,0,0 };
			ai_real allWeight = 0.0f;
			for (unsigned int j = 0; j < mesh->mNumBones; j++) 
			{
				aiBone* bone = mesh->mBones[j];
				for (unsigned int weightIndex = 0; weightIndex < bone->mNumWeights; weightIndex++) 
				{
					if (bone->mWeights[weightIndex].mVertexId != i ||
						bone->mWeights[weightIndex].mWeight <= 0)
					{
						continue;
					}
					float weightValue = bone->mWeights[weightIndex].mWeight;
					//現在のウェイトが上位4つに入るか判定
					for (unsigned int w = 0; w < 4; w++)
					{
						if (weight[w].f < weightValue)
						{
							// シフトして挿入（現在のw以降を後ろにずらす）
							for (int k = 3; k > w; k--)
							{
								weight[k] = weight[k - 1];
								boneIndex.b[k] = boneIndex.b[k - 1];
							}
							//新しい値を挿入
							weight[w].f = weightValue;
							boneIndex.b[w] = j;
							break;
						}
					}
					allWeight += bone->mWeights[weightIndex].mWeight;
				}
			}
			//ゼロ除算回避しつつ正規化
			if (allWeight > 0.0f) 
			{
				//ウェイトの合計を1.0に正規化（ゼロ除算を回避)
				allWeight = 1.0f / allWeight;
				weight[0].f *= allWeight;
				weight[1].f *= allWeight;
				weight[2].f *= allWeight;
				weight[3].f *= allWeight;
			}

			//ウェイト順にソート
			for (int i = 0; i < 3; i++) 
			{
				for (int j = i + 1; j < 4; j++) 
				{
					if (weight[i].f < weight[j].f) 
					{
						std::swap(weight[i], weight[j]);
						std::swap(boneIndex.b[i], boneIndex.b[j]);
					}
				}
			}

			vertices.push_back(boneIndex);
			vertices.push_back(weight[0]);
			vertices.push_back(weight[1]);
			vertices.push_back(weight[2]);
			vertices.push_back(weight[3]);
		}

		v.f = uv.x; vertices.push_back(v);
		v.f = uv.y; vertices.push_back(v);
	}
	// **インデックスデータの変換**
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		if (face.mNumIndices == 3)
		{
			indices.emplace_back(face.mIndices[0]);
			indices.emplace_back(face.mIndices[1]);
			indices.emplace_back(face.mIndices[2]);
		}
	}

	radius = Math::Sqrt(radius);
	//テクスチャとマテリアルの読み込み
	std::unordered_map<string, Texture*> loadedTextures;
	string texFile = "MaterialTexure.png";
	for (unsigned int i = 0; i < scene->mNumMaterials; i++) 
	{
		// メッシュに関連付けられたマテリアルを取得
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		aiString texturePath;
		//ファイルにFBXがあるか
		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) 
		{
			texFile = texturePath.C_Str();

			// 埋め込みテクスチャかどうかチェック
			if (texFile[0] == '.') {
				int embeddedIndex = std::atoi(texFile.c_str() + 1);
				if (embeddedIndex < scene->mNumTextures) {
					aiTexture* embeddedTex = scene->mTextures[embeddedIndex];

					Texture* newTex = new Texture();
					if (newTex->LoadFromAssimp(embeddedTex)) {
						loadedTextures[texFile] = newTex;
					}
					else {
						delete newTex;
					}
				}
			}
			// 通常の外部テクスチャ
			else {
				if (loadedTextures.find(texFile) == loadedTextures.end()) 
				{
					Texture* newTex = new Texture();
					if (newTex->Load(Model::ModelTexturePath + texFile)) 
					{
						loadedTextures[texFile] = newTex;
					}
					else {
						delete newTex;
					}
				}
			}

			if (loadedTextures.find(texFile) != loadedTextures.end()) 
			{
				mTextures.push_back(loadedTextures[texFile]);
			}
		}
		//ないならマテリアル用のテクスチャロード
		else 
		{
			//マテリアル用のテクスチャ取得
			if (loadedTextures.find(texFile) == loadedTextures.end()) 
			{
				Texture* newTex = new Texture();
				if (newTex->Load(Model::ModelTexturePath + texFile)) 
				{
					loadedTextures[texFile] = newTex;
				}
				else {
					delete newTex;
				}
			}

			if (loadedTextures.find(texFile) != loadedTextures.end()) 
			{
				mTextures.push_back(loadedTextures[texFile]);
			}
		}

		MaterialInfo info
		{
				Vector4(0,0,0,0),
				Vector3(0,0,0),
				Vector3(0,0,0),
				Vector3(0,0,0),
				0
		};

		aiColor4D diffuseColor;
		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor)) 
		{

			info.Color = Vector4(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
		}

		// 拡散色（Diffuse Color）の取得
		aiColor3D diffuse(1.0f, 1.0f, 1.0f);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);

		// 環境光（Ambient Color）の取得
		aiColor3D ambient(0.2f, 0.2f, 0.2f);
		material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);

		// 鏡面反射（Specular Color）の取得
		aiColor3D specular(0.5f, 0.5f, 0.5f);
		material->Get(AI_MATKEY_COLOR_SPECULAR, specular);

		// シェーダーに値を送る（glUniform3f を使用）
		info.Ambient = Vector3(ambient.r, ambient.g, ambient.b);
		info.Diffuse = Vector3(diffuse.r, diffuse.g, diffuse.b);
		info.Specular = Vector3(specular.r, specular.g, specular.b);

		mMaterialInfo.push_back(info);

		float shininess = 0.0f;
		if (scene->HasMaterials()) 
		{

			if (AI_SUCCESS != material->Get(AI_MATKEY_SHININESS, shininess)) 
			{
				// デフォルト値を設定
				shininess = 100.0f;
			}
			shininess = shininess / 128.0f;

			info.Shininess = shininess;
		}
	}

	//Skinの場合のLayout変更
	VertexArray::Layout layout = VertexArray::PosNormTex;
	unsigned int vertexCount = static_cast<unsigned>(vertices.size()) / MeshLayout::MESH_VERTEXCOUNT;
	if (mesh->HasBones())
	{
		layout = VertexArray::PosNormSkinTex;
		vertexCount = static_cast<unsigned>(vertices.size()) / MeshLayout::SKINMESH_VERTEXCOUNT;
	}

	mRadiusArray.push_back(radius);
	mBoxs.push_back(box);
	mOBBBoxs.push_back(obbBox);

	VertexArray* va = new VertexArray(vertices.data(), vertexCount, layout, indices.data(), static_cast<unsigned>(indices.size()));
	//頂点配列の作成
	mVertexArrays.push_back(va);



	//fileNameからPath部分だけ取り除く
	string result = StringConverter::RemoveString(fileName, Model::ModelPath);


	//バイナリに変換
	MeshBinHeader header;
	header.layoutType = (layout == VertexArray::PosNormTex) ? 0 : 1;
	header.vertexCount = vertexCount;
	header.indexCount = static_cast<uint32_t>(indices.size());


	header.min = box.mMin;
	header.max = box.mMax;
	header.colliderRadius = radius;          // 半径計算済みと仮定
	

	result = StringConverter::RemoveExtension(result);
	string number = std::to_string(index);
	std::ofstream out(Model::BinaryFilePath + result + number + Model::BinaryPath, std::ios::binary);
	out.write((char*)&header, sizeof(header));
	out.write((char*)vertices.data(), sizeof(Vertex)* vertices.size());
	out.write((char*)indices.data(), sizeof(uint32_t)* indices.size());

	//読み込み成功
	return true;
}

void Mesh::Unload()
{
	mVertexArrays.clear();
}

Texture* Mesh::GetTexture(size_t index)
{
	if (index < mTextures.size())
	{
		return mTextures[index];
	}
	else
	{
		return nullptr;
	}
}
