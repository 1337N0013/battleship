#include <iostream>
#include "FontManager.h"

FontManager& FontManager::getInstance() {
    static FontManager instance;
    return instance;
}

void FontManager::load(ID id, const std::string& filename) {
    std::unique_ptr<sf::Font> font(new sf::Font());
    std::cout << filename << std::endl;
    font->loadFromFile(filename);

    mFontMap.insert(std::make_pair(id, std::move(font)));
}

sf::Font& FontManager::get(ID id) {
    auto foundFont = mFontMap.find(id);
    return *foundFont->second;
}

const sf::Font& FontManager::get(ID id) const {
    auto foundFont = mFontMap.find(id);
    return *foundFont->second;
}