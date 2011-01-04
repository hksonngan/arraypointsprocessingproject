#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "Graph.h"
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

    public delegate void MyDel(ScanData* sData);

    public ref class SegmentationForm : public System::Windows::Forms::Form
    {
    public:

        SegmentsTree* tree;
    private: System::Windows::Forms::Button^  SegmentationIteration;
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
    private: System::Windows::Forms::DataGridView^  CurrentSegment;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^  Id;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^  CountVoxel;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^  WeightSegment;
    private: System::Windows::Forms::DataGridViewCheckBoxColumn^  CheckSegment;
    private: System::Windows::Forms::Button^  DisplaySegments;
    private: System::Windows::Forms::Label^  CountDisplay;
    private: System::Windows::Forms::Label^  CountDisplaylabel;

    public: 

    public: 

    public: 
        LayerSegmentsTree* layerSelect;

        SegmentationForm(void)
        {
            InitializeComponent();
            //
            //TODO: добавьте код конструктора
            //

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
            this->Select = (gcnew System::Windows::Forms::Button());
            this->layerSelectLabel = (gcnew System::Windows::Forms::Label());
            this->LayerSelect = (gcnew System::Windows::Forms::TextBox());
            this->LayerSegmentsGrid = (gcnew System::Windows::Forms::DataGridView());
            this->LayerNum = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->CountSegments = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->MaxCapacity = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->SegmentInfo = (gcnew System::Windows::Forms::GroupBox());
            this->DisplaySegments = (gcnew System::Windows::Forms::Button());
            this->CurrentSegment = (gcnew System::Windows::Forms::DataGridView());
            this->Id = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->CountVoxel = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->WeightSegment = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->CheckSegment = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
            this->CountDisplaylabel = (gcnew System::Windows::Forms::Label());
            this->CountDisplay = (gcnew System::Windows::Forms::Label());
            this->LayerSegmentsTreeInfo->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->LayerSegmentsGrid))->BeginInit();
            this->SegmentInfo->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->CurrentSegment))->BeginInit();
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
            this->LayerSegmentsTreeInfo->Controls->Add(this->Select);
            this->LayerSegmentsTreeInfo->Controls->Add(this->layerSelectLabel);
            this->LayerSegmentsTreeInfo->Controls->Add(this->LayerSelect);
            this->LayerSegmentsTreeInfo->Controls->Add(this->LayerSegmentsGrid);
            this->LayerSegmentsTreeInfo->Enabled = false;
            this->LayerSegmentsTreeInfo->Location = System::Drawing::Point(12, 67);
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
            this->SegmentInfo->Controls->Add(this->CountDisplay);
            this->SegmentInfo->Controls->Add(this->CountDisplaylabel);
            this->SegmentInfo->Controls->Add(this->DisplaySegments);
            this->SegmentInfo->Controls->Add(this->CurrentSegment);
            this->SegmentInfo->Location = System::Drawing::Point(13, 319);
            this->SegmentInfo->Name = L"SegmentInfo";
            this->SegmentInfo->Size = System::Drawing::Size(899, 285);
            this->SegmentInfo->TabIndex = 3;
            this->SegmentInfo->TabStop = false;
            this->SegmentInfo->Text = L"сегменты выбронного уровня";
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
            this->CurrentSegment->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->CurrentSegment->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->Id, this->CountVoxel, 
                this->WeightSegment, this->CheckSegment});
            this->CurrentSegment->Location = System::Drawing::Point(6, 19);
            this->CurrentSegment->Name = L"CurrentSegment";
            this->CurrentSegment->Size = System::Drawing::Size(720, 249);
            this->CurrentSegment->TabIndex = 0;
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
            // WeightSegment
            // 
            this->WeightSegment->HeaderText = L"вес сегмента";
            this->WeightSegment->Name = L"WeightSegment";
            // 
            // CheckSegment
            // 
            this->CheckSegment->HeaderText = L"выбрать";
            this->CheckSegment->Name = L"CheckSegment";
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
            // CountDisplay
            // 
            this->CountDisplay->AutoSize = true;
            this->CountDisplay->Location = System::Drawing::Point(732, 72);
            this->CountDisplay->Name = L"CountDisplay";
            this->CountDisplay->Size = System::Drawing::Size(13, 13);
            this->CountDisplay->TabIndex = 3;
            this->CountDisplay->Text = L"0";
            // 
            // SegmentationForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(924, 616);
            this->Controls->Add(this->SegmentInfo);
            this->Controls->Add(this->LayerSegmentsTreeInfo);
            this->Controls->Add(this->SegmentationIteration);
            this->Controls->Add(this->StartSegmentation);
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
            this->ResumeLayout(false);

        }
