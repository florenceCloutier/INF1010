////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe Utilisateur
///\file Utilisateur.cpp
///\authors Alexis Foulon et Florence Cloutier
///
///Ce programme contient les methodes qui ont pour but la construction de la 
///classe Utilisateur et l'implementation des methodes de cette derniere.
///
///Celles-ci peuvent notamment:
///-Construire par parametre un objet de type Utilisateur
///-Verifier si un film est disponible pour un utilisateur
///-Verifier si le nombre limite d'ecoute de film gratuit est atteint par un 
///utilisateur
///-Verifier si un utilisateur peut regarder un film
///-Retourner les attributs de l'objet de type Utilisateur
///
////////////////////////////////////////////////////////////////////////////////

#include "Utilisateur.h"
#include <iostream>

Utilisateur::Utilisateur(const std::string& nom, unsigned int age, bool estPremium, Pays pays) :
        nom_(nom), age_(age), nbFilmsVus_(0), estPremium_(estPremium), pays_(pays) {}

//! Méthode qui retourne si le film est disponible pour un utilisateur.
//! \param film Le film à évaluer.
//! \return Un bool représentant si un film est disponible à l'utilisateur.
bool Utilisateur::filmEstDisponible(const Film& film) const
{
    static constexpr unsigned int AGE_MINIMUM_POUR_FILMS_RESTREINTS = 16;

    if (film.estRestreintParAge() && age_ < AGE_MINIMUM_POUR_FILMS_RESTREINTS)
        return false;
    else
        return !film.estRestreintDansPays(pays_);
}

//! Retourner si l'utilisateur a atteint la limite de films qu'il peut regarder.
//! \return L'utilisateur à-t'il atteint sa limite de film.
bool Utilisateur::nbLimiteFilmsAtteint() const
{
    if (estPremium_)
        return false;
    else
    {
        return nbFilmsVus_ >= NB_FILMS_GRATUITS;
    }
    
}

//! Vérifier que l'utilisateur n'a pas atteint la limite de films qu'il peut
//! regarder Vérifier que le film est disponnible dans le pays de l'utilisateur.
//! \param film Le film que l'utilisateur veut regarder.
//! \return Le film peut-il être regarder.
bool Utilisateur::regarderFilm(const Film& film)
{   
    if (filmEstDisponible(film) && !nbLimiteFilmsAtteint())
    {
        nbFilmsVus_ ++;
        return true;
    }
    else
        return false;
}

//! Retourner le nombre de films vus.
//! \return Le nombre de films vus.
unsigned int Utilisateur::getNbFilmsVus() const
{
    return nbFilmsVus_;
}