// Decrypt.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
using namespace CryptoPP;

extern "C"
{
	__declspec(dllexport) void Decrypt(const byte src[], unsigned int srcSize, byte dst[], unsigned int dstSize, const byte key[], unsigned int keySize, const byte iv[])
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

	__declspec(dllexport) void DecryptNoDecompress(const byte src[], unsigned int srcSize, byte dst[], unsigned int dstSize, const byte key[], unsigned int keySize, const byte iv[])
	{
		ArraySource as(src, srcSize, true,
			new Base64Decoder(
				new StreamTransformationFilter(CTR_Mode<AES>::Decryption(key, keySize, iv),
					new ArraySink(dst, dstSize)
				)
			)
		);
	}
}