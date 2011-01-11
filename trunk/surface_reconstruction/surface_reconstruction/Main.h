#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

//#include "MainForm.h"
#include "Clusterization/ClusterizationForm.h"
#include "Segmentation/SegmentationForm.h"

namespace surface_reconstruction {

	/// <summary>
	/// Сводка для CentralForm
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>

	public ref class CentralForm : public System::Windows::Forms::Form
	{
	public:
		System::Windows::Forms::Form^ DisplayForm;
		System::Windows::Forms::Form^ DisplaySegmentationForm;
		static SegmentationForm^ segmentationForm = gcnew SegmentationForm();
		static ClusterizationForm^ clusterizationForm = gcnew ClusterizationForm();
	private: System::Windows::Forms::GroupBox^  Networking;
	private: System::Windows::Forms::GroupBox^  ConstructionHistogram;
	private: System::Windows::Forms::GroupBox^  NetReduction;


	public: 

			 ScanData* data;
		CentralForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
	public:
		CentralForm(System::Windows::Forms::Form^ form)
		{
			InitializeComponent();
			DisplayForm = form;
		}
		void ChangeData(ScanData* sData)
		{
			data = sData;
			segmentationForm->data = sData;
			segmentationForm->d();
		}


	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~CentralForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  Segmentation;
	private: System::Windows::Forms::RadioButton^  AggregationSegmentRadioButton;
	private: System::Windows::Forms::RadioButton^  KAverageRadioButton;
	private: System::Windows::Forms::Button^  SegmentationStart;
	private: System::Windows::Forms::GroupBox^  Display;

	private: System::Windows::Forms::Button^  DisplayData;


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
			this->Segmentation = (gcnew System::Windows::Forms::GroupBox());
			this->SegmentationStart = (gcnew System::Windows::Forms::Button());
			this->KAverageRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->AggregationSegmentRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->Display = (gcnew System::Windows::Forms::GroupBox());
			this->DisplayData = (gcnew System::Windows::Forms::Button());
			this->Networking = (gcnew System::Windows::Forms::GroupBox());
			this->ConstructionHistogram = (gcnew System::Windows::Forms::GroupBox());
			this->NetReduction = (gcnew System::Windows::Forms::GroupBox());
			this->Segmentation->SuspendLayout();
			this->Display->SuspendLayout();
			this->SuspendLayout();
			// 
			// Segmentation
			// 
			this->Segmentation->Controls->Add(this->SegmentationStart);
			this->Segmentation->Controls->Add(this->KAverageRadioButton);
			this->Segmentation->Controls->Add(this->AggregationSegmentRadioButton);
			this->Segmentation->Location = System::Drawing::Point(12, 148);
			this->Segmentation->Name = L"Segmentation";
			this->Segmentation->Size = System::Drawing::Size(268, 100);
			this->Segmentation->TabIndex = 0;
			this->Segmentation->TabStop = false;
			this->Segmentation->Text = L"Сегметация";
			// 
			// SegmentationStart
			// 
			this->SegmentationStart->Location = System::Drawing::Point(21, 66);
			this->SegmentationStart->Name = L"SegmentationStart";
			this->SegmentationStart->Size = System::Drawing::Size(75, 23);
			this->SegmentationStart->TabIndex = 2;
			this->SegmentationStart->Text = L"приступить к сегментации";
			this->SegmentationStart->UseVisualStyleBackColor = true;
			this->SegmentationStart->Click += gcnew System::EventHandler(this, &CentralForm::SegmentationStart_Click);
			// 
			// KAverageRadioButton
			// 
			this->KAverageRadioButton->AutoSize = true;
			this->KAverageRadioButton->Location = System::Drawing::Point(21, 43);
			this->KAverageRadioButton->Name = L"KAverageRadioButton";
			this->KAverageRadioButton->Size = System::Drawing::Size(110, 17);
			this->KAverageRadioButton->TabIndex = 1;
			this->KAverageRadioButton->TabStop = true;
			this->KAverageRadioButton->Text = L"метод К-средних";
			this->KAverageRadioButton->UseVisualStyleBackColor = true;
			// 
			// AggregationSegmentRadioButton
			// 
			this->AggregationSegmentRadioButton->AutoSize = true;
			this->AggregationSegmentRadioButton->Location = System::Drawing::Point(21, 20);
			this->AggregationSegmentRadioButton->Name = L"AggregationSegmentRadioButton";
			this->AggregationSegmentRadioButton->Size = System::Drawing::Size(192, 17);
			this->AggregationSegmentRadioButton->TabIndex = 0;
			this->AggregationSegmentRadioButton->TabStop = true;
			this->AggregationSegmentRadioButton->Text = L"метод агрегирования сегментов";
			this->AggregationSegmentRadioButton->UseVisualStyleBackColor = true;
			// 
			// Display
			// 
			this->Display->Controls->Add(this->DisplayData);
			this->Display->Location = System::Drawing::Point(12, 12);
			this->Display->Name = L"Display";
			this->Display->Size = System::Drawing::Size(268, 100);
			this->Display->TabIndex = 2;
			this->Display->TabStop = false;
			this->Display->Text = L"Методы отображения";
			// 
			// DisplayData
			// 
			this->DisplayData->Location = System::Drawing::Point(6, 19);
			this->DisplayData->Name = L"DisplayData";
			this->DisplayData->Size = System::Drawing::Size(221, 23);
			this->DisplayData->TabIndex = 2;
			this->DisplayData->Text = L"Визуализация данных";
			this->DisplayData->UseVisualStyleBackColor = true;
			this->DisplayData->Click += gcnew System::EventHandler(this, &CentralForm::DisplayData_Click);
			// 
			// Networking
			// 
			this->Networking->Location = System::Drawing::Point(12, 369);
			this->Networking->Name = L"Networking";
			this->Networking->Size = System::Drawing::Size(268, 75);
			this->Networking->TabIndex = 3;
			this->Networking->TabStop = false;
			this->Networking->Text = L"Построение сетки";
			// 
			// ConstructionHistogram
			// 
			this->ConstructionHistogram->Location = System::Drawing::Point(12, 254);
			this->ConstructionHistogram->Name = L"ConstructionHistogram";
			this->ConstructionHistogram->Size = System::Drawing::Size(268, 100);
			this->ConstructionHistogram->TabIndex = 4;
			this->ConstructionHistogram->TabStop = false;
			this->ConstructionHistogram->Text = L"Построение и исследование гистограмм";
			// 
			// NetReduction
			// 
			this->NetReduction->Location = System::Drawing::Point(12, 461);
			this->NetReduction->Name = L"NetReduction";
			this->NetReduction->Size = System::Drawing::Size(268, 100);
			this->NetReduction->TabIndex = 5;
			this->NetReduction->TabStop = false;
			this->NetReduction->Text = L"Упрощение сетки";
			// 
			// CentralForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 598);
			this->Controls->Add(this->NetReduction);
			this->Controls->Add(this->ConstructionHistogram);
			this->Controls->Add(this->Networking);
			this->Controls->Add(this->Display);
			this->Controls->Add(this->Segmentation);
			this->Name = L"CentralForm";
			this->Text = L"Main";
			this->Segmentation->ResumeLayout(false);
			this->Segmentation->PerformLayout();
			this->Display->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void DisplayData_Click(System::Object^  sender, System::EventArgs^  e) {
				 DisplayForm->Show();
			 }
	public: void CreateDisplaySegmentation();

	private: System::Void SegmentationStart_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (AggregationSegmentRadioButton->Checked)
				 {
					 CreateDisplaySegmentation();
					 DisplaySegmentationForm->Show();
					 segmentationForm->Show();
				 }
				 if (KAverageRadioButton->Checked)
					 clusterizationForm->Show();

			 }
	};
}
