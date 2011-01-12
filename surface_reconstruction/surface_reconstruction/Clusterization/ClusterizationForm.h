#pragma once

#include "glee.h"
#include <Windows.h>
#include "ClusterizationGraphics.h"
#include "ScanData.h"
#include "K-means.h"
#include <stdio.h>
#include <math.h>

using namespace std;

#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")
#pragma comment (lib,"User32.lib")
#pragma comment (lib,"gdi32.lib")

struct TColor 
{
 float R, G, B, A;						// параметры цвета
 TColor():R(0), G(0), B(0), A(0) {};
 TColor(float value_R, float value_G, float value_B, float value_A): 
        R(value_R), G(value_G), B(value_B), A(value_A) {};
 TColor(float value_R, float value_G, float value_B): R(value_R), G(value_G), B(value_B) {};
};

struct TVoxel							// трёхмерный воксел
{
 TColor Color_2D, Color_3D;				// цвет в 2D- и 3D-режиме соответственно
 bool IsVisible_2D, IsVisible_3D;		// атрибут видимости воксела на сцене 

 // Конструктор по умолчанию
 TVoxel(): Color_2D(TColor(0.0f, 0.0f, 0.0f, 0.0f)), 
		      Color_3D(TColor(0.0f, 0.0f, 0.0f, 0.0f)), 
			  IsVisible_2D(true), IsVisible_3D(true) {};
};

struct TSegment							// сегмент из вокселов
{
 vector <size_t> Index;			// вектор индексов вокселов
 unsigned char transparensy;	// уровень прозрачности
 bool IsVisible;				// атрибут видимости вокселов, входящих в сегмент
 TColor Color;					// цвет сегмента
 short MinDensity;				// минимальное значение плотности 
 short MaxDensity;				// максимальное значение плотности

 TSegment(): IsVisible(false), Color(TColor(0.0f, 0.0f, 0.0f, 0.0f)), transparensy(255) {Index.clear();};
 TSegment(vector <size_t> Value_Index) : Index(Value_Index) {Color = TColor(0.0f, 0.0f, 0.0f, 0.0f);};
};

namespace surface_reconstruction {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ClusterizationForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>

	public delegate void MyVisibleDelegate(size_t index, bool value);
	public delegate void MyColorDelegate(size_t index, TColor Value_Color);

