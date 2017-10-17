#pragma once
#include "stdafx.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref struct eintrag {
	String^ Name;
	String^ Offset;
	String^ Wert;
	String^ HexWert;
};

ref class NTFSParser
{
private: unsigned __int64 offsetZumNTFSGPT=0;
public:
	unsigned __int64 getOffset() {
		return offsetZumNTFSGPT;
	}
	static Stream^ stream;
	static array<eintrag^>^ ausgeleseneEintraege = gcnew  array<eintrag^>(22);
	NTFSParser(Stream^ Filename, unsigned __int64 offset) {
		offsetZumNTFSGPT = offset;
		stream = Filename;
		ausgeleseneEintraege = gcnew  array<eintrag^>(22);
		readJMPInstruction();
		readMagicNr();
		readBytesPerSector();
		readSectorsPerCluster();
		readZeros();
		readUnused1();
		readMediadescriptor();
		readUnused2();
		readSectorsPerTrack();
		readNumberOfHeads();
		readHiddenSectors();
		readUnused3();
		readSignature();
		readTotalSectors();
		readMFTClusterNumber();
		readMFTMirrClusterNumber();
		readClusterPerFileRecordSegment();
		readClusterPerIndexBlock();
		readVolumeSerialNumber();
		readChecksum();
		readBootstrapCode();
		readSignatur55AA();
	};

	array<eintrag^>^ getAusgeleseneEintraege() {
		return ausgeleseneEintraege;
	}


	array<unsigned char>^ hexToAscii(array<unsigned char>^ tmp) {
		array<unsigned char>^ hex = gcnew  array<unsigned char>((tmp->Length * 3) + 2);
		hex[0] = '0';
		hex[1] = 'x';
		for (int i = 2, j = 0; i < hex->Length; i += 3, j++) {
			hex[i] = ((tmp[j] & 0xF0) >> 4) + 48;
			if (hex[i] > 57) {
				hex[i] += 7;
			}
			hex[i + 1] = (tmp[j] & 0x0F) + 48;
			if (hex[i + 1] > 57) {
				hex[i + 1] += 7;
			}
			hex[i + 2] = ' ';
		}
		return hex;
	}

	void readJMPInstruction() {
		stream->Seek(offsetZumNTFSGPT+0, System::IO::SeekOrigin::Begin);
		eintrag ^jmpInstruction = gcnew eintrag();
		jmpInstruction->Name = gcnew String(L"JMP Instruction");
		jmpInstruction->Offset = gcnew String(L"0x0000");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(3);
		stream->Read(tmp, 0, 3);
		if (tmp[0] != 0xeb || tmp[1] != 0x52 || tmp[2] != 0x90) {
			MessageBox::Show(L"Datei enthält keine NTFS Partition...");
		}
		Encoding^ enc = Encoding::UTF8;
		jmpInstruction->Wert = enc->GetString(tmp);
		ausgeleseneEintraege->SetValue(jmpInstruction, 0);
		array<unsigned char>^ hex = hexToAscii(tmp);

		jmpInstruction->HexWert = enc->GetString(hex);
	};

	void readMagicNr() {
		stream->Seek(offsetZumNTFSGPT + 3, System::IO::SeekOrigin::Begin);
		eintrag ^magicNr = gcnew eintrag();
		magicNr->Name = gcnew String(L"Magic Number");
		magicNr->Offset = gcnew String(L"0x0003");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(8);
		stream->Read(tmp, 0, 8);
		if (tmp[0] != 'N' || tmp[1] != 'T' || tmp[2] != 'F' || tmp[3] != 'S') {
			MessageBox::Show(L"Datei enthält keine NTFS Partition...");
		}

		Encoding^ enc = Encoding::UTF8;
		magicNr->Wert = enc->GetString(tmp);

		array<unsigned char>^ hex = hexToAscii(tmp);
		magicNr->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(magicNr, 1);
	};

	void readBytesPerSector() {
		stream->Seek(offsetZumNTFSGPT + 11, System::IO::SeekOrigin::Begin);
		eintrag ^bytesPerSector = gcnew eintrag();
		bytesPerSector->Name = gcnew String(L"Bytes Per Sector");
		bytesPerSector->Offset = gcnew String(L"0x0011");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(2);
		stream->Read(tmp, 0, 2);
		Int16 bPerS = (tmp[1] << 8) | tmp[0];
		Int16Converter conv;

		Encoding^ enc = Encoding::UTF8;
		bytesPerSector->Wert = conv.ConvertToString(bPerS);

		array<unsigned char>^ hex = hexToAscii(tmp);
		bytesPerSector->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(bytesPerSector, 2);
	};
	void readSectorsPerCluster() {
		stream->Seek(offsetZumNTFSGPT + 13, System::IO::SeekOrigin::Begin);
		eintrag ^sectorsPerCluster = gcnew eintrag();
		sectorsPerCluster->Name = gcnew String(L"Sector Per Cluster");
		sectorsPerCluster->Offset = gcnew String(L"0x0013");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(1);
		stream->Read(tmp, 0, 1);
		Int16 sPerC = tmp[0];
		Int16Converter conv;

		Encoding^ enc = Encoding::UTF8;
		sectorsPerCluster->Wert = conv.ConvertToString(sPerC);

		array<unsigned char>^ hex = hexToAscii(tmp);
		sectorsPerCluster->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(sectorsPerCluster, 3);
	};
	void readZeros() {
		stream->Seek(offsetZumNTFSGPT + 16, System::IO::SeekOrigin::Begin);
		eintrag ^zeroBytes = gcnew eintrag();
		zeroBytes->Name = gcnew String(L"Zero Bytes");
		zeroBytes->Offset = gcnew String(L"0x0016");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(3);
		stream->Read(tmp, 0, 3);
		Int16 zero = tmp[0];
		Int16Converter conv;

		Encoding^ enc = Encoding::UTF8;
		zeroBytes->Wert = conv.ConvertToString(zero);

		array<unsigned char>^ hex = hexToAscii(tmp);
		zeroBytes->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(zeroBytes, 4);
	};
	void readUnused1() {
		stream->Seek(offsetZumNTFSGPT + 19, System::IO::SeekOrigin::Begin);
		eintrag ^unusedBytes = gcnew eintrag();
		unusedBytes->Name = gcnew String(L"Unused");
		unusedBytes->Offset = gcnew String(L"0x0019");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(2);
		stream->Read(tmp, 0, 2);
		Int16 unused = tmp[0];
		Int16Converter conv;

		Encoding^ enc = Encoding::UTF8;
		unusedBytes->Wert = conv.ConvertToString(unused);

		array<unsigned char>^ hex = hexToAscii(tmp);
		unusedBytes->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(unusedBytes, 5);
	};
	void readMediadescriptor() {
		stream->Seek(offsetZumNTFSGPT + 21, System::IO::SeekOrigin::Begin);
		eintrag ^mediaDescriptor = gcnew eintrag();
		mediaDescriptor->Name = gcnew String(L"Media Descriptor");
		mediaDescriptor->Offset = gcnew String(L"0x0021");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(1);
		stream->Read(tmp, 0, 1);
		Int16 md = tmp[0];
		String ^ mediaType;
		if (md == 0xF8) {
			mediaType = " = Hard Disk / USB Stick";
		}
		else if (md == 0xF0) {
			mediaType = " Floppy";
		}
		Int16Converter conv;

		Encoding^ enc = Encoding::UTF8;
		mediaDescriptor->Wert = conv.ConvertToString(md) + mediaType;

		array<unsigned char>^ hex = hexToAscii(tmp);
		mediaDescriptor->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(mediaDescriptor, 6);
	};
	void readUnused2() {
		stream->Seek(offsetZumNTFSGPT + 22, System::IO::SeekOrigin::Begin);
		eintrag ^unusedBytes = gcnew eintrag();
		unusedBytes->Name = gcnew String(L"Unused 2");
		unusedBytes->Offset = gcnew String(L"0x0022");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(2);
		stream->Read(tmp, 0, 2);
		Int16 unused = tmp[0];
		Int16Converter conv;

		Encoding^ enc = Encoding::UTF8;
		unusedBytes->Wert = conv.ConvertToString(unused);

		array<unsigned char>^ hex = hexToAscii(tmp);
		unusedBytes->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(unusedBytes, 7);
	};
	void readSectorsPerTrack() {
		stream->Seek(offsetZumNTFSGPT + 24, System::IO::SeekOrigin::Begin);
		eintrag ^sectorsPerTrack = gcnew eintrag();
		sectorsPerTrack->Name = gcnew String(L"Sectors per Track");
		sectorsPerTrack->Offset = gcnew String(L"0x0024");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(2);
		stream->Read(tmp, 0, 2);
		Int16 sPerT = tmp[0];
		Int16Converter conv;

		Encoding^ enc = Encoding::UTF8;
		sectorsPerTrack->Wert = conv.ConvertToString(sPerT);

		array<unsigned char>^ hex = hexToAscii(tmp);
		sectorsPerTrack->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(sectorsPerTrack, 8);
	};
	void readNumberOfHeads() {
		stream->Seek(offsetZumNTFSGPT + 26, System::IO::SeekOrigin::Begin);
		eintrag ^numberOfHeads = gcnew eintrag();
		numberOfHeads->Name = gcnew String(L"Number of Heads");
		numberOfHeads->Offset = gcnew String(L"0x0026");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(2);
		stream->Read(tmp, 0, 2);
		Int16 sPerT = (tmp[1] << 8) | tmp[0];
		Int16Converter conv;

		Encoding^ enc = Encoding::UTF8;
		numberOfHeads->Wert = conv.ConvertToString(sPerT);

		array<unsigned char>^ hex = hexToAscii(tmp);
		numberOfHeads->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(numberOfHeads, 9);
	};
	void readHiddenSectors() {
		stream->Seek(offsetZumNTFSGPT + 28, System::IO::SeekOrigin::Begin);
		eintrag ^hiddenSectors = gcnew eintrag();
		hiddenSectors->Name = gcnew String(L"Hidden Sectors (Sectors befor this Partition)");
		hiddenSectors->Offset = gcnew String(L"0x0028");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(4);
		stream->Read(tmp, 0, 4);
		Int16 sPerT = (tmp[3] << 24) | (tmp[2] << 16) | (tmp[1] << 8) | tmp[0];
		Int16Converter conv;

		Encoding^ enc = Encoding::UTF8;
		hiddenSectors->Wert = conv.ConvertToString(sPerT);

		array<unsigned char>^ hex = hexToAscii(tmp);
		hiddenSectors->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(hiddenSectors, 10);
	};
	void readUnused3() {
		stream->Seek(offsetZumNTFSGPT + 32, System::IO::SeekOrigin::Begin);
		eintrag ^unusedBytes = gcnew eintrag();
		unusedBytes->Name = gcnew String(L"Unused 3");
		unusedBytes->Offset = gcnew String(L"0x0032");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(4);
		stream->Read(tmp, 0, 4);
		Int16 unused3 = (tmp[3] << 24) | (tmp[2] << 16) | (tmp[1] << 8) | tmp[0];
		Int16Converter conv;

		Encoding^ enc = Encoding::UTF8;
		unusedBytes->Wert = conv.ConvertToString(unused3);

		array<unsigned char>^ hex = hexToAscii(tmp);
		unusedBytes->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(unusedBytes, 11);
	};
	void readSignature() {
		stream->Seek(offsetZumNTFSGPT + 36, System::IO::SeekOrigin::Begin);
		eintrag ^signature = gcnew eintrag();
		signature->Name = gcnew String(L"Signature");
		signature->Offset = gcnew String(L"0x0036");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(4);
		stream->Read(tmp, 0, 4);
		if (tmp[0] != 0x80 || tmp[1] != 0x00 || tmp[2] != 0x80 || tmp[3] != 0x00) {
			MessageBox::Show(L"Die Signatur der Datei ist falsch...");
		}

		Encoding^ enc = Encoding::UTF8;
		signature->Wert = enc->GetString(tmp);

		array<unsigned char>^ hex = hexToAscii(tmp);
		signature->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(signature, 12);
	};
	void readTotalSectors() {
		stream->Seek(offsetZumNTFSGPT + 40, System::IO::SeekOrigin::Begin);
		eintrag ^totalSectors = gcnew eintrag();
		totalSectors->Name = gcnew String(L"Total sectors");
		totalSectors->Offset = gcnew String(L"0x0040");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(8);
		stream->Read(tmp, 0, 8);
		Int32 totSec = (tmp[7] << 56) | (tmp[6] << 48) | (tmp[5] << 40) | (tmp[4] << 32) | (tmp[3] << 24) | (tmp[2] << 16) | (tmp[1] << 8) | tmp[0];
		Int32Converter conv;

		Encoding^ enc = Encoding::UTF8;
		totalSectors->Wert = conv.ConvertToString(totSec);

		array<unsigned char>^ hex = hexToAscii(tmp);
		totalSectors->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(totalSectors, 13);
	};
	void readMFTClusterNumber() {
		stream->Seek(offsetZumNTFSGPT + 48, System::IO::SeekOrigin::Begin);
		eintrag ^MFTClusterNumber = gcnew eintrag();
		MFTClusterNumber->Name = gcnew String(L"MFT Cluster Number");
		MFTClusterNumber->Offset = gcnew String(L"0x0048");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(8);
		stream->Read(tmp, 0, 8);
		Int32 clusterNum = (tmp[7] << 56) | (tmp[6] << 48) | (tmp[5] << 40) | (tmp[4] << 32) | (tmp[3] << 24) | (tmp[2] << 16) | (tmp[1] << 8) | tmp[0];
		Int32Converter conv;

		Encoding^ enc = Encoding::UTF8;
		MFTClusterNumber->Wert = conv.ConvertToString(clusterNum);

		array<unsigned char>^ hex = hexToAscii(tmp);
		MFTClusterNumber->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(MFTClusterNumber, 14);
	};
	void readMFTMirrClusterNumber() {
		stream->Seek(offsetZumNTFSGPT + 56, System::IO::SeekOrigin::Begin);
		eintrag ^MFTMirrClusterNumber = gcnew eintrag();
		MFTMirrClusterNumber->Name = gcnew String(L"MFT Mirr Cluster Number");
		MFTMirrClusterNumber->Offset = gcnew String(L"0x0056");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(8);
		stream->Read(tmp, 0, 8);
		Int32 clusterNum = (tmp[7] << 56) | (tmp[6] << 48) | (tmp[5] << 40) | (tmp[4] << 32) | (tmp[3] << 24) | (tmp[2] << 16) | (tmp[1] << 8) | tmp[0];
		Int32Converter conv;

		Encoding^ enc = Encoding::UTF8;
		MFTMirrClusterNumber->Wert = conv.ConvertToString(clusterNum);

		array<unsigned char>^ hex = hexToAscii(tmp);
		MFTMirrClusterNumber->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(MFTMirrClusterNumber, 15);
	};
	void readClusterPerFileRecordSegment() {
		stream->Seek(offsetZumNTFSGPT + 64, System::IO::SeekOrigin::Begin);
		eintrag ^clusterPerFileRecordSegment = gcnew eintrag();
		clusterPerFileRecordSegment->Name = gcnew String(L"Cluster Per File Record Segment");
		clusterPerFileRecordSegment->Offset = gcnew String(L"0x0064");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(4);
		stream->Read(tmp, 0, 4);
		Int32 cPerFRS = (tmp[3] << 24) | (tmp[2] << 16) | (tmp[1] << 8) | tmp[0];
		Int32Converter conv;

		Encoding^ enc = Encoding::UTF8;
		clusterPerFileRecordSegment->Wert = conv.ConvertToString(cPerFRS);

		array<unsigned char>^ hex = hexToAscii(tmp);
		clusterPerFileRecordSegment->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(clusterPerFileRecordSegment, 16);
	};
	void readClusterPerIndexBlock() {
		stream->Seek(offsetZumNTFSGPT + 68, System::IO::SeekOrigin::Begin);
		eintrag ^clusterPerIndexBlock = gcnew eintrag();
		clusterPerIndexBlock->Name = gcnew String(L"Cluster Per Index Block");
		clusterPerIndexBlock->Offset = gcnew String(L"0x0068");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(4);
		stream->Read(tmp, 0, 4);
		Int32 cPerIB = (tmp[3] << 24) | (tmp[2] << 16) | (tmp[1] << 8) | tmp[0];
		Int32Converter conv;

		Encoding^ enc = Encoding::UTF8;
		clusterPerIndexBlock->Wert = conv.ConvertToString(cPerIB);

		array<unsigned char>^ hex = hexToAscii(tmp);
		clusterPerIndexBlock->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(clusterPerIndexBlock, 17);
	};
	void readVolumeSerialNumber() {
		stream->Seek(offsetZumNTFSGPT + 72, System::IO::SeekOrigin::Begin);
		eintrag ^volumeSerialNumber = gcnew eintrag();
		volumeSerialNumber->Name = gcnew String(L"Volume Serial Number");
		volumeSerialNumber->Offset = gcnew String(L"0x0072");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(8);
		stream->Read(tmp, 0, 8);
		Int32 cPerIB = (tmp[7] << 56) | (tmp[6] << 48) | (tmp[5] << 40) | (tmp[4] << 32) | (tmp[3] << 24) | (tmp[2] << 16) | (tmp[1] << 8) | tmp[0];
		Int32Converter conv;

		Encoding^ enc = Encoding::UTF8;
		volumeSerialNumber->Wert = conv.ConvertToString(cPerIB);

		array<unsigned char>^ hex = hexToAscii(tmp);
		volumeSerialNumber->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(volumeSerialNumber, 18);
	};
	void readChecksum() {
		stream->Seek(offsetZumNTFSGPT + 80, System::IO::SeekOrigin::Begin);
		eintrag ^checksum = gcnew eintrag();
		checksum->Name = gcnew String(L"Checksum");
		checksum->Offset = gcnew String(L"0x0080");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(4);
		stream->Read(tmp, 0, 4);
		Int32 cPerIB = (tmp[3] << 24) | (tmp[2] << 16) | (tmp[1] << 8) | tmp[0];
		Int32Converter conv;

		Encoding^ enc = Encoding::UTF8;
		checksum->Wert = conv.ConvertToString(cPerIB);

		array<unsigned char>^ hex = hexToAscii(tmp);
		checksum->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(checksum, 19);
	};
	void readBootstrapCode() {
		stream->Seek(offsetZumNTFSGPT + 84, System::IO::SeekOrigin::Begin);
		eintrag ^checksum = gcnew eintrag();
		checksum->Name = gcnew String(L"Bootstrap Code");
		checksum->Offset = gcnew String(L"0x0084");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(426);
		stream->Read(tmp, 0, 426);


		Encoding^ enc = Encoding::UTF8;
		checksum->Wert = "";

		array<unsigned char>^ hex = hexToAscii(tmp);
		checksum->HexWert = enc->GetString(hex);

		ausgeleseneEintraege->SetValue(checksum, 20);
	};
	void readSignatur55AA() {
		stream->Seek(offsetZumNTFSGPT + 510, System::IO::SeekOrigin::Begin);
		eintrag ^signatur55AA = gcnew eintrag();
		signatur55AA->Name = gcnew String(L"Signatur 0x 55 AA");
		signatur55AA->Offset = gcnew String(L"0x0510");
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(2);
		stream->Read(tmp, 0, 2);
		if (tmp[0] != 0x55 || tmp[1] != 0xAA) {
			MessageBox::Show(L"Signatur 0x 55 AA nicht gefunden...");
		}
		Encoding^ enc = Encoding::UTF8;
		signatur55AA->Wert = enc->GetString(tmp);
		ausgeleseneEintraege->SetValue(signatur55AA, 21);
		array<unsigned char>^ hex = hexToAscii(tmp);

		signatur55AA->HexWert = enc->GetString(hex);
	};
};

