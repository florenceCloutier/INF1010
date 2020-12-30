/*
 * Titre : Pixel.cpp - Travail Pratique #4 - Programmation Orient�e
 * Objet Date : 27 F�vrier 2020 
 * Auteur : Nabil Dabouz, Alexis Foulon, Florence Cloutier
 */

#include "Pixel.h"

/**
 * @brief constructeur par défaut de la classe
 */
Pixel::Pixel()
    : rouge_(0)
    , vert_(0)
    , bleu_(0)
{
}
/**
 * @brief constructeur par paramètres de la classe
 * @param rouge, l'élément R du pixel, entre 0 -> 255
 * @param vert, l'élément G du pixel, entre 0 -> 255
 * @param bleu, l'élément B du pixel, entre 0 -> 255
 */
Pixel::Pixel(uint8_t rouge, uint8_t vert, uint8_t bleu)
    : rouge_(rouge)
    , vert_(vert)
    , bleu_(bleu)
{
}

/**
 * @brief surcharge de l'operateur = pour le constructeur de copie
 * @param pixel Le pixel duquel on souhaite copier les attributs
 */
void Pixel::operator=(const Pixel& pixel)
{
    rouge_ = pixel.rouge_;
    vert_ = pixel.vert_;
    bleu_ = pixel.bleu_;
}

/**
 * @brief Setter de la couleur rouge
 * @param rouge La couleur rouge que l'on souhaite set
 */
void Pixel::setRouge(int rouge)
{
    rouge < 0 ? rouge_ = 0 : rouge < 255 ? rouge_ = uint8_t(rouge) : rouge_ = 255;
}

/**
 * @brief Setter de la couleur vert
 * @param vert La couleur vert que l'on souhaite set
 */
void Pixel::setVert(int vert)
{
    vert < 0 ? vert_ = 0 : vert < 255 ? vert_ = uint8_t(vert) : vert_ = 255;
}

/**
 * @brief Setter de la couleur bleu
 * @param bleu La couleur bleu que l'on souhaite set
 */
void Pixel::setBleu(int bleu)
{
    bleu < 0 ? bleu_ = 0 : bleu < 255 ? bleu_ = uint8_t(bleu) : bleu_ = 255;
}

/**
 * @brief retourne l'attribut rouge_ du pixel
 * @return rouge_ du type uint8_t
 */
uint8_t Pixel::getRouge() const
{
    return rouge_;
}
/**
 * @brief retourne l'attribut vert_ du pixel
 * @return vert_ du type uint8_t
 */
uint8_t Pixel::getVert() const
{
    return vert_;
}
/**
 * @brief retourn l'attribut bleu_ du pixel
 * @return bleu_ du type uint8_t
 */
uint8_t Pixel::getBleu() const
{
    return bleu_;
}

/**
 * @brief Surcharge de l'operateur pour afficher un pixel <<
 * @param os parametre de retour
 * @param pixel que l'on souhaite afficher
 * @return parametre ostream que l'on affiche
 */
std::ostream& operator<<(std::ostream& os, Pixel pixel)
{
    os << '#' << std::hex << std::uppercase << std::setfill('0') << std::setw(2)
       << (int)pixel.getRouge() << ' ' << std::setw(2) << (int)pixel.getVert() << ' '
       << std::setw(2) << (int)pixel.getBleu() << std::setfill(' ');
    return os;
}

/**
 * @brief Surcharge de l'operateur pour lire un pixel >>
 * @param is parametre de retour
 * @param pixel que l'on souhaite input
 * @return parametre istream que l'on input
 */
std::istream& operator>>(std::istream& is, Pixel& pixel)
{
    int rouge, vert, bleu;

    is >> rouge >> vert >> bleu;
    pixel.setRouge(rouge);
    pixel.setVert(vert);
    pixel.setBleu(bleu);

    return is;
}