	public ref class ClusterizationForm : public System::Windows::Forms::Form
	{
	public:
		ClusterizationForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void ChangeVisible_2D(size_t index, bool value)	{VoxelsData[index].IsVisible_2D = value;}
		void ChangeVisible_3D(size_t index, bool value) {VoxelsData[index].IsVisible_3D = value;}

		void ChangeVoxelColor_2D(size_t index, TColor Value_Color) {VoxelsData[index].Color_2D = Value_Color;}
		void ChangeVoxelColor_3D(size_t index, TColor Value_Color) {VoxelsData[index].Color_3D = Value_Color;}

		
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ClusterizationForm()
		{
			ReleaseTextures();

            if (hRC) {
                wglMakeCurrent(NULL,NULL);
                wglDeleteContext(hRC);
                hRC = NULL;
            }

            ReleaseDC(hWnd,hDC);
            hDC = NULL;
            if (components) {
                delete components;
            }
		}

	private: void ReleaseTextures()  // освобождение ресурсов, занятых текстурами 
			 {
              if (layerTextures) 
			  { 
               glDeleteTextures(InputData->sizeZ, layerTextures);
               delete layerTextures;
               layerTextures = 0;
              }
             }

	protected: 

	private: System::Windows::Forms::MenuStrip^  MenuStrip;

	private: System::Windows::Forms::ToolStripMenuItem^  файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem_Download;


	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem_Exit;


	private: System::Windows::Forms::Panel^  RenderingPanel;
	private: System::Windows::Forms::Label^  Label_ClustersCount;
	private: System::Windows::Forms::TrackBar^  TrackBar_ClustersCount;
	private: System::Windows::Forms::GroupBox^  groupBox1;

	private: System::Windows::Forms::OpenFileDialog^  OpenDataDialog;

	public:
		MyVisibleDelegate^ StaticDelInst_Visible_2D;
		MyVisibleDelegate^ StaticDelInst_Visible_3D;
		MyColorDelegate^ StaticDelInst_Color_2D;
		MyColorDelegate^ StaticDelInst_Color_3D;

		ScanData* InputData;						// исходные данные
		KmeansMethod* ClusterizationMethod;			// метод, используемый для кластеризации
		TVoxel* VoxelsData;							// массив трёхмерных вокселов с атрибутами
		vector <TSegment>* Segments_2D;				// вектор сегментов для каждого слоя данных
		vector <TSegment>* Segments_3D;				// вектор сегментов для нескольких слоёв как единого целого

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

		/// <summary>
        /// Required designer variable.
        /// </summary>
        HDC     hDC;
        HGLRC   hRC;
        HWND    hWnd;
        
        GLint theBox;
		GLuint *layerTextures;

        float angleXRotation, angleYRotation; // углы поворота изображения вокруг координатных осей
        Point mousePosition;
        float distance;
		float depth;
	private:
		short MaxDensity;
		float BrightnessMult;

	private: System::Windows::Forms::Timer^  RenderTimer;
	private: System::Windows::Forms::Label^  Label_Status;
	private: System::Windows::Forms::ProgressBar^  ProgressBar_Iterations;
	private: System::Windows::Forms::ProgressBar^  ProgressBar_Layers;

	private: System::Windows::Forms::DataGridView^  DataGridView_Clusters;

private: System::Windows::Forms::TrackBar^  TrackBar_IterationsCount;
private: System::Windows::Forms::Label^  Label_IterationsCount;

private: System::Windows::Forms::Button^  Button_Clusterization;
private: System::ComponentModel::BackgroundWorker^  BackgroundWorker;
private: System::Windows::Forms::Button^  Button_VisualizeSelectedClusters;












private: System::Windows::Forms::ColorDialog^  ColorDialog;







private: System::Windows::Forms::GroupBox^  groupBox2;
private: System::Windows::Forms::Label^  Label_LayerInfo;
private: System::Windows::Forms::CheckBox^  CheckBoxClusters;
private: System::Windows::Forms::TrackBar^  TrackBar_Layers;
private: System::Windows::Forms::Label^  Label_BrightnessMult;
private: System::Windows::Forms::TextBox^  TextBox_BrightnessMult;
private: System::Windows::Forms::CheckBox^  CheckBox_Transparency;
private: System::Windows::Forms::CheckBox^  CheckBox_DepthTest;
private: System::Windows::Forms::Label^  Label_StartLayer;
private: System::Windows::Forms::Label^  Label_FinishLayer;
private: System::Windows::Forms::NumericUpDown^  NumericUpDown_Start;
private: System::Windows::Forms::NumericUpDown^  NumericUpDown_Finish;
private: System::Windows::Forms::TrackBar^  TrackBar_LayersDistance;
private: System::Windows::Forms::Label^  Label_LayersDistance;
private: System::Windows::Forms::GroupBox^  GroupBoxVisualization;
private: System::Windows::Forms::GroupBox^  GroupBoxDim;
private: System::Windows::Forms::RadioButton^  RadioButton_2D;
private: System::Windows::Forms::RadioButton^  RadioButton_3D;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  SegmentNumber;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  VoxelsCount;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Density_Minimum;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Density_Maximum;
private: System::Windows::Forms::DataGridViewButtonColumn^  SegmentColor;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  SegmentTransparensy;
private: System::Windows::Forms::DataGridViewCheckBoxColumn^  IsSegmentVisible;

private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->MenuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem_Download = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem_Exit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->RenderingPanel = (gcnew System::Windows::Forms::Panel());
			this->Label_ClustersCount = (gcnew System::Windows::Forms::Label());
			this->TrackBar_ClustersCount = (gcnew System::Windows::Forms::TrackBar());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->TrackBar_IterationsCount = (gcnew System::Windows::Forms::TrackBar());
			this->Label_IterationsCount = (gcnew System::Windows::Forms::Label());
			this->OpenDataDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->RenderTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->Label_Status = (gcnew System::Windows::Forms::Label());
			this->ProgressBar_Iterations = (gcnew System::Windows::Forms::ProgressBar());
			this->ProgressBar_Layers = (gcnew System::Windows::Forms::ProgressBar());
			this->DataGridView_Clusters = (gcnew System::Windows::Forms::DataGridView());
			this->SegmentNumber = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->VoxelsCount = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Density_Minimum = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Density_Maximum = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->SegmentColor = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->SegmentTransparensy = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->IsSegmentVisible = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
			this->Button_Clusterization = (gcnew System::Windows::Forms::Button());
			this->BackgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->Button_VisualizeSelectedClusters = (gcnew System::Windows::Forms::Button());
			this->ColorDialog = (gcnew System::Windows::Forms::ColorDialog());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->Label_LayerInfo = (gcnew System::Windows::Forms::Label());
			this->CheckBoxClusters = (gcnew System::Windows::Forms::CheckBox());
			this->TrackBar_Layers = (gcnew System::Windows::Forms::TrackBar());
			this->Label_BrightnessMult = (gcnew System::Windows::Forms::Label());
			this->TextBox_BrightnessMult = (gcnew System::Windows::Forms::TextBox());
			this->CheckBox_Transparency = (gcnew System::Windows::Forms::CheckBox());
			this->CheckBox_DepthTest = (gcnew System::Windows::Forms::CheckBox());
			this->Label_StartLayer = (gcnew System::Windows::Forms::Label());
			this->Label_FinishLayer = (gcnew System::Windows::Forms::Label());
			this->NumericUpDown_Start = (gcnew System::Windows::Forms::NumericUpDown());
			this->NumericUpDown_Finish = (gcnew System::Windows::Forms::NumericUpDown());
			this->TrackBar_LayersDistance = (gcnew System::Windows::Forms::TrackBar());
			this->Label_LayersDistance = (gcnew System::Windows::Forms::Label());
			this->GroupBoxVisualization = (gcnew System::Windows::Forms::GroupBox());
			this->GroupBoxDim = (gcnew System::Windows::Forms::GroupBox());
			this->RadioButton_2D = (gcnew System::Windows::Forms::RadioButton());
			this->RadioButton_3D = (gcnew System::Windows::Forms::RadioButton());
			this->MenuStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_ClustersCount))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_IterationsCount))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DataGridView_Clusters))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_Layers))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NumericUpDown_Start))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NumericUpDown_Finish))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_LayersDistance))->BeginInit();
			this->GroupBoxVisualization->SuspendLayout();
			this->GroupBoxDim->SuspendLayout();
			this->SuspendLayout();
			// 
			// MenuStrip
			// 
			this->MenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->файлToolStripMenuItem});
			this->MenuStrip->Location = System::Drawing::Point(0, 0);
			this->MenuStrip->Name = L"MenuStrip";
			this->MenuStrip->Size = System::Drawing::Size(1128, 26);
			this->MenuStrip->TabIndex = 1;
			this->MenuStrip->Text = L"menuStrip1";
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->ToolStripMenuItem_Download, 
				this->ToolStripMenuItem_Exit});
			this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
			this->файлToolStripMenuItem->Size = System::Drawing::Size(54, 22);
			this->файлToolStripMenuItem->Text = L"Файл";
			// 
			// ToolStripMenuItem_Download
			// 
			this->ToolStripMenuItem_Download->Name = L"ToolStripMenuItem_Download";
			this->ToolStripMenuItem_Download->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->ToolStripMenuItem_Download->Size = System::Drawing::Size(226, 22);
			this->ToolStripMenuItem_Download->Text = L"Загрузить...";
			this->ToolStripMenuItem_Download->Click += gcnew System::EventHandler(this, &ClusterizationForm::ToolStripMenuItem_Download_Click);
			// 
			// ToolStripMenuItem_Exit
			// 
			this->ToolStripMenuItem_Exit->Name = L"ToolStripMenuItem_Exit";
			this->ToolStripMenuItem_Exit->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::F4));
			this->ToolStripMenuItem_Exit->Size = System::Drawing::Size(226, 22);
			this->ToolStripMenuItem_Exit->Text = L"Выход";
			this->ToolStripMenuItem_Exit->Click += gcnew System::EventHandler(this, &ClusterizationForm::ToolStripMenuItem_Exit_Click);
			// 
			// RenderingPanel
			// 
			this->RenderingPanel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->RenderingPanel->BackColor = System::Drawing::SystemColors::ControlText;
			this->RenderingPanel->Location = System::Drawing::Point(3, 29);
			this->RenderingPanel->Name = L"RenderingPanel";
			this->RenderingPanel->Size = System::Drawing::Size(569, 742);
			this->RenderingPanel->TabIndex = 3;
			this->RenderingPanel->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &ClusterizationForm::RenderingPanel_MouseWheel);
			this->RenderingPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &ClusterizationForm::RenderingPanel_MouseMove);
			this->RenderingPanel->Click += gcnew System::EventHandler(this, &ClusterizationForm::RenderingPanel_Click);
			this->RenderingPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &ClusterizationForm::RenderingPanel_MouseDown);
			// 
			// Label_ClustersCount
			// 
			this->Label_ClustersCount->AutoSize = true;
			this->Label_ClustersCount->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->Label_ClustersCount->Location = System::Drawing::Point(12, 28);
			this->Label_ClustersCount->Name = L"Label_ClustersCount";
			this->Label_ClustersCount->Size = System::Drawing::Size(252, 17);
			this->Label_ClustersCount->TabIndex = 4;
			this->Label_ClustersCount->Text = L"Максимальное число сегментов:";
			// 
			// TrackBar_ClustersCount
			// 
			this->TrackBar_ClustersCount->Location = System::Drawing::Point(297, 24);
			this->TrackBar_ClustersCount->Maximum = 100;
			this->TrackBar_ClustersCount->Minimum = 2;
			this->TrackBar_ClustersCount->Name = L"TrackBar_ClustersCount";
			this->TrackBar_ClustersCount->Size = System::Drawing::Size(234, 56);
			this->TrackBar_ClustersCount->TabIndex = 5;
			this->TrackBar_ClustersCount->Value = 10;
			this->TrackBar_ClustersCount->ValueChanged += gcnew System::EventHandler(this, &ClusterizationForm::TrackBar_ClustersCount_ValueChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->BackColor = System::Drawing::Color::Snow;
			this->groupBox1->Controls->Add(this->TrackBar_IterationsCount);
			this->groupBox1->Controls->Add(this->Label_IterationsCount);
			this->groupBox1->Controls->Add(this->Label_ClustersCount);
			this->groupBox1->Controls->Add(this->TrackBar_ClustersCount);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox1->Location = System::Drawing::Point(585, 434);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(533, 144);
			this->groupBox1->TabIndex = 11;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Настройки сегментации";
			// 
			// TrackBar_IterationsCount
			// 
			this->TrackBar_IterationsCount->Location = System::Drawing::Point(298, 84);
			this->TrackBar_IterationsCount->Maximum = 500;
			this->TrackBar_IterationsCount->Minimum = 1;
			this->TrackBar_IterationsCount->Name = L"TrackBar_IterationsCount";
			this->TrackBar_IterationsCount->Size = System::Drawing::Size(233, 56);
			this->TrackBar_IterationsCount->TabIndex = 7;
			this->TrackBar_IterationsCount->Value = 50;
			this->TrackBar_IterationsCount->ValueChanged += gcnew System::EventHandler(this, &ClusterizationForm::TrackBar_IterationsCount_ValueChanged);
			// 
			// Label_IterationsCount
			// 
			this->Label_IterationsCount->AutoSize = true;
			this->Label_IterationsCount->Location = System::Drawing::Point(4, 89);
			this->Label_IterationsCount->Name = L"Label_IterationsCount";
			this->Label_IterationsCount->Size = System::Drawing::Size(260, 17);
			this->Label_IterationsCount->TabIndex = 6;
			this->Label_IterationsCount->Text = L"Количество итераций алгоритма:";
			// 
			// OpenDataDialog
			// 
			this->OpenDataDialog->FileName = L"*.bin";
			this->OpenDataDialog->Filter = L"bin-файлы(*.bin)|*.bin|All Files(*.*)|*.*";
			this->OpenDataDialog->Title = L"Загрузить bin-файл";
			// 
			// RenderTimer
			// 
			this->RenderTimer->Enabled = true;
			this->RenderTimer->Interval = 30;
			this->RenderTimer->Tick += gcnew System::EventHandler(this, &ClusterizationForm::RenderTimer_Tick);
			// 
			// Label_Status
			// 
			this->Label_Status->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_Status->AutoSize = true;
			this->Label_Status->Location = System::Drawing::Point(7, 775);
			this->Label_Status->Name = L"Label_Status";
			this->Label_Status->Size = System::Drawing::Size(91, 17);
			this->Label_Status->TabIndex = 12;
			this->Label_Status->Text = L"Label_Status";
			// 
			// ProgressBar_Iterations
			// 
			this->ProgressBar_Iterations->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->ProgressBar_Iterations->Location = System::Drawing::Point(3, 796);
			this->ProgressBar_Iterations->Name = L"ProgressBar_Iterations";
			this->ProgressBar_Iterations->Size = System::Drawing::Size(569, 23);
			this->ProgressBar_Iterations->Step = 1;
			this->ProgressBar_Iterations->TabIndex = 13;
			// 
			// ProgressBar_Layers
			// 
			this->ProgressBar_Layers->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->ProgressBar_Layers->Location = System::Drawing::Point(3, 825);
			this->ProgressBar_Layers->Name = L"ProgressBar_Layers";
			this->ProgressBar_Layers->Size = System::Drawing::Size(569, 23);
			this->ProgressBar_Layers->Step = 1;
			this->ProgressBar_Layers->TabIndex = 14;
			// 
			// DataGridView_Clusters
			// 
			this->DataGridView_Clusters->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataGridView_Clusters->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->DataGridView_Clusters->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {this->SegmentNumber, 
				this->VoxelsCount, this->Density_Minimum, this->Density_Maximum, this->SegmentColor, this->SegmentTransparensy, this->IsSegmentVisible});
			this->DataGridView_Clusters->Location = System::Drawing::Point(7, 25);
			this->DataGridView_Clusters->Name = L"DataGridView_Clusters";
			this->DataGridView_Clusters->RowTemplate->Height = 24;
			this->DataGridView_Clusters->Size = System::Drawing::Size(517, 179);
			this->DataGridView_Clusters->TabIndex = 15;
			this->DataGridView_Clusters->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &ClusterizationForm::DataGridView_Clusters_CellValueChanged);
			this->DataGridView_Clusters->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &ClusterizationForm::DataGridView_Clusters_CellClick);
			// 
			// SegmentNumber
			// 
			this->SegmentNumber->HeaderText = L"Индекс сегмента";
			this->SegmentNumber->Name = L"SegmentNumber";
			// 
			// VoxelsCount
			// 
			this->VoxelsCount->HeaderText = L"Число вокселов";
			this->VoxelsCount->Name = L"VoxelsCount";
			// 
			// Density_Minimum
			// 
			this->Density_Minimum->HeaderText = L"Минимальная плотность";
			this->Density_Minimum->Name = L"Density_Minimum";
			// 
			// Density_Maximum
			// 
			this->Density_Maximum->HeaderText = L"Максимальная плотность";
			this->Density_Maximum->Name = L"Density_Maximum";
			// 
			// SegmentColor
			// 
			this->SegmentColor->HeaderText = L"Цвет";
			this->SegmentColor->Name = L"SegmentColor";
			this->SegmentColor->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			// 
			// SegmentTransparensy
			// 
			this->SegmentTransparensy->HeaderText = L"Прозрачность";
			this->SegmentTransparensy->Name = L"SegmentTransparensy";
			// 
			// IsSegmentVisible
			// 
			this->IsSegmentVisible->HeaderText = L"Отобразить";
			this->IsSegmentVisible->Name = L"IsSegmentVisible";
			// 
			// Button_Clusterization
			// 
			this->Button_Clusterization->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->Button_Clusterization->Location = System::Drawing::Point(621, 594);
			this->Button_Clusterization->Name = L"Button_Clusterization";
			this->Button_Clusterization->Size = System::Drawing::Size(183, 32);
			this->Button_Clusterization->TabIndex = 16;
			this->Button_Clusterization->Text = L"Сегментировать данные";
			this->Button_Clusterization->UseVisualStyleBackColor = true;
			this->Button_Clusterization->Click += gcnew System::EventHandler(this, &ClusterizationForm::Button_Clusterization_Click);
			// 
			// BackgroundWorker
			// 
			this->BackgroundWorker->WorkerReportsProgress = true;
			this->BackgroundWorker->WorkerSupportsCancellation = true;
			this->BackgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ClusterizationForm::BackgroundWorker_DoWork);
			this->BackgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &ClusterizationForm::BackgroundWorker_RunWorkerCompleted);
			this->BackgroundWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &ClusterizationForm::BackgroundWorker_ProgressChanged);
			// 
			// Button_VisualizeSelectedClusters
			// 
			this->Button_VisualizeSelectedClusters->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->Button_VisualizeSelectedClusters->Location = System::Drawing::Point(844, 594);
			this->Button_VisualizeSelectedClusters->Name = L"Button_VisualizeSelectedClusters";
			this->Button_VisualizeSelectedClusters->Size = System::Drawing::Size(241, 32);
			this->Button_VisualizeSelectedClusters->TabIndex = 17;
			this->Button_VisualizeSelectedClusters->Text = L"Отобразить выбранные сегменты";
			this->Button_VisualizeSelectedClusters->UseVisualStyleBackColor = true;
			this->Button_VisualizeSelectedClusters->Click += gcnew System::EventHandler(this, &ClusterizationForm::Button_VisualizeSelectedClusters_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->DataGridView_Clusters);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox2->Location = System::Drawing::Point(585, 638);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(533, 210);
			this->groupBox2->TabIndex = 18;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Информация о сегментах";
			// 
			// Label_LayerInfo
			// 
			this->Label_LayerInfo->AutoSize = true;
			this->Label_LayerInfo->Location = System::Drawing::Point(14, 125);
			this->Label_LayerInfo->Name = L"Label_LayerInfo";
			this->Label_LayerInfo->Size = System::Drawing::Size(175, 17);
			this->Label_LayerInfo->TabIndex = 7;
			this->Label_LayerInfo->Text = L"Номер текущего слоя:";
			// 
			// CheckBoxClusters
			// 
			this->CheckBoxClusters->AutoSize = true;
			this->CheckBoxClusters->Location = System::Drawing::Point(181, 352);
			this->CheckBoxClusters->Name = L"CheckBoxClusters";
			this->CheckBoxClusters->Size = System::Drawing::Size(196, 21);
			this->CheckBoxClusters->TabIndex = 0;
			this->CheckBoxClusters->Text = L"Отображать сегменты";
			this->CheckBoxClusters->UseVisualStyleBackColor = true;
			this->CheckBoxClusters->Click += gcnew System::EventHandler(this, &ClusterizationForm::CheckBoxClusters_Click);
			this->CheckBoxClusters->CheckedChanged += gcnew System::EventHandler(this, &ClusterizationForm::CheckBoxClusters_CheckedChanged);
			// 
			// TrackBar_Layers
			// 
			this->TrackBar_Layers->Location = System::Drawing::Point(209, 120);
			this->TrackBar_Layers->Name = L"TrackBar_Layers";
			this->TrackBar_Layers->Size = System::Drawing::Size(311, 56);
			this->TrackBar_Layers->TabIndex = 8;
			this->TrackBar_Layers->ValueChanged += gcnew System::EventHandler(this, &ClusterizationForm::TrackBar_Layers_ValueChanged);
			// 
			// Label_BrightnessMult
			// 
			this->Label_BrightnessMult->AutoSize = true;
			this->Label_BrightnessMult->Location = System::Drawing::Point(13, 302);
			this->Label_BrightnessMult->Name = L"Label_BrightnessMult";
			this->Label_BrightnessMult->Size = System::Drawing::Size(161, 17);
			this->Label_BrightnessMult->TabIndex = 9;
			this->Label_BrightnessMult->Text = L"Множитель яркости:";
			// 
			// TextBox_BrightnessMult
			// 
			this->TextBox_BrightnessMult->Location = System::Drawing::Point(176, 300);
			this->TextBox_BrightnessMult->Name = L"TextBox_BrightnessMult";
			this->TextBox_BrightnessMult->Size = System::Drawing::Size(56, 22);
			this->TextBox_BrightnessMult->TabIndex = 10;
			this->TextBox_BrightnessMult->TextChanged += gcnew System::EventHandler(this, &ClusterizationForm::TextBox_BrightnessMult_TextChanged);
			// 
			// CheckBox_Transparency
			// 
			this->CheckBox_Transparency->AutoSize = true;
			this->CheckBox_Transparency->Location = System::Drawing::Point(248, 301);
			this->CheckBox_Transparency->Name = L"CheckBox_Transparency";
			this->CheckBox_Transparency->Size = System::Drawing::Size(136, 21);
			this->CheckBox_Transparency->TabIndex = 11;
			this->CheckBox_Transparency->Text = L"Прозрачность";
			this->CheckBox_Transparency->UseVisualStyleBackColor = true;
			this->CheckBox_Transparency->CheckedChanged += gcnew System::EventHandler(this, &ClusterizationForm::CheckBox_Transparency_CheckedChanged);
			// 
			// CheckBox_DepthTest
			// 
			this->CheckBox_DepthTest->AutoSize = true;
			this->CheckBox_DepthTest->Location = System::Drawing::Point(390, 301);
			this->CheckBox_DepthTest->Name = L"CheckBox_DepthTest";
			this->CheckBox_DepthTest->Size = System::Drawing::Size(131, 21);
			this->CheckBox_DepthTest->TabIndex = 12;
			this->CheckBox_DepthTest->Text = L"Тест глубины";
			this->CheckBox_DepthTest->UseVisualStyleBackColor = true;
			// 
			// Label_StartLayer
			// 
			this->Label_StartLayer->AutoSize = true;
			this->Label_StartLayer->Location = System::Drawing::Point(56, 191);
			this->Label_StartLayer->Name = L"Label_StartLayer";
			this->Label_StartLayer->Size = System::Drawing::Size(137, 17);
			this->Label_StartLayer->TabIndex = 13;
			this->Label_StartLayer->Text = L"Начальный слой:";
			// 
			// Label_FinishLayer
			// 
			this->Label_FinishLayer->AutoSize = true;
			this->Label_FinishLayer->Location = System::Drawing::Point(268, 191);
			this->Label_FinishLayer->Name = L"Label_FinishLayer";
			this->Label_FinishLayer->Size = System::Drawing::Size(128, 17);
			this->Label_FinishLayer->TabIndex = 14;
			this->Label_FinishLayer->Text = L"Конечный слой:";
			// 
			// NumericUpDown_Start
			// 
			this->NumericUpDown_Start->Location = System::Drawing::Point(196, 189);
			this->NumericUpDown_Start->Name = L"NumericUpDown_Start";
			this->NumericUpDown_Start->Size = System::Drawing::Size(42, 22);
			this->NumericUpDown_Start->TabIndex = 15;
			this->NumericUpDown_Start->ValueChanged += gcnew System::EventHandler(this, &ClusterizationForm::NumericUpDown_Start_ValueChanged);
			// 
			// NumericUpDown_Finish
			// 
			this->NumericUpDown_Finish->Location = System::Drawing::Point(398, 189);
			this->NumericUpDown_Finish->Name = L"NumericUpDown_Finish";
			this->NumericUpDown_Finish->Size = System::Drawing::Size(40, 22);
			this->NumericUpDown_Finish->TabIndex = 16;
			this->NumericUpDown_Finish->ValueChanged += gcnew System::EventHandler(this, &ClusterizationForm::NumericUpDown_Finish_ValueChanged);
			// 
			// TrackBar_LayersDistance
			// 
			this->TrackBar_LayersDistance->Location = System::Drawing::Point(250, 231);
			this->TrackBar_LayersDistance->Maximum = 100;
			this->TrackBar_LayersDistance->Minimum = 1;
			this->TrackBar_LayersDistance->Name = L"TrackBar_LayersDistance";
			this->TrackBar_LayersDistance->Size = System::Drawing::Size(274, 56);
			this->TrackBar_LayersDistance->TabIndex = 17;
			this->TrackBar_LayersDistance->Value = 1;
			this->TrackBar_LayersDistance->ValueChanged += gcnew System::EventHandler(this, &ClusterizationForm::TrackBar_LayersDistance_ValueChanged);
			// 
			// Label_LayersDistance
			// 
			this->Label_LayersDistance->AutoSize = true;
			this->Label_LayersDistance->Location = System::Drawing::Point(16, 240);
			this->Label_LayersDistance->Name = L"Label_LayersDistance";
			this->Label_LayersDistance->Size = System::Drawing::Size(211, 17);
			this->Label_LayersDistance->TabIndex = 18;
			this->Label_LayersDistance->Text = L"Расстояние между слоями:";
			// 
			// GroupBoxVisualization
			// 
			this->GroupBoxVisualization->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->GroupBoxVisualization->BackColor = System::Drawing::Color::Snow;
			this->GroupBoxVisualization->Controls->Add(this->Label_LayersDistance);
			this->GroupBoxVisualization->Controls->Add(this->TrackBar_LayersDistance);
			this->GroupBoxVisualization->Controls->Add(this->NumericUpDown_Finish);
			this->GroupBoxVisualization->Controls->Add(this->NumericUpDown_Start);
			this->GroupBoxVisualization->Controls->Add(this->Label_FinishLayer);
			this->GroupBoxVisualization->Controls->Add(this->Label_StartLayer);
			this->GroupBoxVisualization->Controls->Add(this->CheckBox_DepthTest);
			this->GroupBoxVisualization->Controls->Add(this->CheckBox_Transparency);
			this->GroupBoxVisualization->Controls->Add(this->TextBox_BrightnessMult);
			this->GroupBoxVisualization->Controls->Add(this->Label_BrightnessMult);
			this->GroupBoxVisualization->Controls->Add(this->GroupBoxDim);
			this->GroupBoxVisualization->Controls->Add(this->TrackBar_Layers);
			this->GroupBoxVisualization->Controls->Add(this->CheckBoxClusters);
			this->GroupBoxVisualization->Controls->Add(this->Label_LayerInfo);
			this->GroupBoxVisualization->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->GroupBoxVisualization->Location = System::Drawing::Point(585, 38);
			this->GroupBoxVisualization->Name = L"GroupBoxVisualization";
			this->GroupBoxVisualization->Size = System::Drawing::Size(533, 382);
			this->GroupBoxVisualization->TabIndex = 2;
			this->GroupBoxVisualization->TabStop = false;
			this->GroupBoxVisualization->Text = L"Настройки визуализации";
			// 
			// GroupBoxDim
			// 
			this->GroupBoxDim->BackColor = System::Drawing::Color::Snow;
			this->GroupBoxDim->Controls->Add(this->RadioButton_2D);
			this->GroupBoxDim->Controls->Add(this->RadioButton_3D);
			this->GroupBoxDim->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->GroupBoxDim->Location = System::Drawing::Point(65, 33);
			this->GroupBoxDim->Name = L"GroupBoxDim";
			this->GroupBoxDim->Size = System::Drawing::Size(411, 74);
			this->GroupBoxDim->TabIndex = 1;
			this->GroupBoxDim->TabStop = false;
			this->GroupBoxDim->Text = L"Режим сегментации и визуализации данных";
			// 
			// RadioButton_2D
			// 
			this->RadioButton_2D->AutoSize = true;
			this->RadioButton_2D->Checked = true;
			this->RadioButton_2D->Location = System::Drawing::Point(3, 34);
			this->RadioButton_2D->Name = L"RadioButton_2D";
			this->RadioButton_2D->Size = System::Drawing::Size(187, 21);
			this->RadioButton_2D->TabIndex = 1;
			this->RadioButton_2D->TabStop = true;
			this->RadioButton_2D->Text = L"По одному слою (2D)";
			this->RadioButton_2D->UseVisualStyleBackColor = true;
			this->RadioButton_2D->Click += gcnew System::EventHandler(this, &ClusterizationForm::RadioButton_2D_Click);
			// 
			// RadioButton_3D
			// 
			this->RadioButton_3D->AutoSize = true;
			this->RadioButton_3D->Location = System::Drawing::Point(215, 35);
			this->RadioButton_3D->Name = L"RadioButton_3D";
			this->RadioButton_3D->Size = System::Drawing::Size(193, 21);
			this->RadioButton_3D->TabIndex = 0;
			this->RadioButton_3D->Text = L"Несколько слоёв (3D)";
			this->RadioButton_3D->UseVisualStyleBackColor = true;
			this->RadioButton_3D->Click += gcnew System::EventHandler(this, &ClusterizationForm::RadioButton_3D_Click);
			// 
			// ClusterizationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(120, 120);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->ClientSize = System::Drawing::Size(1128, 853);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->Button_VisualizeSelectedClusters);
			this->Controls->Add(this->Button_Clusterization);
			this->Controls->Add(this->ProgressBar_Layers);
			this->Controls->Add(this->ProgressBar_Iterations);
			this->Controls->Add(this->Label_Status);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->RenderingPanel);
			this->Controls->Add(this->GroupBoxVisualization);
			this->Controls->Add(this->MenuStrip);
			this->MainMenuStrip = this->MenuStrip;
			this->Name = L"ClusterizationForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Сегментация методом k-средних";
			this->Load += gcnew System::EventHandler(this, &ClusterizationForm::ClusterizationForm_Load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ClusterizationForm::ClusterizationForm_FormClosing);
			this->Resize += gcnew System::EventHandler(this, &ClusterizationForm::ClusterizationForm_Resize);
			this->MenuStrip->ResumeLayout(false);
			this->MenuStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_ClustersCount))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_IterationsCount))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DataGridView_Clusters))->EndInit();
			this->groupBox2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_Layers))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NumericUpDown_Start))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NumericUpDown_Finish))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_LayersDistance))->EndInit();
			this->GroupBoxVisualization->ResumeLayout(false);
			this->GroupBoxVisualization->PerformLayout();
			this->GroupBoxDim->ResumeLayout(false);
			this->GroupBoxDim->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::String^ GetStringOfColor(TColor Color)
				 {
					 return L"Color[R = "+((unsigned char)(Color.R*255)).ToString()+L", "+
						          L"G = "+((unsigned char)(Color.G*255)).ToString()+L", "+
								  L"B = "+((unsigned char)(Color.B*255)).ToString()+L"]";
				 }

		private: System::UInt32 MinDensityOfSegment_2D(size_t LayerIndex, size_t SegmentIndex)
			 {
			  UInt32 result = UInt32::MaxValue;
			  vector <size_t>::iterator iter = Segments_2D[LayerIndex].at(SegmentIndex).Index.begin();
			  vector <size_t>::iterator _end = Segments_2D[LayerIndex].at(SegmentIndex).Index.end();
			  for (; iter!=_end; ++iter)
			  if ((UInt32)InputData->data[*iter+LayerIndex*InputData->sizeX*InputData->sizeY]<result)
			  result = InputData->data[*iter+LayerIndex*InputData->sizeX*InputData->sizeY];
			  
			  return result;
			 }

	 private: System::UInt32 MaxDensityOfSegment_2D(size_t LayerIndex, size_t SegmentIndex)
			  {
			   UInt32 result = 0;
			   vector <size_t>::iterator iter = Segments_2D[LayerIndex].at(SegmentIndex).Index.begin();
			   vector <size_t>::iterator _end = Segments_2D[LayerIndex].at(SegmentIndex).Index.end();
			   for (; iter!=_end; ++iter)
			   if ((UInt32)InputData->data[*iter+LayerIndex*InputData->sizeX*InputData->sizeY]>result)
			   result = InputData->data[*iter+LayerIndex*InputData->sizeX*InputData->sizeY];
			  
			   return result;
			  }

   private: System::UInt32 MinDensityOfSegment_3D(size_t StartLayerIndex, size_t SegmentIndex)
			{
			  UInt32 result = UInt32::MaxValue;
			  vector <size_t>::iterator iter = Segments_3D->at(SegmentIndex).Index.begin();
			  vector <size_t>::iterator _end = Segments_3D->at(SegmentIndex).Index.end();
			  for (; iter!=_end; ++iter)
			  if ((UInt32)InputData->data[*iter+StartLayerIndex*InputData->sizeX*InputData->sizeY]<result)
			  result = InputData->data[*iter+StartLayerIndex*InputData->sizeX*InputData->sizeY];
			  
			  return result;
			}

	private: System::UInt32 MaxDensityOfSegment_3D(size_t StartLayerIndex, size_t SegmentIndex)
			 {
			  UInt32 result = 0;
			  vector <size_t>::iterator iter = Segments_3D->at(SegmentIndex).Index.begin();
			  vector <size_t>::iterator _end = Segments_3D->at(SegmentIndex).Index.end();
			  for (; iter!=_end; ++iter)
			  if ((UInt32)InputData->data[*iter+StartLayerIndex*InputData->sizeX*InputData->sizeY]>result)
			  result = InputData->data[*iter+StartLayerIndex*InputData->sizeX*InputData->sizeY];
			  
			  return result;
			 }

	private: System::Void DrawGLScene() 
			 {
              glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
              glLoadIdentity();

              glTranslatef(0.0f, 0.0f, -distance);
              //glTranslatef(0.0f, 0.0f, -3.0f);
              glRotatef(90.0f, 0.0f, 0.0, 1.0f);
              glRotatef(angleXRotation, 1.0f, 0.0f, 0.0f);
              glRotatef(angleYRotation, 0.0f, 1.0f, 0.0f);
              
			  if (this->CheckBox_Transparency->Checked) 
			  {
               glEnable(GL_BLEND);
               if (CheckBox_DepthTest->Checked) 
			   {
                glDisable(GL_DEPTH_TEST);
               }
              }
				  
				  //RenderLayer(this->TrackBar_Layers->Value);
				  
				  if (InputData && InputData->data) 
				   {
					if (this->RadioButton_3D->Checked)
					{
					 float localDepth = -((float)(NumericUpDown_Finish->Value-NumericUpDown_Start->Value) * InputData->scaleZ * this->TrackBar_LayersDistance->Value / 2.0f);
					 float width = (float)(InputData->sizeX / 2) * InputData->scaleX;
                     float height = (float)(InputData->sizeY / 2) * InputData->scaleY;
                         
					 for (size_t iLayer = (size_t)NumericUpDown_Start->Value; iLayer < NumericUpDown_Finish->Value + 1; ++iLayer) 
				     {
					  glTranslatef(0.0f, 0.0f, -localDepth * 2 / ((size_t)(NumericUpDown_Finish->Value - NumericUpDown_Start->Value + 1)));
                      glBindTexture(GL_TEXTURE_2D, layerTextures[iLayer]);
                      glBegin(GL_QUADS); 
				      {
                       glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height, localDepth);
                       glTexCoord2f(1.0f, 0.0f); glVertex3f( width, -height, localDepth);
                       glTexCoord2f(0.0f, 0.0f); glVertex3f( width,  height, localDepth);
                       glTexCoord2f(0.0f, 1.0f); glVertex3f(-width,  height, localDepth);
				      }   
				      glEnd();
				     }

					 glBindTexture(GL_TEXTURE_2D, 0);
					} else

				    if (this->RadioButton_2D->Checked)
				    {
				     // визуализация по слоям
					 float width = (float)(InputData->sizeX / 2) * InputData->scaleX;
                     float height = (float)(InputData->sizeY / 2) * InputData->scaleY;
					 glTranslatef(0.0f, 0.0f, 0.0f);
					 glBindTexture(GL_TEXTURE_2D, layerTextures[this->TrackBar_Layers->Value]);
					 glBegin(GL_QUADS);
					 {
					  glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height, 0.0f);
					  glTexCoord2f(1.0f, 0.0f); glVertex3f( width, -height, 0.0f);
                      glTexCoord2f(0.0f, 0.0f); glVertex3f( width,  height, 0.0f);
                      glTexCoord2f(0.0f, 1.0f); glVertex3f(-width,  height, 0.0f);
					 }
					 glEnd();

					 glBindTexture(GL_TEXTURE_2D, 0);
                   
				    } 
					  
                   }
				  
				  if (CheckBox_Transparency->Checked) 
				  {
                   glDisable(GL_BLEND);
                   if (CheckBox_DepthTest->Checked) 
				   {
                    glEnable(GL_DEPTH_TEST);
                   }
                  }
				  
					

				  
				  
              }

	private: System::Void RenderLayer(size_t z) 
			 {
			  /* glScalef(InputData->scaleX, InputData->scaleY, InputData->scaleZ);
              glTranslatef(0.0f, 0.0f, ((float)(InputData->sizeZ / 2) - z) * InputData->scaleZ);
              glPushMatrix();
              for (size_t iColumn = 0; iColumn < InputData->sizeX; ++iColumn) 
			  {
               glPushMatrix();
               glTranslatef(((float)(InputData->sizeX / 2) - iColumn) * InputData->scaleX, 0.0f, 0.0f);
               for (size_t iRow = 0; iRow < InputData->sizeY; ++iRow) 
			   {
                glPushMatrix();
                glTranslatef(0.0f, ((float)(InputData->sizeY / 2) - iRow) * InputData->scaleY, 0.0f);
				float grayIntense = (float)(InputData->GetDensity(iRow, iColumn, z))/ MaxDensity;
                grayIntense *= BrightnessMult;
				size_t reducedIndex = iRow+InputData->sizeX*iColumn+InputData->sizeX*InputData->sizeY*z;
				if (this->CheckBoxClusters->Checked) 
				{
				 if (this->IsVoxelVisible[reducedIndex])
				 glColor3f(VoxelColor[reducedIndex].R, VoxelColor[reducedIndex].G, VoxelColor[reducedIndex].B);
				 else glColor3f(0.0f, 0.0f, 0.0f);
				}
				else glColor3f(grayIntense, grayIntense, grayIntense);
                glCallList(theBox);
                glPopMatrix();
               }
			   
               glPopMatrix();
              }
              glPopMatrix(); */
             }

	private: System::Void ClusterizationForm_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
			  GLuint PixelFormat;

			  hWnd = (HWND)(intptr_t)this->RenderingPanel->Handle;
                 hDC = GetDC(hWnd);
                 if (!hDC) {
                     this->Label_Status->Text = L"Can't Create A GL Device Context";
                     return;
                 }

                 BYTE colorBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
                 static PIXELFORMATDESCRIPTOR pfd= {            // pfd Tells Windows How We Want Things To Be
                     sizeof(PIXELFORMATDESCRIPTOR),                // Size Of This Pixel Format Descriptor
                     1,                                            // Version Number
                     PFD_DRAW_TO_WINDOW |                          // Format Must Support Window
                     PFD_SUPPORT_OPENGL |                          // Format Must Support OpenGL
                     PFD_DOUBLEBUFFER,                             // Must Support Double Buffering
                     PFD_TYPE_RGBA,                                // Request An RGBA Format
                     colorBits,                                    // Select Our Color Depth
                     0, 0, 0, 0, 0, 0,                             // Color Bits Ignored
                     0,                                            // No Alpha Buffer
                     0,                                            // Shift Bit Ignored
                     0,                                            // No Accumulation Buffer
                     0, 0, 0, 0,                                   // Accumulation Bits Ignored
                     24,                                           // 24Bit Z-Buffer (Depth Buffer)  
                     0,                                            // No Stencil Buffer
                     0,                                            // No Auxiliary Buffer
                     PFD_MAIN_PLANE,                               // Main Drawing Layer
                     0,                                            // Reserved
                     0, 0, 0                                       // Layer Masks Ignored
                 };

                 LoadLibrary(L"opengl32.dll");
                 PixelFormat = ChoosePixelFormat(hDC, &pfd);
                 if (!PixelFormat) {
                     this->Label_Status->Text = L"Can't Find A Suitable PixelFormat.";
                     return;
                 }
                 if (!SetPixelFormat(hDC, PixelFormat, &pfd)) {
                     this->Label_Status->Text = L"Can't Set The PixelFormat.";
                     return;
                 }
                 hRC = wglCreateContext(hDC);
                 if (!hRC) {
                     this->Label_Status->Text = L"Can't Create A GL Rendering Context. GetLastError: " + GetLastError();
                     return;
                 }
                 if (!wglMakeCurrent(hDC, hRC)) {
                     this->Label_Status->Text = L"Can't Activate The GL Rendering Context.";
                     return;
                 }
                 this->Label_Status->Text = L"GL context created!";

                 ClusterizationForm_Resize(sender, e);

                 if (!ClusterizationInitGL()) {
                     this->Label_Status->Text = L"Failed to init GL";
                 }

                 depth = 10.0f;
                 theBox = glGenLists(1);
                 glNewList(theBox, GL_COMPILE);
                 glBegin(GL_QUADS); {
                     // front face
                     //glNormal3f(0.0f, 0.0f, 1.0f);
                     glVertex3f(0.5f, 0.5f, 0.5f * depth);
                     glVertex3f(0.5f, -0.5f, 0.5f * depth);
                     glVertex3f(-0.5f, -0.5f, 0.5f * depth);
                     glVertex3f(-0.5f, 0.5f, 0.5f * depth);

                     // left face
                     //glNormal3f(-1.0f, 0.0f, 0.0f);
                     glVertex3f(-0.5f, 0.5f, 0.5f * depth);
                     glVertex3f(-0.5f, -0.5f, 0.5f * depth);
                     glVertex3f(-0.5f, -0.5f, -0.5f * depth);
                     glVertex3f(-0.5f, 0.5f, -0.5f * depth);

                     // back face
                     //glNormal3f(0.0f, 0.0f, -1.0f);
                     glVertex3f(-0.5f, 0.5f, -0.5f * depth);
                     glVertex3f(-0.5f, -0.5f, -0.5f * depth);
                     glVertex3f(0.5f, -0.5f, -0.5f * depth);
                     glVertex3f(0.5f, 0.5f, -0.5f * depth);

                     // right face
                     //glNormal3f(1.0f, 0.0f, 0.0f);
                     glVertex3f(0.5f, 0.5f, -0.5f * depth);
                     glVertex3f(0.5f, -0.5f, -0.5f * depth);
                     glVertex3f(0.5f, -0.5f, 0.5f * depth);
                     glVertex3f(0.5f, 0.5f, 0.5f * depth);

                     // top face
                     //glNormal3f(0.0f, 1.0f, 0.0f);
                     glVertex3f(-0.5f, 0.5f, -0.5f * depth);
                     glVertex3f(0.5f, 0.5f, -0.5f * depth);
                     glVertex3f(0.5f, 0.5f, 0.5f * depth);
                     glVertex3f(-0.5f, 0.5f, 0.5f * depth);

                     // bottom face
                     //glNormal3f(0.0f, -1.0f, 0.0f);
                     glVertex3f(-0.5f, -0.5f, 0.5f * depth);
                     glVertex3f(0.5f, -0.5f, 0.5f * depth);
                     glVertex3f(0.5f, -0.5f, -0.5f * depth);
                     glVertex3f(-0.5f, -0.5f, -0.5f * depth);
                 }
                 glEnd();
                 glEndList();

				 this->TrackBar_Layers->Enabled = false;
				 this->NumericUpDown_Start->Enabled = false;
				 this->NumericUpDown_Finish->Enabled = false;
				 this->TextBox_BrightnessMult->Enabled = false;
				 this->Button_Clusterization->Enabled = false;
				 this->DataGridView_Clusters->Enabled = false;
				 this->Button_VisualizeSelectedClusters->Enabled = false;
				 
				 this->Label_LayersDistance->Text = L"Расстояние между слоями: "+this->TrackBar_LayersDistance->Value.ToString();

				 this->Label_ClustersCount->Text = L"Максимальное число сегментов: "+this->TrackBar_ClustersCount->Value.ToString();
				 this->Label_IterationsCount->Text = L"Количество итераций алгоритма: "+this->TrackBar_IterationsCount->Value.ToString();
				 				 
                 InputData = new ScanData();
				 				 
				 Segments_2D = NULL; Segments_3D = NULL; VoxelsData = NULL;

				 //this->VoxelColor = NULL; this->IsVoxelVisible = NULL;
				 
				 layerTextures = 0;
			 }
	private: System::Void ToolStripMenuItem_Download_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
			  if (this->OpenDataDialog->ShowDialog() == Windows::Forms::DialogResult::OK) 
			  {
               String ^pathToDataFile = OpenDataDialog->FileName;
               if (System::IO::File::Exists(pathToDataFile)) 
			   {
               pathToDataFile = pathToDataFile->Replace("\\","\\\\");
               if (InputData->LoadData((char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(pathToDataFile).ToPointer())) 
			   {
               this->Label_Status->Text = L"Данные из bin-файла загружены."; 

			   this->Label_LayerInfo->Text = L"Номер текущего слоя: "+this->TrackBar_Layers->Value.ToString();

               float fileSize = (float)(IO::FileInfo(pathToDataFile).Length >> 20);
                
			   VoxelsData = new TVoxel [InputData->TotalSize];

			   MaxDensity = 0;

			   for (size_t i = 0; i < InputData->TotalSize; ++i) 
			   {
			    VoxelsData[i].Color_2D = VoxelsData[i].Color_3D = TColor(0.0f, 0.0f, 0.0f, 0.0f);

				VoxelsData[i].IsVisible_2D = VoxelsData[i].IsVisible_3D = true;

                if (MaxDensity < InputData->data[i]) MaxDensity = InputData->data[i];
			   }

			   ProgressBar_Layers->Maximum = InputData->sizeZ;
			   TrackBar_Layers->Maximum = InputData->sizeZ-1;
			   TrackBar_Layers->Value = 0;
			   NumericUpDown_Start->Maximum = InputData->sizeZ-1;
			   NumericUpDown_Start->Value = 0;
			   NumericUpDown_Finish->Maximum = InputData->sizeZ-1;
			   NumericUpDown_Finish->Value = InputData->sizeZ-1;

			   this->Button_VisualizeSelectedClusters->Enabled = false;

			   if (this->RadioButton_2D->Checked)
			   {
				this->TrackBar_Layers->Enabled = true;
			   }

			   if (this->RadioButton_3D->Checked)
			   {
			    this->NumericUpDown_Start->Enabled = true;
			    this->NumericUpDown_Finish->Enabled = true;
			   }
					
			   this->TextBox_BrightnessMult->Enabled = true;

			   this->Button_Clusterization->Enabled = true;

			   angleXRotation = angleYRotation = 0.0f;
               distance = 600.f;

			   TextBox_BrightnessMult->Text = L"30,0";
               BrightnessMult = 30.f;

			   GenerateTextures();
                    
			  }

			 } else {
                     this->Label_Status->Text = "Ошибка! Некорректное чтение файла.";
                 }
			  } else {
                  this->Label_Status->Text = "Ошибка! Файл не найден.";
             } 

			 }

