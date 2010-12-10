#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLu.h>

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

    private:
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
    private: System::Windows::Forms::TextBox^  textBoxCurrentLayer;
    private: System::Windows::Forms::Label^  labelCurrentLayer;
    private: System::Windows::Forms::TrackBar^  trackBarLayer;
    private: System::Windows::Forms::TextBox^  textBoxBrightnessMult;

    private: System::Windows::Forms::Label^  labelBrightnessMult;






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
                 this->textBoxBrightnessMult = (gcnew System::Windows::Forms::TextBox());
                 this->labelBrightnessMult = (gcnew System::Windows::Forms::Label());
                 this->textBoxCurrentLayer = (gcnew System::Windows::Forms::TextBox());
                 this->labelCurrentLayer = (gcnew System::Windows::Forms::Label());
                 this->trackBarLayer = (gcnew System::Windows::Forms::TrackBar());
                 this->groupBoxRender->SuspendLayout();
                 this->groupBoxLoadData->SuspendLayout();
                 this->groupBoxRenderParams->SuspendLayout();
                 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarLayer))->BeginInit();
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
                 this->GLWindow->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::GLWindow_MouseMove);
                 this->GLWindow->Click += gcnew System::EventHandler(this, &MainForm::GLWindow_Click);
                 this->GLWindow->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::GLWindow_MouseDown);
                 this->GLWindow->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::GLWindow_MouseWheel);
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
                 this->groupBoxRenderParams->Controls->Add(this->textBoxBrightnessMult);
                 this->groupBoxRenderParams->Controls->Add(this->labelBrightnessMult);
                 this->groupBoxRenderParams->Controls->Add(this->textBoxCurrentLayer);
                 this->groupBoxRenderParams->Controls->Add(this->labelCurrentLayer);
                 this->groupBoxRenderParams->Controls->Add(this->trackBarLayer);
                 this->groupBoxRenderParams->Location = System::Drawing::Point(523, 143);
                 this->groupBoxRenderParams->Name = L"groupBoxRenderParams";
                 this->groupBoxRenderParams->Size = System::Drawing::Size(216, 292);
                 this->groupBoxRenderParams->TabIndex = 6;
                 this->groupBoxRenderParams->TabStop = false;
                 this->groupBoxRenderParams->Text = L"Параметры визуализации";
                 // 
                 // textBoxBrightnessMult
                 // 
                 this->textBoxBrightnessMult->Location = System::Drawing::Point(133, 65);
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
                 this->labelBrightnessMult->Location = System::Drawing::Point(6, 68);
                 this->labelBrightnessMult->Name = L"labelBrightnessMult";
                 this->labelBrightnessMult->Size = System::Drawing::Size(112, 13);
                 this->labelBrightnessMult->TabIndex = 3;
                 this->labelBrightnessMult->Text = L"Множитель яркости:";
                 // 
                 // textBoxCurrentLayer
                 // 
                 this->textBoxCurrentLayer->Location = System::Drawing::Point(133, 17);
                 this->textBoxCurrentLayer->Name = L"textBoxCurrentLayer";
                 this->textBoxCurrentLayer->Size = System::Drawing::Size(67, 20);
                 this->textBoxCurrentLayer->TabIndex = 2;
                 this->textBoxCurrentLayer->Text = L"0";
                 this->textBoxCurrentLayer->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
                 this->textBoxCurrentLayer->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxCurrentLayer_TextChanged);
                 // 
                 // labelCurrentLayer
                 // 
                 this->labelCurrentLayer->AutoSize = true;
                 this->labelCurrentLayer->Location = System::Drawing::Point(6, 20);
                 this->labelCurrentLayer->Name = L"labelCurrentLayer";
                 this->labelCurrentLayer->Size = System::Drawing::Size(109, 13);
                 this->labelCurrentLayer->TabIndex = 1;
                 this->labelCurrentLayer->Text = L"Визуализация слоя:";
                 // 
                 // trackBarLayer
                 // 
                 this->trackBarLayer->Location = System::Drawing::Point(6, 36);
                 this->trackBarLayer->Maximum = 0;
                 this->trackBarLayer->Name = L"trackBarLayer";
                 this->trackBarLayer->Size = System::Drawing::Size(204, 45);
                 this->trackBarLayer->TabIndex = 0;
                 this->trackBarLayer->ValueChanged += gcnew System::EventHandler(this, &MainForm::trackBarLayer_ValueChanged);
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
                 this->MinimumSize = System::Drawing::Size(640, 480);
                 this->Name = L"MainForm";
                 this->Text = L"Аццкая рисовалка";
                 this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
                 this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
                 this->groupBoxRender->ResumeLayout(false);
                 this->groupBoxLoadData->ResumeLayout(false);
                 this->groupBoxLoadData->PerformLayout();
                 this->groupBoxRenderParams->ResumeLayout(false);
                 this->groupBoxRenderParams->PerformLayout();
                 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarLayer))->EndInit();
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
                      RenderLayer(this->trackBarLayer->Value);
                  }
              }

              private: Void RenderLayer(size_t z) {
                  glScalef(data->scaleX, data->scaleY, data->scaleZ);
                  glTranslatef(0.0f, 0.0f, ((float)(data->sizeZ / 2) - z) * data->scaleZ);
                  glPushMatrix();
                  for (size_t iColumn = 0; iColumn < data->sizeY; ++iColumn) {
                      glPushMatrix();
                      glTranslatef(((float)(data->sizeX / 2) - iColumn) * data->scaleX, 0.0f, 0.0f);
                      for (size_t iRow = 0; iRow < data->sizeX; ++iRow) {
                          glPushMatrix();
                          glTranslatef(0.0f, ((float)(data->sizeY / 2) - iRow) * data->scaleY, 0.0f);
                          float grayIntense = (float)(data->data[iRow + iColumn * data->sizeX + z * data->sizeX * data->sizeY]) / maxVal;
                          grayIntense *= brightnessMult;
                          glColor3f(grayIntense, grayIntense, grayIntense);
                          glCallList(theBox);
                          glPopMatrix();
                      }
                      glPopMatrix();
                  }
                  glPopMatrix();
              }

private: System::Void DrawTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
                 DrawGLScene();
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

                     this->trackBarLayer->Maximum = data->sizeZ - 1;
                     this->trackBarLayer->Value = 0;
                 } else {
                     this->labelStatus->Text = "Error. Incorrect reading input data file.";
                 }
             } else {
                 this->labelStatus->Text = "Error. Input data file not exist.";
             }
         }
    private: System::Void trackBarLayer_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->textBoxCurrentLayer->Text = this->trackBarLayer->Value.ToString();
             }

private: System::Void textBoxCurrentLayer_TextChanged(System::Object^  sender, System::EventArgs^  e) {
             Int32 curValue;
             try {
                 curValue = Int32::Parse(this->textBoxCurrentLayer->Text);
             } catch (...) {
                 this->labelStatus->Text = "Error. Layer value should be unsigned int.";
                 return;
             }
             if (curValue >= 0 && curValue < data->sizeZ) {
                 this->trackBarLayer->Value = curValue;
             } else {
                 this->labelStatus->Text = "Error. Layer should be in range [0;" + (data->sizeZ - 1) + L"].";
             }
         }

private: System::Void GLWindow_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
             if (e->Button == Windows::Forms::MouseButtons::Left) {
                 Point tmpPosition = mousePosition;
                 mousePosition = e->Location;
                 angleYRotation -= tmpPosition.X - mousePosition.X;
                 angleXRotation -= tmpPosition.Y - mousePosition.Y;
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
};
}

