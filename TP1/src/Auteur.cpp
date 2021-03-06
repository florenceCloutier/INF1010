////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe Auteur
///\file Auteur.cpp
///\authors Alexis Foulon et Florence Cloutier
///
///Ce programme contient les methodes qui ont pour but la construction de la classe Auteur et l'implementation des methodes de cette derniere.
///
///Celles-ci peuvent notamment:
///-Construire par parametre un objet de type Auteur
///-Afficher un objet de type Auteur
///-Retourner les attributs de l'objet de type Auteur
///
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Auteur.h"

Auteur::Auteur(const std::string& nom, unsigned int anneeDeNaissance) : nom_(nom), anneeDeNaissance_(anneeDeNaissance), nbFilms_(0) {}

//! Méthode qui affiche un auteur.
//! \param stream Le stream dans lequel afficher.
void Auteur::afficher(std::ostream& stream) const
{
    // Ne modifiez pas cette fonction
    stream << "Nom: " << nom_ << " | Date de naissance: " << anneeDeNaissance_
           << " | Nombre de films: " << nbFilms_;
}

//! Méthode qui retourne le nom de l'auteur.
//! \return Le nom de l'auteur.
const std::string& Auteur::getNom() const
{
    return nom_;
}

//! Méthode qui retourne l'année de naissance de l'auteur.
//! \return L'année de naissance de l'auteur.
unsigned int Auteur::getAnneeDeNaissance() const
{
    return anneeDeNaissance_;
}

//! Méthode qui retourne le nombre de film de l'auteur.
//! \return Le nombre de films de l'auteur.
unsigned int Auteur::getNbFilms() const
{
    return nbFilms_;
}

//! Méthode qui modifie le nombre de film d'un auteur.
//! \param nbFilms Le nombre de film.
void Auteur::setNbFilms(unsigned int nbFilms)
{
    nbFilms_ = nbFilms;
}
