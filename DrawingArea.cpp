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
    // if (Node::buildRoute) {
    //     bool firstClickedNode = false, secondClickedNode = false;
    //     if (!firstClickedNode && !secondClickedNode) {
    //         int x1 = event->x;
    //         int y1 = event->y;
    //         Node::setClickedNode(Node(x1, y1));
    //         firstClickedNode = true;
    //         Node::buildRoute = false;
    //         std::cout << "FIRST IFFF" << std::endl;
    //     }
    //     if (firstClickedNode && !secondClickedNode && 
    //         (int)event->x != Node::clickedNode[0].getX() &&
    //         (int)event->y != Node::clickedNode[0].getY()) {
    //             int x2 = event->x;
    //             int y2 = event->y;
    //             Node::clickedNode[1] = Node(x2, y2);
    //             secondClickedNode = true;
    //             Node::buildRoute = false;
    //             std::cout << "SECOND IFFFFF" << std::endl;
    //     }
    //     Node::playerOn = false;
    // }

    if (Node::playerOn) {
        Node node((int)event->x, (int)event->y);
        // this Node is occupied
        node.setOccupied();
        node.setAdjacentNodes();
        if (Node::checkIfNodeIsOccupied(node, Node::allNodes)){
            Node::setClickedNode(node);
            Node::isClicked = true;
            Node::playerOn = false;
        }
        queue_draw();
    } else {
        CatanMainWindow win;
        Gtk::MessageDialog d(win, "Press on the BUILD button to enable building",
            false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK);
        d.run();
    }
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
    this->drawHouses(cr);

    // this->drawRoutes(cr);

    // update the widget
    queue_draw();

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
    *Node::allNodes = {Node()};

    // loop through each tuile object
    for (int i = 0; i < this->tuilesVector->size(); i++)
    {
        // we will get all the nodes of each tuile
        std::vector<Node> *nodes = tuilesVector->at(i).getNodesCoordinates();
        
        // loop through each node and draw a cricle
        for (int nodeindex = 0; nodeindex < nodes->size(); nodeindex++)
        {
            // currentNode = {nodes[nodeindex].getX(), nodes[nodeindex].getY()};

            Node currentNode = nodes->at(nodeindex);

            if (!Node::checkIfNodeIsOccupied(currentNode, Node::allNodes))
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

        std::vector<Node> *edges = tuilesVector->at(i).getEdgesCoordinates();

        // loop through each edge node and draw a cricle
        for (int nodeindex = 0; nodeindex < edges->size(); nodeindex++)
        {
            // currentNode = {nodes[nodeindex].getX(), nodes[nodeindex].getY()};

            Node currentNode = edges->at(nodeindex);

            if (!Node::checkIfNodeIsOccupied(currentNode, Node::allNodes))
            {
                cr->set_line_width(1.0);
                cr->save();
                cr->arc(currentNode.getX(), currentNode.getY(), 5, 0.0, 2 * M_PI);
                cr->close_path();
                cr->set_source_rgba(0.95, 0.95, 0.95, 0.5);
                cr->fill_preserve();
                cr->restore();
                cr->stroke();
                Node::setAllNodes(currentNode);
            }
        }
    }
}

void Drawing::setTuiles(int index, std::string img)
{
    if (index <= 19)
        this->tuilesVector->at(index).setNumberOfTuile(std::stoi(img.substr(img.find('/') + 1, 1)));
    else
        this->tuilesVector->at(index).setNumberOfTuile(std::stoi(img.substr(img.find('/') + 1, 2)));
    
    this->tuilesVector->at(index).setRessourceOfTuile(randTokensPositions[index][2]);
    this->tuilesVector->at(index).setNodesCoordinates(randTokensPositions[index][0], randTokensPositions[index][1]);
    this->tuilesVector->at(index).setEdgesCoordinates();
}

