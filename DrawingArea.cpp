#include "DrawingArea.h"


Drawing::Drawing()
{
    image = Gdk::Pixbuf::create_from_file("images/Board.png");
    scale = 0.22;
}

Drawing::~Drawing() {}

bool Drawing::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) 
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    cr->scale(scale, scale);
    Gdk::Cairo::set_source_pixbuf(cr, image, (width/2) / scale - image->get_width()/2,
    (height/2)/scale - image->get_height()/2);
    cr->rectangle(0, 0, get_allocation().get_width()/scale, get_allocation().get_width()/scale);
    cr->fill();
    return true;
}


CatanMainWindow::CatanMainWindow() {

    // set title
    set_title("Catan Universe Game");

    // resize main window
    resize(1800, 900);
    set_border_width(20);

    // load image into a box widget
    eventBox.add(drawing);
    eventBox.set_events(Gdk::ALL_EVENTS_MASK);
    eventBox.signal_button_press_event().connect(
        sigc::mem_fun(*this, &CatanMainWindow::onClicked)
    );
    imageBox.pack_start(eventBox);
    imageBox.set_size_request(1000, 900);
    imageBox.set_halign(Gtk::ALIGN_CENTER);
    imageBox.set_valign(Gtk::ALIGN_CENTER);

    // configure left side
    left_label.set_text("the turn is up to the user\nScore = ");
    leftUpBox.pack_start(left_label);
    leftUpBox.set_halign(Gtk::ALIGN_START);
    leftUpBox.set_valign(Gtk::ALIGN_START);


    // configure right side
    right_label.set_text("Dice value = ");
    startDice.add_label("Throw dice");
    rightUpBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    rightUpBox->set_spacing(10);
    rightUpBox->pack_start(right_label);
    rightUpBox->pack_start(startDice);
    rightUpBox->set_halign(Gtk::ALIGN_END);
    rightUpBox->set_valign(Gtk::ALIGN_END);

    // attach into grid and center the main grid
    mainGrid.attach(imageBox, 10, 2, 3, 1);
    mainGrid.attach(leftUpBox, 0, 0, 1, 1);
    mainGrid.attach(*rightUpBox, 20, 0, 1, 1);
    mainGrid.set_halign(Gtk::ALIGN_CENTER);
    mainGrid.set_valign(Gtk::ALIGN_CENTER);

    // add grid
    add(mainGrid);
    show_all_children();
} 

bool CatanMainWindow::onClicked(GdkEventButton* button_event) {
    std::cout << "x= " << button_event-> x << std::endl;
    std::cout << "y= " << button_event-> y << std::endl;
}

CatanMainWindow::~CatanMainWindow() {}























// bool Drawing::on_scroll_event(GdkEventScroll *event) 
// {
//     scale -= event->delta_y/10.;
//     if (scale < 0.1) scale = 0.1;
//     std::cout << scale << std::endl;
//     std::cout.flush();
//     queue_draw();
//     return true;
// }