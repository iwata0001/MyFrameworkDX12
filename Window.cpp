#include "Window.h"

#include <Windows.h>

LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//メッセージごとに処理を選択
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

bool Window::Create(int clientWidth, int clientHeight, const std::wstring titleName, const std::wstring& windowCalssName)
{
	// インスタンスハンドル取得
	HINSTANCE hInst = GetModuleHandle(0);

	//===============================
	// メインウィンドウ作成
	//===============================

	// ウィンドウクラスの定義
	WNDCLASSEX wc = {};
	wc. cbSize = sizeof(WNDCLASSEX); //構造体のサイズ
	wc.lpfnWndProc = (WNDPROC)WindowProcedure; // ウィンドウ関数
	wc.lpszClassName = windowCalssName.c_str(); // ウィンドウクラス名
	wc.hInstance = hInst; // インスタンスハンドル

	// ウィンドウクラスの登録
	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	// ウィンドウの作成
	m_hWnd = CreateWindow(
		windowCalssName.c_str(), // ウィンドウクラス名
		titleName.c_str(), // ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW - WS_THICKFRAME, // ウィンドウのタイプを標準タイプに
		0, // ウィンドウの位置X
		0, // ウィンドウの位置Y
		clientWidth, // ウィンドウの幅
		clientHeight, // ウィンドウの高さ
		nullptr, // 親ウィンドウのハンドル
		nullptr, // メニューのハンドル
		hInst, // インスタンスハンドル
		this
	);

	if (m_hWnd == nullptr)
	{
		return false;
	}

	// ウィンドウの表示
	ShowWindow(m_hWnd, SW_SHOW);

	// ウィンドウの更新
	UpdateWindow(m_hWnd);

	return true;

}

bool Window::ProcessMessage()
{
	// メッセージ取得
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		// 終了メッセージが来た
		if (msg.message == WM_QUIT) {
			return false;
		}

		// メッセージ処理
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}