// Initialize the draw house method
void Drawing::drawHouses(const Cairo::RefPtr<Cairo::Context> &cr)
{
    if (Node::clickedNode[0].getX() != 0) {
        // get the house
        houseImage = Gdk::Pixbuf::create_from_file("Tokens/green_house.png");
        houseImage = houseImage->scale_simple((houseImage->get_height()) * 0.5, (houseImage->get_width()) * 0.5,
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
        Node node = Node::clickedNode[0];
        // std::vector<int> a = Tuile::getTilesOfANode(node, tuilesVector);
    }
}

void Drawing::drawRoutes(const Cairo::RefPtr<Cairo::Context> &cr)
{
    if (Node::clickedNode[0].getX() != 0 && Node::clickedNode[1].getX() != 0) {
        cr->set_line_width(2);
        cr->set_source_rgb(0.0, 0.8, 0.0);
        cr->move_to(Node::clickedNode[0].getX(), Node::clickedNode[0].getY());
        cr->line_to(Node::clickedNode[1].getX(), Node::clickedNode[1].getY());
        cr->stroke();
    }
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

    this->diceValue = 0;

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

    imageBox.set_spacing(5);
    imageBox.pack_start(eventBox, Gtk::PACK_EXPAND_WIDGET);
    imageBox.set_size_request(1000, 900);
    imageBox.set_halign(Gtk::ALIGN_CENTER);
    imageBox.set_valign(Gtk::ALIGN_CENTER);

    // configure left side
    left_label.set_text("the turn is up to the user number 1\nScore = 0");
    leftUpBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    leftUpBox->set_spacing(10);
    leftUpBox->pack_start(left_label);
    build.add_label("Build");
    build.signal_clicked().connect(
        sigc::mem_fun(*this, &CatanMainWindow::enableBuild)
    );
    buildRoute.add_label("Build route");
    buildRoute.signal_clicked().connect(
        sigc::mem_fun(*this, &CatanMainWindow::enableBuildRoutes)
    );
    leftUpBox->pack_start(build);
    leftUpBox->pack_start(buildRoute);
    leftUpBox->set_halign(Gtk::ALIGN_START);
    leftUpBox->set_valign(Gtk::ALIGN_START);


    // configure right side
    right_label.set_text("Dice value = 0");
    startDice.add_label("Throw dice");
    startDice.signal_clicked().connect(sigc::mem_fun(*this, &CatanMainWindow::onClickStartDice));
    rightUpBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    rightUpBox->set_spacing(10);
    rightUpBox->pack_start(right_label);
    rightUpBox->pack_start(startDice);
    rightUpBox->set_halign(Gtk::ALIGN_END);
    rightUpBox->set_valign(Gtk::ALIGN_END);

    // attach into grid and center the main grid
    mainGrid.attach(imageBox, 12, 0, 3, 1);
    mainGrid.attach(*leftUpBox, 0, 0, 1, 1);
    mainGrid.attach(*rightUpBox, 30, 0, 1, 1);
    // mainGrid.set_halign(Gtk::ALIGN_CENTER);
    // mainGrid.set_valign(Gtk::ALIGN_CENTER);

    queue_draw();

    // add grid
    add(mainGrid);
    show_all_children();
} 

CatanMainWindow::~CatanMainWindow() {}

bool CatanMainWindow::onClicked(GdkEventButton* button_event) {
    // std::cout << "x= " << button_event-> x << std::endl;
    // std::cout << "y= " << button_event-> y << std::endl;
    // std::cout << "-------------------------------" << std::endl;
}

void CatanMainWindow::setDiceValue(int a)
{
    this->diceValue = a;
}

void CatanMainWindow::onClickStartDice()
{
    int random = GAME.startDice();
    this->setDiceValue(random);
    this->right_label.set_text("Dice value = " + std::to_string(this->getDiceValue()));
}

int CatanMainWindow::getDiceValue()
{
    return this->diceValue;
}

void CatanMainWindow::enableBuild()
{
    GAME.enableBuilding();
    Gtk::MessageDialog d(*this, "Press on a green point to build",
    false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
    d.run();
}

void CatanMainWindow::enableBuildRoutes()
{
    GAME.enableBuildingRoute();
    Gtk::MessageDialog d(*this, "Click on the two points to build a route",
    false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
    d.run();
}
