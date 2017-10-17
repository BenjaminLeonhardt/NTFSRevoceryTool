#pragma once
#include "MFTAttribute.h"
#include "Calc.h"
using namespace System;
using namespace System::Collections;
using namespace System::Text;
using namespace System::IO;

ref class MFTEintrag
{
public:
	MFTEintrag() {};

	ref struct mftRecordHeader {
		array<unsigned char>^ magicNrFILE = gcnew  array<unsigned char>(4);
		__int16 offsetUpdateSequence;
		__int16 UpdateSequenceSizeInWords;
		__int64 LogFileSequenceNumber;
		__int16 SequenceNumber;
		__int16 HardlinkCount;
		unsigned __int16 OffsetFirstAttribut;
		__int16 FlagsMFTRecordHeader;
		__int32 RealSizeOfTheFileRecord;
		__int32 AllocateSizeOfTheFileRecord;
		__int64 BaseFileRecord;
		__int16 NextAttributeID;
		__int16 padding;
		__int32 IDOfThisRecord;
		__int16 UpdateSequenceNumber;
		__int32 UpdateSequenceArray;
		__int16 padding2;
	} mftRH;

	ArrayList^ attributeArray;



	MFTEintrag(unsigned __int64 offset, Stream^ filestream) {
		filestream->Seek(offset, System::IO::SeekOrigin::Begin);
		array<unsigned char>^ tmp = gcnew array<unsigned char>(56);
		filestream->Read(tmp, 0, 54);
		for (int i = 0; i < 4; i++) {
			this->mftRH.magicNrFILE[i] = tmp[i];
		}

		if(offset>=0x140FC7800){
			int a = 0;
		}

		if (this->mftRH.magicNrFILE[0] != 'F' || this->mftRH.magicNrFILE[1] != 'I' || this->mftRH.magicNrFILE[2] != 'L' || this->mftRH.magicNrFILE[3] != 'E') {
			Console::WriteLine(L"FILE Header nicht gefunden... Dies ist kein MFT Eintrag.");
			delete tmp;
			return;
		}
		this->mftRH.offsetUpdateSequence = Calc::get2Byte(tmp, 4);
		this->mftRH.UpdateSequenceSizeInWords = Calc::get2Byte(tmp, 6);
		this->mftRH.LogFileSequenceNumber = Calc::get8Byte(tmp, 8);
		this->mftRH.SequenceNumber = Calc::get2Byte(tmp, 16);
		this->mftRH.HardlinkCount = Calc::get2Byte(tmp, 18);
		this->mftRH.OffsetFirstAttribut = Calc::get2Byte(tmp, 20);
		this->mftRH.FlagsMFTRecordHeader = Calc::get2Byte(tmp, 22);
		this->mftRH.RealSizeOfTheFileRecord = Calc::get4Byte(tmp, 24);
		this->mftRH.AllocateSizeOfTheFileRecord = Calc::get4Byte(tmp, 28);
		this->mftRH.BaseFileRecord = Calc::get8Byte(tmp, 32);
		this->mftRH.NextAttributeID = Calc::get2Byte(tmp, 40);
		this->mftRH.padding = Calc::get2Byte(tmp, 42);
		this->mftRH.IDOfThisRecord = Calc::get4Byte(tmp, 44);
		this->mftRH.UpdateSequenceNumber = Calc::get2Byte(tmp, 48);
		this->mftRH.UpdateSequenceArray = Calc::get4Byte(tmp, 50);
		this->mftRH.padding2 = Calc::get2Byte(tmp, 54);

		filestream->Seek(offset, System::IO::SeekOrigin::Begin);
		delete tmp;
		if (this->mftRH.RealSizeOfTheFileRecord < 10000 && this->mftRH.RealSizeOfTheFileRecord > 100) {
			tmp = gcnew array<unsigned char>(this->mftRH.RealSizeOfTheFileRecord);
			filestream->Read(tmp, 0, this->mftRH.RealSizeOfTheFileRecord);
		}
		else {
			return;
		}
		unsigned __int32 offsetAttribute = this->mftRH.OffsetFirstAttribut;
		if (this->mftRH.OffsetFirstAttribut + 8 > tmp->Length-1) {
			return;
		}
		attributeArray = gcnew ArrayList;
		__int32 step = Calc::get4Byte(tmp, offsetAttribute + 4);
		int i = 0;
		while ((offsetAttribute + 24) < this->mftRH.RealSizeOfTheFileRecord && step != 0 && this->mftRH.RealSizeOfTheFileRecord<10000 && i<50) {
			i++;
			if (i > 50) {
				Console::WriteLine("Hier stimmt evtl was nicht");
			}
			MFTAttribute^ neuesAttribute = gcnew MFTAttribute(tmp, offsetAttribute);
			attributeArray->Add(neuesAttribute);
			
			offsetAttribute = offsetAttribute + Calc::get4Byte(tmp, offsetAttribute + 4);
			delete neuesAttribute;
		}
		delete tmp;
	};
};

