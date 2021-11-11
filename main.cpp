#include "DrawingArea.h"

int main(int argc, char* argv[]) 
{
    auto app = Gtk::Application::create(argc, argv);
    CatanMainWindow mainWindow;
    app->run(mainWindow);
    return 0;
}