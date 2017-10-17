#pragma once
#include "Calc.h"
ref class attributeHeaderResident{
public:
	attributeHeaderResident() {

	};

	attributeHeaderResident(array<unsigned char>^ tmp, short offset) {
		LengthOfTheAttributeWithoutHeader = Calc::get4Byte(tmp, offset + 16);
		OffsetToStartOfAttributeDataStreamFromStartOfHeader = Calc::get2Byte(tmp, offset + 20);
		indexedFlag = tmp[offset + 22];
		padding = tmp[offset + 23];
	};

	__int32 getLengthOfTheAttributeWithoutHeader() {
		return LengthOfTheAttributeWithoutHeader;
	};

	__int16 getOffsetToStartOfAttributeDataStreamFromStartOfHeader() {
		return OffsetToStartOfAttributeDataStreamFromStartOfHeader;
	};

	__int8 getIndexedFlag() {
		return indexedFlag;
	};

	__int8 getPadding() {
		return padding;
	};

private:
	__int32 LengthOfTheAttributeWithoutHeader;
	__int16 OffsetToStartOfAttributeDataStreamFromStartOfHeader;
	__int8 indexedFlag;
	__int8 padding;
};

