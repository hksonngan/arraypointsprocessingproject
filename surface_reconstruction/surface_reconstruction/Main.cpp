#include "StdAfx.h"
#include "Main.h"

#include "MainForm.h"

void  surface_reconstruction::CentralForm::CreateDisplaySegmentation()
{
    MainForm^ mainForm = gcnew MainForm();
    mainForm->StaticDelInst = gcnew MyDel(this, &CentralForm::ChangeData);
    MyDel ^ StaticDelInst = gcnew MyDel(mainForm, &MainForm::ChangeData);
    DisplaySegmentationForm = mainForm;
    segmentationForm->StaticDelInst = gcnew MyDel(mainForm, &MainForm::ChangeData);
    //segmentationForm->data = safe_cast<MainForm>(mainForm->data);
}