#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "Graph.h"
#include "GPUGraph.h"
#include <stdlib.h>

namespace surface_reconstruction {

	/// <summary>
	/// Сводка для SegmentationForm
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>

	public ref class SegmentationForm : public System::Windows::Forms::Form
	{
	public:
		SegmentsTree* tree;
		SegmentsTree2* tree2;

	private: System::Windows::Forms::GroupBox^  LayerSegmentsTreeInfo;
	private: System::Windows::Forms::GroupBox^  SegmentInfo;
	private: System::Windows::Forms::DataGridView^  LayerSegmentsGrid;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  LayerNum;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  CountSegments;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  MaxCapacity;
	private: System::Windows::Forms::TextBox^  LayerSelect;


	private: System::Windows::Forms::Label^  layerSelectLabel;
	private: System::Windows::Forms::Button^  Select;






	public: 
		ScanData* data;
		MyDel ^ StaticDelInst;
		ScanData* sd;
		int segmentationType;
	private: System::Windows::Forms::DataGridView^  CurrentSegment;




	private: System::Windows::Forms::Button^  DisplaySegments;
	private: System::Windows::Forms::Label^  CountDisplay;
	private: System::Windows::Forms::Label^  CountDisplaylabel;
	private: System::Windows::Forms::GroupBox^  SegmentationGroup;
	private: System::Windows::Forms::Button^  SegmentationIteration;
	private: System::Windows::Forms::Button^  StartSegmentation;
	private: System::Windows::Forms::GroupBox^  SegmentationType0;


	private: System::Windows::Forms::TextBox^  StartStep;
	private: System::Windows::Forms::Label^  StartStepLabel;
	private: System::Windows::Forms::RadioButton^  GPU;
	private: System::Windows::Forms::RadioButton^  CPU;
	private: System::Windows::Forms::Button^  button1;

	public: 

	public: 

	public: 
		LayerSegmentsTree* layerSelect;
	private: System::Windows::Forms::Button^  ReplaceData;
	private: System::Windows::Forms::TextBox^  Increment;
	private: System::Windows::Forms::Label^  IncrementDataLabel1;
	private: System::Windows::Forms::Button^  IncrementData;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Id;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  CountVoxel;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  MinWeightSegment;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  MeanWeightSegment;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  MaxWeightSegment;
	private: System::Windows::Forms::DataGridViewCheckBoxColumn^  CheckSegment;
	private: System::Windows::Forms::GroupBox^  Display;
	private: System::Windows::Forms::RadioButton^  InitialDataDisplay;
	private: System::Windows::Forms::RadioButton^  NewDataDisplay;





	public: 

	public: 
		LayerSegmentsTree2* layerSelect2;
	private: System::Windows::Forms::Label^  MinVoxelLabel;
	private: System::Windows::Forms::NumericUpDown^  MinVoxel;
	public: 

	public: 

	public: 

	public: 
		bool isDisplayInitialData;

		SegmentationForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			segmentationType = 0;
			sd = new ScanData();
			layerSelect = 0;
			layerSelect2 = 0;
			isDisplayInitialData = true;
			tree = 0;
			tree2 = 0;
		}

