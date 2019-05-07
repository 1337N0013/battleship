#include <unordered_map>
#include <SFML/Graphics.hpp>

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

class FontManager {
   public:
    FontManager(const FontManager&) = delete;
    void operator=(const FontManager&) = delete;

    enum class ID { Normal, Bold };
    static FontManager& getInstance();
    void load(ID id, const std::string& filename);
    sf::Font& get(ID id);
    const sf::Font& get(ID id) const;

   private:
    FontManager() {}
    std::unordered_map<ID, std::unique_ptr<sf::Font>> mFontMap;
};

#endif