// Формирование текстур для рендеринга			
private: System::Void GenerateTextures()
		 {
		  ReleaseTextures();

          layerTextures = new GLuint[InputData->sizeZ];
          glGenTextures(InputData->sizeZ, layerTextures);

		  float *tmp = new float[4 * InputData->sizeX * InputData->sizeY];

          for (size_t iLayer = 0; iLayer < InputData->sizeZ; ++iLayer) 
		  {
           for (size_t i = 0; i < InputData->sizeX * InputData->sizeY * 4; i += 4) 
		   {
			size_t reducedIndex = i / 4 + iLayer * InputData->sizeX * InputData->sizeY;
            if (CheckBoxClusters->Checked)			// если сегменты отображаются 
			{
			 if (this->RadioButton_2D->Checked && VoxelsData[reducedIndex].IsVisible_2D)
			 {
			  tmp[i] = VoxelsData[reducedIndex].Color_2D.R;
			  tmp[i+1] = VoxelsData[reducedIndex].Color_2D.G;
			  tmp[i+2] = VoxelsData[reducedIndex].Color_2D.B;
			  tmp[i+3] = VoxelsData[reducedIndex].Color_2D.A; //= 0.30f*tmp[i]+0.59f*tmp[i+1]+0.11f*tmp[i+2];
			 }
			 else if (this->RadioButton_3D->Checked && VoxelsData[reducedIndex].IsVisible_3D)
			 {
			  tmp[i] = VoxelsData[reducedIndex].Color_3D.R;
			  tmp[i+1] = VoxelsData[reducedIndex].Color_3D.G;
			  tmp[i+2] = VoxelsData[reducedIndex].Color_3D.B;
			  tmp[i+3] = VoxelsData[reducedIndex].Color_3D.A; //= 0.30f*tmp[i]+0.59f*tmp[i+1]+0.11f*tmp[i+2];
			 }
			 else tmp[i+3] = tmp[i+2] = tmp[i+1] = tmp[i] = 0.0f;
			}
			else tmp[i+3] = tmp[i+2] = tmp[i+1] = tmp[i] = InputData->data[reducedIndex] * BrightnessMult / MaxDensity;
            //tmp[i + 1] = tmp[i]; 
           }

           glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
           glBindTexture(GL_TEXTURE_2D, layerTextures[iLayer]);

           glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP);
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

           //glTexImage2D(GL_TEXTURE_2D, 0, 1, InputData->sizeX, InputData->sizeY, 0, GL_INTENSITY, GL_SHORT, InputData->data + iLayer * InputData->sizeX * InputData->sizeY * sizeof(short)); // не работает, сцуко! :(
           glTexImage2D(GL_TEXTURE_2D, 0, 4/*GL_LUMINANCE_ALPHA*/, InputData->sizeX, InputData->sizeY, 0, GL_RGBA, GL_FLOAT, tmp);
		  }

          delete tmp;
		 }

