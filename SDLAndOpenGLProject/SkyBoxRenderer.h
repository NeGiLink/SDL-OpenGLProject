#pragma once
#include "Math.h"
#include "Texture.h"
#include "Shader.h"
#include "WinMain.h"
#include "BaseScene.h"

class SkyBoxRenderer
{
private:
    class BaseScene* mGame;
    class Texture* mTexture;      // Cubemap用
    class VertexArray* mCubeVAO;  // 裏面描画用の立方体メッシュ
    int mVerticesCount;
public:
    SkyBoxRenderer();
    ~SkyBoxRenderer();

    // Cubemap読み込み
    void Load(const std::string& file, int faceSize = 512);

    void Update(float deltaTime) {}

    void Draw(class Shader* shader, const Matrix4& view, const Matrix4& proj);

    void UnLoad();

    class Texture* GetTexture() const { return mTexture; }
};

