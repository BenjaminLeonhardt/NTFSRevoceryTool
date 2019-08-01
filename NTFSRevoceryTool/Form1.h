#pragma once
#include "stdafx.h"
#include "NTFSParser.h"
#include "MFTEintrag.h"
#include "mitScanGefundeneDatei.h"
#include "extensionFileParser.h"


namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Globalization;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  lblTitel;
	private: System::Windows::Forms::Label^  lblDateiname;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: Thread^ t1;



	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  NameSpalte;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Offset;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Wert;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  HexWert;




	protected:

	protected:

	private:
		Stream^ filestream;
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::DataGridView^  dataGridView2;



	private: System::Windows::Forms::Label^  label2;





	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label3;




			 ArrayList^ mftEintraege;
			 ArrayList^ weitereMFTEintraege;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Nr;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  MFTIndex;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dOderf;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  gelöscht;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  DateiOderOrdnername;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Dateigröße;
	private: System::Windows::Forms::Button^  btnAlleDateienRetten;
	private: System::Windows::Forms::Button^  ausgewählteDateiRetten;

	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Dateiart;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::Button^  laufwerkOeffnen;




			 ArrayList^ listeAllerDurchScanGefundenenDateien;
	public:
		ToolStripProgressBar^ getToolStripProgressBar1() {
			return toolStripProgressBar1;
		}
		Stream^ getFilestream() {
			return filestream;
		}
		DataGridView^ getDataGridView2() {
			return dataGridView2;
		}
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lblTitel = (gcnew System::Windows::Forms::Label());
			this->lblDateiname = (gcnew System::Windows::Forms::Label());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->NameSpalte = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Offset = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Wert = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->HexWert = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->Nr = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->MFTIndex = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dOderf = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->gelöscht = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DateiOderOrdnername = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Dateigröße = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Dateiart = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->btnAlleDateienRetten = (gcnew System::Windows::Forms::Button());
			this->ausgewählteDateiRetten = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->laufwerkOeffnen = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// lblTitel
			// 
			this->lblTitel->AutoSize = true;
			this->lblTitel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24));
			this->lblTitel->Location = System::Drawing::Point(5, 9);
			this->lblTitel->Name = L"lblTitel";
			this->lblTitel->Size = System::Drawing::Size(299, 37);
			this->lblTitel->TabIndex = 0;
			this->lblTitel->Text = L"NTFS File Extractor";
			// 
			// lblDateiname
			// 
			this->lblDateiname->AutoSize = true;
			this->lblDateiname->Location = System::Drawing::Point(124, 84);
			this->lblDateiname->Name = L"lblDateiname";
			this->lblDateiname->Size = System::Drawing::Size(104, 13);
			this->lblDateiname->TabIndex = 1;
			this->lblDateiname->Text = L"Keine Datei geöffnet";
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->NameSpalte,
					this->Offset, this->Wert, this->HexWert
			});
			this->dataGridView1->Location = System::Drawing::Point(12, 135);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(543, 530);
			this->dataGridView1->TabIndex = 2;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataGridView1_CellContentClick);
			// 
			// NameSpalte
			// 
			this->NameSpalte->HeaderText = L"Name";
			this->NameSpalte->Name = L"NameSpalte";
			// 
			// Offset
			// 
			this->Offset->HeaderText = L"Offset";
			this->Offset->Name = L"Offset";
			// 
			// Wert
			// 
			this->Wert->HeaderText = L"Wert";
			this->Wert->Name = L"Wert";
			// 
			// HexWert
			// 
			this->HexWert->HeaderText = L"HexWert";
			this->HexWert->Name = L"HexWert";
			this->HexWert->Width = 200;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 79);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(106, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Image Datei öffnen";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(8, 112);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(146, 20);
			this->label1->TabIndex = 4;
			this->label1->Text = L"VBR Informationen";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// dataGridView2
			// 
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {
				this->Nr, this->MFTIndex,
					this->dOderf, this->gelöscht, this->DateiOderOrdnername, this->Dateigröße, this->Dateiart
			});
			this->dataGridView2->Location = System::Drawing::Point(629, 135);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->Size = System::Drawing::Size(587, 530);
			this->dataGridView2->TabIndex = 5;
			// 
			// Nr
			// 
			this->Nr->HeaderText = L"Nr.";
			this->Nr->Name = L"Nr";
			this->Nr->Width = 50;
			// 
			// MFTIndex
			// 
			this->MFTIndex->HeaderText = L"MFTIndex";
			this->MFTIndex->Name = L"MFTIndex";
			this->MFTIndex->Width = 80;
			// 
			// dOderf
			// 
			this->dOderf->HeaderText = L"Datei oder Ordner";
			this->dOderf->Name = L"dOderf";
			this->dOderf->Width = 50;
			// 
			// gelöscht
			// 
			this->gelöscht->HeaderText = L"gelöscht";
			this->gelöscht->Name = L"gelöscht";
			this->gelöscht->Width = 50;
			// 
			// DateiOderOrdnername
			// 
			this->DateiOderOrdnername->HeaderText = L"Datei / Ordnername";
			this->DateiOderOrdnername->Name = L"DateiOderOrdnername";
			this->DateiOderOrdnername->Width = 200;
			// 
			// Dateigröße
			// 
			this->Dateigröße->HeaderText = L"Dateigröße";
			this->Dateigröße->Name = L"Dateigröße";
			this->Dateigröße->Width = 113;
			// 
			// Dateiart
			// 
			this->Dateiart->HeaderText = L"Dateiart";
			this->Dateiart->Name = L"Dateiart";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(629, 112);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(190, 20);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Gefundene MFT Einträge";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(629, 79);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(95, 23);
			this->button2->TabIndex = 7;
			this->button2->Text = L"Suche starten";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(626, 54);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(503, 13);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Nach weiteren MFT Einträgen sowie nach Dateien anhand von Header und Tailer suche"
				L"n (sehr langsam)";
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripProgressBar1,
					this->toolStripStatusLabel1
			});
			this->statusStrip1->Location = System::Drawing::Point(0, 683);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(1228, 22);
			this->statusStrip1->TabIndex = 10;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripProgressBar1
			// 
			this->toolStripProgressBar1->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
			this->toolStripProgressBar1->Size = System::Drawing::Size(100, 16);
			this->toolStripProgressBar1->Visible = false;
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(240, 17);
			this->toolStripStatusLabel1->Text = L"Fortschritt bei 0.000%, 0 b von 0 b bearbeitet";
			this->toolStripStatusLabel1->Visible = false;
			// 
			// btnAlleDateienRetten
			// 
			this->btnAlleDateienRetten->Enabled = false;
			this->btnAlleDateienRetten->Location = System::Drawing::Point(923, 79);
			this->btnAlleDateienRetten->Name = L"btnAlleDateienRetten";
			this->btnAlleDateienRetten->Size = System::Drawing::Size(137, 23);
			this->btnAlleDateienRetten->TabIndex = 11;
			this->btnAlleDateienRetten->Text = L"Alle Dateien retten";
			this->btnAlleDateienRetten->UseVisualStyleBackColor = true;
			// 
			// ausgewählteDateiRetten
			// 
			this->ausgewählteDateiRetten->Enabled = false;
			this->ausgewählteDateiRetten->Location = System::Drawing::Point(1079, 79);
			this->ausgewählteDateiRetten->Name = L"ausgewählteDateiRetten";
			this->ausgewählteDateiRetten->Size = System::Drawing::Size(137, 23);
			this->ausgewählteDateiRetten->TabIndex = 12;
			this->ausgewählteDateiRetten->Text = L"Ausgewählte Datei retten";
			this->ausgewählteDateiRetten->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(434, 79);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(121, 23);
			this->button4->TabIndex = 13;
			this->button4->Text = L"Dateiarten auswählen";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// laufwerkOeffnen
			// 
			this->laufwerkOeffnen->Location = System::Drawing::Point(12, 50);
			this->laufwerkOeffnen->Name = L"laufwerkOeffnen";
			this->laufwerkOeffnen->Size = System::Drawing::Size(106, 23);
			this->laufwerkOeffnen->TabIndex = 14;
			this->laufwerkOeffnen->Text = L"Laufwerk öffnen";
			this->laufwerkOeffnen->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1228, 705);
			this->Controls->Add(this->laufwerkOeffnen);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->ausgewählteDateiRetten);
			this->Controls->Add(this->btnAlleDateienRetten);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->lblDateiname);
			this->Controls->Add(this->lblTitel);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private:			String^ toolStripStatusString1 = L"Fortschritt bei ";
							String^ toolStripStatusString2 = L"%, ";
							String^ toolStripStatusString3 = L" b von ";
							String^ toolStripStatusString4 = L" b bearbeitet";
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void dataGridView1_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		dataGridView1->Rows->Clear();
		dataGridView2->Rows->Clear();

		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog;
		openFileDialog->ShowDialog();
		filestream = openFileDialog->OpenFile();
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(520);
		filestream->Seek(0, System::IO::SeekOrigin::Begin);
		filestream->Read(tmp, 0, 520);


		if (tmp[3] == 'N' && tmp[4] == 'T' && tmp[5] == 'F' && tmp[6] == 'S') {
			NTFSParser ntfsP(openFileDialog->OpenFile(), 0);
			leseNTFSImage(ntfsP, filestream, openFileDialog);
		}
		else if (tmp[0] == '<' && tmp[1] == '<' && tmp[2] == '<' && tmp[3] == 0x20&&tmp[4] == 'O' && tmp[5] == 'r' && tmp[6] == 'a' && tmp[7] == 'c'&& tmp[8] == 'l' && tmp[9] == 'e' && tmp[10] == 0x20 && tmp[11] == 'V'&& tmp[12] == 'M') {
			NTFSParser ntfsP(openFileDialog->OpenFile(), 3145728);
			leseNTFSImage(ntfsP, filestream, openFileDialog);
		}
		else {
			lblDateiname->Text = openFileDialog->FileName + " Datei enthält keine NTFS Partition.";
		}
	}

	void leseNTFSImage(NTFSParser% ntfsP, Stream^ filestream, OpenFileDialog^ openFileDialog) {
				 lblDateiname->Text = openFileDialog->FileName;
				 __int32 offsetFuerMFT = 0;
				 for (int i = 0; i < 22; i++) {
					 dataGridView1->Rows->Add(ntfsP.getAusgeleseneEintraege()[i]->Name, ntfsP.getAusgeleseneEintraege()[i]->Offset, ntfsP.getAusgeleseneEintraege()[i]->Wert, ntfsP.getAusgeleseneEintraege()[i]->HexWert);
					 if (ntfsP.getAusgeleseneEintraege()[i]->Name == "MFT Cluster Number") {
						 offsetFuerMFT = Int64::Parse(ntfsP.getAusgeleseneEintraege()[i]->Wert) + (ntfsP.getOffset() / 4096);
					 }
				 }
				 mftEintraege = gcnew ArrayList;
				 __int64 bytesFuerEinenEintrag = 512 * 2;
				 bool gefunden = true;
				 __int32 step = 0;
				 while (gefunden) {
					 MFTEintrag^ mfte = gcnew MFTEintrag((offsetFuerMFT * 8 * 512) + (bytesFuerEinenEintrag*step), openFileDialog->OpenFile());
					 if (mfte->mftRH.magicNrFILE[0] != 'F' || mfte->mftRH.magicNrFILE[1] != 'I' || mfte->mftRH.magicNrFILE[2] != 'L' || mfte->mftRH.magicNrFILE[3] != 'E') {
						 gefunden = false;
						 break;
					 }
					 mftEintraege->Add(mfte);
					 step++;
				 }
				 IEnumerator^ enu = mftEintraege->GetEnumerator();
				 while (enu->MoveNext()) {
					 MFTEintrag^ eintrag = safe_cast<MFTEintrag^>(enu->Current);
					 String^ dateiOderOrdner = (eintrag->mftRH.FlagsMFTRecordHeader & 0x2) >> 1 ? L"Ordner" : L"Datei";
					 String^ geloescht = eintrag->mftRH.FlagsMFTRecordHeader && 0x1 ? L"" : L"Ja";
					 MFTAttribute^ attribut;
					 String^ dateinameString = L"";
					 IEnumerator^ enuAttrib;
					 if (eintrag->attributeArray != nullptr) {
						 enuAttrib = eintrag->attributeArray->GetEnumerator();
						 while (enuAttrib->MoveNext()) {
							 attribut = safe_cast<MFTAttribute^>(enuAttrib->Current);
							 if (attribut->attribute30FilenameP != nullptr) {
								 for (int i = 0; i < attribut->attribute30FilenameP->FilenameInUnicode->Length; i++) {
									 dateinameString += attribut->attribute30FilenameP->FilenameInUnicode[i];
								 }
							 }
						 }
					 }
					 if (dateinameString != nullptr) {
						 dataGridView2->Rows->Add(EintragCounter++, eintrag->mftRH.SequenceNumber, dateiOderOrdner, geloescht, dateinameString, L"");
					 }
				 }
			 }

	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}

			 delegate void weitereEintraege();
			 BackgroundWorker^ backgroundWorker1;

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

		//this->backgroundWorker1->RunWorkerAsync();
		this->t1 = gcnew Thread(gcnew ThreadStart(this, &Form1::sucheNachWeiterenEintraegen));
		//this->t1 = gcnew Thread(gcnew ThreadStart(this, &Form1::threadProcedure));
		this->t1->Start();

	}

	delegate void delegeateNewToolStripProgressBar(double);

	void setNewToolStripProgressBar(double neuerWert) {
			this->toolStripProgressBar1->Value = neuerWert;		
	}

	delegate void delegeateNewToolStripProgressBarVisible(bool);

	void setNewToolStripProgressBarVisible(bool neuerWert) {
			this->toolStripProgressBar1->Visible = neuerWert;		
	}

	delegate void delegeateNewToolStripStatusLabel(String^);

	void setNewToolStripStatusLabel1(String^ neuerWert) {
		this->toolStripStatusLabel1->Text = neuerWert;
	}

	delegate void delegeateToolStripStatusLabel1Visible(bool);

	void setNewToolStripStatusLabel1Visible(bool neuerWert) {
		this->toolStripStatusLabel1->Visible = neuerWert;
	}

	delegate void delegeateAusgewählteDateiRettenEnable(bool);

	void setAusgewählteDateiRettenEnable(bool neuerWert) {
		this->ausgewählteDateiRetten->Enabled = neuerWert;
	}

	delegate void delegeateBtnAlleDateienRettenEnable(bool);

	void setBtnAlleDateienRettenEnable(bool neuerWert) {
		this->btnAlleDateienRetten->Enabled = neuerWert;
	}

	void sucheNachWeiterenEintraegen() {
		delegeateNewToolStripProgressBarVisible^ delegeateNewToolStripProgressBarVisibleObj = gcnew delegeateNewToolStripProgressBarVisible(this, &Form1::setNewToolStripProgressBarVisible);
		this->Invoke(delegeateNewToolStripProgressBarVisibleObj, gcnew array<Object^> { true});
		delegeateToolStripStatusLabel1Visible^ delegeateNewToolStripStatusLabel1VisibleObj = gcnew delegeateToolStripStatusLabel1Visible(this, &Form1::setNewToolStripStatusLabel1Visible);
		this->Invoke(delegeateNewToolStripStatusLabel1VisibleObj, gcnew array<Object^> { true});
		delegeateNewToolStripProgressBar^ delegeateNewToolStripProgressBarObj = gcnew delegeateNewToolStripProgressBar(this, &Form1::setNewToolStripProgressBar);
		delegeateNewToolStripStatusLabel^ delegeateNewToolStripStatusLabelObj = gcnew delegeateNewToolStripStatusLabel(this, &Form1::setNewToolStripStatusLabel1);
		extensionFileParser fileParser;
		unsigned __int64 aktuelleStelle = 0;
		__int32 junk = 1048576;
		array<unsigned char>^ tmp = gcnew  array<unsigned char>(junk);
		weitereMFTEintraege = gcnew ArrayList;
		listeAllerDurchScanGefundenenDateien = gcnew ArrayList;
		unsigned __int64 length = filestream->Length;
		NumberFormatInfo^ provider = gcnew NumberFormatInfo();
		provider->PercentDecimalDigits = 4;
		while (filestream->Length >= aktuelleStelle) {
			Double^ d = gcnew Double((((double)1 / (double)filestream->Length) * 100));
			this->Invoke(delegeateNewToolStripStatusLabelObj, gcnew array<Object^> { toolStripStatusString1 + Convert::ToString((((double)aktuelleStelle / (double)filestream->Length) * 100),provider) + toolStripStatusString2 + aktuelleStelle + toolStripStatusString3 + filestream->Length + toolStripStatusString4});
			if (aktuelleStelle == 0) {
				this->Invoke(delegeateNewToolStripProgressBarObj, gcnew array<Object^> { (((double)1 / (double)filestream->Length) * 100)});
			}
			else {
				this->Invoke(delegeateNewToolStripProgressBarObj, gcnew array<Object^> { (((double)aktuelleStelle / (double)filestream->Length) * 100)});						 
			}

			Console::WriteLine(aktuelleStelle + " byte daten verarbeitet.");
			tmp = gcnew  array<unsigned char>(junk);
			filestream->Seek(aktuelleStelle, System::IO::SeekOrigin::Begin);
			filestream->Read(tmp, 0, junk);
			byteNode^ prevNode;
			byteNode^ letzteKorrektErkannteDateiEndung;
			byteNode^ node;
			for (unsigned __int64 i = 0; i < junk - 4; i++) {
				if (tmp[i] == 'F' && tmp[i + 1] == 'I' && tmp[i + 2] == 'L' && tmp[i + 3] == 'E') {
					MFTEintrag^ eintrag = gcnew MFTEintrag(aktuelleStelle + i, filestream);
					weitereMFTEintraege->Add(eintrag);




					String^ dateiOderOrdner = (eintrag->mftRH.FlagsMFTRecordHeader & 0x2) >> 1 ? L"Ordner" : L"Datei";
					String^ geloescht = eintrag->mftRH.FlagsMFTRecordHeader && 0x1 ? L"" : L"Ja";
					MFTAttribute^ attribut;
					String^ dateinameString = L"";
					IEnumerator^ enuAttrib;
					int laenge=0;
					if (eintrag->attributeArray != nullptr) {
						enuAttrib = eintrag->attributeArray->GetEnumerator();
						while (enuAttrib->MoveNext()) {
							attribut = safe_cast<MFTAttribute^>(enuAttrib->Current);
							if (attribut->attribute30FilenameP != nullptr) {
								if (laenge == 0) {
									laenge = attribut->attribute30FilenameP->FilenameInUnicode->Length;
									for (int i = 0; i < attribut->attribute30FilenameP->FilenameInUnicode->Length; i++) {
										dateinameString += attribut->attribute30FilenameP->FilenameInUnicode[i];
									}
								}
								else {
									if (laenge < attribut->attribute30FilenameP->FilenameInUnicode->Length) {
										dateinameString = L"";
										for (int i = 0; i < attribut->attribute30FilenameP->FilenameInUnicode->Length; i++) {
											dateinameString += attribut->attribute30FilenameP->FilenameInUnicode[i];
										}
									}
								}
							}									
							delete attribut;
						}
						delete enuAttrib;
					}
					if (dateinameString != nullptr) {
						setNewRowEintrag(eintrag, dateiOderOrdner, geloescht, dateinameString);
						//this->dataGridView2->Rows->Add(eintrag->mftRH.SequenceNumber, dateiOderOrdner, geloescht, dateinameString, L"");
					}



					delete eintrag;
				}
				bool weitereBytesErkannt = true;
				unsigned int j = 0;
				prevNode = fileParser.getRootNode();
				letzteKorrektErkannteDateiEndung = nullptr;
				while (weitereBytesErkannt) {
					node = nullptr;
					bool gefunden = false;
					if ((i + j) > 1048576) {
						tmp = gcnew  array<unsigned char>(junk);
						aktuelleStelle += (i + j);
						if (aktuelleStelle + junk < filestream->Length) {
							junk = filestream->Length - aktuelleStelle;
						}
						filestream->Seek(aktuelleStelle, System::IO::SeekOrigin::Begin);
						filestream->Read(tmp, 0, junk);
						
					}
					
					if (prevNode->getChildes()[tmp[i + j]] != nullptr) {
						node = prevNode->getChildes()[tmp[i + j]];
						prevNode = node;
						j++;
						if (node->getExtention() != nullptr) {
							letzteKorrektErkannteDateiEndung = node;
						}
						gefunden = true;
					}
					if (!gefunden) {
						if (j > 0) {
							if (prevNode->getExtention() != nullptr) {
								mitScanGefundeneDatei^ datei = gcnew mitScanGefundeneDatei(aktuelleStelle + i, prevNode->getHeader(), prevNode->getExtention(), filestream, prevNode->getTailer());
								listeAllerDurchScanGefundenenDateien->Add(datei);
								weitereBytesErkannt = false;
							}
							else {
								if (letzteKorrektErkannteDateiEndung != nullptr) {
									if (letzteKorrektErkannteDateiEndung->getExtention() != nullptr) {
										mitScanGefundeneDatei^ datei = gcnew mitScanGefundeneDatei(aktuelleStelle + i, letzteKorrektErkannteDateiEndung->getHeader(), letzteKorrektErkannteDateiEndung->getExtention(), filestream, letzteKorrektErkannteDateiEndung->getTailer());
										listeAllerDurchScanGefundenenDateien->Add(datei);
										letzteKorrektErkannteDateiEndung->setCounter(letzteKorrektErkannteDateiEndung->getCounter() + 1);
										letzteKorrektErkannteDateiEndung = nullptr;
										weitereBytesErkannt = false;
									}
								}
							}
						}
						weitereBytesErkannt = false;
					}
				}
			}
			delete tmp;

			aktuelleStelle += junk;
		}

		IEnumerator^ enu = weitereMFTEintraege->GetEnumerator();
		/*while (enu->MoveNext()) {
			MFTEintrag^ eintrag = safe_cast<MFTEintrag^>(enu->Current);
			String^ dateiOderOrdner = (eintrag->mftRH.FlagsMFTRecordHeader & 0x2) >> 1 ? L"Ordner" : L"Datei";
			String^ geloescht = eintrag->mftRH.FlagsMFTRecordHeader && 0x1 ? L"" : L"Ja";
			MFTAttribute^ attribut;
			String^ dateinameString = L"";
			IEnumerator^ enuAttrib;
			if (eintrag->attributeArray != nullptr) {
				enuAttrib = eintrag->attributeArray->GetEnumerator();
				while (enuAttrib->MoveNext()) {
					attribut = safe_cast<MFTAttribute^>(enuAttrib->Current);
					if (attribut->attribute30FilenameP != nullptr) {
						for (int i = 0; i < attribut->attribute30FilenameP->FilenameInUnicode->Length; i++) {
							dateinameString += attribut->attribute30FilenameP->FilenameInUnicode[i];
						}
					}
					delete attribut;
				}
				delete enuAttrib;
			}
			if (dateinameString != nullptr) {
				setNewRowEintrag(eintrag, dateiOderOrdner, geloescht, dateinameString);
				//this->dataGridView2->Rows->Add(eintrag->mftRH.SequenceNumber, dateiOderOrdner, geloescht, dateinameString, L"");
			}
			delete eintrag;

		}*/
				 
		enu = listeAllerDurchScanGefundenenDateien->GetEnumerator();
		while (enu->MoveNext()) {
			mitScanGefundeneDatei^ datei = safe_cast<mitScanGefundeneDatei^>(enu->Current);
			setNewRowDatei(datei);
			//this->dataGridView2->Rows->Add(L"?", L"Datei", L"", L"" + fileCounter + "." + datei->getErkannteDateiArt(), L"");				 
					 
		}
		delete enu;
		this->Invoke(delegeateNewToolStripStatusLabel1VisibleObj, gcnew array<Object^> { false});
		this->Invoke(delegeateNewToolStripProgressBarVisibleObj, gcnew array<Object^> { false});

		delegeateBtnAlleDateienRettenEnable^ delegeateBtnAlleDateienRettenEnableObj = gcnew delegeateBtnAlleDateienRettenEnable(this, &Form1::setBtnAlleDateienRettenEnable);
		this->Invoke(delegeateBtnAlleDateienRettenEnableObj, gcnew array<Object^> { true});
		delegeateAusgewählteDateiRettenEnable^ delegeateAusgewählteDateiRettenEnableObj = gcnew delegeateAusgewählteDateiRettenEnable(this, &Form1::setAusgewählteDateiRettenEnable);
		this->Invoke(delegeateAusgewählteDateiRettenEnableObj, gcnew array<Object^> { true});

	};

	delegate void delegeateNewRowMFTEintrag(MFTEintrag^ eintrag, String^ dateiOderOrdner, String^ geloescht, String^ dateinameString);

	void setNewRowEintrag(MFTEintrag^ eintrag, String^ dateiOderOrdner, String^ geloescht, String^ dateinameString) {
		if (this->dataGridView2->InvokeRequired) {
			delegeateNewRowMFTEintrag^ delegeateNewRowMFTEintragObj =
				gcnew delegeateNewRowMFTEintrag(this, &Form1::setNewRowEintrag);
			this->Invoke(delegeateNewRowMFTEintragObj, gcnew array<Object^> { eintrag, dateiOderOrdner, geloescht, dateinameString});
		}
		else {
			dataGridView2->Rows->Add(EintragCounter++,eintrag->mftRH.SequenceNumber, dateiOderOrdner, geloescht, dateinameString, L"");
		}
	}

	public: static unsigned __int64 EintragCounter = 0;
	public: static unsigned __int64 fileCounter = 0;
			delegate void delegeateNewRowDatei(mitScanGefundeneDatei^ datei);

	void setNewRowDatei(mitScanGefundeneDatei^ datei) {
		if (this->dataGridView2->InvokeRequired) {
			delegeateNewRowDatei^ delegateSetNewRowDateiObj =
				gcnew delegeateNewRowDatei(this, &Form1::setNewRowDatei);
			this->Invoke(delegateSetNewRowDateiObj, gcnew array<Object^> { datei });
		}
		else {
			this->dataGridView2->Rows->Add(EintragCounter++,L"?", L"Datei", L"", L"" + fileCounter++ + "." + datei->getErkannteDateiArt(), L"");
		}
	}


};
}
