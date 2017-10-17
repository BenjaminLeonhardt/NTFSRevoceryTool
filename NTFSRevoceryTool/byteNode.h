#pragma once
using namespace System;
using namespace System::IO;
using namespace System::Collections;
ref class byteNode{
public:
	byteNode() {
		if (childes == nullptr) {
			//childes = gcnew ArrayList;
			childes = gcnew array<byteNode^>(256);
		}
	};
	byteNode(String^ byteAlsAscii,__int8 byte, String^ extention):byteAlsAscii(byteAlsAscii),byte(byte),extention(extention){
		if (childes == nullptr) {
			//childes = gcnew ArrayList;
			childes = gcnew array<byteNode^>(256);
		}
	};
	/*ArrayList^ getChildes() {
		return childes;
	}
	void setNewChild(byteNode^ neuesChildByte) {
		childes->Add(neuesChildByte);
	}*/
	array<byteNode^>^ getChildes() {
		return childes;
	}
	void setNewChild(byteNode^ neuesChildByte) {
		childes[neuesChildByte->getByte()]=neuesChildByte;
	}
	unsigned __int8 getByte() {
		return byte;
	}
	void setByte(__int8 newByte) {
		this->byte = newByte;
	}
	String^ getByteAlsAscii() {
		return byteAlsAscii;
	}
	void setByteAlsAscii(String^ newByteAlsAscii) {
		this->byteAlsAscii=newByteAlsAscii;
	}
	String^ getExtention() {
		return extention;
	}
	void setExtention(String^ newExtention) {
		this->extention = newExtention;
	}
	String^ getTailer() {
		return tailer;
	}
	void setTailer(String^ newTailer) {
		this->tailer = newTailer;
	}
	String^ getHeader() {
		return header;
	}
	void setHeader(String^ newHeader) {
		this->header = newHeader;
	}

	unsigned __int64 getCounter() {
		return counter++;
	}
	void setCounter(unsigned __int64 counter) {
		this->counter = counter;
	}
private:
	String^ byteAlsAscii;
	unsigned __int8 byte;
	//ArrayList^ childes;
	array<byteNode^>^ childes;
	String^ extention;
	String^ tailer;
	String^ header;
	unsigned __int64 counter;
};

