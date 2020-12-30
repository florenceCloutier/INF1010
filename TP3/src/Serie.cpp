#include "Serie.h"

//! Constructeur par défaut
//! \param auteur L'auteur associé au Média
Serie::Serie(Auteur* auteur)
    : Media(auteur, TypeMedia::Serie)
{
}

//! Constructeur par paramètre
//! \param nom Le nom du Média
//! \param anneDeSortie L'anné de sortie
//! \param genre Le genre du Média
//! \param pays Le pays d'origine du Média
//! \param estRestreintParAge Le Média est-il restreint par age
//! \param auteur L'auteur du Média
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur)
    : Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, TypeMedia::Serie)
{
}

//! Constructeur par copie
//! \param serie La serie à copier
Serie::Serie(const Serie& serie)
    : Media(serie)
{   
    for(const std::unique_ptr<Saison>& saison : serie.saisons_)
        saisons_.push_back(std::make_unique<Saison>(*saison));
}

//! Affiche une série
//! \param os Le stream dans lequel afficher
//! \return Le stream dans lequel on a afficher
std::ostream& Serie::afficher(std::ostream& os) const
{
    Media::afficher(os);

    for (const std::unique_ptr<Saison>& saison : saisons_)
        os << *saison;

    return os;
}

//! Copie la série et alloue dynamiquement une copie
//! \return Un pointeur sur la copie
std::unique_ptr<Media> Serie::clone() const
{
    return std::make_unique<Serie>(*this);
}