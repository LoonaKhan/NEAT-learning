#pragma once

#include "vector"
#include "SFML/Graphics.hpp"

extern std::vector<sf::Texture> plr_textures;

extern std::vector<sf::Texture> obs_textures;

extern sf::Texture floor_texture;

void loadTextures();