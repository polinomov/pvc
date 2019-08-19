
#include <string>
#include <iostream>
#include "icompute.h"
#include "font.h"
#include "OpenGL/shaders/ginclude.h"
#include "OpenGL/shaders/render-font.cs.glsl"

namespace pcrlib 
{
	static const uint8_t fontSrc[95][7] = {
		0,    0,   0,   0,   0,   0,   0, // ' '  32
		0,    6,  95,  95,   6,   0,   0, // '!'  33
		0,    7,   7,   0,   7,   7,   0, // '"'  34
		20, 127, 127,  20, 127, 127,  20, // '#'  35
		36,  46, 107, 107,  58,  18,   0, // '$'  36
		70, 102,  48,  24,  12, 102,  98, // '%'  37
		48, 122,  79,  93,  55, 122,  72, // '&'  38
		4,    7,   3,   0,   0,   0,   0, // '''  39
		0,   28,  62,  99,  65,   0,   0, // '('  40
		0,   65,  99,  62,  28,   0,   0, // ')'  41
		8,   42,  62,  28,  28,  62,  42, // '*'  42
		8,    8,  62,  62,   8,   8,   0, // '+'  43
		0,  128, 224,  96,   0,   0,   0, // ','  44
		8,    8,   8,   8,   8,   8,   0, // '-'  45
		0,    0,  96,  96,   0,   0,   0, // '.'  46
		96,  48,  24,  12,   6,   3,   1, // '/'  47
		62, 127, 113,  89,  77, 127,  62, // '0'  48
		64,  66, 127, 127,  64,  64,   0, // '1'  49
		98, 115,  89,  73, 111, 102,   0, // '2'  50
		34,  99,  73,  73, 127,  54,   0, // '3'  51
		24,  28,  22,  83, 127, 127,  80, // '4'  52
		39, 103,  69,  69, 125,  57,   0, // '5'  53
		60, 126,  75,  73, 121,  48,   0, // '6'  54
		3,    3, 113, 121,  15,   7,   0, // '7'  55
		54, 127,  73,  73, 127,  54,   0, // '8'  56
		6,   79,  73, 105,  63,  30,   0, // '9'  57
		0,    0, 102, 102,   0,   0,   0, // ':'  58
		0,  128, 230, 102,   0,   0,   0, // ';'  59
		8,   28,  54,  99,  65,   0,   0, // '<'  60
		36,  36,  36,  36,  36,  36,   0, // '='  61
		0,   65,  99,  54,  28,   8,   0, // '>'  62
		2,    3,  81,  89,  15,   6,   0, // '?'  63
		62, 127,  65,  93,  93,  31,  30, // '@'  64
		124,126,  19,  19, 126, 124,   0, // 'A'  65
		65, 127, 127,  73,  73, 127,  54, // 'B'  66
		28,  62,  99,  65,  65,  99,  34, // 'C'  67
		65, 127, 127,  65,  99,  62,  28, // 'D'  68
		65, 127, 127,  73,  93,  65,  99, // 'E'  69
		65, 127, 127,  73,  29,   1,   3, // 'F'  70
		28,  62,  99,  65,  81, 115, 114, // 'G'  71
		127,127,   8,   8, 127, 127,   0, // 'H'  72
		0,   65, 127, 127,  65,   0,   0, // 'I'  73
		48, 112,  64,  65, 127,  63,   1, // 'J'  74
		65, 127, 127,   8,  28, 119,  99, // 'K'  75
		65, 127, 127,  65,  64,  96, 112, // 'L'  76
		127,127,  14,  28,  14, 127, 127, // 'M'  77
		127,127,   6,  12,  24, 127, 127, // 'N'  78
		28,  62,  99,  65,  99,  62,  28, // 'O'  79
		65, 127, 127,  73,   9,  15,   6, // 'P'  80
		30,  63,  33, 113, 127,  94,   0, // 'Q'  81
		65, 127, 127,   9,  25, 127, 102, // 'R'  82
		38, 111,  77,  89, 115,  50,   0, // 'S'  83
		3,   65, 127, 127,  65,   3,   0, // 'T'  84
		127,127,  64,  64, 127, 127,   0, // 'U'  85
		31,  63,  96,  96,  63,  31,   0, // 'V'  86
		127,127,  48,  24,  48, 127, 127, // 'W'  87
		67, 103,  60,  24,  60, 103,  67, // 'X'  88
		7,   79, 120, 120,  79,   7,   0, // 'Y'  89
		71,  99, 113,  89,  77, 103, 115, // 'Z'  90
		0,  127, 127,  65,  65,   0,   0, // '['  91
		1,    3,   6,  12,  24,  48,  96, // '\'  92
		0,   65,  65, 127, 127,   0,   0, // ']'  93
		8,   12,   6,   3,   6,  12,   8, // '^'  94
		128,128, 128, 128, 128, 128, 128, // '_'  95
		0,    0,   3,   7,   4,   0,   0, // '`'  96
		32, 116,  84,  84,  60, 120,  64, // 'a'  97
		65, 127,  63,  72,  72, 120,  48, // 'b'  98
		56, 124,  68,  68, 108,  40,   0, // 'c'  99
		48, 120,  72,  73,  63, 127,  64, // 'd' 100
		56, 124,  84,  84,  92,  24,   0, // 'e' 101
		72, 126, 127,  73,   3,   2,   0, // 'f' 102
		56, 188, 164, 164, 252, 120,   0, // 'g' 103
		65, 127, 127,   8,   4, 124, 120, // 'h' 104
		0,   68, 125, 125,  64,   0,   0, // 'i' 105
		96, 224, 128, 128, 253, 125,   0, // 'j' 106
		65, 127, 127,  16,  56, 108,  68, // 'k' 107
		0,   65, 127, 127,  64,   0,   0, // 'l' 108
		120,124,  28,  56,  28, 124, 120, // 'm' 109
		124,124,   4,   4, 124, 120,   0, // 'n' 110
		56, 124,  68,  68, 124,  56,   0, // 'o' 111
		0,  252, 252, 164,  36,  60,  24, // 'p' 112
		24,  60,  36, 164, 248, 252, 132, // 'q' 113
		68, 124, 120,  76,   4,  28,  24, // 'r' 114
		72,  92,  84,  84, 116,  36,   0, // 's' 115
		0,    4,  62, 127,  68,  36,   0, // 't' 116
		60, 124,  64,  64,  60, 124,  64, // 'u' 117
		28,  60,  96,  96,  60,  28,   0, // 'v' 118
		60, 124, 112,  56, 112, 124,  60, // 'w' 119
		68, 108,  56,  16,  56, 108,  68, // 'x' 120
		60, 188, 160, 160, 252, 124,   0, // 'y' 121
		76, 100, 116,  92,  76, 100,   0, // 'z' 122
		8,    8,  62, 119,  65,  65,   0, // '{' 123
		0,    0,   0, 119, 119,   0,   0, // '|' 124
		65,  65, 119,  62,   8,   8,   0, // '}' 125
		2,    3,   1,   3,   2,   3,   1, // '~' 126
	};

