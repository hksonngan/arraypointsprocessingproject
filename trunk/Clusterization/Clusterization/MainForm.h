#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLu.h>

#include "graphics.h"
#include "ScanData.h"
#include "K-means.h"


#include <stdio.h>

using namespace std;

#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")
#pragma comment (lib,"User32.lib")
#pragma comment (lib,"gdi32.lib")

struct TColor 
{
 float R, G, B;
 TColor():R(0), G(0), B(0) {};
 TColor(float value_R, 
	    float value_G, 
		float value_B): R(value_R), G(value_G), B(value_B) {};
};

namespace Clusterization {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>

	public delegate void MyDelegate(bool* IsVisible);

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void ChangeVisible(bool* IsVisible)
		{
			IsVoxelVisible = IsVisible;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^  CheckBoxClusters;
	protected: 

	private: System::Windows::Forms::MenuStrip^  MenuStrip;

	private: System::Windows::Forms::ToolStripMenuItem^  файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem_Download;

	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem_Properties;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem_Exit;
	private: System::Windows::Forms::GroupBox^  GroupBoxVisualization;

	private: System::Windows::Forms::Panel^  RenderingPanel;
	private: System::Windows::Forms::Label^  Label_ClustersCount;
	private: System::Windows::Forms::TrackBar^  TrackBar_ClustersCount;



	private: System::Windows::Forms::Label^  Label_LayerInfo;





	private: System::Windows::Forms::TrackBar^  TrackBar_Layers;

	private: System::Windows::Forms::GroupBox^  GroupBoxDim;


	private: System::Windows::Forms::RadioButton^  RadioButton_2D;
	private: System::Windows::Forms::RadioButton^  RadioButton_3D;
	private: System::Windows::Forms::Label^  Label_BrightnessMult;



	private: System::Windows::Forms::TextBox^  TextBox_BrightnessMult;




	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::OpenFileDialog^  OpenDataDialog;

	private:
			short MaxDensity;
			float BrightnessMult;

	public:
		MyDelegate^ StaticDelInst;
		ScanData* InputData;					// исходные данные
		KmeansMethod* ClusterizationMethod;		// метод, используемый для кластеризации
		size_t* Cluster_ID;						// метки вокселов
		TColor* VoxelColor;						// цвета кластеризованных вокселов
		size_t* NClusters;						// количество кластеров для каждого слоя
		bool* IsVoxelVisible;					// признак видимости воксела при визуализации
		vector<vector <size_t> >* Clusters;		// вектор кластеров для каждого слоя данных

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

        float angleXRotation, angleYRotation;
        Point mousePosition;
        float distance;
	private: System::Windows::Forms::Timer^  RenderTimer;
	private: System::Windows::Forms::Label^  Label_Status;
	private: System::Windows::Forms::ProgressBar^  ProgressBar_Iterations;
	private: System::Windows::Forms::ProgressBar^  ProgressBar_Layers;


	private: System::Windows::Forms::DataGridView^  DataGridView_Clusters;







private: System::Windows::Forms::TrackBar^  TrackBar_IterationsCount;
private: System::Windows::Forms::Label^  Label_IterationsCount;


private: System::Windows::Forms::DataGridViewTextBoxColumn^  Cluster_id;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  VoxelsCount;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  MeanDensity;
private: System::Windows::Forms::DataGridViewComboBoxColumn^  Color;
private: System::Windows::Forms::DataGridViewCheckBoxColumn^  Visible;
private: System::Windows::Forms::Button^  Button_Clusterization;
private: System::ComponentModel::BackgroundWorker^  BackgroundWorker;
private: System::Windows::Forms::Button^  Button_VisualizeSelectedClusters;


	private: System::ComponentModel::IContainer^  components;



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->CheckBoxClusters = (gcnew System::Windows::Forms::CheckBox());
			this->MenuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem_Download = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem_Properties = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem_Exit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->GroupBoxVisualization = (gcnew System::Windows::Forms::GroupBox());
			this->TextBox_BrightnessMult = (gcnew System::Windows::Forms::TextBox());
			this->Label_BrightnessMult = (gcnew System::Windows::Forms::Label());
			this->GroupBoxDim = (gcnew System::Windows::Forms::GroupBox());
			this->RadioButton_2D = (gcnew System::Windows::Forms::RadioButton());
			this->RadioButton_3D = (gcnew System::Windows::Forms::RadioButton());
			this->TrackBar_Layers = (gcnew System::Windows::Forms::TrackBar());
			this->Label_LayerInfo = (gcnew System::Windows::Forms::Label());
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
			this->Cluster_id = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->VoxelsCount = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->MeanDensity = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Color = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->Visible = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
			this->Button_Clusterization = (gcnew System::Windows::Forms::Button());
			this->BackgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->Button_VisualizeSelectedClusters = (gcnew System::Windows::Forms::Button());
			this->MenuStrip->SuspendLayout();
			this->GroupBoxVisualization->SuspendLayout();
			this->GroupBoxDim->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_Layers))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_ClustersCount))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_IterationsCount))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DataGridView_Clusters))->BeginInit();
			this->SuspendLayout();
			// 
			// CheckBoxClusters
			// 
			this->CheckBoxClusters->AutoSize = true;
			this->CheckBoxClusters->Location = System::Drawing::Point(15, 244);
			this->CheckBoxClusters->Name = L"CheckBoxClusters";
			this->CheckBoxClusters->Size = System::Drawing::Size(197, 21);
			this->CheckBoxClusters->TabIndex = 0;
			this->CheckBoxClusters->Text = L"Отображать кластеры";
			this->CheckBoxClusters->UseVisualStyleBackColor = true;
			this->CheckBoxClusters->Click += gcnew System::EventHandler(this, &MainForm::CheckBoxClusters_Click);
			// 
			// MenuStrip
			// 
			this->MenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->файлToolStripMenuItem});
			this->MenuStrip->Location = System::Drawing::Point(0, 0);
			this->MenuStrip->Name = L"MenuStrip";
			this->MenuStrip->Size = System::Drawing::Size(1091, 26);
			this->MenuStrip->TabIndex = 1;
			this->MenuStrip->Text = L"menuStrip1";
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->ToolStripMenuItem_Download, 
				this->ToolStripMenuItem_Properties, this->ToolStripMenuItem_Exit});
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
			this->ToolStripMenuItem_Download->Click += gcnew System::EventHandler(this, &MainForm::ToolStripMenuItem_Download_Click);
			// 
			// ToolStripMenuItem_Properties
			// 
			this->ToolStripMenuItem_Properties->Name = L"ToolStripMenuItem_Properties";
			this->ToolStripMenuItem_Properties->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::P));
			this->ToolStripMenuItem_Properties->Size = System::Drawing::Size(226, 22);
			this->ToolStripMenuItem_Properties->Text = L"Свойства";
			// 
			// ToolStripMenuItem_Exit
			// 
			this->ToolStripMenuItem_Exit->Name = L"ToolStripMenuItem_Exit";
			this->ToolStripMenuItem_Exit->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::F4));
			this->ToolStripMenuItem_Exit->Size = System::Drawing::Size(226, 22);
			this->ToolStripMenuItem_Exit->Text = L"Выход";
			this->ToolStripMenuItem_Exit->Click += gcnew System::EventHandler(this, &MainForm::ToolStripMenuItem_Exit_Click);
			// 
			// GroupBoxVisualization
			// 
			this->GroupBoxVisualization->BackColor = System::Drawing::Color::Snow;
			this->GroupBoxVisualization->Controls->Add(this->TextBox_BrightnessMult);
			this->GroupBoxVisualization->Controls->Add(this->Label_BrightnessMult);
			this->GroupBoxVisualization->Controls->Add(this->GroupBoxDim);
			this->GroupBoxVisualization->Controls->Add(this->TrackBar_Layers);
			this->GroupBoxVisualization->Controls->Add(this->CheckBoxClusters);
			this->GroupBoxVisualization->Controls->Add(this->Label_LayerInfo);
			this->GroupBoxVisualization->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->GroupBoxVisualization->Location = System::Drawing::Point(533, 29);
			this->GroupBoxVisualization->Name = L"GroupBoxVisualization";
			this->GroupBoxVisualization->Size = System::Drawing::Size(543, 321);
			this->GroupBoxVisualization->TabIndex = 2;
			this->GroupBoxVisualization->TabStop = false;
			this->GroupBoxVisualization->Text = L"Настройки визуализации";
			// 
			// TextBox_BrightnessMult
			// 
			this->TextBox_BrightnessMult->Location = System::Drawing::Point(175, 195);
			this->TextBox_BrightnessMult->Name = L"TextBox_BrightnessMult";
			this->TextBox_BrightnessMult->Size = System::Drawing::Size(56, 22);
			this->TextBox_BrightnessMult->TabIndex = 10;
			// 
			// Label_BrightnessMult
			// 
			this->Label_BrightnessMult->AutoSize = true;
			this->Label_BrightnessMult->Location = System::Drawing::Point(12, 197);
			this->Label_BrightnessMult->Name = L"Label_BrightnessMult";
			this->Label_BrightnessMult->Size = System::Drawing::Size(161, 17);
			this->Label_BrightnessMult->TabIndex = 9;
			this->Label_BrightnessMult->Text = L"Множитель яркости:";
			// 
			// GroupBoxDim
			// 
			this->GroupBoxDim->Controls->Add(this->RadioButton_2D);
			this->GroupBoxDim->Controls->Add(this->RadioButton_3D);
			this->GroupBoxDim->Location = System::Drawing::Point(57, 34);
			this->GroupBoxDim->Name = L"GroupBoxDim";
			this->GroupBoxDim->Size = System::Drawing::Size(431, 81);
			this->GroupBoxDim->TabIndex = 1;
			this->GroupBoxDim->TabStop = false;
			this->GroupBoxDim->Text = L"Способ визуализации";
			// 
			// RadioButton_2D
			// 
			this->RadioButton_2D->AutoSize = true;
			this->RadioButton_2D->Checked = true;
			this->RadioButton_2D->Location = System::Drawing::Point(257, 39);
			this->RadioButton_2D->Name = L"RadioButton_2D";
			this->RadioButton_2D->Size = System::Drawing::Size(120, 21);
			this->RadioButton_2D->TabIndex = 1;
			this->RadioButton_2D->TabStop = true;
			this->RadioButton_2D->Text = L"2D (слоями)";
			this->RadioButton_2D->UseVisualStyleBackColor = true;
			// 
			// RadioButton_3D
			// 
			this->RadioButton_3D->AutoSize = true;
			this->RadioButton_3D->Enabled = false;
			this->RadioButton_3D->Location = System::Drawing::Point(54, 39);
			this->RadioButton_3D->Name = L"RadioButton_3D";
			this->RadioButton_3D->Size = System::Drawing::Size(146, 21);
			this->RadioButton_3D->TabIndex = 0;
			this->RadioButton_3D->Text = L"3D (полностью)";
			this->RadioButton_3D->UseVisualStyleBackColor = true;
			// 
			// TrackBar_Layers
			// 
			this->TrackBar_Layers->Location = System::Drawing::Point(230, 135);
			this->TrackBar_Layers->Name = L"TrackBar_Layers";
			this->TrackBar_Layers->Size = System::Drawing::Size(311, 56);
			this->TrackBar_Layers->TabIndex = 8;
			this->TrackBar_Layers->ValueChanged += gcnew System::EventHandler(this, &MainForm::TrackBar_Layers_ValueChanged);
			// 
			// Label_LayerInfo
			// 
			this->Label_LayerInfo->AutoSize = true;
			this->Label_LayerInfo->Location = System::Drawing::Point(12, 144);
			this->Label_LayerInfo->Name = L"Label_LayerInfo";
			this->Label_LayerInfo->Size = System::Drawing::Size(203, 17);
			this->Label_LayerInfo->TabIndex = 7;
			this->Label_LayerInfo->Text = L"Визуализировать слой № ";
			// 
			// RenderingPanel
			// 
			this->RenderingPanel->BackColor = System::Drawing::SystemColors::ControlText;
			this->RenderingPanel->Location = System::Drawing::Point(3, 29);
			this->RenderingPanel->Name = L"RenderingPanel";
			this->RenderingPanel->Size = System::Drawing::Size(513, 658);
			this->RenderingPanel->TabIndex = 3;
			// 
			// Label_ClustersCount
			// 
			this->Label_ClustersCount->AutoSize = true;
			this->Label_ClustersCount->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->Label_ClustersCount->Location = System::Drawing::Point(11, 31);
			this->Label_ClustersCount->Name = L"Label_ClustersCount";
			this->Label_ClustersCount->Size = System::Drawing::Size(253, 17);
			this->Label_ClustersCount->TabIndex = 4;
			this->Label_ClustersCount->Text = L"Максимальное число кластеров:";
			// 
			// TrackBar_ClustersCount
			// 
			this->TrackBar_ClustersCount->Location = System::Drawing::Point(307, 28);
			this->TrackBar_ClustersCount->Maximum = 100;
			this->TrackBar_ClustersCount->Minimum = 2;
			this->TrackBar_ClustersCount->Name = L"TrackBar_ClustersCount";
			this->TrackBar_ClustersCount->Size = System::Drawing::Size(234, 56);
			this->TrackBar_ClustersCount->TabIndex = 5;
			this->TrackBar_ClustersCount->Value = 10;
			this->TrackBar_ClustersCount->ValueChanged += gcnew System::EventHandler(this, &MainForm::TrackBar_ClustersCount_ValueChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::Snow;
			this->groupBox1->Controls->Add(this->TrackBar_IterationsCount);
			this->groupBox1->Controls->Add(this->Label_IterationsCount);
			this->groupBox1->Controls->Add(this->Label_ClustersCount);
			this->groupBox1->Controls->Add(this->TrackBar_ClustersCount);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox1->Location = System::Drawing::Point(533, 356);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(543, 130);
			this->groupBox1->TabIndex = 11;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Настройки кластеризации";
			// 
			// TrackBar_IterationsCount
			// 
			this->TrackBar_IterationsCount->Location = System::Drawing::Point(308, 72);
			this->TrackBar_IterationsCount->Maximum = 500;
			this->TrackBar_IterationsCount->Minimum = 10;
			this->TrackBar_IterationsCount->Name = L"TrackBar_IterationsCount";
			this->TrackBar_IterationsCount->Size = System::Drawing::Size(233, 56);
			this->TrackBar_IterationsCount->TabIndex = 7;
			this->TrackBar_IterationsCount->Value = 50;
			this->TrackBar_IterationsCount->ValueChanged += gcnew System::EventHandler(this, &MainForm::TrackBar_IterationsCount_ValueChanged);
			// 
			// Label_IterationsCount
			// 
			this->Label_IterationsCount->AutoSize = true;
			this->Label_IterationsCount->Location = System::Drawing::Point(4, 76);
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
			this->RenderTimer->Tick += gcnew System::EventHandler(this, &MainForm::RenderTimer_Tick);
			// 
			// Label_Status
			// 
			this->Label_Status->AutoSize = true;
			this->Label_Status->Location = System::Drawing::Point(7, 694);
			this->Label_Status->Name = L"Label_Status";
			this->Label_Status->Size = System::Drawing::Size(91, 17);
			this->Label_Status->TabIndex = 12;
			this->Label_Status->Text = L"Label_Status";
			// 
			// ProgressBar_Iterations
			// 
			this->ProgressBar_Iterations->Location = System::Drawing::Point(3, 718);
			this->ProgressBar_Iterations->Name = L"ProgressBar_Iterations";
			this->ProgressBar_Iterations->Size = System::Drawing::Size(513, 23);
			this->ProgressBar_Iterations->Step = 1;
			this->ProgressBar_Iterations->TabIndex = 13;
			// 
			// ProgressBar_Layers
			// 
			this->ProgressBar_Layers->Location = System::Drawing::Point(3, 747);
			this->ProgressBar_Layers->Name = L"ProgressBar_Layers";
			this->ProgressBar_Layers->Size = System::Drawing::Size(513, 23);
			this->ProgressBar_Layers->Step = 1;
			this->ProgressBar_Layers->TabIndex = 14;
			// 
			// DataGridView_Clusters
			// 
			this->DataGridView_Clusters->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->DataGridView_Clusters->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {this->Cluster_id, 
				this->VoxelsCount, this->MeanDensity, this->Color, this->Visible});
			this->DataGridView_Clusters->Location = System::Drawing::Point(534, 541);
			this->DataGridView_Clusters->Name = L"DataGridView_Clusters";
			this->DataGridView_Clusters->RowTemplate->Height = 24;
			this->DataGridView_Clusters->Size = System::Drawing::Size(545, 191);
			this->DataGridView_Clusters->TabIndex = 15;
			// 
			// Cluster_id
			// 
			this->Cluster_id->HeaderText = L"Номер кластера";
			this->Cluster_id->Name = L"Cluster_id";
			// 
			// VoxelsCount
			// 
			this->VoxelsCount->HeaderText = L"Число вокселов";
			this->VoxelsCount->Name = L"VoxelsCount";
			// 
			// MeanDensity
			// 
			this->MeanDensity->HeaderText = L"Средняя плотность";
			this->MeanDensity->Name = L"MeanDensity";
			// 
			// Color
			// 
			this->Color->HeaderText = L"Цвет";
			this->Color->Name = L"Color";
			// 
			// Visible
			// 
			this->Visible->HeaderText = L"Отобразить";
			this->Visible->Name = L"Visible";
			// 
			// Button_Clusterization
			// 
			this->Button_Clusterization->Location = System::Drawing::Point(720, 497);
			this->Button_Clusterization->Name = L"Button_Clusterization";
			this->Button_Clusterization->Size = System::Drawing::Size(183, 32);
			this->Button_Clusterization->TabIndex = 16;
			this->Button_Clusterization->Text = L"Кластеризовать данные";
			this->Button_Clusterization->UseVisualStyleBackColor = true;
			this->Button_Clusterization->Click += gcnew System::EventHandler(this, &MainForm::Button_Clusterization_Click);
			// 
			// BackgroundWorker
			// 
			this->BackgroundWorker->WorkerReportsProgress = true;
			this->BackgroundWorker->WorkerSupportsCancellation = true;
			this->BackgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::BackgroundWorker_DoWork);
			this->BackgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainForm::BackgroundWorker_RunWorkerCompleted);
			this->BackgroundWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MainForm::BackgroundWorker_ProgressChanged);
			// 
			// Button_VisualizeSelectedClusters
			// 
			this->Button_VisualizeSelectedClusters->Location = System::Drawing::Point(695, 740);
			this->Button_VisualizeSelectedClusters->Name = L"Button_VisualizeSelectedClusters";
			this->Button_VisualizeSelectedClusters->Size = System::Drawing::Size(241, 30);
			this->Button_VisualizeSelectedClusters->TabIndex = 17;
			this->Button_VisualizeSelectedClusters->Text = L"Отобразить выбранные кластеры";
			this->Button_VisualizeSelectedClusters->UseVisualStyleBackColor = true;
			this->Button_VisualizeSelectedClusters->Click += gcnew System::EventHandler(this, &MainForm::Button_VisualizeSelectedClusters_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1091, 776);
			this->Controls->Add(this->Button_VisualizeSelectedClusters);
			this->Controls->Add(this->Button_Clusterization);
			this->Controls->Add(this->DataGridView_Clusters);
			this->Controls->Add(this->ProgressBar_Layers);
			this->Controls->Add(this->ProgressBar_Iterations);
			this->Controls->Add(this->Label_Status);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->RenderingPanel);
			this->Controls->Add(this->GroupBoxVisualization);
			this->Controls->Add(this->MenuStrip);
			this->MainMenuStrip = this->MenuStrip;
			this->Name = L"MainForm";
			this->Text = L"Проект по СКГ: кластеризация";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
			this->MenuStrip->ResumeLayout(false);
			this->MenuStrip->PerformLayout();
			this->GroupBoxVisualization->ResumeLayout(false);
			this->GroupBoxVisualization->PerformLayout();
			this->GroupBoxDim->ResumeLayout(false);
			this->GroupBoxDim->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_Layers))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_ClustersCount))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_IterationsCount))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DataGridView_Clusters))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void DrawGLScene() {
                  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                  glLoadIdentity();

                  glTranslatef(0.0f, 0.0f, -distance);
                  //glTranslatef(0.0f, 0.0f, -3.0f);
                  glRotatef(90.0f, 0.0f, 0.0, 1.0f);
                  glRotatef(angleXRotation, 1.0f, 0.0f, 0.0f);
                  glRotatef(angleYRotation, 0.0f, 1.0f, 0.0f);
                  /*
                  glBegin(GL_TRIANGLES); {
                      glColor3f((GLfloat)(rand() / (rand()+1)),
                          (GLfloat)(rand() / (rand()+1)),
                          (GLfloat)(rand() / (rand()+1)));
                      glVertex3f(-1.0f, -0.4f, 0.0f);

                      glColor3f((GLfloat)(rand() / (rand()+1)),
                          (GLfloat)(rand() / (rand()+1)),
                          (GLfloat)(rand() / (rand()+1)));
                      glVertex3f( 1.0f, -0.4f, 0.0f);

                      glColor3f((GLfloat)(rand() / (rand()+1)),
                          (GLfloat)(rand() / (rand()+1)),
                          (GLfloat)(rand() / (rand()+1)));
                      glVertex3f( 0.0f,  1.0f, 0.0f);
                  }
                  glEnd();
                  //*/
                  //glColor3f(1.0f, 1.0f, 1.0f);
                  //glCallList(theBox);

				  if (this->RadioButton_2D->Checked)
				  {
				   // визуализация по слоям
                   if (InputData && InputData->data) 
				   {
					   RenderLayer(this->TrackBar_Layers->Value);
					  // RenderClusters();
                   }
				  } 
				  if (this->RadioButton_3D->Checked)
				  {
				   // трёхмерная визуализация
				  }
              }

	private: System::Void RenderLayer(size_t z) 
			 {
			  glScalef(InputData->scaleX, InputData->scaleY, InputData->scaleZ);
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
              glPopMatrix();
             }

	private: System::Void CalcClusters()
			 {
			  /* ClusterizationMethod = new KmeansMethod(InputData->GetLayer(TrackBar_Layers->Value));
			  ClusterizationMethod->SetClustersNumber(5);
			  ClusterizationMethod->SetCountIterations(200);

			  Label_Status->Text = L"Выполняется кластеризация данных. Пожалуйста, подождите...";
						 
			  vector <vector <size_t> > Clusters = ClusterizationMethod->GetClusters();

			  Labels = NULL; 
						 
			  Labels = new size_t [InputData->sizeX*InputData->sizeY*InputData->sizeZ];

			  NClusters = Clusters.size();

			  for (size_t i = 0; i < NClusters; ++i)
			  {
    		   vector <size_t> cluster = Clusters.at(i);

			   vector<size_t>::iterator iter = cluster.begin();
			   vector<size_t>::iterator _end = cluster.end();
			   for (; iter!=_end; ++iter) Labels[*iter] = i;
			  }

			  Label_Status->Text = L"Данные кластеризованы."; */
			 }

	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
			  GLuint PixelFormat;

			  hWnd = (HWND)(intptr_t)this->RenderingPanel->Handle;
              hDC = GetDC(hWnd);
              if (!hDC) 
			  {
               this->Label_Status->Text = L"Can't Create A GL Device Context";
               return;
              }

              BYTE colorBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
              static PIXELFORMATDESCRIPTOR pfd = 
			  {           
																   // pfd Tells Windows How We Want Things To Be
               sizeof(PIXELFORMATDESCRIPTOR),					   // Size Of This Pixel Format Descriptor
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

                 MainForm_Resize(sender, e);

                 if (!InitGL()) {
                    this->Label_Status->Text = L"Failed to init GL";
                 }

                 theBox = glGenLists(1);
                 glNewList(theBox, GL_COMPILE);
                 glBegin(GL_QUADS); {
                     // front face
                     glNormal3f(0.0f, 0.0f, 1.0f);
                     glVertex3f(0.5f, 0.5f, 0.5f);
                     glVertex3f(0.5f, -0.5f, 0.5f);
                     glVertex3f(-0.5f, -0.5f, 0.5f);
                     glVertex3f(-0.5f, 0.5f, 0.5f);

                     // left face
                     glNormal3f(-1.0f, 0.0f, 0.0f);
                     glVertex3f(-0.5f, 0.5f, 0.5f);
                     glVertex3f(-0.5f, -0.5f, 0.5f);
                     glVertex3f(-0.5f, -0.5f, -0.5f);
                     glVertex3f(-0.5f, 0.5f, -0.5f);

                     // back face
                     glNormal3f(0.0f, 0.0f, -1.0f);
                     glVertex3f(-0.5f, 0.5f, -0.5f);
                     glVertex3f(-0.5f, -0.5f, -0.5f);
                     glVertex3f(0.5f, -0.5f, -0.5f);
                     glVertex3f(0.5f, 0.5f, -0.5f);

                     // right face
                     glNormal3f(1.0f, 0.0f, 0.0f);
                     glVertex3f(0.5f, 0.5f, -0.5f);
                     glVertex3f(0.5f, -0.5f, -0.5f);
                     glVertex3f(0.5f, -0.5f, 0.5f);
                     glVertex3f(0.5f, 0.5f, 0.5f);

                     // top face
                     glNormal3f(0.0f, 1.0f, 0.0f);
                     glVertex3f(-0.5f, 0.5f, -0.5f);
                     glVertex3f(0.5f, 0.5f, -0.5f);
                     glVertex3f(0.5f, 0.5f, 0.5f);
                     glVertex3f(-0.5f, 0.5f, 0.5f);

                     // bottom face
                     glNormal3f(0.0f, -1.0f, 0.0f);
                     glVertex3f(-0.5f, -0.5f, 0.5f);
                     glVertex3f(0.5f, -0.5f, 0.5f);
                     glVertex3f(0.5f, -0.5f, -0.5f);
                     glVertex3f(-0.5f, -0.5f, -0.5f);
                 }
                 glEnd();
                 glEndList();

                 InputData = new ScanData();
				 ClusterizationMethod = new KmeansMethod();
				 this->Clusters = NULL; this->VoxelColor = NULL;
				 this->IsVoxelVisible = NULL;
			 }
	private: System::Void ToolStripMenuItem_Download_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
			  if (this->OpenDataDialog->ShowDialog() == Windows::Forms::DialogResult::OK) 
			  {
               //this->textBoxInputFile->Text = this->openDataDialog->FileName;
               //textBoxInputFile->Select(textBoxInputFile->Text->Length, 0);
               //textBoxInputFile->ScrollToCaret();
               //angleXRotation = angleYRotation = 0.0f;

 			   String ^pathToDataFile = OpenDataDialog->FileName;
               if (System::IO::File::Exists(pathToDataFile)) {
               pathToDataFile = pathToDataFile->Replace("\\","\\\\");
               if (InputData->LoadData((char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(pathToDataFile).ToPointer())) {
                  this->Label_Status->Text = L"Данные из bin-файла загружены."; 

                     float fileSize = (float)(IO::FileInfo(pathToDataFile).Length >> 20);
                     /* this->labelDataFileName->Text = L"Файл: " + pathToDataFile->Substring(pathToDataFile->LastIndexOf("\\")+1) +
                                                     L" (" + fileSize + L" MB)"; */

                     //this->labelLayerWidth->Text = L"Ширина слоя: " + data->sizeX;
                     //this->labelLayerHeight->Text = L"Высота слоя: " + data->sizeY;
                     //this->labelLayerNum->Text = L"Кол-во слоев: " + data->sizeZ;

                     //this->labelVoxelX->Text = L"Размер по X: " + data->scaleX;
                     //this->labelVoxelY->Text = L"Размер по Y: " + data->scaleY;
                     //this->labelVoxelZ->Text = L"Размер по Z: " + data->scaleZ;

                     MaxDensity = 0;
					 for (size_t i = 0; i < InputData->sizeX*InputData->sizeY*InputData->sizeZ; ++i) 
					 {
                         if (MaxDensity < InputData->data[i]) 
						 {
                             MaxDensity = InputData->data[i];
                         }
                     }

					 //if (RadioButton_2D->Checked) CalcClusters();

					 ProgressBar_Layers->Maximum = InputData->sizeZ;
					 TrackBar_Layers->Maximum = InputData->sizeZ-1;
					 TrackBar_Layers->Value = 0;

					 if (RadioButton_3D->Checked)
					 {
						/* ClusterizationMethod = new MedianMethod(InputData);
						 ClusterizationMethod->SetClustersNumber(100000);

						 this->Label_Status->Text = L"Выполняется кластеризация данных. Пожалуйста, подождите...";

						 //Clusters = &ClusterizationMethod->GetClusters();

						 this->Label_Status->Text = L"Данные кластеризованы.";*/
					 }

					
			  
				     

					

                     angleXRotation = angleYRotation = 0.0f;
                     distance = 600.f;

					 TextBox_BrightnessMult->Text = L"30,0";
                     BrightnessMult = 30.f;

					 
                    
			   }

                 } else {
                     // this->labelStatus->Text = "Ошибка! Некорректное чтение файла.";
                 }
			  } else {
                 // this->labelStatus->Text = "Ошибка! Файл не найден.";
             } 

			 }
			
			 
