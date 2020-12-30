/*
 * Titre : PivoterMatrice.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz, Alexis Foulon et Florence Cloutier
 */

#ifndef PIVOTER_MATRICE_H
#define PIVOTER_MATRICE_H

#include "def.h"

/**
 * @brief definition de la classe PivoterMatrice
 */
template<class M>
class PivoterMatrice
{
public:
    // Constructeurs
    PivoterMatrice();
    PivoterMatrice(M* matrice);
    // Destructeur
    ~PivoterMatrice() = default;
    void pivoterMatrice(Direction direction);

private:
    Coordonnees changerCoordonneesCentreMatrice(Coordonnees coords) const;
    Coordonnees recupererCoordonnees(Coordonnees coords) const;
    M* matrice_;
};

/**
 * @brief constructeur par défaut de la classe
 */
template<class M>
inline PivoterMatrice<M>::PivoterMatrice()
{
}

/**
 * @brief constructeur par paramètre de la classe
 */
template<class M>
inline PivoterMatrice<M>::PivoterMatrice(M* matrice)
    : matrice_(matrice)
{
}

/**
 * @brief trouver les coordonnées du point par rapport au centre de la matrice
 * @param coords les coordonnées du point originales
 * @return coordonnees changees du point par rapport au centre de la matrice
 */
template<class M>
inline Coordonnees PivoterMatrice<M>::changerCoordonneesCentreMatrice(Coordonnees coords) const
{
    return {(int)(coords.x - matrice_->getWidth() / 2),
            (int)(coords.y - matrice_->getHeight() / 2)};
}

/**
 * @brief revenir au système précédent, trouver les coordonnées du point par
 * rapport au premier élément de la matrice
 * @param coords les coordonnées du point originales
 */
template<class M>
inline Coordonnees PivoterMatrice<M>::recupererCoordonnees(Coordonnees coords) const
{
    return {(int)(coords.x + matrice_->getWidth() / 2),
            (int)(coords.y + matrice_->getHeight() / 2)};
}

/**
 * @brief pivote la matrice dans une certaine direction par rapport au centre de cette derniere
 * @param direction les coordonnées du point originales
 */
template<class M>
void PivoterMatrice<M>::pivoterMatrice(Direction direction)
{
    std::unique_ptr<M> matriceCopie = matrice_->clone();

    for (unsigned int y = 0; y < matrice_->getHeight(); ++y)
    {
        for (unsigned int x = 0; x < matrice_->getWidth(); ++x)
        {
            Coordonnees coord = changerCoordonneesCentreMatrice({(int)x, (int)y});
            int temp = coord.x;

            if (direction == Direction::Right)
            {
                coord.x = 0 - coord.y;
                coord.y = temp;
            }
            else
            {
                coord.x = coord.y;
                coord.y = 0 - temp;
            }
            coord = recupererCoordonnees(coord);
            matrice_->ajouterElement(matriceCopie->operator()(y, x), coord.y, coord.x);
        }
    }
}

#endif
