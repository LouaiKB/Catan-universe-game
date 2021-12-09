#include "DrawingArea.h"

Drawing::Drawing()
{
    mainBoardImage = Gdk::Pixbuf::create_from_file("images/Board.png");
    add_events(Gdk::BUTTON_PRESS_MASK);
}

Drawing::~Drawing() {}

bool Drawing::on_button_press_event(GdkEventButton* event)
{
    if (Node::buildRoute) {
        Node node((int)event->x, (int)event->y);
        Edge edge = Edge::getSpecificEdge(node, Edge::allEdges);
        if (Edge::checkIfNodeExists(edge, Edge::allEdges)) {
            Edge::setClickedNode(edge);
            Edge::isClicked = true;
            Node::buildRoute = false;
        }
        queue_draw();
        return 1;
    }

    if (Node::playerOn) {
        Node node((int)event->x, (int)event->y);
        if (Node::checkIfNodeExists(node, Node::allNodes)) {
            if (Node::checkIfNodeExists(node, Node::allClickedNodes)) {
                CatanMainWindow win;
                Gtk::MessageDialog d(win, "You can't build here!",
                    false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
                d.run();
            } else {
                node.setOccupied();
                node.setAdjacentNodes();
                Node::setClickedNode(node);
                Node::isClicked = true;
                Node::playerOn = false;
            } 
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

    // Draw Routes
    this->drawRoutes(cr);

    // update the widget
    // queue_draw();

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
    *Edge::allEdges = {Edge()};

    // loop through each tuile object
    for (int i = 0; i < this->tuilesVector->size(); i++)
    {
        // we will get all the nodes of each tuile
        std::vector<Node> *nodes = tuilesVector->at(i).getNodesCoordinates();

        // loop through each node and draw a cricle
        for (int nodeindex = 0; nodeindex < nodes->size(); nodeindex++)
        {
            Node currentNode = nodes->at(nodeindex);

            if (!Node::checkIfNodeExists(currentNode, Node::allNodes))
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

        std::vector<Edge> *edges = tuilesVector->at(i).getEdgesCoordinates();

        // loop through each edge node and draw a cricle
        for (int nodeindex = 0; nodeindex < edges->size(); nodeindex++)
        {
            Edge currentEdge = edges->at(nodeindex);

            if (!Edge::checkIfNodeExists(currentEdge, Edge::allEdges))
            {
                cr->set_line_width(1.0);
                cr->save();
                cr->arc(currentEdge.getX(), currentEdge.getY(), 5, 0.0, 2 * M_PI);
                cr->close_path();
                cr->set_source_rgba(0.95, 0.95, 0.95, 0.5);
                cr->fill_preserve();
                cr->restore();
                cr->stroke();
                Edge::setAllEdges(currentEdge);
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
    CatanMainWindow win;
    win.setAllPlayers();

    if (Node::clickedNode[0].getX() != 0) {
        if (Node::isClicked) {
            win.setCurrentPlayer();
            Player currentPlayer = win.getCurrentPlayer();
            currentPlayer.setAppropriateNode(Node::clickedNode[0]);
            Player::allClickedNodes->push_back(currentPlayer);
            Node::isClicked = false;
            Node::allClickedNodes->push_back(Node::clickedNode[0]);
        }
        for (int j = 0; j < Player::allClickedNodes->size(); j++) {
            houseImage = Gdk::Pixbuf::create_from_file(Player::allClickedNodes->at(j).getSettlment());
            houseImage = houseImage->scale_simple((houseImage->get_height()) * 0.5, (houseImage->get_width()) * 0.5,
                                                Gdk::INTERP_BILINEAR);
            cr->save();

            Node currentNode = Player::allClickedNodes->at(j).getAppropriateNode();
            double x_pos = currentNode.getX() - 20;
            double y_pos = currentNode.getY() - 20;

            Gdk::Cairo::set_source_pixbuf(cr, houseImage, x_pos, y_pos);
            cr->rectangle(0, 0, 1000, 900);
            cr->fill();
            // cr->restore();
            
            // Node::clickedNode[0].setAdjacentNodes();
            currentNode.setAdjacentNodes();
            std::vector<Node> adjacentNodes = currentNode.getAdjacentNodes();
            for (int i = 0; i < adjacentNodes.size(); i++) {
                // search the node from all nodes
                Node specifiNode = Node::getSpecificNode(adjacentNodes[i]);
                Node::allClickedNodes->push_back(specifiNode);
                // if we find that node 
                if (specifiNode.getX()) {
                    cr->set_line_width(1.0);
                    cr->save();
                    cr->arc(specifiNode.getX(), specifiNode.getY(), 7.2, 0.0, 2 * M_PI);
                    cr->close_path();
                    cr->set_source_rgba(0.8, 0.0, 0.0, 0.6);
                    cr->fill_preserve();
                    // cr->restore();
                    cr->stroke();
                }
            }
        }
    }
}

void Drawing::drawRoutes(const Cairo::RefPtr<Cairo::Context> &cr)
{
    CatanMainWindow win;
    win.setAllPlayers();
    if (Edge::clickedEdge[0].getX() != 0) {
        Edge edge = Edge::clickedEdge[0];
        if (Edge::isClicked) {
            win.setCurrentPlayer();
            Player currentPlayer = win.getCurrentPlayer();
            currentPlayer.setAppropriateEdge(Edge::clickedEdge[0]);
            Player::allClickedEdges->push_back(currentPlayer);
            Edge::isClicked = false;
        }
        for (int i = 0; i < Player::allClickedEdges->size(); i++) {
            Edge currentEdge = Player::allClickedEdges->at(i).getAppropriateEdge();
            std::vector<Node> nodesOfTheEdge = Edge::getNodesOfAnEdge(currentEdge);
            cr->save();
            cr->set_line_width(4.9);
            switch (Player::allClickedEdges->at(i).getNumberOfPlayer())
            {
            case 1:
                cr->set_source_rgb(0.0, 0.5, 0.0);
                break;
            
            case 2:
                cr->set_source_rgb(0.0, 0.0, 0.5);
                break;
            
            case 3:
                cr->set_source_rgb(0.5, 0.0, 0.0);
                break;
            
            case 4:
                cr->set_source_rgb(0.5, 0.5, 0.0);
                break;
            
            case 5:
                cr->set_source_rgb(0.6, 0.8, 0.1);
                break;
            
            case 6:
                cr->set_source_rgb(0.8, 0.8, 0.8);
                break;

            default:
                break;
            }

            cr->move_to(nodesOfTheEdge[0].getX(), nodesOfTheEdge[0].getY());
            cr->line_to(nodesOfTheEdge[1].getX(), nodesOfTheEdge[1].getY());
            cr->stroke();
        }
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

    // GAME->setPlayers();
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
    nextPlayer.add_label("Next Player");
    nextPlayer.signal_clicked().connect(
        sigc::mem_fun(*this, &CatanMainWindow::switchPlayer)
    );

    leftUpBox->pack_start(build);
    leftUpBox->pack_start(buildRoute);
    leftUpBox->pack_start(nextPlayer);
    leftUpBox->set_halign(Gtk::ALIGN_START);
    leftUpBox->set_valign(Gtk::ALIGN_START);


    // configure right side
    right_label.set_text("Dice value = 0");
    startDice.add_label("Throw dice");
    choosePlayer.add_label("choose players");
    choosePlayer.signal_clicked().connect(sigc::mem_fun(*this, &CatanMainWindow::getPlayersFromCombo));
    startDice.signal_clicked().connect(sigc::mem_fun(*this, &CatanMainWindow::onClickStartDice));
    rightUpBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    combo.append("2");
    combo.append("3");
    combo.append("4");
    combo.append("5");
    combo.append("6");
    combo.append("choose number of players");
    combo.set_active(5);
    rightUpBox->set_spacing(10);
    rightUpBox->pack_start(right_label);
    rightUpBox->pack_start(startDice);
    rightUpBox->pack_start(combo);
    rightUpBox->pack_start(choosePlayer);
    rightUpBox->set_halign(Gtk::ALIGN_END);
    rightUpBox->set_valign(Gtk::ALIGN_END);

    // attach into grid and center the main grid
    mainGrid.attach(imageBox, 12, 0, 3, 1);
    mainGrid.attach(*leftUpBox, 0, 0, 1, 1);
    mainGrid.attach(*rightUpBox, 30, 0, 1, 1);
    // mainGrid.set_halign(Gtk::ALIGN_CENTER);
    // mainGrid.set_valign(Gtk::ALIGN_CENTER);

    // queue_draw();

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
    int random = GAME->startDice();
    this->setDiceValue(random);
    this->right_label.set_text("Dice value = " + std::to_string(this->getDiceValue()));
}

int CatanMainWindow::getDiceValue()
{
    return this->diceValue;
}

void CatanMainWindow::enableBuild()
{
    GAME->enableBuilding();
    Gtk::MessageDialog d(*this, "Press on a green point to build",
    false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
    d.run();
}

void CatanMainWindow::enableBuildRoutes()
{
    GAME->enableBuildingRoute();
    // Gtk::MessageDialog d(*this, "Click on the two points to build a route",
    // false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
    // d.run();
}


// Player CatanMainWindow::getCurrentPlayer(int player)
// {
//     this->currentPlayer = GAME->getPlayers()->at(player);
//     return this->currentPlayer;
// }

int CatanMainWindow::playerId = 0;
// int CatanMainWindow::numPlayers;

void CatanMainWindow::switchPlayer()
{
    if (CatanMainWindow::playerId != this->players->size() - 1) {
        left_label.set_text("the turn is up to the user number " + std::to_string(CatanMainWindow::playerId + 1)
            + "\nScore = " + std::to_string(this->currentPlayer.getScore()));
        CatanMainWindow::playerId++;
    }
    else {
        CatanMainWindow::playerId = 0;
    }
}

// std::vector<Player>* CatanMainWindow::getPlayers()
// {
//     this->players->at(0) = Player(1);
//     this->players->at(1) = Player(2);
//     this->players->at(2) = Player(3);
//     return this->players;
// }

void CatanMainWindow::setAllPlayers()
{
    // std::cout << this->numberOfPlayers << std::endl;
    // if (this->numberOfPlayers == 0) {
    //     this->numberOfPlayers = 1;
    // } else {
    //     this->numberOfPlayers = 1;
    // }
    // for (int i = 0; i < this->numberOfPlayers; i++) {
    //     this->players->at(i) = Player(i+1);
    // }
    this->players->at(0) = Player(2);
    this->players->at(1) = Player(3);
    this->players->at(2) = Player(4);
}

Player CatanMainWindow::getCurrentPlayer()
{
    return this->currentPlayer;
}

void CatanMainWindow::setCurrentPlayer()
{
    this->currentPlayer = this->players->at(CatanMainWindow::playerId);
}

void CatanMainWindow::getPlayersFromCombo()
{
    Gtk::MessageDialog dialog(*this, "Number of players", false, Gtk::MESSAGE_INFO);
    dialog.set_secondary_text("There will be " + combo.get_active_text() + " players!");
    dialog.run();
    this->numberOfPlayers = std::stoi(combo.get_active_text());
}

// void CatanMainWindow::setNumberOfPlayers()
// {
// }