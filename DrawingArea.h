#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <iostream>

class Drawing : public Gtk::DrawingArea
{
public:
    Drawing();
    ~Drawing();
protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    // bool on_scroll_event(GdkEventScroll *);

private:
    Glib::RefPtr<Gdk::Pixbuf> image;
    double scale;
};

class CatanMainWindow : public Gtk::Window 
{
public:
    CatanMainWindow();
    virtual ~CatanMainWindow();
    bool onClicked(GdkEventButton* button_event);

private:
    Drawing drawing;
    Gtk::Grid mainGrid;
    Gtk::Box imageBox, leftUpBox;
    Gtk::Button startDice;
    Gtk::Label left_label, right_label;
    Gtk::Box* rightUpBox = nullptr;
    // now we will try adding the event box
    Gtk::EventBox eventBox;
};
#endif