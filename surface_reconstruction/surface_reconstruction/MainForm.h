#pragma once

#include <Windows.h>

#include "glee.h"

#include "graphics.h"
#include "ScanData.h"
#include "SegmentationForm.h"

#include <stdio.h>

#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")
#pragma comment (lib,"User32.lib")
#pragma comment (lib,"gdi32.lib")

namespace surface_reconstruction {

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

        void ChangeData(ScanData* sData)
        {
            data = sData;
        }

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>

        ~MainForm()
        {
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
    private: System::Windows::Forms::Button^  buttonOpenFile;
    protected: 

    protected: 

    protected: 

    protected: 

    private: System::Windows::Forms::Label^  labelStatus;
    protected: 

    public:
        ScanData *data;
        static SegmentationForm^ segmentationForm = gcnew SegmentationForm();

    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        HDC     hDC;
        HGLRC   hRC;
        HWND    hWnd;

        GLint theBox;
        unsigned int vertexVBOID, indexVBOID, colorVBOID;

        float angleXRotation, angleYRotation;
        Point mousePosition;
        float distance;

        float maxVal;
        float brightnessMult;
    private: System::Windows::Forms::Panel^  GLWindow;
    private: System::Windows::Forms::GroupBox^  groupBoxRender;
    private: System::Windows::Forms::Timer^  timerDraw;
    private: System::Windows::Forms::OpenFileDialog^  openDataDialog;





    private: System::Windows::Forms::GroupBox^  groupBoxLoadData;
    private: System::Windows::Forms::Button^  buttonLoadData;

    private: System::Windows::Forms::TextBox^  textBoxInputFile;
    private: System::Windows::Forms::Label^  labelDataFileName;
    private: System::Windows::Forms::Label^  labelVoxelZ;
    private: System::Windows::Forms::Label^  labelVoxelY;
    private: System::Windows::Forms::Label^  labelVoxelX;
    private: System::Windows::Forms::Label^  labelLayerNum;
    private: System::Windows::Forms::Label^  labelLayerHeight;
    private: System::Windows::Forms::Label^  labelLayerWidth;
    private: System::Windows::Forms::GroupBox^  groupBoxRenderParams;
    private: System::Windows::Forms::TextBox^  textBoxLayerStart;

    private: System::Windows::Forms::Label^  labelCurrentLayer;
    private: System::Windows::Forms::TrackBar^  trackBarLayerStart;


    private: System::Windows::Forms::TextBox^  textBoxBrightnessMult;

    private: System::Windows::Forms::Label^  labelBrightnessMult;
    private: System::Windows::Forms::Button^  Segmentation;
    private: System::Windows::Forms::GroupBox^  groupBoxRenderType;
    private: System::Windows::Forms::RadioButton^  radioButtonRenderTypeVBO;
    private: System::Windows::Forms::RadioButton^  radioButtonRenderTypeImmediate;
    private: System::Windows::Forms::TrackBar^  trackBarLayerEnd;

    private: System::Windows::Forms::TextBox^  textBoxLayerEnd;
    private: System::Windows::Forms::Label^  labelLayerDistance;
    private: System::Windows::Forms::TrackBar^  trackBarLayerDistance;









    private: System::ComponentModel::IContainer^  components;



#pragma region Windows Form Designer generated code
             /// <summary>
             /// Required method for Designer support - do not modify
             /// the contents of this method with the code editor.
             /// </summary>
             void InitializeComponent(void)
             {
                 this->components = (gcnew System::ComponentModel::Container());
                 this->buttonOpenFile = (gcnew System::Windows::Forms::Button());
                 this->labelStatus = (gcnew System::Windows::Forms::Label());
                 this->GLWindow = (gcnew System::Windows::Forms::Panel());
                 this->groupBoxRender = (gcnew System::Windows::Forms::GroupBox());
                 this->timerDraw = (gcnew System::Windows::Forms::Timer(this->components));
                 this->openDataDialog = (gcnew System::Windows::Forms::OpenFileDialog());
                 this->groupBoxLoadData = (gcnew System::Windows::Forms::GroupBox());
                 this->labelVoxelZ = (gcnew System::Windows::Forms::Label());
                 this->labelVoxelY = (gcnew System::Windows::Forms::Label());
                 this->labelVoxelX = (gcnew System::Windows::Forms::Label());
                 this->labelLayerNum = (gcnew System::Windows::Forms::Label());
                 this->labelLayerHeight = (gcnew System::Windows::Forms::Label());
                 this->labelLayerWidth = (gcnew System::Windows::Forms::Label());
                 this->labelDataFileName = (gcnew System::Windows::Forms::Label());
                 this->buttonLoadData = (gcnew System::Windows::Forms::Button());
                 this->textBoxInputFile = (gcnew System::Windows::Forms::TextBox());
                 this->groupBoxRenderParams = (gcnew System::Windows::Forms::GroupBox());
                 this->labelLayerDistance = (gcnew System::Windows::Forms::Label());
                 this->trackBarLayerDistance = (gcnew System::Windows::Forms::TrackBar());
                 this->trackBarLayerEnd = (gcnew System::Windows::Forms::TrackBar());
                 this->textBoxLayerEnd = (gcnew System::Windows::Forms::TextBox());
                 this->groupBoxRenderType = (gcnew System::Windows::Forms::GroupBox());
                 this->radioButtonRenderTypeVBO = (gcnew System::Windows::Forms::RadioButton());
                 this->radioButtonRenderTypeImmediate = (gcnew System::Windows::Forms::RadioButton());
                 this->Segmentation = (gcnew System::Windows::Forms::Button());
                 this->textBoxBrightnessMult = (gcnew System::Windows::Forms::TextBox());
                 this->labelBrightnessMult = (gcnew System::Windows::Forms::Label());
                 this->textBoxLayerStart = (gcnew System::Windows::Forms::TextBox());
                 this->labelCurrentLayer = (gcnew System::Windows::Forms::Label());
                 this->trackBarLayerStart = (gcnew System::Windows::Forms::TrackBar());
                 this->groupBoxRender->SuspendLayout();
                 this->groupBoxLoadData->SuspendLayout();
                 this->groupBoxRenderParams->SuspendLayout();
                 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarLayerDistance))->BeginInit();
                 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarLayerEnd))->BeginInit();
                 this->groupBoxRenderType->SuspendLayout();
                 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarLayerStart))->BeginInit();
                 this->SuspendLayout();
                 // 
                 // buttonOpenFile
                 // 
                 this->buttonOpenFile->Location = System::Drawing::Point(6, 46);
                 this->buttonOpenFile->Name = L"buttonOpenFile";
                 this->buttonOpenFile->Size = System::Drawing::Size(104, 21);
                 this->buttonOpenFile->TabIndex = 0;
                 this->buttonOpenFile->Text = L"Открыть";
                 this->buttonOpenFile->UseVisualStyleBackColor = true;
                 this->buttonOpenFile->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
                 // 
                 // labelStatus
                 // 
                 this->labelStatus->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
                 this->labelStatus->AutoSize = true;
                 this->labelStatus->Location = System::Drawing::Point(3, 438);
                 this->labelStatus->Name = L"labelStatus";
                 this->labelStatus->Size = System::Drawing::Size(41, 13);
                 this->labelStatus->TabIndex = 1;
                 this->labelStatus->Text = L"Статус";
                 // 
                 // GLWindow
                 // 
                 this->GLWindow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
                     | System::Windows::Forms::AnchorStyles::Left) 
                     | System::Windows::Forms::AnchorStyles::Right));
                 this->GLWindow->Location = System::Drawing::Point(6, 19);
                 this->GLWindow->Name = L"GLWindow";
                 this->GLWindow->Size = System::Drawing::Size(499, 406);
                 this->GLWindow->TabIndex = 2;
                 this->GLWindow->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::GLWindow_MouseWheel);
                 this->GLWindow->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::GLWindow_MouseMove);
                 this->GLWindow->Click += gcnew System::EventHandler(this, &MainForm::GLWindow_Click);
                 this->GLWindow->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::GLWindow_MouseDown);
                 // 
                 // groupBoxRender
                 // 
                 this->groupBoxRender->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
                     | System::Windows::Forms::AnchorStyles::Left) 
                     | System::Windows::Forms::AnchorStyles::Right));
                 this->groupBoxRender->Controls->Add(this->GLWindow);
                 this->groupBoxRender->Location = System::Drawing::Point(6, 4);
                 this->groupBoxRender->Name = L"groupBoxRender";
                 this->groupBoxRender->Size = System::Drawing::Size(511, 431);
                 this->groupBoxRender->TabIndex = 3;
                 this->groupBoxRender->TabStop = false;
                 this->groupBoxRender->Text = L"Окно демонстрации";
                 // 
                 // timerDraw
                 // 
                 this->timerDraw->Enabled = true;
                 this->timerDraw->Interval = 30;
                 this->timerDraw->Tick += gcnew System::EventHandler(this, &MainForm::DrawTimer_Tick);
                 // 
                 // openDataDialog
                 // 
                 this->openDataDialog->FileName = L"*.bin";
                 this->openDataDialog->Filter = L"Bin files(*.bin)|*.bin|All Files(*.*)|*.*";
                 this->openDataDialog->Title = L"Open an Existing Document";
                 // 
                 // groupBoxLoadData
                 // 
                 this->groupBoxLoadData->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
                 this->groupBoxLoadData->Controls->Add(this->labelVoxelZ);
                 this->groupBoxLoadData->Controls->Add(this->labelVoxelY);
                 this->groupBoxLoadData->Controls->Add(this->labelVoxelX);
                 this->groupBoxLoadData->Controls->Add(this->labelLayerNum);
                 this->groupBoxLoadData->Controls->Add(this->labelLayerHeight);
                 this->groupBoxLoadData->Controls->Add(this->labelLayerWidth);
                 this->groupBoxLoadData->Controls->Add(this->labelDataFileName);
                 this->groupBoxLoadData->Controls->Add(this->buttonLoadData);
                 this->groupBoxLoadData->Controls->Add(this->textBoxInputFile);
                 this->groupBoxLoadData->Controls->Add(this->buttonOpenFile);
                 this->groupBoxLoadData->Location = System::Drawing::Point(523, 4);
                 this->groupBoxLoadData->Name = L"groupBoxLoadData";
                 this->groupBoxLoadData->Size = System::Drawing::Size(217, 133);
                 this->groupBoxLoadData->TabIndex = 5;
                 this->groupBoxLoadData->TabStop = false;
                 this->groupBoxLoadData->Text = L"Данные";
                 // 
                 // labelVoxelZ
                 // 
                 this->labelVoxelZ->AutoSize = true;
                 this->labelVoxelZ->Location = System::Drawing::Point(111, 109);
                 this->labelVoxelZ->Name = L"labelVoxelZ";
                 this->labelVoxelZ->Size = System::Drawing::Size(74, 13);
                 this->labelVoxelZ->TabIndex = 9;
                 this->labelVoxelZ->Text = L"Размер по Z:";
                 // 
                 // labelVoxelY
                 // 
                 this->labelVoxelY->AutoSize = true;
                 this->labelVoxelY->Location = System::Drawing::Point(111, 96);
                 this->labelVoxelY->Name = L"labelVoxelY";
                 this->labelVoxelY->Size = System::Drawing::Size(74, 13);
                 this->labelVoxelY->TabIndex = 8;
                 this->labelVoxelY->Text = L"Размер по Y:";
                 // 
                 // labelVoxelX
                 // 
                 this->labelVoxelX->AutoSize = true;
                 this->labelVoxelX->Location = System::Drawing::Point(111, 83);
                 this->labelVoxelX->Name = L"labelVoxelX";
                 this->labelVoxelX->Size = System::Drawing::Size(74, 13);
                 this->labelVoxelX->TabIndex = 7;
                 this->labelVoxelX->Text = L"Размер по X:";
                 // 
                 // labelLayerNum
                 // 
                 this->labelLayerNum->AutoSize = true;
                 this->labelLayerNum->Location = System::Drawing::Point(2, 109);
                 this->labelLayerNum->Name = L"labelLayerNum";
                 this->labelLayerNum->Size = System::Drawing::Size(77, 13);
                 this->labelLayerNum->TabIndex = 6;
                 this->labelLayerNum->Text = L"Кол-во слоев:";
                 // 
                 // labelLayerHeight
                 // 
                 this->labelLayerHeight->AutoSize = true;
                 this->labelLayerHeight->Location = System::Drawing::Point(2, 96);
                 this->labelLayerHeight->Name = L"labelLayerHeight";
                 this->labelLayerHeight->Size = System::Drawing::Size(75, 13);
                 this->labelLayerHeight->TabIndex = 5;
                 this->labelLayerHeight->Text = L"Высота слоя:";
                 // 
                 // labelLayerWidth
                 // 
                 this->labelLayerWidth->AutoSize = true;
                 this->labelLayerWidth->Location = System::Drawing::Point(2, 83);
                 this->labelLayerWidth->Name = L"labelLayerWidth";
                 this->labelLayerWidth->Size = System::Drawing::Size(76, 13);
                 this->labelLayerWidth->TabIndex = 4;
                 this->labelLayerWidth->Text = L"Ширина слоя:";
                 // 
                 // labelDataFileName
                 // 
                 this->labelDataFileName->AutoSize = true;
                 this->labelDataFileName->Location = System::Drawing::Point(2, 70);
                 this->labelDataFileName->Name = L"labelDataFileName";
                 this->labelDataFileName->Size = System::Drawing::Size(39, 13);
                 this->labelDataFileName->TabIndex = 3;
                 this->labelDataFileName->Text = L"Файл:";
                 // 
                 // buttonLoadData
                 // 
                 this->buttonLoadData->Location = System::Drawing::Point(116, 46);
                 this->buttonLoadData->Name = L"buttonLoadData";
                 this->buttonLoadData->Size = System::Drawing::Size(94, 22);
                 this->buttonLoadData->TabIndex = 2;
                 this->buttonLoadData->Text = L"Загрузить";
                 this->buttonLoadData->UseVisualStyleBackColor = true;
                 this->buttonLoadData->Click += gcnew System::EventHandler(this, &MainForm::buttonLoadData_Click);
                 // 
                 // textBoxInputFile
                 // 
                 this->textBoxInputFile->Location = System::Drawing::Point(6, 20);
                 this->textBoxInputFile->Name = L"textBoxInputFile";
                 this->textBoxInputFile->Size = System::Drawing::Size(204, 20);
                 this->textBoxInputFile->TabIndex = 1;
                 // 
                 // groupBoxRenderParams
                 // 
                 this->groupBoxRenderParams->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
                     | System::Windows::Forms::AnchorStyles::Right));
                 this->groupBoxRenderParams->Controls->Add(this->labelLayerDistance);
                 this->groupBoxRenderParams->Controls->Add(this->trackBarLayerDistance);
                 this->groupBoxRenderParams->Controls->Add(this->trackBarLayerEnd);
                 this->groupBoxRenderParams->Controls->Add(this->textBoxLayerEnd);
                 this->groupBoxRenderParams->Controls->Add(this->groupBoxRenderType);
                 this->groupBoxRenderParams->Controls->Add(this->Segmentation);
                 this->groupBoxRenderParams->Controls->Add(this->textBoxBrightnessMult);
                 this->groupBoxRenderParams->Controls->Add(this->labelBrightnessMult);
                 this->groupBoxRenderParams->Controls->Add(this->textBoxLayerStart);
                 this->groupBoxRenderParams->Controls->Add(this->labelCurrentLayer);
                 this->groupBoxRenderParams->Controls->Add(this->trackBarLayerStart);
                 this->groupBoxRenderParams->Location = System::Drawing::Point(523, 143);
                 this->groupBoxRenderParams->Name = L"groupBoxRenderParams";
                 this->groupBoxRenderParams->Size = System::Drawing::Size(216, 292);
                 this->groupBoxRenderParams->TabIndex = 6;
                 this->groupBoxRenderParams->TabStop = false;
                 this->groupBoxRenderParams->Text = L"Параметры визуализации";
                 // 
                 // labelLayerDistance
                 // 
                 this->labelLayerDistance->AutoSize = true;
                 this->labelLayerDistance->Location = System::Drawing::Point(10, 176);
                 this->labelLayerDistance->Name = L"labelLayerDistance";
                 this->labelLayerDistance->Size = System::Drawing::Size(147, 13);
                 this->labelLayerDistance->TabIndex = 10;
                 this->labelLayerDistance->Text = L"Расстояние между слоями:";
                 // 
                 // trackBarLayerDistance
                 // 
                 this->trackBarLayerDistance->Location = System::Drawing::Point(9, 192);
                 this->trackBarLayerDistance->Maximum = 150;
                 this->trackBarLayerDistance->Minimum = 1;
                 this->trackBarLayerDistance->Name = L"trackBarLayerDistance";
                 this->trackBarLayerDistance->Size = System::Drawing::Size(200, 45);
                 this->trackBarLayerDistance->TabIndex = 9;
                 this->trackBarLayerDistance->Value = 50;
                 // 
                 // trackBarLayerEnd
                 // 
                 this->trackBarLayerEnd->Location = System::Drawing::Point(6, 141);
                 this->trackBarLayerEnd->Maximum = 0;
                 this->trackBarLayerEnd->Name = L"trackBarLayerEnd";
                 this->trackBarLayerEnd->Size = System::Drawing::Size(204, 45);
                 this->trackBarLayerEnd->TabIndex = 8;
                 this->trackBarLayerEnd->ValueChanged += gcnew System::EventHandler(this, &MainForm::trackBarLayerEnd_ValueChanged);
                 // 
                 // textBoxLayerEnd
                 // 
                 this->textBoxLayerEnd->Location = System::Drawing::Point(164, 94);
                 this->textBoxLayerEnd->Name = L"textBoxLayerEnd";
                 this->textBoxLayerEnd->Size = System::Drawing::Size(36, 20);
                 this->textBoxLayerEnd->TabIndex = 7;
                 this->textBoxLayerEnd->Text = L"0";
                 this->textBoxLayerEnd->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
                 this->textBoxLayerEnd->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxLayerEnd_TextChanged);
                 // 
                 // groupBoxRenderType
                 // 
                 this->groupBoxRenderType->Controls->Add(this->radioButtonRenderTypeVBO);
                 this->groupBoxRenderType->Controls->Add(this->radioButtonRenderTypeImmediate);
                 this->groupBoxRenderType->Location = System::Drawing::Point(6, 19);
                 this->groupBoxRenderType->Name = L"groupBoxRenderType";
                 this->groupBoxRenderType->Size = System::Drawing::Size(204, 69);
                 this->groupBoxRenderType->TabIndex = 6;
                 this->groupBoxRenderType->TabStop = false;
                 this->groupBoxRenderType->Text = L"Метод визуализации";
                 // 
                 // radioButtonRenderTypeVBO
                 // 
                 this->radioButtonRenderTypeVBO->AutoSize = true;
                 this->radioButtonRenderTypeVBO->Checked = true;
                 this->radioButtonRenderTypeVBO->Location = System::Drawing::Point(7, 42);
                 this->radioButtonRenderTypeVBO->Name = L"radioButtonRenderTypeVBO";
                 this->radioButtonRenderTypeVBO->Size = System::Drawing::Size(120, 17);
                 this->radioButtonRenderTypeVBO->TabIndex = 1;
                 this->radioButtonRenderTypeVBO->TabStop = true;
                 this->radioButtonRenderTypeVBO->Text = L"Vertex Buffer Object";
                 this->radioButtonRenderTypeVBO->UseVisualStyleBackColor = true;
                 this->radioButtonRenderTypeVBO->CheckedChanged += gcnew System::EventHandler(this, &MainForm::radioButtonRenderTypeVBO_CheckedChanged);
                 // 
                 // radioButtonRenderTypeImmediate
                 // 
                 this->radioButtonRenderTypeImmediate->AutoSize = true;
                 this->radioButtonRenderTypeImmediate->Location = System::Drawing::Point(7, 19);
                 this->radioButtonRenderTypeImmediate->Name = L"radioButtonRenderTypeImmediate";
                 this->radioButtonRenderTypeImmediate->Size = System::Drawing::Size(73, 17);
                 this->radioButtonRenderTypeImmediate->TabIndex = 0;
                 this->radioButtonRenderTypeImmediate->Text = L"Immediate";
                 this->radioButtonRenderTypeImmediate->UseVisualStyleBackColor = true;
                 // 
                 // Segmentation
                 // 
                 this->Segmentation->Enabled = false;
                 this->Segmentation->Location = System::Drawing::Point(13, 256);
                 this->Segmentation->Name = L"Segmentation";
                 this->Segmentation->Size = System::Drawing::Size(92, 23);
                 this->Segmentation->TabIndex = 5;
                 this->Segmentation->Text = L"сегментация";
                 this->Segmentation->UseVisualStyleBackColor = true;
                 this->Segmentation->Click += gcnew System::EventHandler(this, &MainForm::Segmentation_Click);
                 // 
                 // textBoxBrightnessMult
                 // 
                 this->textBoxBrightnessMult->Location = System::Drawing::Point(133, 237);
                 this->textBoxBrightnessMult->Name = L"textBoxBrightnessMult";
                 this->textBoxBrightnessMult->Size = System::Drawing::Size(67, 20);
                 this->textBoxBrightnessMult->TabIndex = 4;
                 this->textBoxBrightnessMult->Text = L"30,0";
                 this->textBoxBrightnessMult->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
                 this->textBoxBrightnessMult->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxBrightnessMult_TextChanged);
                 // 
                 // labelBrightnessMult
                 // 
                 this->labelBrightnessMult->AutoSize = true;
                 this->labelBrightnessMult->Location = System::Drawing::Point(10, 240);
                 this->labelBrightnessMult->Name = L"labelBrightnessMult";
                 this->labelBrightnessMult->Size = System::Drawing::Size(112, 13);
                 this->labelBrightnessMult->TabIndex = 3;
                 this->labelBrightnessMult->Text = L"Множитель яркости:";
                 // 
                 // textBoxLayerStart
                 // 
                 this->textBoxLayerStart->Location = System::Drawing::Point(121, 94);
                 this->textBoxLayerStart->Name = L"textBoxLayerStart";
                 this->textBoxLayerStart->Size = System::Drawing::Size(36, 20);
                 this->textBoxLayerStart->TabIndex = 2;
                 this->textBoxLayerStart->Text = L"0";
                 this->textBoxLayerStart->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
                 this->textBoxLayerStart->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxCurrentLayer_TextChanged);
                 // 
                 // labelCurrentLayer
                 // 
                 this->labelCurrentLayer->AutoSize = true;
                 this->labelCurrentLayer->Location = System::Drawing::Point(6, 96);
                 this->labelCurrentLayer->Name = L"labelCurrentLayer";
                 this->labelCurrentLayer->Size = System::Drawing::Size(115, 13);
                 this->labelCurrentLayer->TabIndex = 1;
                 this->labelCurrentLayer->Text = L"Визуализация слоев:";
                 // 
                 // trackBarLayerStart
                 // 
                 this->trackBarLayerStart->Location = System::Drawing::Point(6, 112);
                 this->trackBarLayerStart->Maximum = 0;
                 this->trackBarLayerStart->Name = L"trackBarLayerStart";
                 this->trackBarLayerStart->Size = System::Drawing::Size(204, 45);
                 this->trackBarLayerStart->TabIndex = 0;
                 this->trackBarLayerStart->ValueChanged += gcnew System::EventHandler(this, &MainForm::trackBarLayer_ValueChanged);
                 // 
                 // MainForm
                 // 
                 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
                 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
                 this->ClientSize = System::Drawing::Size(744, 453);
                 this->Controls->Add(this->groupBoxRenderParams);
                 this->Controls->Add(this->groupBoxLoadData);
                 this->Controls->Add(this->groupBoxRender);
                 this->Controls->Add(this->labelStatus);
                 this->DoubleBuffered = true;
                 this->MinimumSize = System::Drawing::Size(640, 480);
                 this->Name = L"MainForm";
                 this->Text = L"Аццкая рисовалка";
                 this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
                 this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
                 this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
                 this->groupBoxRender->ResumeLayout(false);
                 this->groupBoxLoadData->ResumeLayout(false);
                 this->groupBoxLoadData->PerformLayout();
                 this->groupBoxRenderParams->ResumeLayout(false);
                 this->groupBoxRenderParams->PerformLayout();
                 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarLayerDistance))->EndInit();
                 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarLayerEnd))->EndInit();
                 this->groupBoxRenderType->ResumeLayout(false);
                 this->groupBoxRenderType->PerformLayout();
                 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarLayerStart))->EndInit();
                 this->ResumeLayout(false);
                 this->PerformLayout();

             }
