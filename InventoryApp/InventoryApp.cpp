#include "InventoryApp.h"
#include "MainWindow.h"

bool InventoryApp::OnInit()
{
    MainWindow* window = new MainWindow("Inventory");
    window->Show();

    return true;
}