private: System::Void ToolStripMenuItem_Exit_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 Close();
		 }
private: System::Void RenderTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
			 //GenerateTextures();
			 DrawGLScene();
			 SwapBuffers(hDC);
		 }
private: System::Void ClusterizationForm_Resize(System::Object^  sender, System::EventArgs^  e) {
			 GLsizei height = this->RenderingPanel->Height;
                 GLsizei width = this->RenderingPanel->Width;
                 if (height == 0) {
                     height = 1;
                 }

                 glViewport(0, 0, width, height);

                 glMatrixMode(GL_PROJECTION);
                 glLoadIdentity();

                 gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);

                 glMatrixMode(GL_MODELVIEW);
                 glLoadIdentity();

                 DrawGLScene();
                 SwapBuffers(hDC);

		 }
private: System::Void TrackBar_Layers_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
		  this->Label_LayerInfo->Text = L"Номер текущего слоя: "+this->TrackBar_Layers->Value.ToString();
			 
		  if (this->RadioButton_2D->Checked && Segments_2D)
		  {
		   size_t z  = this->TrackBar_Layers->Value;

		   this->DataGridView_Clusters->RowCount = Segments_2D[z].size()+1;
		   for (size_t index = 0; index < Segments_2D[z].size(); ++index)
		   {
		    this->DataGridView_Clusters->Rows[index]->Cells[0]->Value = index.ToString();
		    this->DataGridView_Clusters->Rows[index]->Cells[1]->Value = Segments_2D[z].at(index).Index.size().ToString();
		    this->DataGridView_Clusters->Rows[index]->Cells[2]->Value = Segments_2D[z].at(index).MinDensity.ToString();
		    this->DataGridView_Clusters->Rows[index]->Cells[3]->Value = Segments_2D[z].at(index).MaxDensity.ToString();
		    this->DataGridView_Clusters->Rows[index]->Cells[4]->Value = this->GetStringOfColor(Segments_2D[z].at(index).Color);
		    this->DataGridView_Clusters->Rows[index]->Cells[5]->Value = Segments_2D[z].at(index).transparensy.ToString();
		    this->DataGridView_Clusters->Rows[index]->Cells[6]->Value = Segments_2D[z].at(index).IsVisible;
		   }
    	  }  
		 }
