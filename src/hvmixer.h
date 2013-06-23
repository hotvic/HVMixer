#include <gtkmm.h>

#ifndef HVMIXER_H
#define HVMIXER_H

namespace HVMixer {

class SettingsWindow : public Gtk::Dialog
{
public:
    SettingsWindow();
    virtual ~SettingsWindow();
    int opensw();

protected:
    // Signal handlers
    void on_cancel_clicked();
    void on_save_clicked();
    
    // Widgets
    Gtk::Box boxmixer1, boxmixer2;
    Gtk::Label lblmixer1, lblmixer2;
    Gtk::Entry mixername1, mixername2;
};

/*class hvmixer
{
public:
    hvmixer();
    ~hvmixer();

};*/

}

#endif // HVMIXER_H
