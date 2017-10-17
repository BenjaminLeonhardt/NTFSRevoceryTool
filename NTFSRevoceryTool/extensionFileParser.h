#pragma once
#include "byteNode.h"
ref class extensionFileParser{
public:
	/*extensionFileParser() {
		filestream = gcnew StreamReader("DateiSignaturen.txt");
		while (!filestream->EndOfStream) {
			String^ fileExtention = filestream->ReadLine();
			int i = 0;
			__int8 byte;
			if (rootNode == nullptr) {
				rootNode = gcnew byteNode;
			}
			byteNode^ node;
			byteNode^ prevNode;
			String^ byteAlsAscii;
			bool gefunden = false;
			IEnumerator^ enu = rootNode->getChildes()->GetEnumerator();
			prevNode = rootNode;
			__int8 headerExtentionOderTailer = 0;
			while (i < fileExtention->Length) {
				if (i > 0) {
					if (fileExtention[i - 1].Equals(':')) {
						node->setHeader(fileExtention->Substring(0, fileExtention->IndexOf(":")));
						node->setExtention(fileExtention->Substring(i, (fileExtention->LastIndexOf(":"))-i) );
						headerExtentionOderTailer++;
					}
				}
				if (headerExtentionOderTailer == 0) {
					byteAlsAscii = fileExtention->Substring(i, 2);
					byte = AsciiToHex(byteAlsAscii);
					while (enu->MoveNext()) {
						node = safe_cast<byteNode^>(enu->Current);
						if (node->getByte() == byte) {
							gefunden = true;
							enu = node->getChildes()->GetEnumerator();
							prevNode = node;
							break;
						}
					}
					if (!gefunden) {
						node = gcnew byteNode(byteAlsAscii, byte, nullptr);
						prevNode->setNewChild(node);
						prevNode = node;
						enu = node->getChildes()->GetEnumerator();
					}
					i += 3;
					gefunden = false;
				}
				else if (headerExtentionOderTailer == 1) {					
					node->setTailer(fileExtention->Substring(fileExtention->LastIndexOf(":")+1));
					break;
				}
			}
			
		}
	};*/

	extensionFileParser() {
		filestream = gcnew StreamReader("DateiSignaturen.txt");
		maxDepth = 0;
		while (!filestream->EndOfStream) {
			String^ fileExtention = filestream->ReadLine();
			
			int i = 0;
			unsigned __int8 byte;
			if (rootNode == nullptr) {
				rootNode = gcnew byteNode;
			}
			byteNode^ node;
			byteNode^ currentNode;
			byteNode^ prevNode;
			String^ byteAlsAscii;
			bool gefunden = false;
			//IEnumerator^ enu = rootNode->getChildes()->GetEnumerator();
			prevNode = rootNode;
			__int8 headerExtentionOderTailer = 0;
			while (i < fileExtention->Length) {
				if (i > 0) {
					if (fileExtention[i - 1].Equals(':')) {
						node->setHeader(fileExtention->Substring(0, fileExtention->IndexOf(":")));
						if (i > maxDepth) {
							maxDepth = (i / 3);
						}
						node->setExtention(fileExtention->Substring(fileExtention->LastIndexOf(":")+1, (fileExtention->Length-1- fileExtention->LastIndexOf(":"))));
						headerExtentionOderTailer++;
					}
				}
				if (headerExtentionOderTailer == 0) {
					try {
						byteAlsAscii = fileExtention->Substring(i, 2);
					}
					catch (Exception^ e) {

					}
					byte = AsciiToHex(byteAlsAscii);
					if (prevNode->getChildes()[byte] != nullptr) {						
						prevNode = prevNode->getChildes()[byte];
					}else {
						node = gcnew byteNode(byteAlsAscii, byte, nullptr);
						prevNode->getChildes()[node->getByte()]=node;
						prevNode = node;						
					}
					i += 3;
					gefunden = false;
				}
				else if (headerExtentionOderTailer == 1) {
					node->setTailer(fileExtention->Substring(fileExtention->LastIndexOf(":") + 1));
					break;
				}
			}

		}
	};
	unsigned __int8 AsciiToHex(String^ ascii) {
		unsigned __int8 returnWert = 0;
		for (int i = 0; i < 2; i++) {
			unsigned __int8 tmp = 0;
			if (ascii[i] == '0') {
				i == 0 ? (tmp = 0x00) : tmp = 0x00;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == '1') {
				i == 0 ? (tmp = 0x10) : tmp = 0x01;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == '2') {
				i == 0 ? (tmp = 0x20) : tmp = 0x02;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == '3') {
				i == 0 ? (tmp = 0x30) : tmp = 0x03;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == '4') {
				i == 0 ? (tmp = 0x40) : tmp = 0x04;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == '5') {
				i == 0 ? (tmp = 0x50) : tmp = 0x05;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == '6') {
				i == 0 ? (tmp = 0x60) : tmp = 0x06;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == '7') {
				i == 0 ? (tmp = 0x70) : tmp = 0x07;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == '8') {
				i == 0 ? (tmp = 0x80) : tmp = 0x08;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == '9') {
				i == 0 ? (tmp = 0x90) : tmp = 0x09;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == 'a'|| ascii[i] == 'A') {
				i == 0 ? (tmp = 0xa0) : tmp = 0x0a;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == 'b' || ascii[i] == 'B') {
				i == 0 ? (tmp = 0xb0) : tmp = 0x0b;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == 'c' || ascii[i] == 'C') {
				i == 0 ? (tmp = 0xc0) : tmp = 0x0c;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == 'd' || ascii[i] == 'D') {
				i == 0 ? (tmp = 0xd0) : tmp = 0x0d;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == 'e' || ascii[i] == 'E') {
				i == 0 ? (tmp = 0xe0) : tmp = 0x0e;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == 'f' || ascii[i] == 'F') {
				i == 0 ? (tmp = 0xf0) : tmp = 0x0f;
				returnWert = returnWert | tmp;
			}
			else if (ascii[i] == 'x' || ascii[i] == 'F') {
				i == 0 ? (tmp = 0xf0) : tmp = 0x0f;
				returnWert = returnWert | tmp;
			}
		}
		return returnWert;
	}
	byteNode^ getRootNode() {
		return rootNode;
	}
	__int32 getMaxDepth() {
		return maxDepth;
	}
private:
	byteNode^ rootNode;
	StreamReader^ filestream;
	__int32 maxDepth;
};

