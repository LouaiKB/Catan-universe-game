#include "DrawingArea.h"

Drawing::Drawing()
{
    mainBoardImage = Gdk::Pixbuf::create_from_file("images/Board.png");
    // Node::isClicked = false;
    add_events(Gdk::BUTTON_PRESS_MASK);
}

Drawing::~Drawing() {}

bool Drawing::on_button_press_event(GdkEventButton* event)
{
    Node node((int)event->x, (int)event->y);
    // this Node is occupied
    node.setOccupied();
    node.setAdjacentNodes();
    if (Node::checkIfNodeIsOccupied(node, true)){
        Node::setClickedNode(node);
        // Node::setOccupiedHouseNodes({(int)event->x, (int)event->y});
        Node::isClicked = true;
    }
    // delete[] Node::clickedNode;
    queue_draw();
}

bool Drawing::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) 
{
    // Get width of the main image
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    // Draw main board
    this->drawMainWindow(cr, width, height);

    // Draw tokens
    this->drawTokens(cr);

    // Draw circles
        this->drawNodeCircles(cr);

    // Draw house onclick
    if (Node::isClicked) {
        // std::cout << "DRAW HOUSE INSIDE SCOPE" << std::endl;
        this->drawHouses(cr);
        // Node::isClicked ;
    // Node::isClicked = false;
    }

    return true;
}

void Drawing::drawMainWindow(const Cairo::RefPtr<Cairo::Context> &cr, const int mainWidth, const int mainHeight)
{
    mainBoardImage = mainBoardImage->scale_simple(mainWidth, mainHeight, Gdk::INTERP_BILINEAR);
    cr->save();
    Gdk::Cairo::set_source_pixbuf(cr, mainBoardImage, 0, 0);
    cr->rectangle(0, 0, 1000, 900);
    cr->fill();
    cr->restore();
}

void Drawing::drawTokens(const Cairo::RefPtr<Cairo::Context> &cr)
{    
    // Drawing all tokens
    for (int i = 0; i < randTokensPositions.size(); i++)
    {
        std::string imageFile = tokensFileName.at(i);
        tokenImage = Gdk::Pixbuf::create_from_file(imageFile);
        tokenImage = tokenImage->scale_simple((tokenImage->get_height()) * 0.6, (tokenImage->get_width()) * 0.6, 
                                              Gdk::INTERP_BILINEAR);
        cr->save();
        Gdk::Cairo::set_source_pixbuf(cr, tokenImage, randTokensPositions[i][0], randTokensPositions[i][1]);
        cr->rectangle(0, 0, 1000, 900);
        cr->fill();
        cr->restore();

        // set tuiles 
        this->setTuiles(i, imageFile);
    }

    // Drawing the Thief token
    tokenImage = Gdk::Pixbuf::create_from_file(tokensFileName.at(tokensFileName.size() - 1));
    tokenImage = tokenImage->scale_simple((tokenImage->get_height()) * 0.6, (tokenImage->get_width()) * 0.6, 
                                           Gdk::INTERP_BILINEAR);
    cr->save();
    Gdk::Cairo::set_source_pixbuf(cr, tokenImage, thiefTokenPositions[0], thiefTokenPositions[1]);
    cr->rectangle(0, 0, 1000, 900);
    cr->fill();
    cr->restore();
}

void Drawing::drawNodeCircles(const Cairo::RefPtr<Cairo::Context> &cr)
{   
    // Initialize the static vector of nodes  
    Node::allNodes = {Node()};

    // loop through each tuile object
    for (int i = 0; i < this->tuilesVector.size(); i++)
    {
        // we will get all the nodes of each tuile
        std::array<Node, 6> nodes = tuilesVector[i].getNodesCoordinates();
        
        // boolean variable to check if the node is occupied or not
        // std::vector<int> currentNode;
        
        // loop through each node and draw a cricle
        for (int nodeindex = 0; nodeindex < nodes.size(); nodeindex++)
        {
            // currentNode = {nodes[nodeindex].getX(), nodes[nodeindex].getY()};

            Node currentNode = nodes[nodeindex];

            if (!Node::checkIfNodeIsOccupied(currentNode))
            {
                cr->set_line_width(1.0);
                cr->save();
                cr->arc(currentNode.getX(), currentNode.getY(), 7.2, 0.0, 2 * M_PI);
                cr->close_path();
                cr->set_source_rgba(0.0, 0.8, 0.0, 0.6);
                cr->fill_preserve();
                cr->restore();
                cr->stroke();
                Node::setAllNodes(currentNode);
            }
        }
    }
    // queue_draw();
}

void Drawing::setTuiles(int index, std::string img)
{
    if (index <= 19)
        this->tuilesVector[index].setNumberOfTuile(std::stoi(img.substr(img.find('/') + 1, 1)));
    else
        this->tuilesVector[index].setNumberOfTuile(std::stoi(img.substr(img.find('/') + 1, 2)));
    
    this->tuilesVector[index].setRessourceOfTuile(randTokensPositions[index][2]);
    this->tuilesVector[index].setNodesCoordinates(randTokensPositions[index][0], randTokensPositions[index][1]);
}

// Initialize the draw house method
void Drawing::drawHouses(const Cairo::RefPtr<Cairo::Context> &cr)
{
    // get the house
    houseImage = Gdk::Pixbuf::create_from_file("Tokens/green_house.png");
    houseImage = houseImage->scale_simple((houseImage->get_height()) * 0.6, (houseImage->get_width()) * 0.6,
                                          Gdk::INTERP_BILINEAR);
    cr->save();
    double x_pos = Node::clickedNode[0].getX() - 20;
    double y_pos = Node::clickedNode[0].getY() - 20;
    

    Gdk::Cairo::set_source_pixbuf(cr, houseImage, x_pos, y_pos);
    cr->rectangle(0, 0, 1000, 900);
    cr->fill();
    cr->restore();

    Node::clickedNode[0].setAdjacentNodes();
    std::vector<Node> adjacentNodes = Node::clickedNode[0].getAdjacentNodes();
    for (int i = 0; i < adjacentNodes.size(); i++) {
        // search the node from all nodes
        Node specifiNode = Node::getSpecificNode(adjacentNodes[i]);
        
        // if we find that node 
        if (specifiNode.getX()) {
            cr->set_line_width(1.0);
            cr->save();
            cr->arc(specifiNode.getX(), specifiNode.getY(), 7.2, 0.0, 2 * M_PI);
            cr->close_path();
            cr->set_source_rgba(0.8, 0.0, 0.0, 0.6);
            cr->fill_preserve();
            cr->restore();
            cr->stroke();
        }
    }
    queue_draw();
}

std::vector<std::vector<int>> Drawing::shuffleTokensPositions()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(std::begin(tokensPositions), std::end(tokensPositions), g);
    return tokensPositions;
}


CatanMainWindow::CatanMainWindow() {

    // set title
    set_title("Catan Universe Game");

    // resize main window
    resize(1800, 900);
    set_border_width(20);

    // load image into a box widget
    eventBox.add(drawing);
    // eventBox.set_size_request(1800, 1500);
    eventBox.set_events(Gdk::ALL_EVENTS_MASK);
    eventBox.signal_button_press_event().connect(
        sigc::mem_fun(*this, &CatanMainWindow::onClicked)
    );

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
