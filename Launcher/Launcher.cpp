// Launcher.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h>
#include <string>

int main()
{
    // 自分の実行パスを取得
    char buf[MAX_PATH];
    GetModuleFileNameA(NULL, buf, MAX_PATH);
    std::string exePath(buf);

    // 自分があるディレクトリを抽出
    size_t pos = exePath.find_last_of("\\/");
    std::string baseDir = exePath.substr(0, pos);

    // bin フォルダを組み立てる
    std::string binPath = baseDir + "\\bin";
    std::string targetExe = binPath + "\\SDLAndOpenGLProject.exe";

    // DLL 検索パスに bin を追加
    SetDllDirectoryA(binPath.c_str());

    // 本体 exe を起動
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    BOOL ok = CreateProcessA(
        targetExe.c_str(),   // 実行ファイル
        NULL,                // コマンドライン引数（必要ならここに書く）
        NULL, NULL, FALSE,
        0,
        NULL,
        binPath.c_str(),     // 作業ディレクトリを bin に設定
        &si,
        &pi
    );

    if (!ok) {
        MessageBoxA(NULL, "SDLAndOpenGLProject.exe を起動できませんでした", "Launcher Error", MB_OK);
        return 1;
    }

    // 親プロセスは終了してOK（待ちたければ WaitForSingleObject）
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
