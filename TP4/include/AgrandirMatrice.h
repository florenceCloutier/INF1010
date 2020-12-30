/*
 * Titre : AgrandirMatrice.h - Travail Pratique #4 - Programmation Orient�e
 * Objet Date : 27 F�vrier 2020 
 * Auteur : Nabil Dabouz, Alexis Foulon, Florence Cloutier
 */

#ifndef AGRANDIR_MATRICE_H
#define AGRANDIR_MATRICE_H

#include "def.h"

/**
 * @brief definition de la classe AgrandirMatrice
 */
template<class M>
class AgrandirMatrice
{
public:
    AgrandirMatrice();
    AgrandirMatrice(M* matrice);
    ~AgrandirMatrice() = default;
    Coordonnees trouverLePlusProcheVoisin(const unsigned int& rapport, size_t posY,
                                          size_t posX) const;
    void redimensionnerImage(const unsigned int& rapport);

private:
    M* matrice_;
};

/**
 * @brief constructeur par défaut de la classe
 */
template<class M>
AgrandirMatrice<M>::AgrandirMatrice()
{
}

/**
 * @brief constructeur par paramètre de la classe
 */
template<class M>
AgrandirMatrice<M>::AgrandirMatrice(M* matrice)
    : matrice_(matrice)
{
}

/**
 * @brief trouver le point le plus proche du point (posX, posY) dans la matrice
 * originale
 * @param rapport, le rapport du redimensionnement de l'image
 * @param posX, la colonne du point dans la nouvelle image
 * @param posY, la ligne du point dans la nouvelle image
 * @return coordonnées du point le plus proche
 */
template<class M>
Coordonnees AgrandirMatrice<M>::trouverLePlusProcheVoisin(const unsigned int& rapport, size_t posY,
                                                          size_t posX) const
{
    return {int(posX / rapport), int(posY / rapport)};
}

/**
 * @brief Redimensionner l'image selon un rapport passe en parametre
 * @param rapport, le rapport du redimensionnement de l'image
 */
template<class M>
void AgrandirMatrice<M>::redimensionnerImage(const unsigned int& rapport)
{
    std::unique_ptr<M> matriceCopie = matrice_->clone();

    matrice_->setHeight(matrice_->getHeight() * rapport);
    matrice_->setWidth(matrice_->getWidth() * rapport);

    for (size_t y = 0; y < matrice_->getHeight(); ++y)
    {
        for (size_t x = 0; x < matrice_->getWidth(); ++x)
        {
            Coordonnees coord = trouverLePlusProcheVoisin(rapport, y, x);
            matrice_->ajouterElement(matriceCopie->operator()(coord.x, coord.y), y, x);
        }
    }
}

#endif
