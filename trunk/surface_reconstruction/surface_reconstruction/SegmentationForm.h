#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "Graph.h"

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
    private: System::Windows::Forms::Button^  SegmentationIteration;
    private: System::Windows::Forms::GroupBox^  LayerSegmentsTreeInfo;
    private: System::Windows::Forms::GroupBox^  SegmentInfo;
    private: System::Windows::Forms::DataGridView^  LayerSegmentsGrid;

    private: System::Windows::Forms::DataGridViewTextBoxColumn^  CountSegments;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^  MaxCapacity;


    public: 
        ScanData *data;

        SegmentationForm(void)
        {
            InitializeComponent();
            //
            //TODO: добавьте код конструктора
            //
            
            //SegmentsTree tree0;
            

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
        }
    private: System::Windows::Forms::Button^  StartSegmentation;
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
            this->StartSegmentation = (gcnew System::Windows::Forms::Button());
            this->SegmentationIteration = (gcnew System::Windows::Forms::Button());
            this->LayerSegmentsTreeInfo = (gcnew System::Windows::Forms::GroupBox());
            this->LayerSegmentsGrid = (gcnew System::Windows::Forms::DataGridView());
            this->CountSegments = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->MaxCapacity = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->SegmentInfo = (gcnew System::Windows::Forms::GroupBox());
            this->LayerSegmentsTreeInfo->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->LayerSegmentsGrid))->BeginInit();
            this->SuspendLayout();
            // 
            // StartSegmentation
            // 
            this->StartSegmentation->Location = System::Drawing::Point(0, 12);
            this->StartSegmentation->Name = L"StartSegmentation";
            this->StartSegmentation->Size = System::Drawing::Size(75, 49);
            this->StartSegmentation->TabIndex = 0;
            this->StartSegmentation->Text = L"начать новую сегментацию";
            this->StartSegmentation->UseVisualStyleBackColor = true;
            this->StartSegmentation->Click += gcnew System::EventHandler(this, &SegmentationForm::StartSegmentation_Click);
            // 
            // SegmentationIteration
            // 
            this->SegmentationIteration->Enabled = false;
            this->SegmentationIteration->Location = System::Drawing::Point(81, 12);
            this->SegmentationIteration->Name = L"SegmentationIteration";
            this->SegmentationIteration->Size = System::Drawing::Size(84, 49);
            this->SegmentationIteration->TabIndex = 1;
            this->SegmentationIteration->Text = L"итерация сегментации";
            this->SegmentationIteration->UseVisualStyleBackColor = true;
            this->SegmentationIteration->Click += gcnew System::EventHandler(this, &SegmentationForm::SegmentationIteration_Click);
            // 
            // LayerSegmentsTreeInfo
            // 
            this->LayerSegmentsTreeInfo->Controls->Add(this->LayerSegmentsGrid);
            this->LayerSegmentsTreeInfo->Location = System::Drawing::Point(12, 67);
            this->LayerSegmentsTreeInfo->Name = L"LayerSegmentsTreeInfo";
            this->LayerSegmentsTreeInfo->Size = System::Drawing::Size(642, 306);
            this->LayerSegmentsTreeInfo->TabIndex = 2;
            this->LayerSegmentsTreeInfo->TabStop = false;
            this->LayerSegmentsTreeInfo->Text = L"уровни сегментации";
            // 
            // LayerSegmentsGrid
            // 
            this->LayerSegmentsGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->LayerSegmentsGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->CountSegments, 
                this->MaxCapacity});
            this->LayerSegmentsGrid->Location = System::Drawing::Point(6, 19);
            this->LayerSegmentsGrid->Name = L"LayerSegmentsGrid";
            this->LayerSegmentsGrid->Size = System::Drawing::Size(606, 214);
            this->LayerSegmentsGrid->TabIndex = 0;
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
            this->SegmentInfo->Location = System::Drawing::Point(13, 398);
            this->SegmentInfo->Name = L"SegmentInfo";
            this->SegmentInfo->Size = System::Drawing::Size(641, 206);
            this->SegmentInfo->TabIndex = 3;
            this->SegmentInfo->TabStop = false;
            this->SegmentInfo->Text = L"выбранный сегмент";
            // 
            // SegmentationForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(685, 616);
            this->Controls->Add(this->SegmentInfo);
            this->Controls->Add(this->LayerSegmentsTreeInfo);
            this->Controls->Add(this->SegmentationIteration);
            this->Controls->Add(this->StartSegmentation);
            this->Name = L"SegmentationForm";
            this->Text = L"SegmentationForm";
            this->Load += gcnew System::EventHandler(this, &SegmentationForm::SegmentationForm_Load);
            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &SegmentationForm::SegmentationForm_FormClosing);
            this->LayerSegmentsTreeInfo->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->LayerSegmentsGrid))->EndInit();
            this->ResumeLayout(false);

        }
#pragma endregion
    private: System::Void StartSegmentation_Click(System::Object^  sender, System::EventArgs^  e) {
                 tree = new SegmentsTree(data);
                 SegmentationIteration->Enabled = true;
                 LayerSegmentsGrid->RowCount = LayerSegmentsGrid->RowCount + 1;
                 LayerSegmentsGrid->Rows[0]->Cells[0]->Value = "0"; 

             }
    private: System::Void SegmentationForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
                 e->Cancel = true;
                 Hide();
             }
    private: System::Void SegmentationForm_Load(System::Object^  sender, System::EventArgs^  e) {
             }
    private: System::Void SegmentationIteration_Click(System::Object^  sender, System::EventArgs^  e) {
                tree->CreateNewLayer();
             }
    };
}