private: System::Void ToolStripMenuItem_Exit_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 Close();
		 }
private: System::Void RenderTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
			 DrawGLScene();
			 SwapBuffers(hDC);
		 }
private: System::Void MainForm_Resize(System::Object^  sender, System::EventArgs^  e) {
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
private: System::Void TrackBar_Layers_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->Label_LayerInfo->Text = L"Визуализировать слой № "+this->TrackBar_Layers->Value.ToString();
			 
			 if (this->Clusters!=NULL)
			 {
			 int clusters_count = this->DataGridView_Clusters->RowCount-1;
			 size_t z  = this->TrackBar_Layers->Value;

			 this->DataGridView_Clusters->RowCount = this->NClusters[z]+1;
			 for (size_t index = 0; index < this->NClusters[z]; ++index)
			 {
				 this->DataGridView_Clusters->Rows[index]->Cells[0]->Value = index.ToString();
				 this->DataGridView_Clusters->Rows[index]->Cells[1]->Value = Clusters[z].at(index).size().ToString();
				 if (index>=clusters_count-1) this->DataGridView_Clusters->Rows[index]->Cells[4]->Value = false;
			 }
    		 }

		 }
private: System::Void CheckBoxClusters_Click(System::Object^  sender, System::EventArgs^  e) {
			 //this->RenderClusters();

		 }
