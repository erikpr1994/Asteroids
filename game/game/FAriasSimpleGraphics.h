#pragma once

#define WIN32_LEAN_AND_MEAN             // Excluir material rara vez utilizado de encabezados de Windows

#include <Windows.h>
#include <iostream>
#include <string>
#include <map>

namespace FASG
{
	class Vector2;
	class Sprite;


	enum class ConsoleFontRatios : short
	{
		_4x6 = 0, _8x8, _5x12, _7x12, _8x18, _9x20, _10x18, _11x24, _12x16, _13x28, _16x8, _16x12, _17x36, _24x24
	};

	enum class EBackColor : unsigned short
	{
		Black = 0x00,
		Red = BACKGROUND_RED,
		Green = BACKGROUND_GREEN,
		Yellow = BACKGROUND_RED | BACKGROUND_GREEN,
		Blue = BACKGROUND_BLUE,
		Magenta = BACKGROUND_RED | BACKGROUND_BLUE,
		Cyan = BACKGROUND_BLUE | BACKGROUND_GREEN,
		White = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN,
		LightBlack = Black | BACKGROUND_INTENSITY,
		LightRed = Red | BACKGROUND_INTENSITY,
		LightGreen = Green | BACKGROUND_INTENSITY,
		LightYellow = Yellow | BACKGROUND_INTENSITY,
		LightBlue = Blue | BACKGROUND_INTENSITY,
		LightMagenta = Magenta | BACKGROUND_INTENSITY,
		LightCyan = Cyan | BACKGROUND_INTENSITY,
		LightWhite = White | BACKGROUND_INTENSITY,
		Alpha0 = 0b100000000
	};

	enum class EForeColor : unsigned short
	{
		Black = 0x0,
		Red = FOREGROUND_RED,
		Green = FOREGROUND_GREEN,
		Yellow = FOREGROUND_RED | FOREGROUND_GREEN,
		Blue = FOREGROUND_BLUE,
		Magenta = FOREGROUND_RED | FOREGROUND_BLUE,
		Cyan = FOREGROUND_BLUE | FOREGROUND_GREEN,
		White = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN,
		LightBlack = Black | FOREGROUND_INTENSITY,
		LightRed = Red | FOREGROUND_INTENSITY,
		LightGreen = Green | FOREGROUND_INTENSITY,
		LightYellow = Yellow | FOREGROUND_INTENSITY,
		LightBlue = Blue | FOREGROUND_INTENSITY,
		LightMagenta = Magenta | FOREGROUND_INTENSITY,
		LightCyan = Cyan | FOREGROUND_INTENSITY,
		LightWhite = White | FOREGROUND_INTENSITY,
		Alpha0 = 0b100000000
	};

	enum class EAligned
	{
		LEFT,
		CENTER,
		RIGHT
	};

	void InitConsole(int _width, int _height);
	void DestroyConsole();

	void ShowConsoleCursor(bool showFlag);
	void SetFontSizeRatio(ConsoleFontRatios size);

	void WritePixelBuffer(int x, int y, EBackColor color);
	void WritePixelBuffer(int x1, int y1, int x2, int y2, EBackColor color);
	
	void WriteCharBuffer(int x, int y, char _char, EForeColor color);
	void WriteStringBuffer(int x, int y, std::string _string, EForeColor color);
	void WriteStringBuffer(int y, EAligned aligned, std::string _string, EForeColor color);
	void WriteSpriteBuffer(int x, int y, const Sprite& sprite);

	void RenderFrame();

	float GetDeltaTime();
	float GetTime();

	bool IsKeyPressed(char key);
	bool IsKeyDown(char key);
	bool IsMouseButtonDown(int i);
	Vector2 GetMousePosition();

	class Vector2
	{
	public:
		Vector2();
		Vector2(float x, float y) :x(x), y(y) {};
		Vector2(float c) :x(c), y(c) {};

		~Vector2();

		float x, y;

	};

	bool CheckBoundingBoxes(FASG::Sprite* sp1, FASG::Sprite* sp2);

	class Sprite final
	{

		EBackColor AtoBackColor(char c);

	public:
		Sprite();
		Sprite(std::string SpriteAssetFileName);
		~Sprite();

		void LoadSprite(std::string SpriteAssetFileName);

		Vector2 Location;
		static void SetCollisionCallback(void (*callbackFunc)(std::string sprite1Tag, std::string sprite2Tag));
		static void AddToCollisionSystem(Sprite& sprite, std::string spriteTag);

		int GetWidth() const { return spwidth; }
		int GetHeight() const { return spheight; }
		EBackColor* GetBuffer() const { return bufferColor; }
	private:
		int spwidth;
		int spheight;
		EBackColor* bufferColor;
		static std::map<std::string, Sprite*> collisionSprites;
		static void (*OnCollision)(std::string sprite1Tag, std::string sprite2Tag);
		static void CheckCollisions();

		friend void RenderFrame();
	};
}