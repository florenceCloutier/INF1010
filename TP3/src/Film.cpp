////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe Film
///\file Film.cpp
///\authors Alexis Foulon et Florence Cloutier
///
/// Ce programme contient les methodes qui ont pour but la construction de la classe Film et
/// l'implementation des methodes de cette derniere.
///
/// Celles-ci peuvent notamment:
///-Construire par parametre un objet de type Film
///-Afficher les attributs de l'objet de type Film
///-Lire les attributs de l'objet de type Film
///-Copier dynamiquement un Film 
///
////////////////////////////////////////////////////////////////////////////////

#include "Film.h"
#include <memory>

//! Constructeur avec parametres de la classe Film 
Film::Film(Auteur* auteur)
    : Media(auteur, TypeMedia::Film)
    , duree_("")
{
}

//! Constructeur avec parametres de la classe Film
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
           bool estRestreintParAge, Auteur* auteur, const std::string& duree)
    : Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, TypeMedia::Film)
    , duree_(duree)
{
}

//! Methode qui affiche les attributs d'un film
//! \param os Le stream dans lequel affiché
//! \return Le stream dans lequel on à affiché
std::ostream& Film::afficher(std::ostream& os) const
{
    Media::afficher(os);
    os << std::string(8, ' ') << "Durée: " << duree_ << std::endl;

    return os;
}

//! Methode qui lit les attributs d'un film
//! \param is Le stream dans lequel il faut lire
//! \return Le stream dans lut
std::istream& Film::lire(std::istream& is)
{
    Media::lire(is);
    is >> std::quoted(duree_);

    return is;
}

//! Methode qui retourne une copie allouee dynamiquement de Film
//! \return un pointeur sur un Film
std::unique_ptr<Media> Film::clone() const
{
    return std::make_unique<Film>(*this);
}
