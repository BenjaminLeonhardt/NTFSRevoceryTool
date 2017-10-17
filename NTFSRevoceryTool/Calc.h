#pragma once
ref class Calc abstract sealed
{
public:
	static __int16 get2Byte(array<unsigned char>^ tmp, unsigned int offset) {
		return tmp[offset] | (tmp[offset + 1] << 8);
	}
	static __int32 get4Byte(array<unsigned char>^ tmp, unsigned int offset) {
		return tmp[offset] | (tmp[offset + 1] << 8) | (tmp[offset + 2] << 16) | (tmp[offset + 3] << 24);
	}
	static __int64 get8Byte(array<unsigned char>^ tmp, unsigned int offset) {
		return tmp[offset] | (tmp[offset + 1] << 8) | (tmp[offset + 2] << 16) | (tmp[offset + 3] << 24) | tmp[offset + 4] << 32 | (tmp[offset + 5] << 40) | (tmp[offset + 6] << 48) | (tmp[offset + 7] << 56);
	}
};