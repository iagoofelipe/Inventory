#include "InventoryApp.h"

namespace inventory
{
    bool InventoryApp::OnInit()
    {
        controller.Initialize();

        return true;
    }
}