#pragma once

#include <Windows.h>

#include "glee.h"

#include "graphics.h"
#include "ScanData.h"

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
            generateTextures();
        }

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>

        ~MainForm()
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
    private: void ReleaseTextures() {
                 if (layerTextures) { 
                    glDeleteTextures(data->sizeZ, layerTextures);
                    delete layerTextures;
                    layerTextures = 0;
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
        MyDel ^ StaticDelInst;
    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        HDC     hDC;
        HGLRC   hRC;
        HWND    hWnd;

        GLint theBox;
        GLuint vertexVBOID, indexVBOID, colorVBOID;
        GLuint *layerTextures, shaderTexture;

        GLuint vertShader, fragShader, shaderProg;

        float angleXRotation, angleYRotation;
        Point mousePosition;
        float distance;
        float alphaTestValue;
        float depth;

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

    private: System::Windows::Forms::GroupBox^  groupBoxRenderType;
    private: System::Windows::Forms::RadioButton^  radioButtonRenderTypeVBO;
    private: System::Windows::Forms::RadioButton^  radioButtonRenderTypeImmediate;
    private: System::Windows::Forms::TrackBar^  trackBarLayerEnd;

    private: System::Windows::Forms::TextBox^  textBoxLayerEnd;
    private: System::Windows::Forms::Label^  labelLayerDistance;
    private: System::Windows::Forms::TrackBar^  trackBarLayerDistance;
private: System::Windows::Forms::CheckBox^  checkBoxTransperancy;
private: System::Windows::Forms::RadioButton^  radioButtonRenderTypeTexture;
private: System::Windows::Forms::CheckBox^  checkBoxDepthTest;
private: System::Windows::Forms::TextBox^  textBoxAlphaTest;
private: System::Windows::Forms::RadioButton^  radioButtonRenderTypeTexture3D;

private: System::Windows::Forms::Label^  labelAlphaValue;
private: System::Windows::Forms::TrackBar^  trackBarAlphaValue;
private: System::Windows::Forms::CheckBox^  checkBoxAlphaTest;
private: System::Windows::Forms::CheckBox^  checkBoxOneLayer;
private: System::Windows::Forms::TrackBar^  trackBarBrightMult;
private: System::Windows::Forms::RadioButton^  radioButtonRenderTypeShader;
private: System::Windows::Forms::Button^  buttonShaderRecompile;














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
                 this->trackBarBrightMult = (gcnew System::Windows::Forms::TrackBar());
                 this->checkBoxOneLayer = (gcnew System::Windows::Forms::CheckBox());
                 this->labelAlphaValue = (gcnew System::Windows::Forms::Label());
                 this->trackBarAlphaValue = (gcnew System::Windows::Forms::TrackBar());
                 this->checkBoxAlphaTest = (gcnew System::Windows::Forms::CheckBox());
                 this->textBoxAlphaTest = (gcnew System::Windows::Forms::TextBox());
                 this->checkBoxDepthTest = (gcnew System::Windows::Forms::CheckBox());
                 this->checkBoxTransperancy = (gcnew System::Windows::Forms::CheckBox());
                 this->labelLayerDistance = (gcnew System::Windows::Forms::Label());
                 this->trackBarLayerDistance = (gcnew System::Windows::Forms::TrackBar());
                 this->trackBarLayerEnd = (gcnew System::Windows::Forms::TrackBar());
                 this->textBoxLayerEnd = (gcnew System::Windows::Forms::TextBox());
                 this->groupBoxRenderType = (gcnew System::Windows::Forms::GroupBox());
                 this->buttonShaderRecompile = (gcnew System::Windows::Forms::Button());
                 this->radioButtonRenderTypeShader = (gcnew System::Windows::Forms::RadioButton());
                 this->radioButtonRenderTypeTexture3D = (gcnew System::Windows::Forms::RadioButton());
                 this->radioButtonRenderTypeTexture = (gcnew System::Windows::Forms::RadioButton());
                 this->radioButtonRenderTypeVBO = (gcnew System::Windows::Forms::RadioButton());
                 this->radioButtonRenderTypeImmediate = (gcnew System::Windows::Forms::RadioButton());
                 this->textBoxBrightnessMult = (gcnew System::Windows::Forms::TextBox());
                 this->labelBrightnessMult = (gcnew System::Windows::Forms::Label());
                 this->textBoxLayerStart = (gcnew System::Windows::Forms::TextBox());
                 this->labelCurrentLayer = (gcnew System::Windows::Forms::Label());
                 this->trackBarLayerStart = (gcnew System::Windows::Forms::TrackBar());
                 this->groupBoxRender->SuspendLayout();
                 this->groupBoxLoadData->SuspendLayout();
                 this->groupBoxRenderParams->SuspendLayout();
                 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarBrightMult))->BeginInit();
                 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarAlphaValue))->BeginInit();
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
                 this->labelStatus->Location = System::Drawing::Point(3, 579);
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
                 this->GLWindow->Size = System::Drawing::Size(499, 547);
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
                 this->groupBoxRender->Size = System::Drawing::Size(511, 572);
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
                 this->labelLayerHeight->Location = System::Drawing::Point(4, 96);
                 this->labelLayerHeight->Name = L"labelLayerHeight";
                 this->labelLayerHeight->Size = System::Drawing::Size(75, 13);
                 this->labelLayerHeight->TabIndex = 5;
                 this->labelLayerHeight->Text = L"Высота слоя:";
                 // 
                 // labelLayerWidth
                 // 
                 this->labelLayerWidth->AutoSize = true;
                 this->labelLayerWidth->Location = System::Drawing::Point(3, 83);
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
                 this->groupBoxRenderParams->Controls->Add(this->trackBarBrightMult);
                 this->groupBoxRenderParams->Controls->Add(this->checkBoxOneLayer);
                 this->groupBoxRenderParams->Controls->Add(this->labelAlphaValue);
                 this->groupBoxRenderParams->Controls->Add(this->trackBarAlphaValue);
                 this->groupBoxRenderParams->Controls->Add(this->checkBoxAlphaTest);
                 this->groupBoxRenderParams->Controls->Add(this->textBoxAlphaTest);
                 this->groupBoxRenderParams->Controls->Add(this->checkBoxDepthTest);
                 this->groupBoxRenderParams->Controls->Add(this->checkBoxTransperancy);
                 this->groupBoxRenderParams->Controls->Add(this->labelLayerDistance);
                 this->groupBoxRenderParams->Controls->Add(this->trackBarLayerDistance);
                 this->groupBoxRenderParams->Controls->Add(this->trackBarLayerEnd);
                 this->groupBoxRenderParams->Controls->Add(this->textBoxLayerEnd);
                 this->groupBoxRenderParams->Controls->Add(this->groupBoxRenderType);
                 this->groupBoxRenderParams->Controls->Add(this->textBoxBrightnessMult);
                 this->groupBoxRenderParams->Controls->Add(this->labelBrightnessMult);
                 this->groupBoxRenderParams->Controls->Add(this->textBoxLayerStart);
                 this->groupBoxRenderParams->Controls->Add(this->labelCurrentLayer);
                 this->groupBoxRenderParams->Controls->Add(this->trackBarLayerStart);
                 this->groupBoxRenderParams->Location = System::Drawing::Point(523, 143);
                 this->groupBoxRenderParams->Name = L"groupBoxRenderParams";
                 this->groupBoxRenderParams->Size = System::Drawing::Size(216, 433);
                 this->groupBoxRenderParams->TabIndex = 6;
                 this->groupBoxRenderParams->TabStop = false;
                 this->groupBoxRenderParams->Text = L"Параметры визуализации";
                 // 
                 // trackBarBrightMult
                 // 
                 this->trackBarBrightMult->Location = System::Drawing::Point(5, 388);
                 this->trackBarBrightMult->Maximum = 100;
                 this->trackBarBrightMult->Minimum = 1;
                 this->trackBarBrightMult->Name = L"trackBarBrightMult";
                 this->trackBarBrightMult->Size = System::Drawing::Size(146, 45);
                 this->trackBarBrightMult->TabIndex = 18;
                 this->trackBarBrightMult->Value = 1;
                 this->trackBarBrightMult->ValueChanged += gcnew System::EventHandler(this, &MainForm::trackBarBrightMult_ValueChanged);
                 // 
                 // checkBoxOneLayer
                 // 
                 this->checkBoxOneLayer->AutoSize = true;
                 this->checkBoxOneLayer->Location = System::Drawing::Point(43, 171);
                 this->checkBoxOneLayer->Name = L"checkBoxOneLayer";
                 this->checkBoxOneLayer->Size = System::Drawing::Size(90, 17);
                 this->checkBoxOneLayer->TabIndex = 17;
                 this->checkBoxOneLayer->Text = L"Только один";
                 this->checkBoxOneLayer->UseVisualStyleBackColor = true;
                 this->checkBoxOneLayer->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBoxOneLayer_CheckedChanged);
                 // 
                 // labelAlphaValue
                 // 
                 this->labelAlphaValue->AutoSize = true;
                 this->labelAlphaValue->Location = System::Drawing::Point(6, 310);
                 this->labelAlphaValue->Name = L"labelAlphaValue";
                 this->labelAlphaValue->Size = System::Drawing::Size(94, 13);
                 this->labelAlphaValue->TabIndex = 16;
                 this->labelAlphaValue->Text = L"Пороговое знач.:";
                 // 
                 // trackBarAlphaValue
                 // 
                 this->trackBarAlphaValue->Location = System::Drawing::Point(9, 326);
                 this->trackBarAlphaValue->Maximum = 1000;
                 this->trackBarAlphaValue->Name = L"trackBarAlphaValue";
                 this->trackBarAlphaValue->Size = System::Drawing::Size(142, 45);
                 this->trackBarAlphaValue->TabIndex = 15;
                 this->trackBarAlphaValue->ValueChanged += gcnew System::EventHandler(this, &MainForm::trackBarAlphaValue_ValueChanged);
                 // 
                 // checkBoxAlphaTest
                 // 
                 this->checkBoxAlphaTest->AutoSize = true;
                 this->checkBoxAlphaTest->Checked = true;
                 this->checkBoxAlphaTest->CheckState = System::Windows::Forms::CheckState::Checked;
                 this->checkBoxAlphaTest->Location = System::Drawing::Point(103, 309);
                 this->checkBoxAlphaTest->Name = L"checkBoxAlphaTest";
                 this->checkBoxAlphaTest->Size = System::Drawing::Size(95, 17);
                 this->checkBoxAlphaTest->TabIndex = 14;
                 this->checkBoxAlphaTest->Text = L"ALPHA_TEST";
                 this->checkBoxAlphaTest->UseVisualStyleBackColor = true;
                 this->checkBoxAlphaTest->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBoxAlphaTest_CheckedChanged);
                 this->checkBoxAlphaTest->EnabledChanged += gcnew System::EventHandler(this, &MainForm::checkBoxAlphaTest_EnabledChanged);
                 // 
                 // textBoxAlphaTest
                 // 
                 this->textBoxAlphaTest->Location = System::Drawing::Point(157, 326);
                 this->textBoxAlphaTest->Name = L"textBoxAlphaTest";
                 this->textBoxAlphaTest->Size = System::Drawing::Size(43, 20);
                 this->textBoxAlphaTest->TabIndex = 13;
                 this->textBoxAlphaTest->Text = L"0";
                 this->textBoxAlphaTest->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
                 this->textBoxAlphaTest->TextChanged += gcnew System::EventHandler(this, &MainForm::textBox1_TextChanged);
                 // 
                 // checkBoxDepthTest
                 // 
                 this->checkBoxDepthTest->AutoSize = true;
                 this->checkBoxDepthTest->Checked = true;
                 this->checkBoxDepthTest->CheckState = System::Windows::Forms::CheckState::Checked;
                 this->checkBoxDepthTest->Enabled = false;
                 this->checkBoxDepthTest->Location = System::Drawing::Point(103, 291);
                 this->checkBoxDepthTest->Name = L"checkBoxDepthTest";
                 this->checkBoxDepthTest->Size = System::Drawing::Size(97, 17);
                 this->checkBoxDepthTest->TabIndex = 12;
                 this->checkBoxDepthTest->Text = L"DEPTH_TEST";
                 this->checkBoxDepthTest->UseVisualStyleBackColor = true;
                 // 
                 // checkBoxTransperancy
                 // 
                 this->checkBoxTransperancy->AutoSize = true;
                 this->checkBoxTransperancy->Location = System::Drawing::Point(13, 291);
                 this->checkBoxTransperancy->Name = L"checkBoxTransperancy";
                 this->checkBoxTransperancy->Size = System::Drawing::Size(91, 17);
                 this->checkBoxTransperancy->TabIndex = 11;
                 this->checkBoxTransperancy->Text = L"Transperancy";
                 this->checkBoxTransperancy->UseVisualStyleBackColor = true;
                 this->checkBoxTransperancy->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBoxTransperancy_CheckedChanged);
                 // 
                 // labelLayerDistance
                 // 
                 this->labelLayerDistance->AutoSize = true;
                 this->labelLayerDistance->Location = System::Drawing::Point(10, 247);
                 this->labelLayerDistance->Name = L"labelLayerDistance";
                 this->labelLayerDistance->Size = System::Drawing::Size(147, 13);
                 this->labelLayerDistance->TabIndex = 10;
                 this->labelLayerDistance->Text = L"Расстояние между слоями:";
                 // 
                 // trackBarLayerDistance
                 // 
                 this->trackBarLayerDistance->Location = System::Drawing::Point(9, 263);
                 this->trackBarLayerDistance->Maximum = 150;
                 this->trackBarLayerDistance->Minimum = 1;
                 this->trackBarLayerDistance->Name = L"trackBarLayerDistance";
                 this->trackBarLayerDistance->Size = System::Drawing::Size(200, 45);
                 this->trackBarLayerDistance->TabIndex = 9;
                 this->trackBarLayerDistance->Value = 35;
                 // 
                 // trackBarLayerEnd
                 // 
                 this->trackBarLayerEnd->Location = System::Drawing::Point(6, 215);
                 this->trackBarLayerEnd->Maximum = 0;
                 this->trackBarLayerEnd->Name = L"trackBarLayerEnd";
                 this->trackBarLayerEnd->Size = System::Drawing::Size(204, 45);
                 this->trackBarLayerEnd->TabIndex = 8;
                 this->trackBarLayerEnd->ValueChanged += gcnew System::EventHandler(this, &MainForm::trackBarLayerEnd_ValueChanged);
                 // 
                 // textBoxLayerEnd
                 // 
                 this->textBoxLayerEnd->Location = System::Drawing::Point(171, 169);
                 this->textBoxLayerEnd->Name = L"textBoxLayerEnd";
                 this->textBoxLayerEnd->Size = System::Drawing::Size(29, 20);
                 this->textBoxLayerEnd->TabIndex = 7;
                 this->textBoxLayerEnd->Text = L"0";
                 this->textBoxLayerEnd->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
                 this->textBoxLayerEnd->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxLayerEnd_TextChanged);
                 // 
                 // groupBoxRenderType
                 // 
                 this->groupBoxRenderType->Controls->Add(this->buttonShaderRecompile);
                 this->groupBoxRenderType->Controls->Add(this->radioButtonRenderTypeShader);
                 this->groupBoxRenderType->Controls->Add(this->radioButtonRenderTypeTexture3D);
                 this->groupBoxRenderType->Controls->Add(this->radioButtonRenderTypeTexture);
                 this->groupBoxRenderType->Controls->Add(this->radioButtonRenderTypeVBO);
                 this->groupBoxRenderType->Controls->Add(this->radioButtonRenderTypeImmediate);
                 this->groupBoxRenderType->Location = System::Drawing::Point(6, 19);
                 this->groupBoxRenderType->Name = L"groupBoxRenderType";
                 this->groupBoxRenderType->Size = System::Drawing::Size(204, 134);
                 this->groupBoxRenderType->TabIndex = 6;
                 this->groupBoxRenderType->TabStop = false;
                 this->groupBoxRenderType->Text = L"Метод визуализации";
                 // 
                 // buttonShaderRecompile
                 // 
                 this->buttonShaderRecompile->Location = System::Drawing::Point(151, 107);
                 this->buttonShaderRecompile->Name = L"buttonShaderRecompile";
                 this->buttonShaderRecompile->Size = System::Drawing::Size(50, 24);
                 this->buttonShaderRecompile->TabIndex = 5;
                 this->buttonShaderRecompile->Text = L"Upd.";
                 this->buttonShaderRecompile->UseVisualStyleBackColor = true;
                 this->buttonShaderRecompile->Click += gcnew System::EventHandler(this, &MainForm::buttonShaderRecompile_Click);
                 // 
                 // radioButtonRenderTypeShader
                 // 
                 this->radioButtonRenderTypeShader->AutoSize = true;
                 this->radioButtonRenderTypeShader->Checked = true;
                 this->radioButtonRenderTypeShader->Location = System::Drawing::Point(7, 111);
                 this->radioButtonRenderTypeShader->Name = L"radioButtonRenderTypeShader";
                 this->radioButtonRenderTypeShader->Size = System::Drawing::Size(114, 17);
                 this->radioButtonRenderTypeShader->TabIndex = 4;
                 this->radioButtonRenderTypeShader->TabStop = true;
                 this->radioButtonRenderTypeShader->Text = L"Raycasting (GLSL)";
                 this->radioButtonRenderTypeShader->UseVisualStyleBackColor = true;
                 this->radioButtonRenderTypeShader->CheckedChanged += gcnew System::EventHandler(this, &MainForm::radioButtonRenderTypeShader_CheckedChanged);
                 // 
                 // radioButtonRenderTypeTexture3D
                 // 
                 this->radioButtonRenderTypeTexture3D->AutoSize = true;
                 this->radioButtonRenderTypeTexture3D->Location = System::Drawing::Point(7, 88);
                 this->radioButtonRenderTypeTexture3D->Name = L"radioButtonRenderTypeTexture3D";
                 this->radioButtonRenderTypeTexture3D->Size = System::Drawing::Size(162, 17);
                 this->radioButtonRenderTypeTexture3D->TabIndex = 3;
                 this->radioButtonRenderTypeTexture3D->Text = L"Использовать 3D текстуру";
                 this->radioButtonRenderTypeTexture3D->UseVisualStyleBackColor = true;
                 this->radioButtonRenderTypeTexture3D->CheckedChanged += gcnew System::EventHandler(this, &MainForm::radioButtonRenderTypeTexture3D_CheckedChanged);
                 // 
                 // radioButtonRenderTypeTexture
                 // 
                 this->radioButtonRenderTypeTexture->AutoSize = true;
                 this->radioButtonRenderTypeTexture->Location = System::Drawing::Point(7, 65);
                 this->radioButtonRenderTypeTexture->Name = L"radioButtonRenderTypeTexture";
                 this->radioButtonRenderTypeTexture->Size = System::Drawing::Size(165, 17);
                 this->radioButtonRenderTypeTexture->TabIndex = 2;
                 this->radioButtonRenderTypeTexture->Text = L"Использовать 2D текстуры";
                 this->radioButtonRenderTypeTexture->UseVisualStyleBackColor = true;
                 this->radioButtonRenderTypeTexture->CheckedChanged += gcnew System::EventHandler(this, &MainForm::radioButtonRenderTypeTexture_CheckedChanged);
                 // 
                 // radioButtonRenderTypeVBO
                 // 
                 this->radioButtonRenderTypeVBO->AutoSize = true;
                 this->radioButtonRenderTypeVBO->Location = System::Drawing::Point(7, 42);
                 this->radioButtonRenderTypeVBO->Name = L"radioButtonRenderTypeVBO";
                 this->radioButtonRenderTypeVBO->Size = System::Drawing::Size(120, 17);
                 this->radioButtonRenderTypeVBO->TabIndex = 1;
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
                 // textBoxBrightnessMult
                 // 
                 this->textBoxBrightnessMult->Location = System::Drawing::Point(157, 388);
                 this->textBoxBrightnessMult->Name = L"textBoxBrightnessMult";
                 this->textBoxBrightnessMult->Size = System::Drawing::Size(41, 20);
                 this->textBoxBrightnessMult->TabIndex = 4;
                 this->textBoxBrightnessMult->Text = L"30,0";
                 this->textBoxBrightnessMult->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
                 this->textBoxBrightnessMult->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxBrightnessMult_TextChanged);
                 // 
                 // labelBrightnessMult
                 // 
                 this->labelBrightnessMult->AutoSize = true;
                 this->labelBrightnessMult->Location = System::Drawing::Point(6, 370);
                 this->labelBrightnessMult->Name = L"labelBrightnessMult";
                 this->labelBrightnessMult->Size = System::Drawing::Size(112, 13);
                 this->labelBrightnessMult->TabIndex = 3;
                 this->labelBrightnessMult->Text = L"Множитель яркости:";
                 // 
                 // textBoxLayerStart
                 // 
                 this->textBoxLayerStart->Location = System::Drawing::Point(133, 169);
                 this->textBoxLayerStart->Name = L"textBoxLayerStart";
                 this->textBoxLayerStart->Size = System::Drawing::Size(32, 20);
                 this->textBoxLayerStart->TabIndex = 2;
                 this->textBoxLayerStart->Text = L"0";
                 this->textBoxLayerStart->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
                 this->textBoxLayerStart->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxCurrentLayer_TextChanged);
                 // 
                 // labelCurrentLayer
                 // 
                 this->labelCurrentLayer->AutoSize = true;
                 this->labelCurrentLayer->Location = System::Drawing::Point(6, 172);
                 this->labelCurrentLayer->Name = L"labelCurrentLayer";
                 this->labelCurrentLayer->Size = System::Drawing::Size(35, 13);
                 this->labelCurrentLayer->TabIndex = 1;
                 this->labelCurrentLayer->Text = L"Слои:";
                 // 
                 // trackBarLayerStart
                 // 
                 this->trackBarLayerStart->Location = System::Drawing::Point(6, 186);
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
                 this->ClientSize = System::Drawing::Size(744, 594);
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
                 this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
                 this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
                 this->groupBoxRender->ResumeLayout(false);
                 this->groupBoxLoadData->ResumeLayout(false);
                 this->groupBoxLoadData->PerformLayout();
                 this->groupBoxRenderParams->ResumeLayout(false);
                 this->groupBoxRenderParams->PerformLayout();
                 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarBrightMult))->EndInit();
                 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarAlphaValue))->EndInit();
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

                 data = new ScanData();
                 layerTextures = 0;
                 vertexVBOID = indexVBOID = colorVBOID = 0;
                 alphaTestValue = 0.2f;

                 PrepareShaders();
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

                 if (!radioButtonRenderTypeShader->Checked) {
                     glTranslatef(0.0f, 0.0f, -distance);
                 }
                 else {
                    glTranslatef(0.0f, 0.0f, -3.0f);
                 }
                 glRotatef(90.0f, 0.0f, 0.0, 1.0f);
                 if (!radioButtonRenderTypeShader->Checked) {
                     glRotatef(angleXRotation, 1.0f, 0.0f, 0.0f);
                     glRotatef(angleYRotation, 0.0f, 1.0f, 0.0f);
                 }
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

                 if (checkBoxTransperancy->Checked) {
                     glEnable(GL_BLEND);
                     if (!checkBoxDepthTest->Checked) {
                         glDisable(GL_DEPTH_TEST);
                     }    
                 }
                 if (checkBoxAlphaTest->Checked) {
                     glEnable(GL_ALPHA_TEST);
                     glAlphaFunc(GL_GREATER, alphaTestValue);
                 }

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
                             glColorPointer(4, GL_FLOAT, 0, (char*)(iLayer * data->sizeX * data->sizeY * 32 * sizeof(float)));
                             glDrawElements(GL_QUADS, data->sizeX * data->sizeY * 24, GL_UNSIGNED_INT, 0);
                         }

                         glDisableClientState(GL_VERTEX_ARRAY);
                         glDisableClientState(GL_COLOR_ARRAY);

                         glBindBuffer(GL_ARRAY_BUFFER, 0);
                         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                     }
                     else if (radioButtonRenderTypeTexture->Checked ||
                              radioButtonRenderTypeTexture3D->Checked) {
                         float localDepth = -((float)(trackBarLayerEnd->Value - trackBarLayerStart->Value) * data->scaleZ * trackBarLayerDistance->Value / 2.0f);
                         float width = (float)(data->sizeX / 2) * data->scaleX;
                         float height = (float)(data->sizeY / 2) * data->scaleY;

                         GLenum target = radioButtonRenderTypeTexture3D->Checked ? GL_TEXTURE_3D : GL_TEXTURE_2D;

                         glEnable(target);
                         glBindTexture(target, layerTextures[0]);

                         glColor4f(brightnessMult / (float)(trackBarBrightMult->Maximum), brightnessMult / (float)(trackBarBrightMult->Maximum), brightnessMult / (float)(trackBarBrightMult->Maximum), 1.0f);
                         for (size_t iLayer = trackBarLayerStart->Value; iLayer < trackBarLayerEnd->Value + 1; ++iLayer) {
                             glTranslatef(0.0f, 0.0f, -localDepth * 2 / (trackBarLayerEnd->Value - trackBarLayerStart->Value + 1));
                             if (target == GL_TEXTURE_2D) {
                                 glBindTexture(GL_TEXTURE_2D, layerTextures[iLayer]);
                                 glBegin(GL_QUADS); {
                                     glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height, localDepth);
                                     glTexCoord2f(1.0f, 0.0f); glVertex3f( width, -height, localDepth);
                                     glTexCoord2f(0.0f, 0.0f); glVertex3f( width,  height, localDepth);
                                     glTexCoord2f(0.0f, 1.0f); glVertex3f(-width,  height, localDepth);
                                 } glEnd();
                             }
                             else if (target == GL_TEXTURE_3D) {
                                 float texZCoord = iLayer / (float)(data->sizeZ - 1);
                                 glBegin(GL_QUADS); {
                                     glTexCoord3f(1.0f, 1.0f, texZCoord); glVertex3f(-width, -height, +localDepth);
                                     glTexCoord3f(1.0f, 0.0f, texZCoord); glVertex3f(+width, -height, +localDepth);
                                     glTexCoord3f(0.0f, 0.0f, texZCoord); glVertex3f(+width, +height, +localDepth);
                                     glTexCoord3f(0.0f, 1.0f, texZCoord); glVertex3f(-width, +height, +localDepth);
                                 } glEnd();
                             }
                         }

                         glBindTexture(target, 0);
                         glDisable(target);
                     }
                     else if (radioButtonRenderTypeShader->Checked) {
                         glEnable(GL_TEXTURE_3D);
                         glActiveTexture(GL_TEXTURE0);
                         glBindTexture(GL_TEXTURE_3D, shaderTexture);

                         glUseProgram(shaderProg);

                         GLint texLoc;
                         texLoc = glGetUniformLocation(shaderProg, "myTexture");
                         glUniform1i(texLoc, 0);

                         GLint startLayerLoc;
                         startLayerLoc = glGetUniformLocation(shaderProg, "startLayer");
                         glUniform1i(startLayerLoc, trackBarLayerStart->Value);

                         GLint endLayerLoc;
                         endLayerLoc = glGetUniformLocation(shaderProg, "endLayer");
                         glUniform1i(endLayerLoc, trackBarLayerEnd->Value);

                         GLint layerDistanceLoc;
                         layerDistanceLoc = glGetUniformLocation(shaderProg, "layerDistance");
                         glUniform1f(layerDistanceLoc, data->sizeZ * trackBarLayerDistance->Value);

                         //float pCoord = trackBarLayerStart->Value / (float)(data->sizeZ - 1);
                         float pCoord = 1.0 / (float)(data->sizeZ - 1);
                         GLint pCoordLoc;
                         pCoordLoc = glGetUniformLocation(shaderProg, "pCoordPerLayer");
                         glUniform1f(pCoordLoc, pCoord);

                         float mult = brightnessMult / (float)(trackBarBrightMult->Maximum);
                         GLint multLoc;
                         multLoc = glGetUniformLocation(shaderProg, "multCoeff");
                         glUniform1f(multLoc, mult);

                         GLint yRotLoc;
                         yRotLoc = glGetUniformLocation(shaderProg, "rotTheta");
                         glUniform1f(yRotLoc, angleYRotation);

                         GLint xRotLoc;
                         xRotLoc = glGetUniformLocation(shaderProg, "rotPhi");
                         glUniform1f(xRotLoc, angleXRotation);

                         GLint distanceLoc;
                         distanceLoc = glGetUniformLocation(shaderProg, "distance");
                         glUniform1f(distanceLoc, distance * 0.005f);

                         GLint alphaTestValueLoc;
                         alphaTestValueLoc = glGetUniformLocation(shaderProg, "alphaTestValue");
                         glUniform1f(alphaTestValueLoc, alphaTestValue);

                         glBegin(GL_QUADS);
                             glTexCoord2f(1.0f, 1.0f); glVertex3f(+2.0f, +2.0f, 0.0f);
                             glTexCoord2f(1.0f, 0.0f); glVertex3f(+2.0f, -2.0f, 0.0f);
                             glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 0.0f);
                             glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, +2.0f, 0.0f);
                         glEnd();
                         
                         glUseProgram(NULL);

                         glDisable(GL_TEXTURE_3D);
                     }
                 }

                 if (checkBoxTransperancy->Checked) {
                     glDisable(GL_BLEND);
                     if (!checkBoxDepthTest->Checked) {
                        glEnable(GL_DEPTH_TEST);
                     }
                 }
                 if (checkBoxAlphaTest->Checked) {
                     glDisable(GL_ALPHA_TEST);
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
                         glColor4f(grayIntense, grayIntense, grayIntense, grayIntense);
                         glCallList(theBox);
                     }
                     glTranslatef(-data->scaleX, data->sizeY * data->scaleY, 0.0f);
                 }
                 glPopMatrix();
             }

    private: Void PrepareShaders() {
                 vertShader = glCreateShader(GL_VERTEX_SHADER);
                 fragShader = glCreateShader(GL_FRAGMENT_SHADER);

                 const char** vertSource = (const char **)(LoadFile("vert.glsl"));
                 const char** fragSource = (const char **)(LoadFile("frag.glsl"));

                 glShaderSource(vertShader, 1, vertSource, NULL);
                 glShaderSource(fragShader, 1, fragSource, NULL);

                 GLint state = 0;

                 glCompileShader(vertShader);
                 glGetShaderiv(vertShader, GL_COMPILE_STATUS, &state);
                 if (state != GL_TRUE) {
                     printShaderInfoLog(vertShader);
                     return;
                 }

                 state = 0;
                 glCompileShader(fragShader);
                 glGetShaderiv(fragShader, GL_COMPILE_STATUS, &state);
                 if (state != GL_TRUE) {
                     printShaderInfoLog(fragShader);
                     return;
                 }

                 shaderProg = glCreateProgram();
                 glAttachShader(shaderProg, vertShader);
                 glAttachShader(shaderProg, fragShader);

                 state = 0;
                 glLinkProgram(shaderProg);
                 glGetProgramiv(shaderProg, GL_LINK_STATUS, &state);

                 if (state != GL_TRUE) {
                     GLint capacity = 0;

                     glGetProgramiv(shaderProg, GL_INFO_LOG_LENGTH, &capacity );

                     char *info = new char[capacity];

                     memset(info, 0, capacity);

                     glGetProgramInfoLog(shaderProg, capacity, NULL, info);

                     delete [] info;
                     return;
                 }
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
                         this->labelStatus->Text = L"Data was load.";

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

                         this->textBoxBrightnessMult->Text = L"40,0";
                         brightnessMult = 40.f;

                         this->trackBarLayerStart->Maximum = data->sizeZ - 1;
                         this->trackBarLayerStart->Value = 0;

                         this->trackBarLayerEnd->Maximum = data->sizeZ - 1;
                         this->trackBarLayerEnd->Value = 0;

                         radioButtonRenderTypeVBO_CheckedChanged(sender, e);

                         generateTextures();
                         if (StaticDelInst)
                            StaticDelInst(data);
                     } else {
                         this->labelStatus->Text = "Error. Incorrect reading input data file.";
                     }
                 } else {
                     this->labelStatus->Text = "Error. Input data file not exist.";
                 }             
             }
    private: System::Void trackBarLayer_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (checkBoxOneLayer->Checked) {
                     this->trackBarLayerEnd->Value = trackBarLayerStart->Value;
                     this->textBoxLayerStart->Text = this->trackBarLayerStart->Value.ToString();
                 }
                 else if (this->trackBarLayerStart->Value <= this->trackBarLayerEnd->Value) {
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

    private: System::Void trackBarBrightMult_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
             textBoxBrightnessMult->Text = trackBarBrightMult->Value.ToString();
          }

    private: System::Void trackBarAlphaValue_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
              Double newAlpha = trackBarAlphaValue->Value / 1000.0f;
              textBoxAlphaTest->Text = newAlpha.ToString();
          }

    private: System::Void generateTextures() {
                 ReleaseTextures();

                 bool is3Dtexture = !radioButtonRenderTypeTexture->Checked;

                 size_t numTextures = is3Dtexture ? 1 : data->sizeZ;
                 layerTextures = new GLuint[numTextures];
                 if (!radioButtonRenderTypeShader->Checked) {
                     glGenTextures(numTextures, layerTextures);
                 }
                 else {
                     GLuint tmpTex;
                     glGenTextures(numTextures, &tmpTex);
                     shaderTexture = tmpTex;
                 }

                 size_t dataSize = data->sizeX * data->sizeY * 2;
                 if (radioButtonRenderTypeShader->Checked) {
                     dataSize >>= 1;
                 }
                 if (is3Dtexture) {
                     dataSize *= data->sizeZ;
                 }
                 float *tmp = new float[dataSize];

                 GLenum target = is3Dtexture ? GL_TEXTURE_3D : GL_TEXTURE_2D;
                 size_t numLayers = is3Dtexture ? 1 : data->sizeZ;
                 float additionalMult = 1.5;
                 if (data->sizeZ < 30) {
                     additionalMult = 10;
                 }
                 for (size_t iLayer = 0; iLayer < numLayers; ++iLayer) {
                     for (size_t i = 0; i < dataSize; i += 2) {
                         if (!radioButtonRenderTypeShader->Checked) {
                             tmp[i] = (float)data->data[i / 2 + iLayer * data->sizeX * data->sizeY] * 5.0 * additionalMult / maxVal;
                             tmp[i + 1] = tmp[i];
                         }
                         else {
                             tmp[i] = (float)data->data[i] * 5.0 * additionalMult / maxVal;
                             --i;
                         }
                     }

                     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                     if (!radioButtonRenderTypeShader->Checked) {
                         glBindTexture(target, layerTextures[iLayer]);
                     }
                     else {
                         glBindTexture(target, shaderTexture);
                     }

                     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

                     glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP);
                     glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP);
                     if (is3Dtexture) {
                         glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP);
                     }
                     glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                     glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

                     if (is3Dtexture) {
                         if (radioButtonRenderTypeShader->Checked) {
                             glTexImage3D(GL_TEXTURE_3D, 0, GL_ALPHA, data->sizeX, data->sizeY, data->sizeZ, 0, GL_ALPHA, GL_FLOAT, tmp);
                         }
                         else {
                             glTexImage3D(GL_TEXTURE_3D, 0, GL_LUMINANCE_ALPHA, data->sizeX, data->sizeY, data->sizeZ, 0, GL_LUMINANCE_ALPHA, GL_FLOAT, tmp);
                         }
                     }
                     else {
                         //glTexImage2D(GL_TEXTURE_2D, 0, 1, data->sizeX, data->sizeY, 0, GL_INTENSITY, GL_SHORT, data->data + iLayer * data->sizeX * data->sizeY * sizeof(short)); // не работает, сцуко! :(
                         glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, data->sizeX, data->sizeY, 0, GL_LUMINANCE_ALPHA, GL_FLOAT, tmp);
                     }
                     
                 }

                 delete tmp;
             }

    private: System::Void generateVBOData() {
                 // creating VBO for vertecies
                 float *vertexBuffer;
                 vertexBuffer = new float[data->sizeX * data->sizeY * 8 * 3];
                 for (size_t iColumn = 0; iColumn < data->sizeX; ++iColumn) {
                     for (size_t iRow = 0; iRow < data->sizeY; ++iRow) {
                         if (iRow == 0) {
                             float vert[8*3] = {
                                 +0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), +0.5f + (float)(data->sizeY / 2) * data->scaleY, -0.5f * depth,
                                 +0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), -0.5f + (float)(data->sizeY / 2) * data->scaleY, -0.5f * depth,
                                 -0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), -0.5f + (float)(data->sizeY / 2) * data->scaleY, -0.5f * depth,
                                 -0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), +0.5f + (float)(data->sizeY / 2) * data->scaleY, -0.5f * depth,
                                 +0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), +0.5f + (float)(data->sizeY / 2) * data->scaleY, +0.5f * depth,
                                 +0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), -0.5f + (float)(data->sizeY / 2) * data->scaleY, +0.5f * depth,
                                 -0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), -0.5f + (float)(data->sizeY / 2) * data->scaleY, +0.5f * depth,
                                 -0.5f +(((float)(data->sizeX / 2) - iColumn) * data->scaleX), +0.5f + (float)(data->sizeY / 2) * data->scaleY, +0.5f * depth};

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
                 colorBuffer = new float[data->sizeX * data->sizeY * data->sizeZ * 8 * 4];
                 for (size_t i = 0; i < data->sizeX * data->sizeY * data->sizeZ; ++i) {
                     float curColor = data->data[i] / maxVal * brightnessMult;
                     for (size_t idx = 0; idx < 32; idx += 4) {
                         colorBuffer[i*32 + idx+0] = curColor;
                         colorBuffer[i*32 + idx+1] = curColor;
                         colorBuffer[i*32 + idx+2] = curColor;
                         colorBuffer[i*32 + idx+3] = curColor / brightnessMult * 5; // alpha
                         //colorBuffer[i*32 + idx+3] = 0.5f; // alpha
                     }
                 }

                 if (colorVBOID != 0) {
                     tmp = colorVBOID;
                     glDeleteBuffers(1, &tmp);
                 }

                 glGenBuffers(1, &tmp);
                 colorVBOID = tmp;
                 glBindBuffer(GL_ARRAY_BUFFER, colorVBOID);
                 glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data->sizeX * data->sizeY * data->sizeZ * 32, colorBuffer, GL_STATIC_DRAW);

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
                     trackBarBrightMult->Value = int(brightnessMult);
                 } catch (...) {
                     this->labelStatus->Text = L"Invalid number format for brightness mult.";
                 }
             }
    private: System::Void GLWindow_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->GLWindow->Focus();
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
private: System::Void checkBoxTransperancy_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
             bool state = checkBoxTransperancy->Checked;
             checkBoxDepthTest->Enabled = state;
         }
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
             Double curValue;
             try {
                 curValue = Double::Parse(this->textBoxAlphaTest->Text);
             } catch (...) {
                 this->labelStatus->Text = "Error. Aplha test value should be double.";
                 return;
             }
             if (curValue >= 0 && curValue <= 1) {
                 alphaTestValue = curValue;
                 trackBarAlphaValue->Value = int(alphaTestValue * trackBarAlphaValue->Maximum);
             } else {
                 this->labelStatus->Text = "Error. Aplha test value should be in range [0, 1].";
             }
         }
