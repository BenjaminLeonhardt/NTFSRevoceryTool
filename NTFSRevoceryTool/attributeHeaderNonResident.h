#pragma once
#include "Calc.h"

ref class attributeHeaderNonResident
{
public:
	attributeHeaderNonResident() {

	};

	__int64 getFirstVirtualClusterNumber() {
		return FirstVirtualClusterNumber;
	};

	__int64 getLastVirtualClusterNumber() {
		return LastVirtualClusterNumber;
	};

	__int16 getOffsetToDataRuns() {
		return OffsetToDataRuns;
	};

	__int16 getCompressionUnitSize() {
		return CompressionUnitSize;
	};

	__int32 getPadding() {
		return Padding;
	};

	__int64 getPhysicalSizeOfTheAttribute() {
		return PhysicalSizeOfTheAttribute;
	};

	__int64 getLogicalSizeOfTheAttribute() {
		return LogicalSizeOfTheAttribute;
	};

	__int64 getInitializedSizeOfTheAttributeDataStream() {
		return InitializedSizeOfTheAttributeDataStream;
	};

	attributeHeaderNonResident(array<unsigned char>^ tmp, short offset) {
		FirstVirtualClusterNumber = Calc::get8Byte(tmp, offset + 16);
		LastVirtualClusterNumber = Calc::get8Byte(tmp, offset + 24);
		OffsetToDataRuns = Calc::get2Byte(tmp, offset + 32);
		CompressionUnitSize = Calc::get2Byte(tmp, offset + 34);
		Padding = Calc::get4Byte(tmp, offset + 36);
		PhysicalSizeOfTheAttribute = Calc::get8Byte(tmp, offset + 40);
		LogicalSizeOfTheAttribute = Calc::get8Byte(tmp, offset + 48);
		InitializedSizeOfTheAttributeDataStream = Calc::get8Byte(tmp, offset + 56);
	};

private:
	__int64 FirstVirtualClusterNumber;
	__int64 LastVirtualClusterNumber;
	__int16 OffsetToDataRuns;
	__int16 CompressionUnitSize;
	__int32 Padding;
	__int64 PhysicalSizeOfTheAttribute;
	__int64 LogicalSizeOfTheAttribute;
	__int64 InitializedSizeOfTheAttributeDataStream;
	array<char^>^ NameOfTheAttribute;
};

