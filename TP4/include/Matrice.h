/*
 * Titre : Matrice.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz, Alexis Foulon et Florence Cloutier
 */

#ifndef MATRICE_H
#define MATRICE_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

/**
 * @brief definition de la classe Matrice
 */
template<typename T>
class Matrice
{
public:
    Matrice();
    // Destructeur
    ~Matrice() = default;
    T operator()(const size_t& posY, const size_t& posX) const;
    // Lecture du fichier
    bool chargerDepuisFichier(const std::string& nomFichier);
    bool lireElement(const std::string& elementFichier, const size_t& posY, const size_t& posX);
    // Remplir un matrice
    bool ajouterElement(T element, const size_t& posY, const size_t& posX);
    // Faire une copie
    std::unique_ptr<Matrice<T>> clone() const;
    // Setters
    void setHeight(size_t height);
    void setWidth(size_t width);
    // Getters
    size_t getHeight() const;
    size_t getWidth() const;

private:
    std::vector<std::vector<T>> elements_;
    size_t height_;
    size_t width_;
};

namespace
{
    static constexpr int CAPACITE_MATRICE = 100;
}

/**
 * @brief constructeur par défaut de la classe
 */
template<typename T>
inline Matrice<T>::Matrice()
    : height_(0)
    , width_(0)
{
    elements_.resize(CAPACITE_MATRICE, std::vector<T>(CAPACITE_MATRICE));
}
/**
 * @brief retourne le nombre de lignes de la matrice
 * @return l'attribut height_ de l'objet
 */
template<typename T>
inline size_t Matrice<T>::getHeight() const
{
    return height_;
}
/**
 * @brief retourne le nombre de colonnes de la matrice
 * @return l'attribut width_ de l'objet
 */
template<typename T>
inline size_t Matrice<T>::getWidth() const
{
    return width_;
}

template<typename T>
T Matrice<T>::operator()(const size_t& posY, const size_t& posX) const
{
    if (posY > height_ || posX > width_)
        return T();

    return elements_[posX][posY];
}

template<typename T>
bool Matrice<T>::ajouterElement(T element, const size_t& posY, const size_t& posX)
{
    if (posY > height_ || posX > width_)
        return false;

    elements_[posX][posY] = element;
    return true;
}

template<typename T>
bool Matrice<T>::lireElement(const std::string& elementFichier, const size_t& posY,
                             const size_t& posX)
{
    T element;
    std::stringstream(elementFichier) >> element;

    return ajouterElement(element, posY, posX);
}

template<typename T>
bool Matrice<T>::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream file(nomFichier);
    std::string element;
    size_t posX = 0;
    size_t posY = 0;

    if (!file)
        return false;

    while (!file.eof())
    {
        std::getline(file, element);

        if (element == "L")
        {
            posY = height_;
            posX = 0;
            height_++;
        }
        else 
        {
            if (posX + 1 > width_)
                width_ = posX + 1;

            if (!lireElement(element, posY, posX))
                return false;
            
            posX++;
        }
    }

    return true;
}

template<typename T>
std::unique_ptr<Matrice<T>> Matrice<T>::clone() const
{
    std::unique_ptr<Matrice<T>> matrice = std::make_unique<Matrice<T>>();

    matrice->height_ = height_;
    matrice->width_ = width_;

    for (size_t h = 0; h < height_; h++)
        for (size_t w = 0; w < width_; w++)
            matrice->ajouterElement(elements_[w][h], h, w);

    return std::move(matrice);
}

template<typename T>
void Matrice<T>::setHeight(size_t height)
{
    height > CAPACITE_MATRICE ? height_ = CAPACITE_MATRICE : height_ = height;
}

template<typename T>
void Matrice<T>::setWidth(size_t width)
{
    width > CAPACITE_MATRICE ? width_ = CAPACITE_MATRICE : width_ = width;
}
#endif