private: System::Void CheckBoxClusters_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (this->RadioButton_2D->Checked && Segments_2D || this->RadioButton_3D->Checked && Segments_3D)
			 {
			  DataGridView_Clusters->Enabled = CheckBoxClusters->Checked;
			 
		      Button_VisualizeSelectedClusters->Enabled = CheckBoxClusters->Checked;
			 }

		 }
private: System::Void Button_Clusterization_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
		  this->StaticDelInst_Visible_2D = gcnew MyVisibleDelegate(this, &ClusterizationForm::ChangeVisible_2D);
		  this->StaticDelInst_Visible_3D = gcnew MyVisibleDelegate(this, &ClusterizationForm::ChangeVisible_3D);
		  this->StaticDelInst_Color_2D = gcnew MyColorDelegate(this, &ClusterizationForm::ChangeVoxelColor_2D);
		  this->StaticDelInst_Color_3D = gcnew MyColorDelegate(this, &ClusterizationForm::ChangeVoxelColor_3D);

		  if (RadioButton_2D->Checked)					// если кластеризация по слоям
		  {
		   this->ProgressBar_Layers->Value = 0;

		   Segments_2D = NULL; 
		   
		   //VoxelColor = NULL; 

		   //NClusters = new size_t [InputData->sizeZ];

		   Segments_2D = new vector <TSegment> [InputData->sizeZ];

		   //VoxelColor = new TColor [InputData->TotalSize]; 

		   //IsVoxelVisible = new bool [TotalSize];

		   for (size_t index = 0; index<InputData->TotalSize; ++index) VoxelsData[index].IsVisible_2D = true;
				   
		   for (size_t z = 0; z < InputData->sizeZ; ++z)
		   {
		    ClusterizationMethod = new KmeansMethod(InputData->GetLayer(z));
		    ClusterizationMethod->SetClustersNumber(TrackBar_ClustersCount->Value);
		    ClusterizationMethod->SetCountIterations(TrackBar_IterationsCount->Value);
			
			Label_Status->Text = L"Выполняется кластеризация данных. Пожалуйста, подождите...";
						 
			vector <vector <size_t> > TmpIndexVector = ClusterizationMethod->GetClusters(this->BackgroundWorker);

			size_t NumberOfSegments = TmpIndexVector.size();

 		    for (size_t i = 0; i < NumberOfSegments; ++i)
		    {
    		 vector <size_t> segment_indexes = TmpIndexVector.at(i);

			 Segments_2D[z].push_back(TSegment(segment_indexes));		// сохранение нового сегмента

			 Segments_2D[z].at(i).MinDensity = MinDensityOfSegment_2D(z, i);
			 Segments_2D[z].at(i).MaxDensity = MaxDensityOfSegment_2D(z, i);
			 
			 float grayIntensity = (float)(i+1)/NumberOfSegments;		// вычисление интенсивности каждого воксела из сегмента

			 Segments_2D[z].at(i).Color = TColor(grayIntensity, grayIntensity, grayIntensity, grayIntensity);

			 Segments_2D[z].at(i).transparensy = (unsigned char)(255*grayIntensity);

			 Segments_2D[z].at(i).IsVisible = true;
		     
			 vector<size_t>::iterator iter = segment_indexes.begin();
			 vector<size_t>::iterator _end = segment_indexes.end();
			 for (; iter!=_end; ++iter) 
			 {
		  	  VoxelsData[*iter+z*InputData->sizeX*InputData->sizeY].Color_2D = TColor(grayIntensity, grayIntensity, grayIntensity, grayIntensity);
     		 }
		    }

			// Отображаем ход выполнения процесса
			this->ProgressBar_Layers->Value++;
			
		   }
		   
		   Label_Status->Text = L"Данные кластеризованы.";

		   size_t z = this->TrackBar_Layers->Value;

		   this->DataGridView_Clusters->RowCount = Segments_2D[z].size()+1;

		   //вставка в таблицу информации о кластерах для текущего слоя
		   for (size_t index = 0; index < Segments_2D[z].size(); ++index)
		   {
			this->DataGridView_Clusters->Rows[index]->Cells[0]->Value = index.ToString();
			this->DataGridView_Clusters->Rows[index]->Cells[1]->Value = Segments_2D[z].at(index).Index.size().ToString();
			this->DataGridView_Clusters->Rows[index]->Cells[2]->Value = Segments_2D[z].at(index).MinDensity.ToString();
			this->DataGridView_Clusters->Rows[index]->Cells[3]->Value = Segments_2D[z].at(index).MaxDensity.ToString();
			this->DataGridView_Clusters->Rows[index]->Cells[4]->Value = this->GetStringOfColor(Segments_2D[z].at(index).Color);
			this->DataGridView_Clusters->Rows[index]->Cells[5]->Value = Segments_2D[z].at(index).transparensy.ToString();
			this->DataGridView_Clusters->Rows[index]->Cells[6]->Value = Segments_2D[z].at(index).IsVisible;
		   }

		  }

		  if (this->RadioButton_3D->Checked)				// если кластеризация нескольких слоёв как единого целого
		  {
		   this->ProgressBar_Layers->Value = 0;
		   
		   Segments_3D = NULL; 
		   
		   /* NClusters = NULL;
		   NClusters = new size_t [1]; */

		   Segments_3D = new vector <TSegment> [1];

		   for (size_t index = 0; index<InputData->TotalSize; ++index) VoxelsData[index].IsVisible_3D = true;
	
		   ScanData* Data = InputData->GetSubData((size_t)this->NumericUpDown_Start->Value, (size_t)this->NumericUpDown_Finish->Value);

		   this->ClusterizationMethod = new KmeansMethod(Data);

		   ClusterizationMethod->SetClustersNumber(this->TrackBar_ClustersCount->Value);
		   ClusterizationMethod->SetCountIterations(this->TrackBar_IterationsCount->Value);

  		   Label_Status->Text = L"Выполняется кластеризация данных. Пожалуйста, подождите...";

		   vector <vector <size_t> > TmpIndexVector = this->ClusterizationMethod->GetClusters(this->BackgroundWorker);

		   size_t NumberOfSegments = TmpIndexVector.size();

		   for (size_t i = 0; i < NumberOfSegments; ++i)
		   {
			vector <size_t> segment_indexes = TmpIndexVector.at(i);
			
			Segments_3D->push_back(TSegment(segment_indexes));

			Segments_3D->at(i).MinDensity = MinDensityOfSegment_3D((size_t)this->NumericUpDown_Start->Value, i);
			Segments_3D->at(i).MaxDensity = MaxDensityOfSegment_3D((size_t)this->NumericUpDown_Start->Value, i);
			Segments_3D->at(i).IsVisible = true;
			
			float grayIntensity = (float)(i+1)/NumberOfSegments;

			Segments_3D->at(i).Color = TColor(grayIntensity, grayIntensity, grayIntensity, grayIntensity);

			Segments_3D->at(i).transparensy = (unsigned char)(255*grayIntensity);

		    vector<size_t>::iterator iter = segment_indexes.begin();
		    vector<size_t>::iterator _end = segment_indexes.end();
		    for (; iter!=_end; ++iter) 
		    {
			 VoxelsData[*iter+(size_t)this->NumericUpDown_Start->Value*InputData->sizeX*InputData->sizeY].Color_3D = TColor(grayIntensity, grayIntensity, grayIntensity, grayIntensity);
			 // управление видимостью воксела
			}
		   }

		   this->ProgressBar_Layers->Value = this->ProgressBar_Layers->Maximum;

		   Label_Status->Text = L"Данные кластеризованы.";

		   //size_t z = this->TrackBar_Layers->Value;
		   this->DataGridView_Clusters->RowCount = Segments_3D->size()+1;

		   int value = Segments_3D->size();

		   //вставка в таблицу информации о кластерах для текущего слоя
		   for (size_t index = 0; index < Segments_3D->size(); ++index)
		   {
			this->DataGridView_Clusters->Rows[index]->Cells[0]->Value = index.ToString();
			this->DataGridView_Clusters->Rows[index]->Cells[1]->Value = Segments_3D->at(index).Index.size().ToString();
			this->DataGridView_Clusters->Rows[index]->Cells[2]->Value = Segments_3D->at(index).MinDensity.ToString();
			this->DataGridView_Clusters->Rows[index]->Cells[3]->Value = Segments_3D->at(index).MaxDensity.ToString();
			this->DataGridView_Clusters->Rows[index]->Cells[4]->Value = this->GetStringOfColor(Segments_3D->at(index).Color);
			//int value = Segments_3D->size();
			this->DataGridView_Clusters->Rows[index]->Cells[5]->Value =	Segments_3D->at(index).transparensy.ToString(); 

			this->DataGridView_Clusters->Rows[index]->Cells[6]->Value = Segments_3D->at(index).IsVisible;
		   }
		  }

		  GenerateTextures();

		  if (this->CheckBoxClusters->Checked)
			  this->Button_VisualizeSelectedClusters->Enabled = true;
		 }
