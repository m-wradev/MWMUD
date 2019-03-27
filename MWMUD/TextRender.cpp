#include "TextRender.h"

IDWriteFactory* TextRender::pDWriteFactory = nullptr;

void TextRender::init()
{
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));
}