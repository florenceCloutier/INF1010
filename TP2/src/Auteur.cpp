////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe Auteur
///\file Auteur.cpp
///\authors Alexis Foulon et Florence Cloutier
///
/// Ce programme contient les methodes qui ont pour but la construction de la classe Auteur et
/// l'implementation des methodes de cette derniere.
///
/// Celles-ci peuvent notamment:
///-Construire par parametre un objet de type Auteur
///-Afficher un objet de type Auteur avec une surcharge de l'operateur <<
///-Comparer l'attribut "nom" d'un objet de type Auteur avec une surcharge de l'operateur ==
///-Retourner les attributs de l'objet de type Auteur
///
////////////////////////////////////////////////////////////////////////////////

#include "Auteur.h"
#include <iostream>

//! Constructeur de la classe Auteur
//! \param nom              Nom de l'auteur
//! \param anneeDeNaissance Année de naissance de l'auteur
Auteur::Auteur(const std::string& nom, unsigned int anneeDeNaissance)
    : nom_(nom)
    , anneeDeNaissance_(anneeDeNaissance)
    , nbFilms_(0)
{
}

//! Méthode qui retourne le nom de l'auteur
//! \return Le nom de l'auteur
const std::string& Auteur::getNom() const
{
    return nom_;
}

//! Méthode qui retourne l'année de naissance de l'auteur
//! \return L'année de naissance de l'auteur
unsigned int Auteur::getAnneeDeNaissance() const
{
    return anneeDeNaissance_;
}

//! Méthode qui retourne le nombre de films de l'auteur
//! \return Le nombre de films de l'auteur
unsigned int Auteur::getNbFilms() const
{
    return nbFilms_;
}

//! Méthode qui set le nombre de films de l'auteur
//! \param nbFilms  Le nombre de films de l'auteur
void Auteur::setNbFilms(unsigned int nbFilms)
{
    nbFilms_ = nbFilms;
}

//! Surcharge de l'operateur << pour afficher un auteur
//! \param stream Le stream dans lequel afficher
//! \param auteur L'auter à afficher
//! \return       Le stream dans lequel l'auteur est affiche
std::ostream& operator<<(std::ostream& stream, const Auteur& auteur)
{
    return stream << "Nom: " << auteur.nom_ << " | Date de naissance: " << auteur.anneeDeNaissance_
                  << " | Nombre de films: " << auteur.nbFilms_;
}

//! Surcharge de l'operateur == pour tester le nom de l'auteur
//! \param nom  Le nom à comparer avec celui de l'auteur
//! \return     Un bool qui confirme si les noms des auteurs sont les meme
bool Auteur::operator==(const std::string& nom) const
{
    return nom_ == nom;
}

//! Surcharge de l'operateur == pour tester le nom de l'auteur
//! \param nom    Le nom à comparer avec celui de l'auteur
//! \param auteur L'auteur duquel il faut comparer le nom
//! \return       Un bool qui confirme si les noms des auteurs sont les meme
bool operator==(const std::string& nom, const Auteur& auteur)
{
    return auteur.getNom() == nom;
}