private: System::Void TrackBar_ClustersCount_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->Label_ClustersCount->Text = L"Максимальное число кластеров: "+
											   this->TrackBar_ClustersCount->Value;
		 }
private: System::Void TrackBar_IterationsCount_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->Label_IterationsCount->Text = L"Количество итераций алгоритма: "+
												 this->TrackBar_IterationsCount->Value;
		 }
private: System::Void BackgroundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) 
		 {
		  
		 }
public: System::Void BackgroundWorker_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) 
		 {
		  this->ProgressBar_Iterations->Value = e->ProgressPercentage;
		  this->Label_Status->Text = (this->ProgressBar_Iterations->Value == this->ProgressBar_Iterations->Maximum) ?
			  L"" : L"Выполняется кластеризация слоя данных, "+
		  (100*this->ProgressBar_Iterations->Value/this->ProgressBar_Iterations->Maximum).ToString()+
		  L"% выполнено";
		 }
private: System::Void BackgroundWorker_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
		 }

private: System::Void Button_VisualizeSelectedClusters_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
		  if (this->RadioButton_2D->Checked)
		  {
		   size_t z = (size_t)this->TrackBar_Layers->Value;

		   for (size_t i = 0; i<Segments_2D[z].size(); ++i)
				
		   {
			Segments_2D[z].at(i).IsVisible = (bool)this->DataGridView_Clusters->Rows[i]->Cells[6]->Value;

			vector<size_t>::iterator iter = Segments_2D[z].at(i).Index.begin();
			vector<size_t>::iterator _end = Segments_2D[z].at(i).Index.end();
			for (; iter!=_end; ++iter)
			{
		 	 if ((bool)this->DataGridView_Clusters->Rows[i]->Cells[6]->Value ==true)
			 this->StaticDelInst_Visible_2D(*iter+z*InputData->sizeX*InputData->sizeY, true);
			 else this->StaticDelInst_Visible_2D(*iter+z*InputData->sizeX*InputData->sizeY, false);
			}
		   }
		  }

		  if (this->RadioButton_3D->Checked)
		  {
		   for (size_t i = 0; i<Segments_3D->size(); ++i)
		   {
			Segments_3D->at(i).IsVisible = (bool)this->DataGridView_Clusters->Rows[i]->Cells[6]->Value;

			vector <size_t>::iterator iter = Segments_3D->at(i).Index.begin();
			vector <size_t>::iterator _end = Segments_3D->at(i).Index.end();
			for (; iter!=_end; ++iter)
			{
			 if (*iter+(size_t)this->NumericUpDown_Start->Value*InputData->sizeX*InputData->sizeY<InputData->TotalSize)
			 this->StaticDelInst_Visible_3D(*iter+(size_t)this->NumericUpDown_Start->Value*InputData->sizeX*InputData->sizeY, (bool)this->DataGridView_Clusters->Rows[i]->Cells[6]->Value);
   			}
		   }
		  }

		  GenerateTextures();
		 }
