// Decrypt.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
using namespace CryptoPP;

extern "C"
{
	__declspec(dllexport) void Decrypt(const byte src[], size_t srcSize, byte dst[], size_t dstSize, const byte key[], size_t keySize, const byte iv[])
	{
		ArraySource as(src, srcSize, true,
			new Base64Decoder(
				new StreamTransformationFilter(CTR_Mode<AES>::Decryption(key, keySize, iv),
					new ZlibDecompressor(
						new ArraySink(dst, dstSize)
					)
				)
			)
		);
	}

	__declspec(dllexport) void DecryptNoDecompress(const byte src[], size_t srcSize, byte dst[], size_t dstSize, const byte key[], size_t keySize, const byte iv[])
	{
		ArraySource as(src, srcSize, true,
			new Base64Decoder(
				new StreamTransformationFilter(CTR_Mode<AES>::Decryption(key, keySize, iv),
					new ArraySink(dst, dstSize)
				)
			)
		);
	}

	__declspec(dllexport) void Decompress(const byte src[], size_t srcSize, byte dst[], size_t dstSize)
	{
		ArraySource as(src, srcSize, true,
			new ZlibDecompressor(
				new ArraySink(dst, dstSize)
			)
		);
	}
}