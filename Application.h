#pragma once

#include "Window.h"

class Application
{
public:
	/// <summary>
	/// �A�v���P�[�V�������s
	/// </summary>
	void Excute();

private:
	Window m_window;

	Application() {}

public:
	static Application& Instance()
	{
		static Application instance;
		return instance;
	}
};