private: System::Void Button_Clusterization_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->StaticDelInst= gcnew MyDelegate(this, &MainForm::ChangeVisible);

		  if (RadioButton_2D->Checked)					// если кластеризация по слоям
		  {
		   this->ProgressBar_Layers->Value = 0;

		   NClusters = NULL; Clusters = NULL; Cluster_ID = NULL; VoxelColor = NULL; 

		   NClusters = new size_t [InputData->sizeZ];

		   Clusters = new vector<vector <size_t> > [InputData->sizeZ];

		   Cluster_ID = new size_t [InputData->sizeX*InputData->sizeY*InputData->sizeZ];

	       VoxelColor = new TColor [InputData->sizeX*InputData->sizeY*InputData->sizeZ]; 

		   IsVoxelVisible = new bool [InputData->sizeX*InputData->sizeY*InputData->sizeZ];

		   for (size_t index = 0; index<InputData->sizeX*InputData->sizeY*InputData->sizeZ; ++index)
			   IsVoxelVisible[index] = true;
		   
		   for (size_t z = 0; z < InputData->sizeZ; ++z)
		   {
		    ClusterizationMethod = new KmeansMethod(InputData->GetLayer(z));
		    ClusterizationMethod->SetClustersNumber(TrackBar_ClustersCount->Value);
		    ClusterizationMethod->SetCountIterations(TrackBar_IterationsCount->Value);
			
			Label_Status->Text = L"Выполняется кластеризация данных. Пожалуйста, подождите...";
						 
			Clusters[z] = ClusterizationMethod->GetClusters(this->BackgroundWorker);

		    NClusters[z] = Clusters[z].size();

 		    for (size_t i = 0; i < NClusters[z]; ++i)
		    {
    		 vector <size_t> cluster = Clusters[z].at(i);

		     vector<size_t>::iterator iter = cluster.begin();
			 vector<size_t>::iterator _end = cluster.end();
			 for (; iter!=_end; ++iter) 
			 {
   			  Cluster_ID[*iter+z*InputData->sizeX*InputData->sizeY] = i;
			  float grayIntensity = (float)(i+1)/NClusters[z];
			  VoxelColor[*iter+z*InputData->sizeX*InputData->sizeY] = TColor(grayIntensity, grayIntensity, grayIntensity);
			  // управление видимостью воксела
			 }
		    }

			// Отображаем ход выполнения процесса
			this->ProgressBar_Layers->Value++;
			
		   }
		   
		   Label_Status->Text = L"Данные кластеризованы.";

		   size_t z = this->TrackBar_Layers->Value;
		   this->DataGridView_Clusters->RowCount = this->NClusters[z]+1;

		   //вставка в таблицу информации о кластерах для текущего слоя
		   for (size_t index = 0; index < this->NClusters[z]; ++index)
		   {
			this->DataGridView_Clusters->Rows[index]->Cells[0]->Value = index.ToString();
			this->DataGridView_Clusters->Rows[index]->Cells[1]->Value = Clusters[z].at(index).size().ToString();
			this->DataGridView_Clusters->Rows[index]->Cells[4]->Value = true;
		    //this->Clusters[this->TrackBar_Layers->Value].size();
		   }

		  }

		  if (this->RadioButton_3D->Checked)				// если полная кластеризация
		  {
		   	
		  }

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

private: System::Void Button_VisualizeSelectedClusters_Click(System::Object^  sender, System::EventArgs^  e) {
			 /*if (Clusters!=NULL)
			 {*/
			 bool* IsVisible = new bool [InputData->sizeX*InputData->sizeY*InputData->sizeZ];
			 
			 for (size_t z = 0; z < InputData->sizeZ; ++z)
			 for (int i = 0; i<min((int)this->DataGridView_Clusters->RowCount-1, (int)NClusters[z]); ++i)
				
				 {
					vector<size_t>::iterator iter = Clusters[z].at(i).begin();
					vector<size_t>::iterator _end = Clusters[z].at(i).end();
					for (; iter!=_end; ++iter)
						if ((bool)this->DataGridView_Clusters->Rows[i]->Cells[4]->Value ==true)
							IsVisible[*iter+z*InputData->sizeX*InputData->sizeY] = true;
						else IsVisible[*iter+z*InputData->sizeX*InputData->sizeY] = false;

				 }
				 this->StaticDelInst(IsVisible); 
		 }
};
}

