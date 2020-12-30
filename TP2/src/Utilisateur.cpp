////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe Utilisateur
///\file Utilisateur.cpp
///\authors Alexis Foulon et Florence Cloutier
///
/// Ce programme contient les methodes qui ont pour but la construction de la
/// classe Utilisateur et l'implementation des methodes de cette derniere.
///
/// Celles-ci peuvent notamment:
///-Construire par parametre un objet de type Utilisateur
///-Verifier si un film est disponible pour un utilisateur
///-Verifier si le nombre limite d'ecoute de film gratuit est atteint par un utilisateur
///-Verifier si un utilisateur peut regarder un film
///-Retourner les attributs de l'objet de type Utilisateur
///
////////////////////////////////////////////////////////////////////////////////

#include "Utilisateur.h"

//! Constructeur de la classe Utilisateur
//! \param nom          Le nom de l'utilisateur
//! \param age          L'âge de l'utilisateur
//! \param estPremium   Bool représentant si l'utilisateur est premium
//! \param pays         Pays de l'utilisateur
Utilisateur::Utilisateur(const std::string& nom, unsigned int age, bool estPremium, Pays pays)
    : nom_(nom)
    , age_(age)
    , nbFilmsVus_(0)
    , estPremium_(estPremium)
    , pays_(pays)
{
}

//! Méthode qui retourne si le film est disponible pour un utilisateur
//! \param film Le film à évaluer
//! \return Un bool représentant si un film est disponible à l'utilisateur
bool Utilisateur::filmEstDisponible(const Film& film) const
{
    static constexpr unsigned int AGE_MINIMUM_POUR_FILMS_RESTREINTS = 16;

    bool ageApproprie = true;
    if (age_ < AGE_MINIMUM_POUR_FILMS_RESTREINTS)
    {
        ageApproprie = film.estRestreintParAge() == false;
    }
    return (ageApproprie == true && film.estRestreintDansPays(pays_) == false);
}

//! Méthode qui retourne si un utilisateur a atteint le nombre limite de films qu'il peut regarder
//! \return Un bool représentant si un utilisateur a atteint le nombre limite de films qu'il peut
//! regarder
bool Utilisateur::nbLimiteFilmsAtteint() const
{
    return estPremium_ == false && nbFilmsVus_ >= NB_FILMS_GRATUITS;
}

//! Méthode qui incrémente le nombre de films vus par l'utilisateur
//! \return Un bool représentant si l'utilisateur a pu regarder le film
bool Utilisateur::regarderFilm(const Film& film)
{
    if (nbLimiteFilmsAtteint() == false && filmEstDisponible(film))
    {
        nbFilmsVus_++;
        return true;
    }
    return false;
}

//! Méthode qui retourne le nombre de films vus par l'utilisateur
//! \return Le nombre de films vus par l'utilisateur
unsigned int Utilisateur::getNbFilmsVus() const
{
    return nbFilmsVus_;
}