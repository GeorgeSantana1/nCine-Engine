#ifndef CLASS_NCINE_TEXTURELOADERKTX
#define CLASS_NCINE_TEXTURELOADERKTX

#include <stdint.h> // for header
#include "ITextureLoader.h"

namespace ncine {

/// KTX texture loader
class TextureLoaderKtx : public ITextureLoader
{
  public:
	explicit TextureLoaderKtx(const char *filename);
	explicit TextureLoaderKtx(IFile *fileHandle);

  private:
	static const int KtxIdentifierLength = 12;
	static uint8_t fileIdentifier_[KtxIdentifierLength];

	/// Header for the KTX format
	typedef struct KtxHeader
	{
		uint8_t		identifier[KtxIdentifierLength];
		uint32_t    endianess;
		uint32_t    glType;
		uint32_t    glTypeSize;
		uint32_t    glFormat;
		uint32_t    glInternalFormat;
		uint32_t    glBaseInternalFormat;
		uint32_t    pixelWidth;
		uint32_t    pixelHeight;
		uint32_t    pixelDepth;
		uint32_t    numberOfArrayElements;
		uint32_t    numberOfFaces;
		uint32_t    numberOfMipmapLevels;
		uint32_t	bytesOfKeyValueData;
	} KtxHeader;

	void init();

	/// Reads the KTX header and fills the corresponding structure
	void readHeader(KtxHeader &header);
	/// Parses the KTX header to determine its format
	void parseFormat(const KtxHeader &header);
};

}

#endif