		void EnabledSegmentation()
		{
			SegmentationGroup->Enabled = true;
			sd->scaleX = data->scaleX;
			sd->scaleY = data->scaleY;
			sd->scaleZ = data->scaleZ;
			sd->sizeX = data->sizeX;
			sd->sizeY = data->sizeY;
			sd->sizeZ = data->sizeZ;
			if (sd->data == 0)
				sd->data = new short [sd->sizeX * sd->sizeY * sd->sizeZ];
			for (size_t i = 0; i < sd->sizeX * sd->sizeY * sd->sizeZ; i++)
				sd->data[i] = data->data[i];

			MinVoxel->Maximum = sd->sizeX * sd->sizeY * sd->sizeZ;
		}
		void DisplayData(ScanData* newData)
		{
			StaticDelInst(newData);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~SegmentationForm()
		{
			if (components)
			{
				delete components;
			}
			if (sd != 0)
				delete sd;
		}

	protected: 

	protected: 

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->LayerSegmentsTreeInfo = (gcnew System::Windows::Forms::GroupBox());
			this->Select = (gcnew System::Windows::Forms::Button());
			this->layerSelectLabel = (gcnew System::Windows::Forms::Label());
			this->LayerSelect = (gcnew System::Windows::Forms::TextBox());
			this->LayerSegmentsGrid = (gcnew System::Windows::Forms::DataGridView());
			this->LayerNum = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->CountSegments = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->MaxCapacity = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->SegmentInfo = (gcnew System::Windows::Forms::GroupBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->CountDisplay = (gcnew System::Windows::Forms::Label());
			this->CountDisplaylabel = (gcnew System::Windows::Forms::Label());
			this->DisplaySegments = (gcnew System::Windows::Forms::Button());
			this->CurrentSegment = (gcnew System::Windows::Forms::DataGridView());
			this->Id = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->CountVoxel = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->MinWeightSegment = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->MeanWeightSegment = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->MaxWeightSegment = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->CheckSegment = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
			this->SegmentationGroup = (gcnew System::Windows::Forms::GroupBox());
			this->Display = (gcnew System::Windows::Forms::GroupBox());
			this->NewDataDisplay = (gcnew System::Windows::Forms::RadioButton());
			this->InitialDataDisplay = (gcnew System::Windows::Forms::RadioButton());
			this->Increment = (gcnew System::Windows::Forms::TextBox());
			this->IncrementDataLabel1 = (gcnew System::Windows::Forms::Label());
			this->IncrementData = (gcnew System::Windows::Forms::Button());
			this->ReplaceData = (gcnew System::Windows::Forms::Button());
			this->StartStep = (gcnew System::Windows::Forms::TextBox());
			this->StartStepLabel = (gcnew System::Windows::Forms::Label());
			this->SegmentationType0 = (gcnew System::Windows::Forms::GroupBox());
			this->GPU = (gcnew System::Windows::Forms::RadioButton());
			this->CPU = (gcnew System::Windows::Forms::RadioButton());
			this->SegmentationIteration = (gcnew System::Windows::Forms::Button());
			this->StartSegmentation = (gcnew System::Windows::Forms::Button());
			this->MinVoxelLabel = (gcnew System::Windows::Forms::Label());
			this->MinVoxel = (gcnew System::Windows::Forms::NumericUpDown());
			this->LayerSegmentsTreeInfo->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->LayerSegmentsGrid))->BeginInit();
			this->SegmentInfo->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->CurrentSegment))->BeginInit();
			this->SegmentationGroup->SuspendLayout();
			this->Display->SuspendLayout();
			this->SegmentationType0->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MinVoxel))->BeginInit();
			this->SuspendLayout();
			// 
			// LayerSegmentsTreeInfo
			// 
			this->LayerSegmentsTreeInfo->Controls->Add(this->Select);
			this->LayerSegmentsTreeInfo->Controls->Add(this->layerSelectLabel);
			this->LayerSegmentsTreeInfo->Controls->Add(this->LayerSelect);
			this->LayerSegmentsTreeInfo->Controls->Add(this->LayerSegmentsGrid);
			this->LayerSegmentsTreeInfo->Enabled = false;
			this->LayerSegmentsTreeInfo->Location = System::Drawing::Point(12, 217);
			this->LayerSegmentsTreeInfo->Name = L"LayerSegmentsTreeInfo";
			this->LayerSegmentsTreeInfo->Size = System::Drawing::Size(900, 246);
			this->LayerSegmentsTreeInfo->TabIndex = 2;
			this->LayerSegmentsTreeInfo->TabStop = false;
			this->LayerSegmentsTreeInfo->Text = L"уровни сегментации";
			// 
			// Select
			// 
			this->Select->Location = System::Drawing::Point(606, 10);
			this->Select->Name = L"Select";
			this->Select->Size = System::Drawing::Size(75, 23);
			this->Select->TabIndex = 3;
			this->Select->Text = L"выбрать";
			this->Select->UseVisualStyleBackColor = true;
			this->Select->Click += gcnew System::EventHandler(this, &SegmentationForm::Select_Click);
			// 
			// layerSelectLabel
			// 
			this->layerSelectLabel->AutoSize = true;
			this->layerSelectLabel->Location = System::Drawing::Point(385, 16);
			this->layerSelectLabel->Name = L"layerSelectLabel";
			this->layerSelectLabel->Size = System::Drawing::Size(109, 13);
			this->layerSelectLabel->TabIndex = 2;
			this->layerSelectLabel->Text = L"выбранный уровень";
			// 
			// LayerSelect
			// 
			this->LayerSelect->Location = System::Drawing::Point(500, 13);
			this->LayerSelect->Name = L"LayerSelect";
			this->LayerSelect->Size = System::Drawing::Size(100, 20);
			this->LayerSelect->TabIndex = 1;
			this->LayerSelect->Text = L"1";
			// 
			// LayerSegmentsGrid
			// 
			this->LayerSegmentsGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->LayerSegmentsGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {this->LayerNum, 
				this->CountSegments, this->MaxCapacity});
			this->LayerSegmentsGrid->Location = System::Drawing::Point(6, 19);
			this->LayerSegmentsGrid->Name = L"LayerSegmentsGrid";
			this->LayerSegmentsGrid->Size = System::Drawing::Size(373, 214);
			this->LayerSegmentsGrid->TabIndex = 0;
			this->LayerSegmentsGrid->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &SegmentationForm::LayerSegmentsGrid_CellClick);
			// 
			// LayerNum
			// 
			this->LayerNum->HeaderText = L"№";
			this->LayerNum->Name = L"LayerNum";
			// 
			// CountSegments
			// 
			this->CountSegments->HeaderText = L"кол-во сегментов";
			this->CountSegments->Name = L"CountSegments";
			// 
			// MaxCapacity
			// 
			this->MaxCapacity->HeaderText = L"максимальный объем сегмента";
			this->MaxCapacity->Name = L"MaxCapacity";
			// 
			// SegmentInfo
			// 
			this->SegmentInfo->Controls->Add(this->button1);
			this->SegmentInfo->Controls->Add(this->CountDisplay);
			this->SegmentInfo->Controls->Add(this->CountDisplaylabel);
			this->SegmentInfo->Controls->Add(this->DisplaySegments);
			this->SegmentInfo->Controls->Add(this->CurrentSegment);
			this->SegmentInfo->Enabled = false;
			this->SegmentInfo->Location = System::Drawing::Point(13, 469);
			this->SegmentInfo->Name = L"SegmentInfo";
			this->SegmentInfo->Size = System::Drawing::Size(899, 285);
			this->SegmentInfo->TabIndex = 3;
			this->SegmentInfo->TabStop = false;
			this->SegmentInfo->Text = L"сегменты выбронного уровня";
			// 
			// button1
			// 
			this->button1->AccessibleDescription = L"DisplaySegments2";
			this->button1->Location = System::Drawing::Point(732, 88);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(161, 47);
			this->button1->TabIndex = 4;
			this->button1->Text = L"отобразить все кроме выбранных";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SegmentationForm::button1_Click);
			// 
			// CountDisplay
			// 
			this->CountDisplay->AutoSize = true;
			this->CountDisplay->Location = System::Drawing::Point(732, 72);
			this->CountDisplay->Name = L"CountDisplay";
			this->CountDisplay->Size = System::Drawing::Size(13, 13);
			this->CountDisplay->TabIndex = 3;
			this->CountDisplay->Text = L"0";
			// 
			// CountDisplaylabel
			// 
			this->CountDisplaylabel->AutoSize = true;
			this->CountDisplaylabel->Location = System::Drawing::Point(732, 45);
			this->CountDisplaylabel->Name = L"CountDisplaylabel";
			this->CountDisplaylabel->Size = System::Drawing::Size(125, 13);
			this->CountDisplaylabel->TabIndex = 2;
			this->CountDisplaylabel->Text = L"количество выбранных";
			// 
			// DisplaySegments
			// 
			this->DisplaySegments->Location = System::Drawing::Point(732, 19);
			this->DisplaySegments->Name = L"DisplaySegments";
			this->DisplaySegments->Size = System::Drawing::Size(161, 23);
			this->DisplaySegments->TabIndex = 1;
			this->DisplaySegments->Text = L"Отобразить выбранные сегменты";
			this->DisplaySegments->UseVisualStyleBackColor = true;
			this->DisplaySegments->Click += gcnew System::EventHandler(this, &SegmentationForm::DisplaySegments_Click);
			// 
			// CurrentSegment
			// 
			this->CurrentSegment->AllowUserToAddRows = false;
			this->CurrentSegment->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->CurrentSegment->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {this->Id, this->CountVoxel, 
				this->MinWeightSegment, this->MeanWeightSegment, this->MaxWeightSegment, this->CheckSegment});
			this->CurrentSegment->Location = System::Drawing::Point(6, 19);
			this->CurrentSegment->Name = L"CurrentSegment";
			this->CurrentSegment->Size = System::Drawing::Size(720, 249);
			this->CurrentSegment->TabIndex = 0;
			this->CurrentSegment->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &SegmentationForm::CurrentSegment_CellContentClick);
			// 
			// Id
			// 
			this->Id->HeaderText = L"№";
			this->Id->Name = L"Id";
			// 
			// CountVoxel
			// 
			this->CountVoxel->HeaderText = L"количество вокселей";
			this->CountVoxel->Name = L"CountVoxel";
			// 
			// MinWeightSegment
			// 
			this->MinWeightSegment->HeaderText = L"минимальная плотность в сегменте";
			this->MinWeightSegment->Name = L"MinWeightSegment";
			// 
			// MeanWeightSegment
			// 
			this->MeanWeightSegment->HeaderText = L"средняя плотность в сегменте";
			this->MeanWeightSegment->Name = L"MeanWeightSegment";
			// 
			// MaxWeightSegment
			// 
			this->MaxWeightSegment->HeaderText = L"максимальная  плотность в сегменте";
			this->MaxWeightSegment->Name = L"MaxWeightSegment";
			// 
			// CheckSegment
			// 
			this->CheckSegment->HeaderText = L"выбрать";
			this->CheckSegment->Name = L"CheckSegment";
			// 
			// SegmentationGroup
			// 
			this->SegmentationGroup->Controls->Add(this->MinVoxel);
			this->SegmentationGroup->Controls->Add(this->MinVoxelLabel);
			this->SegmentationGroup->Controls->Add(this->Display);
			this->SegmentationGroup->Controls->Add(this->Increment);
			this->SegmentationGroup->Controls->Add(this->IncrementDataLabel1);
			this->SegmentationGroup->Controls->Add(this->IncrementData);
			this->SegmentationGroup->Controls->Add(this->ReplaceData);
			this->SegmentationGroup->Controls->Add(this->StartStep);
			this->SegmentationGroup->Controls->Add(this->StartStepLabel);
			this->SegmentationGroup->Controls->Add(this->SegmentationType0);
			this->SegmentationGroup->Controls->Add(this->SegmentationIteration);
			this->SegmentationGroup->Controls->Add(this->StartSegmentation);
			this->SegmentationGroup->Enabled = false;
			this->SegmentationGroup->Location = System::Drawing::Point(12, 12);
			this->SegmentationGroup->Name = L"SegmentationGroup";
			this->SegmentationGroup->Size = System::Drawing::Size(900, 159);
			this->SegmentationGroup->TabIndex = 4;
			this->SegmentationGroup->TabStop = false;
			this->SegmentationGroup->Text = L"Сегментация";
			// 
			// Display
			// 
			this->Display->Controls->Add(this->NewDataDisplay);
			this->Display->Controls->Add(this->InitialDataDisplay);
			this->Display->Location = System::Drawing::Point(748, 19);
			this->Display->Name = L"Display";
			this->Display->Size = System::Drawing::Size(146, 71);
			this->Display->TabIndex = 11;
			this->Display->TabStop = false;
			this->Display->Text = L"Отображать";
			this->Display->Enter += gcnew System::EventHandler(this, &SegmentationForm::Display_Enter);
			// 
			// NewDataDisplay
			// 
			this->NewDataDisplay->AutoSize = true;
			this->NewDataDisplay->Location = System::Drawing::Point(6, 42);
			this->NewDataDisplay->Name = L"NewDataDisplay";
			this->NewDataDisplay->Size = System::Drawing::Size(98, 17);
			this->NewDataDisplay->TabIndex = 1;
			this->NewDataDisplay->Text = L"новые данные";
			this->NewDataDisplay->UseVisualStyleBackColor = true;
			this->NewDataDisplay->CheckedChanged += gcnew System::EventHandler(this, &SegmentationForm::radioButton2_CheckedChanged);
			// 
			// InitialDataDisplay
			// 
			this->InitialDataDisplay->AutoSize = true;
			this->InitialDataDisplay->Checked = true;
			this->InitialDataDisplay->Location = System::Drawing::Point(6, 19);
			this->InitialDataDisplay->Name = L"InitialDataDisplay";
			this->InitialDataDisplay->Size = System::Drawing::Size(115, 17);
			this->InitialDataDisplay->TabIndex = 0;
			this->InitialDataDisplay->TabStop = true;
			this->InitialDataDisplay->Text = L"исходные данные";
			this->InitialDataDisplay->UseVisualStyleBackColor = true;
			this->InitialDataDisplay->CheckedChanged += gcnew System::EventHandler(this, &SegmentationForm::InitialDataDisplay_CheckedChanged);
			// 
			// Increment
			// 
			this->Increment->Location = System::Drawing::Point(642, 19);
			this->Increment->Name = L"Increment";
			this->Increment->Size = System::Drawing::Size(100, 20);
			this->Increment->TabIndex = 10;
			this->Increment->Text = L"0";
			// 
			// IncrementDataLabel1
			// 
			this->IncrementDataLabel1->AutoSize = true;
			this->IncrementDataLabel1->Location = System::Drawing::Point(571, 19);
			this->IncrementDataLabel1->Name = L"IncrementDataLabel1";
			this->IncrementDataLabel1->Size = System::Drawing::Size(65, 13);
			this->IncrementDataLabel1->TabIndex = 9;
			this->IncrementDataLabel1->Text = L"слогаемое:";
			// 
			// IncrementData
			// 
			this->IncrementData->Location = System::Drawing::Point(574, 45);
			this->IncrementData->Name = L"IncrementData";
			this->IncrementData->Size = System::Drawing::Size(168, 23);
			this->IncrementData->TabIndex = 8;
			this->IncrementData->Text = L"увеличить исходные данные\r\n";
			this->IncrementData->UseVisualStyleBackColor = true;
			this->IncrementData->Click += gcnew System::EventHandler(this, &SegmentationForm::IncrementData_Click);
			// 
			// ReplaceData
			// 
			this->ReplaceData->Location = System::Drawing::Point(450, 19);
			this->ReplaceData->Name = L"ReplaceData";
			this->ReplaceData->Size = System::Drawing::Size(118, 49);
			this->ReplaceData->TabIndex = 7;
			this->ReplaceData->Text = L"заменить исходные данные на новые\r\n";
			this->ReplaceData->UseVisualStyleBackColor = true;
			this->ReplaceData->Click += gcnew System::EventHandler(this, &SegmentationForm::ReplaceData_Click);
			// 
			// StartStep
			// 
			this->StartStep->Location = System::Drawing::Point(344, 48);
			this->StartStep->Name = L"StartStep";
			this->StartStep->Size = System::Drawing::Size(100, 20);
			this->StartStep->TabIndex = 6;
			this->StartStep->Text = L"10";
			// 
			// StartStepLabel
			// 
			this->StartStepLabel->AutoSize = true;
			this->StartStepLabel->Location = System::Drawing::Point(341, 26);
			this->StartStepLabel->Name = L"StartStepLabel";
			this->StartStepLabel->Size = System::Drawing::Size(99, 13);
			this->StartStepLabel->TabIndex = 5;
			this->StartStepLabel->Text = L"шаг буферизации:";
			this->StartStepLabel->Click += gcnew System::EventHandler(this, &SegmentationForm::StartStepLabel_Click);
			// 
			// SegmentationType0
			// 
			this->SegmentationType0->Controls->Add(this->GPU);
			this->SegmentationType0->Controls->Add(this->CPU);
			this->SegmentationType0->Location = System::Drawing::Point(12, 19);
			this->SegmentationType0->Name = L"SegmentationType0";
			this->SegmentationType0->Size = System::Drawing::Size(155, 71);
			this->SegmentationType0->TabIndex = 4;
			this->SegmentationType0->TabStop = false;
			this->SegmentationType0->Text = L"тип сегментации";
			// 
			// GPU
			// 
			this->GPU->AutoSize = true;
			this->GPU->Location = System::Drawing::Point(6, 42);
			this->GPU->Name = L"GPU";
			this->GPU->Size = System::Drawing::Size(138, 17);
			this->GPU->TabIndex = 1;
			this->GPU->Text = L"параллельная на GPU";
			this->GPU->UseVisualStyleBackColor = true;
			this->GPU->CheckedChanged += gcnew System::EventHandler(this, &SegmentationForm::GPU_CheckedChanged);
			// 
			// CPU
			// 
			this->CPU->AutoSize = true;
			this->CPU->Checked = true;
			this->CPU->Location = System::Drawing::Point(6, 19);
			this->CPU->Name = L"CPU";
			this->CPU->Size = System::Drawing::Size(120, 17);
			this->CPU->TabIndex = 0;
			this->CPU->TabStop = true;
			this->CPU->Text = L"последовательная";
			this->CPU->UseVisualStyleBackColor = true;
			this->CPU->CheckedChanged += gcnew System::EventHandler(this, &SegmentationForm::CPU_CheckedChanged);
			// 
			// SegmentationIteration
			// 
			this->SegmentationIteration->Enabled = false;
			this->SegmentationIteration->Location = System::Drawing::Point(258, 19);
			this->SegmentationIteration->Name = L"SegmentationIteration";
			this->SegmentationIteration->Size = System::Drawing::Size(84, 49);
			this->SegmentationIteration->TabIndex = 3;
			this->SegmentationIteration->Text = L"итерация сегментации";
			this->SegmentationIteration->UseVisualStyleBackColor = true;
			this->SegmentationIteration->Click += gcnew System::EventHandler(this, &SegmentationForm::SegmentationIteration_Click);
			// 
			// StartSegmentation
			// 
			this->StartSegmentation->Location = System::Drawing::Point(173, 19);
			this->StartSegmentation->Name = L"StartSegmentation";
			this->StartSegmentation->Size = System::Drawing::Size(84, 49);
			this->StartSegmentation->TabIndex = 2;
			this->StartSegmentation->Text = L"начать новую сегментацию";
			this->StartSegmentation->UseVisualStyleBackColor = true;
			this->StartSegmentation->Click += gcnew System::EventHandler(this, &SegmentationForm::StartSegmentation_Click);
			// 
			// MinVoxelLabel
			// 
			this->MinVoxelLabel->AutoSize = true;
			this->MinVoxelLabel->Location = System::Drawing::Point(173, 77);
			this->MinVoxelLabel->Name = L"MinVoxelLabel";
			this->MinVoxelLabel->Size = System::Drawing::Size(249, 13);
			this->MinVoxelLabel->TabIndex = 12;
			this->MinVoxelLabel->Text = L"минимальное количество вокселей в сегменте";
			// 
			// MinVoxel
			// 
			this->MinVoxel->Location = System::Drawing::Point(428, 74);
			this->MinVoxel->Name = L"MinVoxel";
			this->MinVoxel->Size = System::Drawing::Size(120, 20);
			this->MinVoxel->TabIndex = 13;
			// 
			// SegmentationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(924, 766);
			this->Controls->Add(this->SegmentationGroup);
			this->Controls->Add(this->SegmentInfo);
			this->Controls->Add(this->LayerSegmentsTreeInfo);
			this->Name = L"SegmentationForm";
			this->Text = L"SegmentationForm";
			this->Load += gcnew System::EventHandler(this, &SegmentationForm::SegmentationForm_Load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &SegmentationForm::SegmentationForm_FormClosing);
			this->LayerSegmentsTreeInfo->ResumeLayout(false);
			this->LayerSegmentsTreeInfo->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->LayerSegmentsGrid))->EndInit();
			this->SegmentInfo->ResumeLayout(false);
			this->SegmentInfo->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->CurrentSegment))->EndInit();
			this->SegmentationGroup->ResumeLayout(false);
			this->SegmentationGroup->PerformLayout();
			this->Display->ResumeLayout(false);
			this->Display->PerformLayout();
			this->SegmentationType0->ResumeLayout(false);
			this->SegmentationType0->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MinVoxel))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void StartSegmentation_Click(System::Object^  sender, System::EventArgs^  e) {
				 String^ str = StartStep->Text;
				 char* s = new char[str->Length];

				 for (int k = 0; k < str->Length; k++)
					 s[k] = char(str[k]);
				 int step = atoi(s); 					

				 if (segmentationType == 0)
				 {
					 tree = new SegmentsTree(data);
					 tree->step = short(step);
					 SegmentationIteration->Enabled = true;
					 LayerSegmentsGrid->RowCount = 1;
					 LayerSegmentsGrid->Rows[0]->Cells[0]->Value = "0"; 
					 unsigned int^ count = tree->root->segmentCount;                 
					 LayerSegmentsGrid->Rows[0]->Cells[1]->Value = count->ToString(); 
					 unsigned int^ w = tree->root->maxCapacity;                 
					 LayerSegmentsGrid->Rows[0]->Cells[2]->Value = w->ToString(); 
				 }
				 else
				 {
					 tree2 = new SegmentsTree2(data);
					 tree2->step = short(step);
					 SegmentationIteration->Enabled = true;
					 LayerSegmentsGrid->RowCount = 1;
					 LayerSegmentsGrid->Rows[0]->Cells[0]->Value = "0"; 
					 unsigned int^ count = tree2->root->segmentCount;                 
					 LayerSegmentsGrid->Rows[0]->Cells[1]->Value = count->ToString(); 
					 unsigned int^ w = tree2->root->maxCapacity;                 
					 LayerSegmentsGrid->Rows[0]->Cells[2]->Value = w->ToString(); 
				 }
			 }
	private: System::Void SegmentationForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 e->Cancel = true;
				 Hide();
			 }
	private: System::Void SegmentationForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void SegmentationIteration_Click(System::Object^  sender, System::EventArgs^  e) {
				 String^ str = StartStep->Text;
				 char* s = new char[str->Length];

				 for (int k = 0; k < str->Length; k++)
					 s[k] = char(str[k]);
				 int step = atoi(s); 					

				 if (segmentationType == 0)
				 {
					 tree->step = step;
					 tree->minVoxel = size_t(MinVoxel->Value.ToOACurrency(MinVoxel->Value) / 10000);
					 LayerSegmentsTree*  newLayer = tree->CreateNewLayer();
					 if (newLayer->segmentCount > (newLayer->down->segmentCount * 0.25))
						 tree->step *= 2; 
					 short^ c = tree->step;
					 StartStep->Text = c->ToString();
					 LayerSegmentsTree* layer = tree->root;
					 int indexLayer = 0;
					 LayerSegmentsGrid->RowCount = LayerSegmentsGrid->RowCount + 1;

					 while (layer != 0)    
					 {
						 int^ c = indexLayer;                
						 LayerSegmentsGrid->Rows[indexLayer]->Cells[0]->Value = c->ToString(); 
						 unsigned int^ count = layer->segmentCount;                 
						 LayerSegmentsGrid->Rows[indexLayer]->Cells[1]->Value = count->ToString(); 
						 unsigned int^ w = layer->maxCapacity;                 
						 LayerSegmentsGrid->Rows[indexLayer]->Cells[2]->Value = w->ToString(); 
						 indexLayer++;
						 layer = layer->up;
					 }
					 LayerSegmentsTreeInfo->Enabled = true;
				 }
				 else
				 {

					 tree2->step = step;

					 LayerSegmentsTree2*  newLayer2 = tree2->CreateNewLayer();
					 if (newLayer2->segmentCount > (newLayer2->down->segmentCount * 0.25))
						 tree2->step *= 2; 
					 short^ c = tree->step;
					 StartStep->Text = c->ToString();
					 LayerSegmentsTree2* layer2 = tree2->root;
					 int indexLayer = 0;
					 LayerSegmentsGrid->RowCount = LayerSegmentsGrid->RowCount + 1;

					 while (layer2 != 0)    
					 {
						 int^ c = indexLayer;                
						 LayerSegmentsGrid->Rows[indexLayer]->Cells[0]->Value = c->ToString(); 
						 unsigned int^ count = layer2->segmentCount;                 
						 LayerSegmentsGrid->Rows[indexLayer]->Cells[1]->Value = count->ToString(); 
						 unsigned int^ w = layer2->maxCapacity;                 
						 LayerSegmentsGrid->Rows[indexLayer]->Cells[2]->Value = w->ToString(); 
						 indexLayer++;
						 layer2 = layer2->up;
					 }
					 LayerSegmentsTreeInfo->Enabled = true;
				 }

			 }
	private: System::Void LayerSegmentsGrid_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
				 LayerSelect->Text = e->RowIndex.ToString();
			 }
	private: System::Void Select_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (segmentationType == 0)
				 {
					 LayerSegmentsTree* layer = tree->root;
					 int i = 0;

					 String^ str = LayerSelect->Text;
					 char* s = new char[str->Length];

					 for (int k = 0; k < str->Length; k++)
						 s[k] = char(str[k]);
					 int curent = atoi(s); 
					 while (layer != 0)    
					 {
						 if (curent == i)
						 {
							 layerSelect = layer;
							 break;
						 }
						 else
						 {
							 layer = layer->up;
							 i++;
						 }
					 }

					 Segment* currentSegment = layerSelect->segment;
					 int j = 0;
					 CurrentSegment->RowCount = layerSelect->segmentCount + 2;
					 while (currentSegment != 0)
					 {
						 int^ c = j;                
						 CurrentSegment->Rows[j]->Cells[0]->Value = c->ToString(); 
						 unsigned int^ count = currentSegment->сapacity;                 
						 CurrentSegment->Rows[j]->Cells[1]->Value = count->ToString(); 
						 short^ w0 = currentSegment->minWeight;                 
						 CurrentSegment->Rows[j]->Cells[2]->Value = w0->ToString();
						 short^ w1 = short((currentSegment->maxWeight - currentSegment->minWeight) / 2);                 
						 CurrentSegment->Rows[j]->Cells[3]->Value = w1->ToString();
						 short^ w2 = currentSegment->maxWeight;                 
						 CurrentSegment->Rows[j]->Cells[4]->Value = w2->ToString();

						 j++;
						 currentSegment = currentSegment->next;
					 }
				 }
				 else
				 {
					 LayerSegmentsTree2* layer2 = tree2->root;
					 int i = 0;

					 String^ str = LayerSelect->Text;
					 char* s = new char[str->Length];

					 for (int k = 0; k < str->Length; k++)
						 s[k] = char(str[k]);
					 int curent = atoi(s); 
					 while (layer2 != 0)    
					 {
						 if (curent == i)
						 {
							 layerSelect2 = layer2;
							 break;
						 }
						 else
						 {
							 layer2 = layer2->up;
							 i++;
						 }
					 }

					 CurrentSegment->RowCount = layerSelect2->segmentCount + 2;

					 for (size_t j = 0; j < layerSelect2->segmentCount; j++)
					 {
						 unsigned int^ c = j;                
						 CurrentSegment->Rows[j]->Cells[0]->Value = c->ToString(); 
						 unsigned int^ count = layerSelect2->countVoxel[j];                 
						 CurrentSegment->Rows[j]->Cells[1]->Value = count->ToString(); 
						 short^ w0 = layerSelect2->minWeight[j];                 
						 CurrentSegment->Rows[j]->Cells[2]->Value = w0->ToString();
						 short^ w1= short((layerSelect2->maxWeight[j] - layerSelect2->minWeight[j]) / 2);                 
						 CurrentSegment->Rows[j]->Cells[3]->Value = w1->ToString();
						 short^ w2= layerSelect2->maxWeight[j];                 
						 CurrentSegment->Rows[j]->Cells[4]->Value = w2->ToString();

					 }
				 }
				 SegmentInfo->Enabled = true;
			 }

	private: System::Void DisplaySegments_Click(System::Object^  sender, System::EventArgs^  e) {
				 int countCheck = 0;
				 for (int i = 0; i < layerSelect->segmentCount; i++)
				 {
					 if (CurrentSegment->Rows[i]->Cells[5]->Value)
					 {
						 if (bool(CurrentSegment->Rows[i]->Cells[5]->Value) == true)
							 countCheck++;
					 }
				 }
				 int^ c = countCheck;  
				 CountDisplay->Text = c->ToString();
				 size_t* indexs = new size_t [countCheck];
				 int k = 0;
				 for (int i = 0; i < layerSelect->segmentCount; i++)
				 {
					 if (CurrentSegment->Rows[i]->Cells[5]->Value)
					 {
						 if (bool(CurrentSegment->Rows[i]->Cells[5]->Value) == true)
						 {
							 indexs[k] = size_t(i);
							 k++;
						 }
					 }
				 }

				 if (segmentationType == 0)
					 layerSelect->CreateData(indexs, size_t(countCheck), sd);
				 else
					 layerSelect2->CreateData(indexs, size_t(countCheck), sd);
				 DisplayData(sd);
				 isDisplayInitialData = false;
				 NewDataDisplay->Checked = true;
				 //mainForm->data = layerSelect->CreateData(indexs, size_t(countCheck));

			 }
	private: System::Void StartStepLabel_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void CPU_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 segmentationType = 0;
			 }
	private: System::Void GPU_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 segmentationType = 1;
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				 int countCheck = 0;
				 for (int i = 0; i < layerSelect->segmentCount; i++)
				 {
					 if (!CurrentSegment->Rows[i]->Cells[5]->Value)
					 {
						 countCheck++;						 
					 }
					 else
						 if (bool(CurrentSegment->Rows[i]->Cells[5]->Value) == false)
							 countCheck++;
				 }
				 int^ c = countCheck;  
				 CountDisplay->Text = c->ToString();
				 size_t* indexs = new size_t [countCheck];
				 int k = 0;
				 for (int i = 0; i < layerSelect->segmentCount; i++)
				 {
					 if (!CurrentSegment->Rows[i]->Cells[5]->Value)
					 {
						 indexs[k] = size_t(i);
						 k++;
					 }
					 else
						 if (bool(CurrentSegment->Rows[i]->Cells[5]->Value) == false)
						 {
							 indexs[k] = size_t(i);
							 k++;
						 }

				 }
				 if (segmentationType == 0)
					 layerSelect->CreateData(indexs, size_t(countCheck), sd);
				 else
					 layerSelect2->CreateData(indexs, size_t(countCheck), sd);
				 DisplayData(sd);
				 isDisplayInitialData = false;
				 NewDataDisplay->Checked = true;
				 //mainForm->data = layerSelect->CreateData(indexs, size_t(countCheck));
			 }
	private: System::Void ReplaceData_Click(System::Object^  sender, System::EventArgs^  e) {
				 size_t dim = data->sizeX * data->sizeY * data->sizeZ;
				 if (sd != 0)
					 for (size_t i = 0; i < dim; i++)
						 data->data[i] = sd->data[i];

				 if (segmentationType == 0)
				 {
					 if (tree != 0)
						 if (tree->root != 0)
						 {
							 LayerSegmentsTree* layer = tree->root;
							 while (layer != 0)    
							 {
								 Segment* currentSegment = layer->segment;
								 Voxel* voxel = 0;

								 while (currentSegment != 0)
								 {
									 short maxw = 0;
									 short minw = 0;
									 voxel = currentSegment->voxel;
									 while (voxel != 0)
									 {
										 if (data->data[voxel->index] > maxw)
											 maxw = data->data[voxel->index];
										 if (data->data[voxel->index] < minw)
											 minw = data->data[voxel->index];

										 voxel = voxel->next;
									 }
									 currentSegment->maxWeight = maxw;
									 currentSegment->minWeight = minw;
									 currentSegment = currentSegment->next;
								 }
								 layer = layer->up;
							 }
							 if (layerSelect != 0)
							 {
								 Segment* currentSegment = layerSelect->segment;
								 int j = 0;
								 CurrentSegment->RowCount = layerSelect->segmentCount + 2;
								 while (currentSegment != 0)
								 {
									 int^ c = j;                
									 CurrentSegment->Rows[j]->Cells[0]->Value = c->ToString(); 
									 unsigned int^ count = currentSegment->сapacity;                 
									 CurrentSegment->Rows[j]->Cells[1]->Value = count->ToString(); 
									 short^ w0 = currentSegment->minWeight;                 
									 CurrentSegment->Rows[j]->Cells[2]->Value = w0->ToString();
									 short^ w1 = short((currentSegment->maxWeight - currentSegment->minWeight) / 2);                 
									 CurrentSegment->Rows[j]->Cells[3]->Value = w1->ToString();
									 short^ w2 = currentSegment->maxWeight;                 
									 CurrentSegment->Rows[j]->Cells[4]->Value = w2->ToString();

									 j++;
									 currentSegment = currentSegment->next;
								 }
							 }
						 }

				 }
				 else
				 {
					 if (tree2 != 0)
						 if (tree2->root != 0)
						 {
							 LayerSegmentsTree2* layer2 = tree2->root;
							 Voxel2* voxel = 0;
							 while (layer2 != 0)    
							 {
								 for (size_t j = 0; j < layer2->segmentCount; j++)
								 {
									 short maxw = 0;
									 short minw = 0;
									 voxel = &layer2->indexVoxel[layer2->startIndexVoxel[j]];
									 while (voxel != 0)
									 {
										 if (data->data[voxel->index] > maxw)
											 maxw = data->data[voxel->index];
										 if (data->data[voxel->index] < minw)
											 minw = data->data[voxel->index];

										 voxel = voxel->next;
									 }
									 layer2->maxWeight[j] = maxw;
									 layer2->minWeight[j] = minw;

								 }
								 layer2 = layer2->up;
							 }

							 if (layerSelect2 != 0)
							 {
								 CurrentSegment->RowCount = layerSelect2->segmentCount + 2;

								 for (size_t j = 0; j < layerSelect2->segmentCount; j++)
								 {
									 unsigned int^ c = j;                
									 CurrentSegment->Rows[j]->Cells[0]->Value = c->ToString(); 
									 unsigned int^ count = layerSelect2->countVoxel[j];                 
									 CurrentSegment->Rows[j]->Cells[1]->Value = count->ToString(); 
									 short^ w0 = layerSelect2->minWeight[j];                 
									 CurrentSegment->Rows[j]->Cells[2]->Value = w0->ToString();
									 short^ w1= short((layerSelect2->maxWeight[j] - layerSelect2->minWeight[j]) / 2);                 
									 CurrentSegment->Rows[j]->Cells[3]->Value = w1->ToString();
									 short^ w2= layerSelect2->maxWeight[j];                 
									 CurrentSegment->Rows[j]->Cells[4]->Value = w2->ToString();

								 }
							 }
						 }

				 }
			 }
	private: System::Void IncrementData_Click(System::Object^  sender, System::EventArgs^  e) {
				 String^ str = Increment->Text;
				 char* s = new char[str->Length];

				 for (int k = 0; k < str->Length; k++)
					 s[k] = char(str[k]);
				 short increment = atoi(s); 
				 size_t dim = data->sizeX * data->sizeY * data->sizeZ;
				 for (size_t i = 0; i < dim; i++)
					 if (data->data[i] != 0)
						 data->data[i] = data->data[i] + increment;
				 if (sd != 0)
				 {
					 for (size_t i = 0; i < dim; i++)
						 if (sd->data[i] != 0)
							 sd->data[i] = sd->data[i] + increment;
				 }



				 if (segmentationType == 0)
				 {
					 if (tree != 0)
						 if (tree->root != 0)
						 {
							 LayerSegmentsTree* layer = tree->root;
							 while (layer != 0)    
							 {
								 Segment* currentSegment = layer->segment;
								 Voxel* voxel = 0;

								 while (currentSegment != 0)
								 {
									 short maxw = 0;
									 short minw = 0;
									 voxel = currentSegment->voxel;
									 while (voxel != 0)
									 {
										 if (data->data[voxel->index] > maxw)
											 maxw = data->data[voxel->index];
										 if (data->data[voxel->index] < minw)
											 minw = data->data[voxel->index];

										 voxel = voxel->next;
									 }
									 currentSegment->maxWeight = maxw;
									 currentSegment->minWeight = minw;
									 currentSegment = currentSegment->next;
								 }
								 layer = layer->up;
							 }
							 if (layerSelect != 0)
							 {
								 Segment* currentSegment = layerSelect->segment;
								 int j = 0;
								 CurrentSegment->RowCount = layerSelect->segmentCount + 2;
								 while (currentSegment != 0)
								 {
									 int^ c = j;                
									 CurrentSegment->Rows[j]->Cells[0]->Value = c->ToString(); 
									 unsigned int^ count = currentSegment->сapacity;                 
									 CurrentSegment->Rows[j]->Cells[1]->Value = count->ToString(); 
									 short^ w0 = currentSegment->minWeight;                 
									 CurrentSegment->Rows[j]->Cells[2]->Value = w0->ToString();
									 short^ w1 = short((currentSegment->maxWeight - currentSegment->minWeight) / 2);                 
									 CurrentSegment->Rows[j]->Cells[3]->Value = w1->ToString();
									 short^ w2 = currentSegment->maxWeight;                 
									 CurrentSegment->Rows[j]->Cells[4]->Value = w2->ToString();

									 j++;
									 currentSegment = currentSegment->next;
								 }
							 }
						 }
				 }
				 else
				 {
					 if (tree2 != 0)
						 if (tree2->root != 0)
						 {
							 LayerSegmentsTree2* layer2 = tree2->root;
							 Voxel2* voxel = 0;
							 while (layer2 != 0)    
							 {
								 for (size_t j = 0; j < layer2->segmentCount; j++)
								 {
									 short maxw = 0;
									 short minw = 0;
									 voxel = &layer2->indexVoxel[layer2->startIndexVoxel[j]];
									 while (voxel != 0)
									 {
										 if (data->data[voxel->index] > maxw)
											 maxw = data->data[voxel->index];
										 if (data->data[voxel->index] < minw)
											 minw = data->data[voxel->index];

										 voxel = voxel->next;
									 }
									 layer2->maxWeight[j] = maxw;
									 layer2->minWeight[j] = minw;

								 }
								 layer2 = layer2->up;
							 }

							 if (layerSelect2 != 0)
							 {
								 CurrentSegment->RowCount = layerSelect2->segmentCount + 2;

								 for (size_t j = 0; j < layerSelect2->segmentCount; j++)
								 {
									 unsigned int^ c = j;                
									 CurrentSegment->Rows[j]->Cells[0]->Value = c->ToString(); 
									 unsigned int^ count = layerSelect2->countVoxel[j];                 
									 CurrentSegment->Rows[j]->Cells[1]->Value = count->ToString(); 
									 short^ w0 = layerSelect2->minWeight[j];                 
									 CurrentSegment->Rows[j]->Cells[2]->Value = w0->ToString();
									 short^ w1= short((layerSelect2->maxWeight[j] - layerSelect2->minWeight[j]) / 2);                 
									 CurrentSegment->Rows[j]->Cells[3]->Value = w1->ToString();
									 short^ w2= layerSelect2->maxWeight[j];                 
									 CurrentSegment->Rows[j]->Cells[4]->Value = w2->ToString();

								 }
							 }
						 }

				 }
				 if (isDisplayInitialData)
					 DisplayData(data);
				 else
					 DisplayData(sd);


			 }
	private: System::Void Display_Enter(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (sd != 0)
				 {
					 DisplayData(sd);
					 isDisplayInitialData = false;
				 }
			 }
	private: System::Void InitialDataDisplay_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 DisplayData(data);
				 isDisplayInitialData = true;
			 }
	private: System::Void CurrentSegment_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 }
	};
}