#pragma endregion
    private: System::Void StartSegmentation_Click(System::Object^  sender, System::EventArgs^  e) {
                 tree = new SegmentsTree(data);
                 SegmentationIteration->Enabled = true;
                 LayerSegmentsGrid->RowCount = 1;
                 LayerSegmentsGrid->Rows[0]->Cells[0]->Value = "0"; 
                 unsigned int^ count = tree->root->segmentCount;                 
                 LayerSegmentsGrid->Rows[0]->Cells[1]->Value = count->ToString(); 
                 unsigned int^ w = tree->root->maxCapacity;                 
                 LayerSegmentsGrid->Rows[0]->Cells[2]->Value = w->ToString(); 
             }
    private: System::Void SegmentationForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
                 e->Cancel = true;
                 Hide();
             }
    private: System::Void SegmentationForm_Load(System::Object^  sender, System::EventArgs^  e) {
             }
    private: System::Void SegmentationIteration_Click(System::Object^  sender, System::EventArgs^  e) {
                 LayerSegmentsTree*  newLayer = tree->CreateNewLayer();
                 if (newLayer->segmentCount > (newLayer->down->segmentCount * 0.25))
                     tree->step *= 2; 
                 LayerSegmentsTree* layer = tree->root;
                 int indexLayer = 0;
                 LayerSegmentsGrid->RowCount = LayerSegmentsGrid->RowCount + tree->countLayer;

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
    private: System::Void LayerSegmentsGrid_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
                 LayerSelect->Text = e->RowIndex.ToString();
             }
    private: System::Void Select_Click(System::Object^  sender, System::EventArgs^  e) {
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
                 CurrentSegment->RowCount = layerSelect->segmentCount;
                 while (currentSegment != 0)
                 {
                     int^ c = j;                
                     CurrentSegment->Rows[j]->Cells[0]->Value = c->ToString(); 
                     unsigned int^ count = currentSegment->сapacity;                 
                     CurrentSegment->Rows[j]->Cells[1]->Value = count->ToString(); 
                     short^ w = currentSegment->weightSegment;                 
                     CurrentSegment->Rows[j]->Cells[2]->Value = w->ToString();

                     j++;
                     currentSegment = currentSegment->next;
                 }
             }

    private: System::Void DisplaySegments_Click(System::Object^  sender, System::EventArgs^  e) {
                 int countCheck = 0;
                 for (int i = 0; i < CurrentSegment->RowCount; i++)
                 {
                     if (CurrentSegment->Rows[i]->Cells[3]->Value)
                         countCheck++;
                 }
                 int^ c = countCheck;  
                 CountDisplay->Text = c->ToString();
                 size_t* indexs = new size_t [countCheck];
                 int k = 0;
                 for (int i = 0; i < CurrentSegment->RowCount; i++)
                 {
                     if (CurrentSegment->Rows[i]->Cells[3]->Value)
                     {
                         indexs[k] = size_t(i);
                         k++;
                     }
                 }
                 ScanData* sd = layerSelect->CreateData(indexs, size_t(countCheck));
                 StaticDelInst(sd);
                 //mainForm->data = layerSelect->CreateData(indexs, size_t(countCheck));

             }



    };
}