	class FontRender : public IFontRenderer
	{
	public:
		static const int m_fontW = 8;
		static const int m_fontH = 8;
		static const int m_numSym = 95;
		static const int m_maxChars = 65000;
		FontChars *m_pCharsXY;
		int m_numCharsToRender;
		ICBuffer * m_bufferChars = NULL;
		ICBuffer  *m_fontImg = NULL;
		ICShader  *m_fontShader = NULL;
		void initFont();
		void setString(const char *pStr, unsigned int x, unsigned int y);
		void renderFont(ICBuffer *pDst, ICBuffer *pGlob);
		void releaseFont();
	}; //class FontRender

	IFontRenderer * IFontRenderer::getInstance()
	{
		FontRender *pRet =  new  FontRender();
		pRet->initFont();
		return pRet;
	}

	void IFontRenderer::release(IFontRenderer **ppIfr) 
	{
		if (*ppIfr) 
		{
			FontRender *pfr = static_cast<FontRender*>(*ppIfr);
			pfr->releaseFont();
			*ppIfr = NULL;
		}
	}

	void FontRender::initFont()
	{
		unsigned int imgSize = m_fontW * m_fontH *m_numSym * sizeof(int);
		unsigned char *pPix = new unsigned char[imgSize];
		memset(pPix, 0, imgSize);
		for (int i = 0; i < m_numSym; i++) 
		{
			unsigned int *pSym = (unsigned int *)pPix;
			pSym += i * m_fontH *m_fontW;
			for (int y = 0; y < m_fontH; y++)
			{
				for (int x = 0; x < m_fontW-1; x++)
				{
					uint8_t dc = fontSrc[i][x];
					int vl = dc & (1 << y);
					int bt = (vl == 0) ? 0 : 1;
					int xx = m_fontW - x -1;
					int yy = m_fontH - y -1;
					pSym[yy + xx * m_fontW] = (bt ==1) ? 1 : 0;
				}
			}
		}

		m_fontImg = createICBuffer();
		m_fontImg->allocate(imgSize);
		m_fontImg->setData(pPix, imgSize);
		delete pPix;

		m_pCharsXY = new FontChars[m_maxChars];
		m_numCharsToRender = 0;
		m_bufferChars = createICBuffer();
		m_bufferChars->allocate(m_maxChars * sizeof(FontChars));

		/*
		setString("                              ", 20, 12);
		setString("   PRESS SPACE TO SHOW HELP   ", 20, 20);
		setString("                              ", 20, 28);
		setString("   Point Size=1 PgUp/PgDn     ", 20, 36);
	    */

		m_fontShader = createICShader();
		m_fontShader->initFromSource(cs_render_font8x8.c_str());
	}

	void FontRender::setString(const char *pStr, unsigned int x, unsigned int y)
	{
		unsigned int xStart = x;
		for (const char *ps = pStr; *ps; ps++)
		{
			unsigned char symIndex = *ps-32;
			if (m_numCharsToRender < m_maxChars) {
				FontChars  *pD = m_pCharsXY + m_numCharsToRender;
				pD->x = xStart;
				pD->y = y;
				if (symIndex < m_numSym) {
					pD->letter = symIndex;
				}
				else {
					pD->letter = 0;
				}
				xStart += m_fontW;
				m_numCharsToRender++;
			}
		}
	}

	void FontRender::renderFont(ICBuffer *pDst, ICBuffer *pGlob)
	{
		if (m_numCharsToRender == 0) 
		{
			return;
		}
		m_bufferChars->setData(m_pCharsXY, m_numCharsToRender * sizeof(FontChars));
		m_fontShader->execute(1, m_numCharsToRender, 1, { pGlob ,m_fontImg,m_bufferChars,pDst });
		m_numCharsToRender = 0;
	}

	void FontRender::releaseFont()
	{
	
	}

}// namespace pcrlib 