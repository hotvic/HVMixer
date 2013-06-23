#include "hvmixer.h"
#include <gtkmm/application.h>

int
main(int argc, char **argv)
{
    Glib::RefPtr<Gtk::Application> app = 
        Gtk::Application::create(argc, argv, "org.hotvic.hvmixer");
    
    HVMixer::SettingsWindow sw;
    sw.opensw();
    
    return app->run(sw);
}