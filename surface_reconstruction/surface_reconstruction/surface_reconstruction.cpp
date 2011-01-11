// surface_reconstruction.cpp : main project file.

#include "stdafx.h"
#include "MainForm.h"
#include "Main.h"

using namespace surface_reconstruction;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
    // Enabling Windows XP visual effects before any controls are created
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false); 

    // Create the main window and run it
    Application::Run(gcnew CentralForm(gcnew MainForm()));
    return 0;
}
