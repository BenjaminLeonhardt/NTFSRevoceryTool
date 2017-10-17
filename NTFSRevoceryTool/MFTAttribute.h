#pragma once
#include "attributeHeaderResident.h"
#include "attributeHeaderNonResident.h"
#include "Calc.h"
using namespace System;
using namespace System::Collections;
using namespace System::Text;
using namespace System::IO;
ref class MFTAttribute
{
public:
	ArrayList^ attribute80Data;//Dataruns
	ArrayList^ attributeB0Bitmap;
	ref struct attribute10StandardInformation {	//Standart Information zeiten etc
		__int64 FileCreationTimestamp;
		__int64 FileModificationTimestamp;
		__int64 MFTRecordModificationTimestamp;
		__int64 LastAccessTimestamp;
		__int32 Fileattributes;
		__int32 HighesVersionNumAllowed;
		__int32 VersionNumber;
		__int32 ClassID;
		__int32 OwnerID;
		__int32 SecurityID;
		__int64 DiskQuotaSize;
		__int64 UpdateSequenceNumber;
	} ^attribute10StandardInformationP;

	ref struct attribute30Filename {	//Dateiname
		__int64 ParentDirectoryFileRecordNumber;
		__int16 ParentDirectorySequenceNumber;
		__int64 FileCreationTimestamp;
		__int64 FileModificationTimestamp;
		__int64 MFTRecordModificationTimestamp;
		__int64 LastAccessTimestamp;
		__int64 PhysicalAllocatedSize;
		__int32 LogicalAllocatedSize;
		__int32 Fileattributes;
		__int32 Extendedattributes;
		unsigned __int8 LengthOfFilename;
		__int8 FilenameNamespace;
		array<__wchar_t>^ FilenameInUnicode;
	}^ attribute30FilenameP;

	ref struct attribute50SecurityDescriptor {	
		__int8 Revision;
		__int8 Padding;
		__int16 ControlFlags;
		__int32 OffsetToUserSID;
		__int32 OffsetToGroupSID;
		__int32 OffsetToSACL;
		__int32 OffsetToDACL;
	}^ attribute50SecurityDescriptorP;

	ref struct attribute90 {
	};
	ref struct attributeA0Index {
	};

	ref struct attribute300 {
	}; 

	ref struct dataRun {
		__int8 size;
		__int32 clusterCount;
		__int32 firstCluster;
	};

	ref struct attributeHeaderPart1 {
		__int32 attributeIdentifierCode;
		__int32 TotalLengthWithHeader;
		__int8 residentFlags;
		__int8 LengthOfattributeName;
		__int16 offsetattributeName;
		__int16 Flags;
		__int16 attributeID;
		attributeHeaderResident^ attributeHeaderPart2Resident;
		attributeHeaderNonResident^ attributeHeaderPart2NonResident;
	} attributeHeaderObj;


	attribute90^ attribute90P;
	attributeA0Index^ attributeA0IndexP;
	attribute300^ attribute300P;


	MFTAttribute() {};
	MFTAttribute(array<unsigned char>^ tmp, short offset) {
		attributeHeaderObj.attributeIdentifierCode = Calc::get4Byte(tmp, offset);
		attributeHeaderObj.TotalLengthWithHeader = Calc::get4Byte(tmp, offset + 4);
		attributeHeaderObj.residentFlags = tmp[offset + 8];
		attributeHeaderObj.LengthOfattributeName = tmp[offset + 9];
		attributeHeaderObj.offsetattributeName = Calc::get2Byte(tmp, offset + 10);
		attributeHeaderObj.Flags = Calc::get2Byte(tmp, offset + 12);
		attributeHeaderObj.attributeID = Calc::get4Byte(tmp, offset + 14);
		bool attributEingetragen = false;
		unsigned short offsetName;
		if (attributeHeaderObj.residentFlags==0) {
			offsetName = offset + 24;
			if (offset + attributeHeaderObj.TotalLengthWithHeader <= offsetName) {
				return;
			}
			attributeHeaderObj.attributeHeaderPart2Resident = gcnew attributeHeaderResident(tmp, offset);	
		}
		else if (attributeHeaderObj.residentFlags==1) {
			offsetName = offset + 64;
			if (offset + attributeHeaderObj.TotalLengthWithHeader <= offsetName || offset + attributeHeaderObj.TotalLengthWithHeader > tmp->Length) {
				return;
			}
			attributeHeaderObj.attributeHeaderPart2NonResident = gcnew attributeHeaderNonResident(tmp, offset);			
		}
		else if (attributeHeaderObj.residentFlags > 1) {
			return;
		}
		
		
		if (attributeHeaderObj.attributeIdentifierCode == 0x10 && !attributEingetragen) {
			attribute10StandardInformationP = gcnew attribute10StandardInformation;
			attribute10StandardInformationP->FileCreationTimestamp = Calc::get8Byte(tmp, offsetName);
			attribute10StandardInformationP->FileModificationTimestamp = Calc::get8Byte(tmp, offsetName + 8);
			attribute10StandardInformationP->MFTRecordModificationTimestamp = Calc::get8Byte(tmp, offsetName + 16);
			attribute10StandardInformationP->LastAccessTimestamp = Calc::get8Byte(tmp, offsetName + 24);
			attribute10StandardInformationP->Fileattributes = Calc::get4Byte(tmp, offsetName + 32);
			attribute10StandardInformationP->HighesVersionNumAllowed = Calc::get4Byte(tmp, offsetName + 36);
			attribute10StandardInformationP->VersionNumber = Calc::get4Byte(tmp, offsetName + 40);
			attribute10StandardInformationP->ClassID = Calc::get4Byte(tmp, offsetName + 44);
			attribute10StandardInformationP->OwnerID = Calc::get4Byte(tmp, offsetName + 48);
			attribute10StandardInformationP->SecurityID = Calc::get4Byte(tmp, offsetName + 52);
			attribute10StandardInformationP->DiskQuotaSize = Calc::get8Byte(tmp, offsetName + 56);
			attribute10StandardInformationP->UpdateSequenceNumber = Calc::get8Byte(tmp, offsetName + 64);
			attributEingetragen = true;
		}

		else if (attributeHeaderObj.attributeIdentifierCode == 0x30 && !attributEingetragen) {
			attribute30FilenameP = gcnew attribute30Filename;
			attribute30FilenameP->ParentDirectoryFileRecordNumber = Calc::get8Byte(tmp, offsetName);
			attribute30FilenameP->ParentDirectorySequenceNumber = Calc::get2Byte(tmp, offsetName+6);
			attribute30FilenameP->FileCreationTimestamp = Calc::get8Byte(tmp, offsetName+8);
			attribute30FilenameP->FileModificationTimestamp = Calc::get8Byte(tmp, offsetName+16);
			attribute30FilenameP->MFTRecordModificationTimestamp = Calc::get8Byte(tmp, offsetName+24);
			attribute30FilenameP->LastAccessTimestamp = Calc::get8Byte(tmp, offsetName+32);
			attribute30FilenameP->PhysicalAllocatedSize = Calc::get8Byte(tmp, offsetName+40);
			attribute30FilenameP->LogicalAllocatedSize = Calc::get8Byte(tmp, offsetName+48);
			attribute30FilenameP->Fileattributes = Calc::get4Byte(tmp, offsetName+56);
			attribute30FilenameP->Extendedattributes = Calc::get4Byte(tmp, offsetName+60);
			attribute30FilenameP->LengthOfFilename = tmp[offsetName + 64];
			attribute30FilenameP->FilenameNamespace = tmp[offsetName + 65];
			unsigned __int8 FileNameLaenge = attribute30FilenameP->LengthOfFilename;
			if ((offsetName + 66 + ((unsigned)attribute30FilenameP->LengthOfFilename*2)) >= tmp->Length) {
				FileNameLaenge = (tmp->Length - (66 + offsetName)-2)/2;
			}

			attribute30FilenameP->FilenameInUnicode = gcnew array<__wchar_t>(FileNameLaenge);
			int i = 0;

			for (i = 0; i < FileNameLaenge; i++) {
					attribute30FilenameP->FilenameInUnicode->SetValue((unsigned short)Calc::get2Byte(tmp, (i * 2) + offsetName + 66), i);
			}
			
			attributEingetragen = true;
		}

		else if (attributeHeaderObj.attributeIdentifierCode == 0x50 && !attributEingetragen) {
			attribute50SecurityDescriptorP = gcnew attribute50SecurityDescriptor;
			attribute50SecurityDescriptorP->Revision = tmp[offsetName];
			attribute50SecurityDescriptorP->Padding = tmp[offsetName+1];
			attribute50SecurityDescriptorP->ControlFlags = Calc::get2Byte(tmp, offsetName + 2);
			attribute50SecurityDescriptorP->OffsetToUserSID = Calc::get4Byte(tmp, offsetName + 4);
			attribute50SecurityDescriptorP->OffsetToGroupSID = Calc::get4Byte(tmp, offsetName + 8);
			attribute50SecurityDescriptorP->OffsetToSACL = Calc::get4Byte(tmp, offsetName + 16);
			attribute50SecurityDescriptorP->OffsetToDACL = Calc::get4Byte(tmp, offsetName + 24);
			attributEingetragen = true;
		}

		else if (attributeHeaderObj.attributeIdentifierCode == 0x80 && attributeHeaderObj.residentFlags == 1 && !attributEingetragen) {
			
			__int16 nextRun = 0;
			__int8 bytesClusterCount = 0;
			__int8 bytesFirstCluster = 0;
			__int16 counter = 0;
			attribute80Data = gcnew ArrayList;
			while (tmp[offsetName + nextRun] != 0x00 && (offsetName + nextRun < tmp->Length-1)) {
				dataRun^ dr = gcnew dataRun;
				dr->size=tmp[offsetName + nextRun];
				bytesClusterCount = (dr->size & 0x0f); 
				bytesFirstCluster = (dr->size >> 4);
				if (offsetName + nextRun + bytesClusterCount + 4 > tmp->Length - 1) {
					break;
				}
				if (bytesClusterCount == 1) {
					dr->clusterCount= tmp[offsetName + nextRun +1];
				}else if(bytesClusterCount == 2) {
					dr->clusterCount = Calc::get2Byte(tmp, offsetName + nextRun + 1) & 0xffff;
				}
				else if (bytesClusterCount == 3) {
					dr->clusterCount = (Calc::get4Byte(tmp, offsetName + nextRun + 1) & 0xffffff00) >> 8;
				}
				else if (bytesClusterCount == 4) {
					dr->clusterCount = Calc::get4Byte(tmp, offsetName + nextRun + 1) ;
				}

				if (bytesFirstCluster == 1) {
					dr->firstCluster = tmp[offsetName + nextRun + bytesClusterCount+1];					
				}
				else if (bytesFirstCluster == 2) {
					dr->firstCluster = Calc::get2Byte(tmp, offsetName + nextRun + bytesClusterCount+1) & 0xffff;
				}
				else if (bytesFirstCluster == 3) {
					dr->firstCluster = (Calc::get4Byte(tmp, offsetName + nextRun + bytesClusterCount+1) & 0xffffff00) >> 8;
				}
				else if (bytesFirstCluster == 4) {
					dr->firstCluster = Calc::get4Byte(tmp, offsetName + nextRun + bytesClusterCount+1);
				}
				
				if (counter != 0) {
					dataRun^ last;
					IEnumerator^ enu = attribute80Data->GetEnumerator();
					while (enu->MoveNext()) {
						last = safe_cast<dataRun^>(enu->Current);
					}
					__int32 maske = 0x80 << (bytesFirstCluster-1)*8;
					__int32 negMaske = 0x80000000;
					negMaske = negMaske >> ((32 - (bytesFirstCluster) * 8)-1);
					if (!((dr->firstCluster & maske)&& maske)) {
						dr->firstCluster = last->firstCluster + dr->firstCluster;
					}
					else if (((dr->firstCluster & maske) && maske)) {
						dr->firstCluster = last->firstCluster + (dr->firstCluster | negMaske);
					}
					delete last;
					delete enu;
				}
				
				attribute80Data->Add(dr);
				nextRun = nextRun + bytesClusterCount + bytesFirstCluster + 1;
				
				counter++;
				attributEingetragen = true;
				delete dr;
			}
		}
		else if (attributeHeaderObj.attributeIdentifierCode == 0x90 && !attributEingetragen) {
			attributEingetragen = true;
		}
		else if (attributeHeaderObj.attributeIdentifierCode == 0xA0 && !attributEingetragen) {
			attributEingetragen = true;
		}
		else if (attributeHeaderObj.attributeIdentifierCode == 0xB0 && !attributEingetragen) {
			__int16 nextRun = 0;
			__int8 bytesClusterCount = 0;
			__int8 bytesFirstCluster = 0;
			__int16 counter = 0;
			attributeB0Bitmap = gcnew ArrayList;
			while (tmp[offsetName + nextRun] != 0x00 && (offsetName + nextRun < tmp->Length)) {
				dataRun^ dr = gcnew dataRun;
				dr->size = tmp[offsetName + nextRun];
				bytesClusterCount = (dr->size & 0x0f);
				bytesFirstCluster = (dr->size >> 4);
				if (bytesClusterCount == 1) {
					dr->clusterCount = tmp[offsetName + nextRun + 1];
				}
				else if (bytesClusterCount == 2) {
					dr->clusterCount = Calc::get2Byte(tmp, offsetName + nextRun + 1) & 0xffff;
				}
				else if (bytesClusterCount == 3) {
					dr->clusterCount = (Calc::get4Byte(tmp, offsetName + nextRun + 1) & 0xffffff00) >> 8;
				}
				else if (bytesClusterCount == 3) {
					dr->clusterCount = Calc::get4Byte(tmp, offsetName + nextRun + 1);
				}

				if (bytesFirstCluster == 1) {
					dr->firstCluster = tmp[offsetName + nextRun + bytesClusterCount + 1];
				}
				else if (bytesFirstCluster == 2) {
					dr->firstCluster = Calc::get2Byte(tmp, offsetName + nextRun + bytesClusterCount + 1) & 0xffff;
				}
				else if (bytesFirstCluster == 3) {
					dr->firstCluster = (Calc::get4Byte(tmp, offsetName + nextRun + bytesClusterCount + 1) & 0xffffff00) >> 8;
				}
				else if (bytesFirstCluster == 3) {
					dr->firstCluster = Calc::get4Byte(tmp, offsetName + nextRun + bytesClusterCount + 1);
				}

				if (counter != 0) {
					dataRun^ last;
					IEnumerator^ enu = attributeB0Bitmap->GetEnumerator();
					while (enu->MoveNext()) {
						last = safe_cast<dataRun^>(enu->Current);
					}
					__int32 maske = 0x80 << (bytesFirstCluster - 1) * 8;
					__int32 negMaske = 0x80000000;
					negMaske = negMaske >> ((32 - (bytesFirstCluster) * 8) - 1);
					if (!((dr->firstCluster & maske) && maske)) {
						dr->firstCluster = last->firstCluster + dr->firstCluster;
					}
					else if (((dr->firstCluster & maske) && maske)) {
						dr->firstCluster = last->firstCluster + (dr->firstCluster | negMaske);
					}
					delete last;
					delete enu;
				}

				attributeB0Bitmap->Add(dr);
				nextRun = nextRun + bytesClusterCount + bytesFirstCluster + 1;
				counter++;
				delete dr;
			}
			attributEingetragen = true;
		}
		else if (attributeHeaderObj.attributeIdentifierCode == 0x300 && !attributEingetragen) {
			attributEingetragen = true;
		}
		attribute50SecurityDescriptor^ attribute50SecurityDescriptorP;
		attribute90^ attribute90P;
		attributeA0Index^ attributeA0IndexP;
		attribute300^ attribute300P;
		delete tmp;
	};
};