private: System::Void NumericUpDown_Start_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (this->NumericUpDown_Start->Value > this->NumericUpDown_Finish->Value)
				 this->NumericUpDown_Start->Value = this->NumericUpDown_Finish->Value; 
		 }
private: System::Void NumericUpDown_Finish_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (this->NumericUpDown_Finish->Value < this->NumericUpDown_Finish->Value)
				 this->NumericUpDown_Finish->Value = this->NumericUpDown_Start->Value;
		 }
private: System::Void RenderingPanel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
		  if (e->Button == Windows::Forms::MouseButtons::Left)
		  {
           Point tmpPosition = mousePosition;
           mousePosition = e->Location;
           angleXRotation -= tmpPosition.X - mousePosition.X;
           angleYRotation += tmpPosition.Y - mousePosition.Y;
          }
		 }
private: System::Void RenderingPanel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
		  if (e->Button == Windows::Forms::MouseButtons::Left) { mousePosition = e->Location; }
		 }
private: System::Void RenderingPanel_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			  distance *= (e->Delta < 0) ? (float)Math::Abs(0.66 * e->Delta / 120) :
                     (float)Math::Abs(1.33 * e->Delta / 120);
		 }
private: System::Void RenderingPanel_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->RenderingPanel->Focus();
		 }
private: System::Void TextBox_BrightnessMult_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 try {
                     BrightnessMult = (float)Double::Parse(this->TextBox_BrightnessMult->Text);
                 } catch (...) 
			     {
					 /*MessageBox::Show("Некорректный числовой формат.", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Error,
						 MessageBoxDefaultButton::Button1, MessageBoxOptions::DefaultDesktopOnly, false); */
					 this->Label_Status->Text = L"Некорректный числовой формат.";
                 }
		 }
private: System::Void CheckBox_Transparency_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->CheckBox_DepthTest->Enabled = this->CheckBox_Transparency->Checked;
		 }


private: System::Void DataGridView_Clusters_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) 
		 {
			 if (e->ColumnIndex==4)
			 {
			  if (this->ColorDialog->ShowDialog()== Windows::Forms::DialogResult::OK)
			  {
			   System::Drawing::Color selectedColor = ColorDialog->Color;
			   TColor tmpColor = TColor((float)selectedColor.R/255, (float)selectedColor.G/255, (float)selectedColor.B/255, (float)selectedColor.A/255);
			   this->DataGridView_Clusters->Rows[e->RowIndex]->Cells[4]->Value = this->GetStringOfColor(tmpColor);
			   this->DataGridView_Clusters->Rows[e->RowIndex]->Cells[5]->Value = selectedColor.A.ToString();

			   if (this->RadioButton_2D->Checked)
			   {
				size_t z = (size_t)this->TrackBar_Layers->Value;
			    //for (size_t z = 0; z < InputData->sizeZ; ++z)
			    {
				//if (e->RowIndex < min(this->DataGridView_Clusters->RowCount-1, (int)NClusters[z]))
			    {
				 Segments_2D[z].at(e->RowIndex).Color = tmpColor;
				 Segments_2D[z].at(e->RowIndex).transparensy = selectedColor.A;

				 vector<size_t>::iterator iter = Segments_2D[z].at(e->RowIndex).Index.begin();
				 vector<size_t>::iterator _end = Segments_2D[z].at(e->RowIndex).Index.end();
			     for (; iter!=_end; ++iter)
			     {
				  this->StaticDelInst_Color_2D(*iter+z*InputData->sizeX*InputData->sizeY, tmpColor);
			      /* if ((bool)this->DataGridView_Clusters->Rows[index]->Cells[4]->Value ==true)
			      IsVoxelVisible[*iter+z*InputData->sizeX*InputData->sizeY] = true;
			      else IsVoxelVisible[*iter+z*InputData->sizeX*InputData->sizeY] = false; 
			      this->StaticDelInst_Visible(*iter+z*InputData->sizeX*InputData->sizeY, bool_value);*/
			     }
				}
				}
			   }
			   
			   if (this->RadioButton_3D->Checked)
			   {
				Segments_3D->at(e->RowIndex).Color = TColor((float)selectedColor.R/255, (float)selectedColor.G/255, (float)selectedColor.B/255, (float)selectedColor.A/255);
				Segments_3D->at(e->RowIndex).transparensy = selectedColor.A;

				vector<size_t>::iterator iter = Segments_3D->at(e->RowIndex).Index.begin();
				vector<size_t>::iterator _end = Segments_3D->at(e->RowIndex).Index.end();
			    for (; iter!=_end; ++iter)
			    {
				 //TColor tmpColor = TColor((float)selectedColor.R/255, (float)selectedColor.G/255, (float)selectedColor.B/255, (float)selectedColor.A/255);
				 if (*iter+(size_t)this->NumericUpDown_Start->Value*InputData->sizeX*InputData->sizeY<InputData->TotalSize)
				 this->StaticDelInst_Color_3D(*iter+(size_t)this->NumericUpDown_Start->Value*InputData->sizeX*InputData->sizeY, tmpColor);
			     /* if ((bool)this->DataGridView_Clusters->Rows[index]->Cells[4]->Value ==true)
			     IsVoxelVisible[*iter+z*InputData->sizeX*InputData->sizeY] = true;
			     else IsVoxelVisible[*iter+z*InputData->sizeX*InputData->sizeY] = false; 
			     this->StaticDelInst_Visible(*iter+z*InputData->sizeX*InputData->sizeY, bool_value); */
			    }
			   }
			  
			   GenerateTextures();
			  }
			 }
		     
			 
         }
			
		 
