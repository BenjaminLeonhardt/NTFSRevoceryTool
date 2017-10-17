#pragma once
using namespace System;
using namespace System::IO;

ref class mitScanGefundeneDatei
{
public:
	mitScanGefundeneDatei() {};
	mitScanGefundeneDatei(__int64 offsetDa, String^ mN, String^ artDerDatei, Stream^ filestream, String^ tailer) {
		offsetDateianfang = offsetDa;
		magicNumber = mN;
		erkannteDateiArt = artDerDatei;
		__int64 aktuelleStelle = offsetDa;
		__int32 junk = 1048576;
		__int32 junkCounter = 0;
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(junk);
		while (filestream->Length >= aktuelleStelle) {
			filestream->Seek(aktuelleStelle, System::IO::SeekOrigin::Begin);
			tmp = gcnew  array<unsigned char>(junk);
			filestream->Read(tmp, 0, junk);
			bool endeGefunden = false;
			int j = 512;
			while (!endeGefunden&&j<junk-512) {
				//if (tailer == nullptr) {
					if ((tmp[(j)-1] == 0x00) && (tmp[(j)-2] == 0x00) && (((j)-1) % 512 == 511)) { //annahme für das Dateiende: am ende eines Sectors steht ein NULL-Byte
						endeGefunden = true;
						erkannteDateigroesse = ((junk*junkCounter)+j);
						return;
					}
					else {
						j += 512;
					}
				/*}
				else {

				}*/
			}
			junkCounter++;
			aktuelleStelle += junk;
		}
	};
	__int64 getOffsetDateianfang() {
		return offsetDateianfang;
	}
	__int64 getErkannteDateigroesse() {
		return erkannteDateigroesse;
	}
	void setErkannteDateigroesse(__int64 erkannteDateigroesse) {
		this->erkannteDateigroesse = erkannteDateigroesse;
	}
	void setOffsetDateianfang(__int64 offsetDateianfang) {
		this->offsetDateianfang = offsetDateianfang;
	}
	String^ getMagicNumber() {
		return magicNumber;
	}
	void setMagicNumber(String^ magicNumber) {
		this->magicNumber = magicNumber;
	}
	String^ getErkannteDateiArt() {
		return erkannteDateiArt;
	}
	void setErkannteDateiArt(String^ erkannteDateiArt) {
		this->erkannteDateiArt = erkannteDateiArt;
	}
private:
	__int64 offsetDateianfang;
	String^ magicNumber;
	String^ erkannteDateiArt;
	__int64 erkannteDateigroesse;
};

