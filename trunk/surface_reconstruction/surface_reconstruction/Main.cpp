#include "StdAfx.h"
#include "Main.h"

#include "MainForm.h"

void  surface_reconstruction::CentralForm::CreateDisplaySegmentation()
{
    MainForm^ mainForm = gcnew MainForm();
    mainForm->GetNewScanData = gcnew SetScanData(this, &CentralForm::ChangeData);
	mainForm->GetIndexSelectVoxel = gcnew SetIndexVoxel(this, &CentralForm::SetIndexVoxelToSegmentation);
    SetScanData ^ StaticDelInst = gcnew SetScanData(mainForm, &MainForm::ChangeData);
    DisplaySegmentationForm = mainForm;
    segmentationForm->StaticDelInst = gcnew SetScanData(mainForm, &MainForm::ChangeData);
}