private: System::Void DataGridView_Clusters_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) 
		 {
			if ((e->ColumnIndex==5) && InputData)
			{
			 int index = e->RowIndex;

			 unsigned char tmp_value = 0;

			 try 
			 {
			  tmp_value = 
			  (unsigned char)System::Int32::Parse((String^)this->DataGridView_Clusters->Rows[index]->Cells[5]->Value);
			 } 
			 catch (...)
			 {
			  Label_Status->Text = L"Некорректный числовой формат.";
			 }

			 //this->DataGridView_Clusters->Rows[index]->Cells[5]->Value = ! this->DataGridView_Clusters->Rows[index]->Cells[4]->Value;

			 if (this->RadioButton_2D->Checked)
		  
			 {
			  size_t z = (size_t)this->TrackBar_Layers->Value;

			  Segments_2D[z].at(index).transparensy = tmp_value;
		   
			  vector<size_t>::iterator iter = Segments_2D[z].at(index).Index.begin();
		      vector<size_t>::iterator _end = Segments_2D[z].at(index).Index.end();
			  for (; iter!=_end; ++iter)
			  {
			   TColor tmpColor = VoxelsData[*iter+z*InputData->sizeX*InputData->sizeY].Color_2D;
			   this->StaticDelInst_Color_2D(*iter+z*InputData->sizeX*InputData->sizeY, TColor(tmpColor.R, tmpColor.G, tmpColor.B, (float)tmp_value/255));
			  }
			  
				GenerateTextures();
			  }

			  if (this->RadioButton_3D->Checked)
			  {
			   Segments_3D->at(index).transparensy = tmp_value;
			   vector<size_t>::iterator iter = Segments_3D->at(index).Index.begin();
			   vector<size_t>::iterator _end = Segments_3D->at(index).Index.end();
			   for (; iter!=_end; ++iter)
			   if (*iter+(size_t)this->NumericUpDown_Start->Value*InputData->sizeX*InputData->sizeY<InputData->TotalSize)
			   {
				TColor tmpColor = VoxelsData[*iter+(size_t)this->NumericUpDown_Start->Value*InputData->sizeX*InputData->sizeY].Color_3D;
				
				this->StaticDelInst_Color_3D(*iter+(size_t)this->NumericUpDown_Start->Value*InputData->sizeX*InputData->sizeY, TColor(tmpColor.R, tmpColor.G, tmpColor.B, (float)tmp_value/255));
			   }

			   GenerateTextures();
			  }
			  
			}

			if ((e->ColumnIndex == 6) && InputData)
			{
			 int index = e->RowIndex;

			 if (this->RadioButton_2D->Checked)
			 {
			  size_t z = (size_t)this->TrackBar_Layers->Value;
			  Segments_2D[z].at(index).IsVisible = (bool)this->DataGridView_Clusters->Rows[index]->Cells[6]->Value;
			  vector <size_t>::iterator iter = Segments_2D[z].at(index).Index.begin();
			  vector <size_t>::iterator _end = Segments_2D[z].at(index).Index.end();
			  for (; iter!=_end; ++iter)
			  {
			   this->StaticDelInst_Visible_2D(*iter+z*InputData->sizeX*InputData->sizeY, Segments_2D[z].at(index).IsVisible);
			  }
					
			 }

			 if (this->RadioButton_3D->Checked)
			 {
			  Segments_3D->at(index).IsVisible = (bool)this->DataGridView_Clusters->Rows[index]->Cells[6]->Value;
			  vector <size_t>::iterator iter = Segments_3D->at(index).Index.begin();
			  vector <size_t>::iterator _end = Segments_3D->at(index).Index.end();
			  for (; iter!=_end; ++iter)
			  {
			   if (*iter+(size_t)this->NumericUpDown_Start->Value*InputData->sizeX*InputData->sizeY<InputData->TotalSize)
			   this->StaticDelInst_Visible_3D(*iter+(size_t)this->NumericUpDown_Start->Value*InputData->sizeX*InputData->sizeY, Segments_3D->at(index).IsVisible);
			  }
					
			 }
				
			 GenerateTextures();
			}
		 }
private: System::Void RadioButton_3D_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (InputData && InputData->data) 
			 {
			  this->ProgressBar_Layers->Maximum = 1;

			  if (this->ProgressBar_Iterations->Value == this->ProgressBar_Iterations->Maximum)
			  this->ProgressBar_Layers->Value = this->ProgressBar_Layers->Maximum;
			  else this->ProgressBar_Layers->Value = 0;

     		  this->NumericUpDown_Start->Enabled = true;
			  this->NumericUpDown_Finish->Enabled = true;
			  this->TrackBar_Layers->Enabled = false;

			  if (Segments_3D)  // если кластеры уже найдены
			  {
			   this->DataGridView_Clusters->RowCount = Segments_3D->size()+1;

			   for (size_t index = 0; index < Segments_3D->size(); ++index)
			   {
			    this->DataGridView_Clusters->Rows[index]->Cells[0]->Value = index.ToString();
			    this->DataGridView_Clusters->Rows[index]->Cells[1]->Value = Segments_3D->at(index).Index.size().ToString();
			    this->DataGridView_Clusters->Rows[index]->Cells[2]->Value = Segments_3D->at(index).MinDensity.ToString();
			    this->DataGridView_Clusters->Rows[index]->Cells[3]->Value = Segments_3D->at(index).MaxDensity.ToString();
                this->DataGridView_Clusters->Rows[index]->Cells[4]->Value = this->GetStringOfColor(Segments_3D->at(index).Color);
			    this->DataGridView_Clusters->Rows[index]->Cells[5]->Value = Segments_3D->at(index).transparensy.ToString();
			    this->DataGridView_Clusters->Rows[index]->Cells[6]->Value = Segments_3D->at(index).IsVisible; 
			   }

			   if (CheckBoxClusters->Checked) 
			   {
			    this->DataGridView_Clusters->Enabled = true; 
			    this->Button_VisualizeSelectedClusters->Enabled = true; 
			   }
			  }
			  
			 
			  else 
				  
			  {
				  this->DataGridView_Clusters->RowCount = 1; 
				  this->DataGridView_Clusters->Enabled = false;
				  this->Button_VisualizeSelectedClusters->Enabled = false; 
			  }
			  
			  GenerateTextures();
			 }
			 else this->ProgressBar_Layers->Maximum = 0;
		 }
private: System::Void RadioButton_2D_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
		  if (InputData && InputData->data) 
		  {
		   this->ProgressBar_Layers->Maximum = InputData->sizeZ;

		   if (this->ProgressBar_Iterations->Value == this->ProgressBar_Iterations->Maximum)
		   this->ProgressBar_Layers->Value = this->ProgressBar_Layers->Maximum;
		   else this->ProgressBar_Layers->Value = 0;

		   this->NumericUpDown_Start->Enabled = false;
		   this->NumericUpDown_Finish->Enabled = false;
		   this->TrackBar_Layers->Enabled = true;

		   if (Segments_2D)										// если кластеры уже найдены
		   {
   		    size_t z = (size_t)this->TrackBar_Layers->Value;

		    this->DataGridView_Clusters->RowCount = Segments_2D[z].size()+1;

		    for (size_t index = 0; index < Segments_2D[z].size(); ++index)
		    {
		     this->DataGridView_Clusters->Rows[index]->Cells[0]->Value = index.ToString();
		     this->DataGridView_Clusters->Rows[index]->Cells[1]->Value = Segments_2D[z].at(index).Index.size().ToString();
		     this->DataGridView_Clusters->Rows[index]->Cells[2]->Value = Segments_2D[z].at(index).MinDensity.ToString();
			 this->DataGridView_Clusters->Rows[index]->Cells[3]->Value = Segments_2D[z].at(index).MaxDensity.ToString();
			 this->DataGridView_Clusters->Rows[index]->Cells[4]->Value = GetStringOfColor(Segments_2D[z].at(index).Color);
			 this->DataGridView_Clusters->Rows[index]->Cells[5]->Value = Segments_2D[z].at(index).transparensy.ToString();
			 this->DataGridView_Clusters->Rows[index]->Cells[6]->Value = Segments_2D[z].at(index).IsVisible;
			}
			   
			if (CheckBoxClusters->Checked) 
			{
			 this->DataGridView_Clusters->Enabled = true; 
			 this->Button_VisualizeSelectedClusters->Enabled = true; 
			}
		   }
		   else 
		   {
		    this->DataGridView_Clusters->Enabled = false; 
			this->Button_VisualizeSelectedClusters->Enabled = false; 
		   }

		   GenerateTextures();
		  }
		  else this->ProgressBar_Layers->Maximum = 0;
		 }
private: System::Void CheckBoxClusters_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 GenerateTextures();
		 }
private: System::Void TrackBar_LayersDistance_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->Label_LayersDistance->Text = L"Расстояние между слоями: "+
												this->TrackBar_LayersDistance->Value.ToString();
		 }
private: System::Void ClusterizationForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 e->Cancel = true;
			 Hide();
		 }
};
}

