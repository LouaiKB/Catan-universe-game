#include "DrawingArea.h"


Drawing::Drawing()
{
    image = Gdk::Pixbuf::create_from_file("images/Board.png");
    smallImage = Gdk::Pixbuf::create_from_file("images/F.png");
    scale = 0.22;
    scaleSmallImage = 2.7;
}

Drawing::~Drawing() {}

bool Drawing::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) 
{
    Coordinates placement;
    // Get width
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    
    // place the first image
    cr->scale(scale, scale);
    Gdk::Cairo::set_source_pixbuf(cr, image, (width/2) / scale - image->get_width()/2,
    (height/2)/scale - image->get_height()/2);
    cr->rectangle(0, 0, get_allocation().get_width()/scale, get_allocation().get_width()/scale);
    cr->fill();

    // place the second image
    cr->scale(scaleSmallImage, scaleSmallImage);
    cr->translate(placement.getXCoordinate(8), placement.getYCoordinate(2));
    Gdk::Cairo::set_source_pixbuf(cr, smallImage, (width/2) / scaleSmallImage - smallImage->get_width()/2,
    (height/2)/scaleSmallImage - smallImage->get_height()/2);
    cr->rectangle(0, 0, get_allocation().get_width()/scaleSmallImage, get_allocation().get_width()/scaleSmallImage);
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
    img.set("images/F.png");
    // img.set_size_request(50, 50);
    // imageBox.pack_start(img, Gtk::PACK_EXPAND_WIDGET);
    imageBox.pack_start(eventBox, Gtk::PACK_EXPAND_WIDGET);
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
    std::cout << "-------------------------------" << std::endl;
}

CatanMainWindow::~CatanMainWindow() {}

Coordinates::Coordinates() {}

Coordinates::~Coordinates() {}

double Coordinates::getXCoordinate(int num)
{
    switch (num)
    {
    case 1:
        return this->X1;
        break;
    case 2:
        return this->X2;
        break;
    case 3:
        return this->X3;
        break;
    case 4:
        return this->X4;
        break;
    case 5:
        return this->X5;
        break;
    case 6:
        return this->X6;
        break;
    case 7:
        return this->X7;
        break;
    case 8:
        return this->X8;
        break;
    case 9:
        return this->X9;
        break;
    case 10:
        return this->X10;
        break;
    case 11:
        return this->X11;
        break;
    case 12:
        return this->X12;
        break;
    case 13:
        return this->X13;
        break;
    case 14:
        return this->X14;
        break;
    case 15:
        return this->X15;
        break;
    case 16:
        return this->X16;
        break;
    default:
        break;
    }
}

double Coordinates::getYCoordinate(int num)
{
    switch (num)
    {
    case 1:
        return this->Y1;
        break;
    case 2:
        return this->Y2;
        break;
    case 3:
        return this->Y3;
        break;
    case 4:
        return this->Y4;
        break;
    case 5:
        return this->Y5;
        break;
    case 6:
        return this->Y6;
        break;
    case 7:
        return this->Y7;
        break;
    case 8:
        return this->Y8;
        break;
    case 9:
        return this->Y9;
        break;
    case 10:
        return this->Y10;
        break;
    case 11:
        return this->Y11;
        break;
    case 12:
        return this->Y12;
        break;
    case 13:
        return this->Y13;
        break;
    default:
        break;
    }
}