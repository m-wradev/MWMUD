#pragma once

#include <DWrite.h>
#pragma comment(lib, "dwrite.lib")

struct TextRender
{
	static IDWriteFactory* pDWriteFactory;

	static void init();
};