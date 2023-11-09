//
// Created by loona on 09/11/23.
//

#include "text.h"

sf::Text generation_text,  top_performer_text, first_parent_text, second_parent_text;


void loadText(){
    generation_text.setFont(gotham_font);
    generation_text.setCharacterSize(18);
    generation_text.setFillColor(sf::Color::Black);
    generation_text.setPosition(0,0);

    top_performer_text.setFont(gotham_font);
    top_performer_text.setCharacterSize(18);
    top_performer_text.setFillColor(sf::Color::Black);
    top_performer_text.setPosition(0,20);

    first_parent_text.setFont(gotham_font);
    first_parent_text.setCharacterSize(18);
    first_parent_text.setFillColor(sf::Color::Black);
    first_parent_text.setPosition(0,40);

    second_parent_text.setFont(gotham_font);
    second_parent_text.setCharacterSize(18);
    second_parent_text.setFillColor(sf::Color::Black);
    second_parent_text.setPosition(0,60);
}


sf::Font gotham_font;

void loadFonts(){
    if (!gotham_font.loadFromFile("../assets/GothamMedium.ttf")) {
        printf("could not load font: GothamMedium.ttf");
        exit(1);
    }
}