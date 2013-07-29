#include <iostream>
#include "hvmixer.h"


int
main(int argc, char **argv)
{
    Gtk::Main kit(argc, argv);

    HVMixer::TrayIcon tray;

    Gtk::Main::run();
}
