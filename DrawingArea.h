#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <iostream>
#include <array>
#include <algorithm>
#include <random>

class Drawing : public Gtk::DrawingArea
{
public:
    Drawing();
    ~Drawing();
    std::vector<std::vector<int>> shuffleTokensPositions();

protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);
    void drawMainWindow(const Cairo::RefPtr<Cairo::Context> &cr, const int, const int);
    void drawTokens(const Cairo::RefPtr<Cairo::Context> &cr);

private:
    Glib::RefPtr<Gdk::Pixbuf> mainBoardImage, tokenImage;
    std::vector<std::string> tokensFileName = {
        "Tokens/A.png", "Tokens/B.png", "Tokens/C.png", "Tokens/D.png", "Tokens/E.png", "Tokens/F.png", "Tokens/G.png", "Tokens/H.png", "Tokens/I.png", "Tokens/J.png",
        "Tokens/K.png", "Tokens/L.png", "Tokens/M.png", "Tokens/N.png", "Tokens/O.png", "Tokens/P.png", "Tokens/Q.png", "Tokens/R.png", "Tokens/S.png", "Tokens/T.png", 
        "Tokens/U.png", "Tokens/V.png", "Tokens/W.png", "Tokens/X.png", "Tokens/Y.png", "Tokens/Z.png", "Tokens/Za.png", "Tokens/Zb.png", "Tokens/Brigand.png"
    };
    std::vector<std::vector<int>> tokensPositions = {
        {475, 80}, {350, 146}, {600, 146}, {225, 217}, {475, 217}, {729, 217}, {100, 285}, {350, 285}, {600, 285}, {852, 285}, {225, 355}, {475, 355}, {730, 355}, {100, 425}, {350, 425}, {852, 425}, {225, 493},
        {475, 493}, {727, 493}, {100, 560}, {350, 560}, {600, 560}, {852, 560}, {225, 630}, {730, 630}, {350, 703}, {600, 703}, {475, 769}
    };
    std::vector<int> thiefTokenPositions = {600, 425};
    std::vector<std::vector<int>> randTokensPositions = shuffleTokensPositions();
};

class CatanMainWindow : public Gtk::Window 
{
public:
    CatanMainWindow();
    virtual ~CatanMainWindow();
    bool onClicked(GdkEventButton* button_event);

private:
    // Gtk::Image img;
    Drawing drawing;
    Gtk::Grid mainGrid;
    Gtk::Box imageBox, leftUpBox;
    Gtk::Button startDice;
    Gtk::Label left_label, right_label;
    Gtk::Box* rightUpBox = nullptr;
    Gtk::EventBox eventBox;
};

class Coordinates
{
public:
    Coordinates();
    ~Coordinates();
    double getXCoordinate(int);
    double getYCoordinate(int);

private:
    // All x coordonants
    const double X1 = 75.0204;
    const double X2 = 113.262;
    const double X3 = 189.667;
    const double X4 = 229.597;
    const double X5 = 305.369;
    const double X6 = 344.367;
    const double X7 = 422.307;
    const double X8 = 461.294;
    const double X9 = 537.43;
    const double X10 = 576.795;
    const double X11 = 653.593;
    const double X12 = 691.461;
    const double X13 = 769.884;
    const double X14 = 808.451;
    const double X15 = 885.451;
    const double X16 = 922.931;
    int horizontalDistanceX = 40;
    int edgeDistanceX = 76;

    // All y coordonants
    const double Y1 = 50.3857;
    const double Y2 = 117.186;
    const double Y3 = 182.623;
    const double Y4 = 250.615;
    const double Y5 = 317.384;
    const double Y6 = 386.856;
    const double Y7 = 452.078;
    const double Y8 = 518.634;
    const double Y9 = 586.283;
    const double Y10 = 655.362;
    const double Y11 = 720.707;
    const double Y12 = 786.421;
    const double Y13 = 852.98;
    int distanceY = 69;
};

#endif