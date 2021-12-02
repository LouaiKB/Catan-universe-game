#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <string>
#include "CatanElements.h"
#include "GamePlay.h"

class Drawing : public Gtk::DrawingArea
{
public:
    Drawing();
    ~Drawing();
    std::vector<std::vector<int>> shuffleTokensPositions();

protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);
    virtual bool on_button_press_event(GdkEventButton* event);
    void drawMainWindow(const Cairo::RefPtr<Cairo::Context> &cr, const int, const int);
    void drawTokens(const Cairo::RefPtr<Cairo::Context> &cr);
    void drawNodeCircles(const Cairo::RefPtr<Cairo::Context> &cr);
    void setTuiles(int, std::string);
    void drawHouses(const Cairo::RefPtr<Cairo::Context> &cr);

private:
    Glib::RefPtr<Gdk::Pixbuf> mainBoardImage, tokenImage, houseImage;
    std::vector<std::string> tokensFileName = {
        "Tokens/2.png", "Tokens/2_.png", "Tokens/3.png", "Tokens/3_.png", "Tokens/3__.png",
        "Tokens/4.png", "Tokens/4_.png", "Tokens/4__.png", "Tokens/5.png", "Tokens/5_.png",
        "Tokens/5__.png", "Tokens/6.png", "Tokens/6_.png", "Tokens/6__.png", "Tokens/8.png", 
        "Tokens/8__.png", "Tokens/8_.png", "Tokens/9.png", "Tokens/9_.png", "Tokens/9__.png", 
        "Tokens/10.png", "Tokens/10_.png", "Tokens/10__.png", "Tokens/11.png", "Tokens/11_.png",
        "Tokens/11__.png", "Tokens/12.png", "Tokens/12_.png", "Tokens/Brigand.png"
    };
    /*
     * tokenPositions is a vector that contains the x position, the y position and the type of the ressource
     * {x position, y position, type of the ressource}
     * we have 5 types of ressources: 1- Brique, 2- Pierre, 3- Mouton, 4- Blé, 5-Bois.
     */

    std::vector<std::vector<int>> tokensPositions = {
        {475, 80, 1}, {350, 146, 2}, {600, 146, 3}, {225, 217, 3}, {475, 217, 4}, {729, 217, 5},
        {100, 285, 1}, {350, 285, 4}, {600, 285, 2}, {852, 285, 4}, {225, 355, 5}, {475, 355, 5},
        {730, 355, 1}, {100, 425, 4}, {350, 425, 3}, {852, 425, 5}, {225, 493, 1}, {475, 493, 1},
        {727, 493, 4}, {100, 560, 2}, {350, 560, 2}, {600, 560, 3}, {852, 560, 3}, {225, 630, 3},
        {730, 630, 2}, {350, 703, 5}, {600, 703, 4}, {475, 769, 5}
    };
    std::vector<int> thiefTokenPositions = {600, 425};
    std::vector<std::vector<int>> randTokensPositions = shuffleTokensPositions();
    std::vector<Tuile> *tuilesVector = new std::vector<Tuile>(28);
};

class CatanMainWindow : public Gtk::Window 
{
public:
    CatanMainWindow();
    virtual ~CatanMainWindow();
    bool onClicked(GdkEventButton* button_event);
    void onClickStartDice();
    void setDiceValue(int);
    void enableBuild();
    int getDiceValue();

private:
    Drawing drawing;
    Gtk::Grid mainGrid;
    Gtk::Box imageBox;
    Gtk::Button startDice, build;
    Gtk::Label left_label, right_label;
    Gtk::Box* rightUpBox = nullptr;
    Gtk::Box* leftUpBox = nullptr;
    Gtk::EventBox eventBox;
    GamePlay GAME;
    int diceValue;
};

#endif