#pragma endregion
    private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
                 if (this->openDataDialog->ShowDialog() == Windows::Forms::DialogResult::OK) {
                     this->textBoxInputFile->Text = this->openDataDialog->FileName;
                     textBoxInputFile->Select(textBoxInputFile->Text->Length, 0);
                     textBoxInputFile->ScrollToCaret();
                     angleXRotation = angleYRotation = 0.0f;
                 }
             }

    private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
                 GLuint PixelFormat;

                 hWnd = (HWND)(intptr_t)this->GLWindow->Handle;
                 hDC = GetDC(hWnd);
                 if (!hDC) {
                     this->labelStatus->Text = L"Can't Create A GL Device Context";
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
                     this->labelStatus->Text = L"Can't Find A Suitable PixelFormat.";
                     return;
                 }
                 if (!SetPixelFormat(hDC, PixelFormat, &pfd)) {
                     this->labelStatus->Text = L"Can't Set The PixelFormat.";
                     return;
                 }
                 hRC = wglCreateContext(hDC);
                 if (!hRC) {
                     this->labelStatus->Text = L"Can't Create A GL Rendering Context. GetLastError: " + GetLastError();
                     return;
                 }
                 if (!wglMakeCurrent(hDC, hRC)) {
                     this->labelStatus->Text = L"Can't Activate The GL Rendering Context.";
                     return;
                 }
                 this->labelStatus->Text = L"GL context created!";

                 MainForm_Resize(sender, e);

                 if (!InitGL()) {
                     this->labelStatus->Text = L"Failed to init GL";
                 }

                 theBox = glGenLists(1);
                 glNewList(theBox, GL_COMPILE);
                 glBegin(GL_QUADS); {
                     // front face
                     //glNormal3f(0.0f, 0.0f, 1.0f);
                     glVertex3f(0.5f, 0.5f, 0.5f);
                     glVertex3f(0.5f, -0.5f, 0.5f);
                     glVertex3f(-0.5f, -0.5f, 0.5f);
                     glVertex3f(-0.5f, 0.5f, 0.5f);

                     // left face
                     //glNormal3f(-1.0f, 0.0f, 0.0f);
                     glVertex3f(-0.5f, 0.5f, 0.5f);
                     glVertex3f(-0.5f, -0.5f, 0.5f);
                     glVertex3f(-0.5f, -0.5f, -0.5f);
                     glVertex3f(-0.5f, 0.5f, -0.5f);

                     // back face
                     //glNormal3f(0.0f, 0.0f, -1.0f);
                     glVertex3f(-0.5f, 0.5f, -0.5f);
                     glVertex3f(-0.5f, -0.5f, -0.5f);
                     glVertex3f(0.5f, -0.5f, -0.5f);
                     glVertex3f(0.5f, 0.5f, -0.5f);

                     // right face
                     //glNormal3f(1.0f, 0.0f, 0.0f);
                     glVertex3f(0.5f, 0.5f, -0.5f);
                     glVertex3f(0.5f, -0.5f, -0.5f);
                     glVertex3f(0.5f, -0.5f, 0.5f);
                     glVertex3f(0.5f, 0.5f, 0.5f);

                     // top face
                     //glNormal3f(0.0f, 1.0f, 0.0f);
                     glVertex3f(-0.5f, 0.5f, -0.5f);
                     glVertex3f(0.5f, 0.5f, -0.5f);
                     glVertex3f(0.5f, 0.5f, 0.5f);
                     glVertex3f(-0.5f, 0.5f, 0.5f);

                     // bottom face
                     //glNormal3f(0.0f, -1.0f, 0.0f);
                     glVertex3f(-0.5f, -0.5f, 0.5f);
                     glVertex3f(0.5f, -0.5f, 0.5f);
                     glVertex3f(0.5f, -0.5f, -0.5f);
                     glVertex3f(-0.5f, -0.5f, -0.5f);
                 }
                 glEnd();
                 glEndList();

                 data = new ScanData();
             }

    private: System::Void MainForm_Resize(System::Object^  sender, System::EventArgs^  e) {
                 GLsizei height = this->GLWindow->Height;
                 GLsizei width = this->GLWindow->Width;
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

    private: Void DrawGLScene() {
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

                 if (data && data->data) {
                     if (radioButtonRenderTypeImmediate->Checked) {
                         for (size_t iLayer = trackBarLayerStart->Value; iLayer < trackBarLayerEnd->Value + 1; ++iLayer) {
                             RenderLayer(iLayer);
                         }
                     }
                     else if (radioButtonRenderTypeVBO->Checked) {
                         glBindBuffer(GL_ARRAY_BUFFER, vertexVBOID);
                         glEnableClientState(GL_VERTEX_ARRAY);
                         glVertexPointer(3, GL_FLOAT, 0, 0);

                         glBindBuffer(GL_ARRAY_BUFFER, colorVBOID);
                         glEnableClientState(GL_COLOR_ARRAY);

                         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);

                         float localSift = -((float)(trackBarLayerEnd->Value - trackBarLayerStart->Value) * data->scaleZ * trackBarLayerDistance->Value / 2.0f);
                         glTranslatef(0.0f, 0.0f, localSift);
                         for (size_t iLayer = trackBarLayerStart->Value; iLayer < trackBarLayerEnd->Value + 1; ++iLayer) {
                             glTranslatef(0.0f, 0.0f, -localSift * 2 / (trackBarLayerEnd->Value - trackBarLayerStart->Value + 1));
                             glColorPointer(3, GL_FLOAT, 0, (char*)(iLayer * data->sizeX * data->sizeY * 24 * sizeof(float)));
                             glDrawElements(GL_QUADS, data->sizeX * data->sizeY * 24, GL_UNSIGNED_INT, 0);
                         }

                         glDisableClientState(GL_VERTEX_ARRAY);
                         glDisableClientState(GL_COLOR_ARRAY);

                         glBindBuffer(GL_ARRAY_BUFFER, 0);
                         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                     }
                 }
             }

    private: Void RenderLayer(size_t iLayer) {
                 glScalef(data->scaleX, data->scaleY, data->scaleZ);
                 glPushMatrix();
                 float localSift = -((float)(trackBarLayerEnd->Value - trackBarLayerStart->Value) * data->scaleZ * trackBarLayerDistance->Value / 2.0f);
                 localSift -= localSift * 2 * (iLayer - trackBarLayerStart->Value) / (trackBarLayerEnd->Value - trackBarLayerStart->Value + 1);
                 glTranslatef(((float)(data->sizeX / 2) * data->scaleX), ((float)(data->sizeY / 2) * data->scaleY), localSift);
                 for (size_t iColumn = 0; iColumn < data->sizeX; ++iColumn) {
                     for (size_t iRow = 0; iRow < data->sizeY; ++iRow) {
                         glTranslatef(0.0f, -data->scaleY, 0.0f);
                         float grayIntense = (float)(data->data[iRow + iColumn * data->sizeY + iLayer * data->sizeX * data->sizeY]) / maxVal;
                         grayIntense *= brightnessMult;
                         glColor3f(grayIntense, grayIntense, grayIntense);
                         glCallList(theBox);
                     }
                     glTranslatef(-data->scaleX, data->sizeY * data->scaleY, 0.0f);
                 }
                 glPopMatrix();
             }

    private: System::Void DrawTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
                 System::DateTime timeBefore = DateTime::Now;
                 DrawGLScene();
                 System::DateTime timeAfter = DateTime::Now;
                 TimeSpan ts = timeAfter - timeBefore;
                 this->Text = L"Время отрисовки кадра: " + ts.Milliseconds + L"ms";
                 SwapBuffers(hDC);
             }

    private: System::Void buttonLoadData_Click(System::Object^  sender, System::EventArgs^  e) {
                 String ^pathToDataFile = this->textBoxInputFile->Text;
                 if (System::IO::File::Exists(pathToDataFile)) {
                     pathToDataFile = pathToDataFile->Replace("\\","\\\\");
                     if (data->LoadData((char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(pathToDataFile).ToPointer())) {
                         this->labelStatus->Text = L"Data was loaded.";

                         float fileSize = (float)(IO::FileInfo(pathToDataFile).Length >> 20);
                         this->labelDataFileName->Text = L"Файл: " + pathToDataFile->Substring(pathToDataFile->LastIndexOf("\\")+1) +
                             L" (" + fileSize + L" MB)";

                         this->labelLayerWidth->Text = L"Ширина слоя: " + data->sizeX;
                         this->labelLayerHeight->Text = L"Высота слоя: " + data->sizeY;
                         this->labelLayerNum->Text = L"Кол-во слоев: " + data->sizeZ;

                         this->labelVoxelX->Text = L"Размер по X: " + data->scaleX;
                         this->labelVoxelY->Text = L"Размер по Y: " + data->scaleY;
                         this->labelVoxelZ->Text = L"Размер по Z: " + data->scaleZ;

                         maxVal = 0;
                         for (size_t i = 10; i < data->sizeX * data->sizeY * data->sizeZ; ++i) {
                             if (maxVal < data->data[i]) {
                                 maxVal = data->data[i];
                             }
                         }

                         angleXRotation = angleYRotation = 0.0f;
                         distance = 600.f;

                         this->textBoxBrightnessMult->Text = L"30,0";
                         brightnessMult = 30.f;

                         this->trackBarLayerStart->Maximum = data->sizeZ - 1;
                         this->trackBarLayerStart->Value = 0;

                         this->trackBarLayerEnd->Maximum = data->sizeZ - 1;
                         this->trackBarLayerEnd->Value = 0;

                         radioButtonRenderTypeVBO_CheckedChanged(sender, e);

                         segmentationForm->data = data;
                         Segmentation->Enabled = true;
                     } else {
                         this->labelStatus->Text = "Error. Incorrect reading input data file.";
                     }
                 } else {
                     this->labelStatus->Text = "Error. Input data file not exist.";
                 }             
             }
    private: System::Void trackBarLayer_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (this->trackBarLayerStart->Value <= this->trackBarLayerEnd->Value) {
                     this->textBoxLayerStart->Text = this->trackBarLayerStart->Value.ToString();
                 }
                 else {
                     this->trackBarLayerStart->Value = this->trackBarLayerEnd->Value;
                 }
             }

    private: System::Void trackBarLayerEnd_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (this->trackBarLayerEnd->Value >= this->trackBarLayerStart->Value) {
                     this->textBoxLayerEnd->Text = this->trackBarLayerEnd->Value.ToString();
                 }
                 else {
                     this->trackBarLayerEnd->Value = this->trackBarLayerStart->Value;
                 }
             }

    private: System::Void generateVBOData() {
                 // creating VBO for vertecies
                 float *vertexBuffer;
                 vertexBuffer = new float[data->sizeX * data->sizeY * 8 * 3];
                 for (size_t iColumn = 0; iColumn < data->sizeX; ++iColumn) {
                     for (size_t iRow = 0; iRow < data->sizeY; ++iRow) {
                         if (iRow == 0) {
                             float vert[8*3] = {
                                 +0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), +0.5f + (float)(data->sizeY / 2) * data->scaleY, -0.5f,
                                 +0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), -0.5f + (float)(data->sizeY / 2) * data->scaleY, -0.5f,
                                 -0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), -0.5f + (float)(data->sizeY / 2) * data->scaleY, -0.5f,
                                 -0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), +0.5f + (float)(data->sizeY / 2) * data->scaleY, -0.5f,
                                 +0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), +0.5f + (float)(data->sizeY / 2) * data->scaleY, +0.5f,
                                 +0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), -0.5f + (float)(data->sizeY / 2) * data->scaleY, +0.5f,
                                 -0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), -0.5f + (float)(data->sizeY / 2) * data->scaleY, +0.5f,
                                 -0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), +0.5f + (float)(data->sizeY / 2) * data->scaleY, +0.5f};

                                 size_t base = iColumn * data->sizeY;
                                 memcpy(vertexBuffer + base * 8 * 3, vert, sizeof(vert));

                                 continue;
                         }
                         else {
                             unsigned int curIndex = iRow + iColumn * data->sizeY;
                             memcpy(vertexBuffer + (curIndex) * 8 * 3,
                                 vertexBuffer + (curIndex - 1) * 8 * 3,
                                 sizeof(float) * 8 * 3);
                             for (int i = 1; i < 24; i += 3) {
                                 vertexBuffer[curIndex * 8 * 3 + i] -= data->scaleY;
                             }
                         }
                     }
                 }

                 unsigned int tmp;

                 if (vertexVBOID != 0) {
                     tmp = vertexVBOID;
                     glDeleteBuffers(1, &tmp);
                 }

                 glGenBuffers(1, &tmp);
                 vertexVBOID = tmp;
                 glBindBuffer(GL_ARRAY_BUFFER, vertexVBOID);
                 glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data->sizeX * data->sizeY * 24, vertexBuffer, GL_STATIC_DRAW);

                 delete vertexBuffer;

                 // creating VBO for indicies
                 unsigned int ind[24] = {0, 1, 2, 3,
                     3, 2, 6, 7,
                     7, 6, 5, 4,
                     4, 5, 1, 0,
                     4, 0, 3, 7,
                     1, 5, 6, 2};

                 unsigned int *indicesBuffer;
                 indicesBuffer = new unsigned int[data->sizeX * data->sizeY * 6 * 4];
                 for (size_t i = 0; i < data->sizeX * data->sizeY * 24; i += 24) {
                     memcpy(indicesBuffer + i, ind, sizeof(ind));
                     for (size_t j = 0; j < 24; ++j) {
                         ind[j] += 8;
                     }
                 }

                 if (indexVBOID != 0) {
                     tmp = indexVBOID;
                     glDeleteBuffers(1, &tmp);
                 }

                 glGenBuffers(1, &tmp);
                 indexVBOID = tmp;
                 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);
                 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data->sizeX * data->sizeY * 24, indicesBuffer, GL_STATIC_DRAW);

                 delete indicesBuffer;

                 // creating VBO for colors
                 float *colorBuffer;
                 colorBuffer = new float[data->sizeX * data->sizeY * data->sizeZ * 8 * 3];
                 for (size_t i = 0; i < data->sizeX * data->sizeY * data->sizeZ; ++i) {
                     float curColor = data->data[i] / maxVal * brightnessMult;
                     for (size_t idx = 0; idx < 24; idx++) {
                         colorBuffer[i*24 + idx] = curColor;
                     }
                 }

                 if (colorVBOID != 0) {
                     tmp = colorVBOID;
                     glDeleteBuffers(1, &tmp);
                 }

                 glGenBuffers(1, &tmp);
                 colorVBOID = tmp;
                 glBindBuffer(GL_ARRAY_BUFFER, colorVBOID);
                 glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data->sizeX * data->sizeY * data->sizeZ * 24, colorBuffer, GL_STATIC_DRAW);

                 delete colorBuffer;
             }

    private: System::Void textBoxCurrentLayer_TextChanged(System::Object^  sender, System::EventArgs^  e) {
                 Int32 curValue;
                 try {
                     curValue = Int32::Parse(this->textBoxLayerStart->Text);
                 } catch (...) {
                     this->labelStatus->Text = "Error. Layer value should be unsigned int.";
                     return;
                 }
                 if (curValue >= 0 && curValue < Int32::Parse(this->textBoxLayerEnd->Text)) {
                     this->trackBarLayerStart->Value = curValue;
                 } else {
                     this->labelStatus->Text = "Error. Layer should be in range [0;" + this->textBoxLayerEnd->Text + L"].";
                 }
             }

    private: System::Void textBoxLayerEnd_TextChanged(System::Object^  sender, System::EventArgs^  e) {
                 Int32 curValue;
                 try {
                     curValue = Int32::Parse(this->textBoxLayerEnd->Text);
                 } catch (...) {
                     this->labelStatus->Text = "Error. Layer value should be unsigned int.";
                     return;
                 }
                 if (curValue >= Int32::Parse(this->textBoxLayerStart->Text) && curValue < data->sizeZ) {
                     this->trackBarLayerEnd->Value = curValue;
                 } else {
                     this->labelStatus->Text = "Error. Layer should be in range [" + this->textBoxLayerEnd->Text +";" + (data->sizeZ - 1) + L"].";
                 }
             }

    private: System::Void GLWindow_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
                 if (e->Button == Windows::Forms::MouseButtons::Left) {
                     Point tmpPosition = mousePosition;
                     mousePosition = e->Location;
                     angleXRotation -= tmpPosition.X - mousePosition.X;
                     angleYRotation += tmpPosition.Y - mousePosition.Y;
                 }
             }

    private: System::Void GLWindow_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
                 if (e->Button == Windows::Forms::MouseButtons::Left) {
                     mousePosition = e->Location;
                 }
             }

    private: System::Void GLWindow_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
                 distance *= (e->Delta < 0) ? (float)Math::Abs(0.66 * e->Delta / 120) :
                     (float)Math::Abs(1.33 * e->Delta / 120);
             }

    private: System::Void textBoxBrightnessMult_TextChanged(System::Object^  sender, System::EventArgs^  e) {
                 try {
                     brightnessMult = (float)Double::Parse(this->textBoxBrightnessMult->Text);
                 } catch (...) {
                     this->labelStatus->Text = L"Invalid number format for brightness mult.";
                 }
             }
    private: System::Void GLWindow_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->GLWindow->Focus();
             }
    private: System::Void Segmentation_Click(System::Object^  sender, System::EventArgs^  e) {
                 segmentationForm->StaticDelInst = gcnew MyDel(this, &MainForm::ChangeData);
                 segmentationForm->Show();             
             }
    private: System::Void radioButtonRenderTypeVBO_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (radioButtonRenderTypeVBO->Checked) {
                     generateVBOData();
                 }
                 else {
                     unsigned int tmp;

                     if (vertexVBOID != 0) {
                         tmp = vertexVBOID;
                         glDeleteBuffers(1, &tmp);
                     }

                     if (colorVBOID != 0) {
                         tmp = colorVBOID;
                         glDeleteBuffers(1, &tmp);
                     }

                     if (indexVBOID != 0) {
                         tmp = indexVBOID;
                         glDeleteBuffers(1, &tmp);
                     }
                 }
             }
    };
}

