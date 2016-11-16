#pragma once
class TextureHelper
{
private:
	int _countTextures;
public:
	TextureHelper();
	~TextureHelper();
	struct TextureImage
	{
		unsigned char *ImageData;
		unsigned int  BPP;
		unsigned int Width, Height;
		unsigned int ID;
		unsigned int Type;
		unsigned int Format;
	};
	void Activate(TextureImage *texture);
	void Load(char *filename, TextureImage *texture);
	void Free(TextureImage *texture);
};