private: System::Void radioButtonRenderTypeTexture_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
             if (radioButtonRenderTypeTexture->Checked) {
                 generateTextures();
             }
         }
private: System::Void radioButtonRenderTypeTexture3D_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
             if (radioButtonRenderTypeTexture3D->Checked) {
                 generateTextures();
             }
         }
private: System::Void radioButtonRenderTypeShader_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
             if (radioButtonRenderTypeShader->Checked) {
                 generateTextures();
             }
         }
private: System::Void checkBoxAlphaTest_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
             bool state = checkBoxAlphaTest->Checked;
             textBoxAlphaTest->Enabled = state;
             trackBarAlphaValue->Enabled = state;
         }
private: System::Void checkBoxAlphaTest_EnabledChanged(System::Object^  sender, System::EventArgs^  e) {
             bool state = checkBoxAlphaTest->Enabled && checkBoxAlphaTest->Checked;
             textBoxAlphaTest->Enabled = state;
             trackBarAlphaValue->Enabled = state;
         }
private: System::Void checkBoxOneLayer_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
             bool state = checkBoxOneLayer->Checked;
             textBoxLayerEnd->Enabled = !state;
             trackBarLayerEnd->Enabled = !state;
             if (state) {
                 trackBarLayerEnd->Value = trackBarLayerStart->Value;
             }
         }
private: System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
             e->Cancel = true;
             Hide();
         }
private: System::Void buttonShaderRecompile_Click(System::Object^  sender, System::EventArgs^  e) {
             PrepareShaders();
         }
};
}

