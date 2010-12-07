#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLu.h>

#include "graphics.h"

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
    private: System::Windows::Forms::Button^  button1;
    private: System::Windows::Forms::Label^  StatusLabel;
    protected: 


    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        HDC     hDC;
        HGLRC   hRC;
        HWND    hWnd;
    private: System::Windows::Forms::Panel^  GLWindow;
    private: System::Windows::Forms::GroupBox^  groupBox1;

    private: System::Windows::Forms::Timer^  DrawTimer;
    private: System::ComponentModel::IContainer^  components;



#pragma region Windows Form Designer generated code
             /// <summary>
             /// Required method for Designer support - do not modify
             /// the contents of this method with the code editor.
             /// </summary>
             void InitializeComponent(void)
             {
                 this->components = (gcnew System::ComponentModel::Container());
                 this->button1 = (gcnew System::Windows::Forms::Button());
                 this->StatusLabel = (gcnew System::Windows::Forms::Label());
                 this->GLWindow = (gcnew System::Windows::Forms::Panel());
                 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
                 this->DrawTimer = (gcnew System::Windows::Forms::Timer(this->components));
                 this->groupBox1->SuspendLayout();
                 this->SuspendLayout();
                 // 
                 // button1
                 // 
                 this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
                 this->button1->Location = System::Drawing::Point(523, 12);
                 this->button1->Name = L"button1";
                 this->button1->Size = System::Drawing::Size(97, 30);
                 this->button1->TabIndex = 0;
                 this->button1->Text = L"button1";
                 this->button1->UseVisualStyleBackColor = true;
                 this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
                 // 
                 // StatusLabel
                 // 
                 this->StatusLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
                 this->StatusLabel->AutoSize = true;
                 this->StatusLabel->Location = System::Drawing::Point(12, 420);
                 this->StatusLabel->Name = L"StatusLabel";
                 this->StatusLabel->Size = System::Drawing::Size(41, 13);
                 this->StatusLabel->TabIndex = 1;
                 this->StatusLabel->Text = L"Статус";
                 // 
                 // GLWindow
                 // 
                 this->GLWindow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
                     | System::Windows::Forms::AnchorStyles::Left) 
                     | System::Windows::Forms::AnchorStyles::Right));
                 this->GLWindow->Location = System::Drawing::Point(6, 19);
                 this->GLWindow->Name = L"GLWindow";
                 this->GLWindow->Size = System::Drawing::Size(499, 387);
                 this->GLWindow->TabIndex = 2;
                 // 
                 // groupBox1
                 // 
                 this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
                     | System::Windows::Forms::AnchorStyles::Left) 
                     | System::Windows::Forms::AnchorStyles::Right));
                 this->groupBox1->Controls->Add(this->GLWindow);
                 this->groupBox1->Location = System::Drawing::Point(6, 4);
                 this->groupBox1->Name = L"groupBox1";
                 this->groupBox1->Size = System::Drawing::Size(511, 412);
                 this->groupBox1->TabIndex = 3;
                 this->groupBox1->TabStop = false;
                 this->groupBox1->Text = L"Окно демонстрации";
                 // 
                 // DrawTimer
                 // 
                 this->DrawTimer->Enabled = true;
                 this->DrawTimer->Interval = 30;
                 this->DrawTimer->Tick += gcnew System::EventHandler(this, &MainForm::DrawTimer_Tick);
                 // 
                 // MainForm
                 // 
                 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
                 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
                 this->ClientSize = System::Drawing::Size(624, 442);
                 this->Controls->Add(this->groupBox1);
                 this->Controls->Add(this->StatusLabel);
                 this->Controls->Add(this->button1);
                 this->MinimumSize = System::Drawing::Size(640, 480);
                 this->Name = L"MainForm";
                 this->Text = L"Аццкая рисовался";
                 this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
                 this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
                 this->groupBox1->ResumeLayout(false);
                 this->ResumeLayout(false);
                 this->PerformLayout();

             }
#pragma endregion
    private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
                 DrawGLScene();
                 SwapBuffers(hDC);
            }

    private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
                 GLuint PixelFormat;

                 hWnd = (HWND)(intptr_t)this->GLWindow->Handle;
                 hDC = GetDC(hWnd);
                 if (!hDC) {
                     this->StatusLabel->Text = L"Can't Create A GL Device Context";
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
                     this->StatusLabel->Text = L"Can't Find A Suitable PixelFormat.";
                     return;
                 }
                 if (!SetPixelFormat(hDC, PixelFormat, &pfd)) {
                     this->StatusLabel->Text = L"Can't Set The PixelFormat.";
                     return;
                 }
                 hRC = wglCreateContext(hDC);
                 if (!hRC) {
                     this->StatusLabel->Text = L"Can't Create A GL Rendering Context. GetLastError: " + GetLastError();
                     return;
                 }
                 if (!wglMakeCurrent(hDC, hRC)) {
                     this->StatusLabel->Text = L"Can't Activate The GL Rendering Context.";
                     return;
                 }
                 this->StatusLabel->Text = L"GL context created!";

                 MainForm_Resize(sender, e);

                 if (!InitGL()) {
                    this->StatusLabel->Text = L"Failed to init GL";
                 }
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

                 gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

                 glMatrixMode(GL_MODELVIEW);
                 glLoadIdentity();

                 DrawGLScene();
                 SwapBuffers(hDC);
             }

private: System::Void DrawTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
             DrawGLScene();
             SwapBuffers(hDC);
         }
};
}

