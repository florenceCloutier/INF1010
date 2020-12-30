////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe Film
///\file Film.cpp
///\authors Alexis Foulon et Florence Cloutier
///
///Ce programme contient les methodes qui ont pour but la construction de la 
///classe Film et l'implementation des methodes de cette derniere.
///
///Celles-ci peuvent notamment:
///-Construire par parametres un objet de type Film
///-Ajouter un pays a la liste de pays restreints d'un film 
///-Verifier si un film est restreint dans un certain pays
///-Afficher un film
///-Verifier si un film est restreint par age
///-Retourner les attributs de l'objet de type Film
///
////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include "Pays.h"
#include "Film.h"
#include "typesafe_enum.h"

namespace
{
    constexpr std::size_t CAPACITE_PAYS_INITIALE = 2;

    //! Fonction qui convertit le enum Film::Genre en string.
    //! \param genre    Le genre à convertir.
    //! \return         Le string qui représente le enum.
    const std::string& getGenreString(Film::Genre genre)
    {
        static const std::string NOMS_GENRES[] = {"Action",
                                                  "Aventure",
                                                  "Comedie",
                                                  "Horreur",
                                                  "Romance"};

        auto index = enum_value(genre);
        assert(valid_as_enum<Pays>(index));
        return NOMS_GENRES[index];
    }

    //! Fonction qui convertit le enum Pays en string.
    //! \param pays     Le pays à convertir.
    //! \return         Le string qui représente le enum.
    const std::string& getPaysString(Pays pays)
    {
        static const std::string NOMS_PAYS[] = {"Bresil",
                                                "Canada",
                                                "Chine",
                                                "EtatsUnis",
                                                "France",
                                                "Japon",
                                                "RoyaumeUni",
                                                "Russie",
                                                "Mexique"};
        auto index = enum_value(pays);
        assert(valid_as_enum<Pays>(index));
        return NOMS_PAYS[index];
    }
} // namespace

//! Constructeur par paramètre.
//! \param nom Nom du film.
//! \param anneeDeSortie Année de sortie du film.
//! \param genre Genre du film.
//! \param pays Pays du film.
//! \param estRestreintParAge Le film est-il restreint par age.
//! \param auteur L'auteur du film.
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
        bool estRestreintParAge, Auteur* auteur) : nom_(nom), anneeDeSortie_(anneeDeSortie),
        genre_(genre), pays_(pays), estRestreintParAge_(estRestreintParAge), auteur_(auteur),
        paysRestreints_(std::make_unique<Pays[]>(CAPACITE_PAYS_INITIALE)), nbPaysRestreints_(0), capacitePaysRestreints_(CAPACITE_PAYS_INITIALE) 
{
    auteur->setNbFilms(auteur->getNbFilms() + 1);
}

//! Méthode qui ajoute un pays à liste des pays restreints du film.
//! \param pays Pays à ajouter à la liste.
void Film::ajouterPaysRestreint(Pays pays)
{
    static constexpr unsigned int AUGMENTATION_CAPACITE_PAYS = 2;

    if (nbPaysRestreints_ < capacitePaysRestreints_)
    {
        paysRestreints_[nbPaysRestreints_] = pays;
        nbPaysRestreints_ ++;
    }
    else 
    {
        capacitePaysRestreints_ *= AUGMENTATION_CAPACITE_PAYS;
        std::unique_ptr<Pays[]> temp = std::make_unique<Pays[]>(capacitePaysRestreints_);
        
        for (unsigned int i = 0; i < nbPaysRestreints_; i++)
            temp[i] = paysRestreints_[i];

        temp[nbPaysRestreints_] = pays;
        nbPaysRestreints_ ++;

        paysRestreints_ = std::move(temp);
    }
}

//! Supprime les pays Restreints en mettant le nombre de pays restreints à 0.
void Film::supprimerPaysRestreints()
{
    nbPaysRestreints_ = 0;
}

//! Chercher si le pays en paramètre se retrouve dans la liste des pays restreints.
//! \param pays Le pays à vérifier.
//! \return Le film est-il restreint dans le pays.
bool Film::estRestreintDansPays(Pays pays) const
{
    for (unsigned int i = 0; i < nbPaysRestreints_; i++)
    {
        if (paysRestreints_[i] == pays)
            return true;
    }
    return false;
}

//! Méthode qui affiche le film.
//! \param stream Le stream dans lequel afficher.
void Film::afficher(std::ostream& stream) const
{
    // Ne modifiez pas cette fonction
    stream << nom_ << "\n\tDate de sortie: " << anneeDeSortie_
           << "\n\tGenre: " << getGenreString(genre_) << "\n\tAuteur: " << auteur_->getNom()
           << "\n\tPays: " << getPaysString(pays_)
           << (nbPaysRestreints_ == 0 ? "\n\tAucun pays restreint." : "\n\tPays restreints:");

    for (std::size_t i = 0; i < nbPaysRestreints_; i++)
    {
        stream << "\n\t\t" << getPaysString(paysRestreints_[i]);
    }
    stream << '\n';
}

//! Retourner le genre.
//! \return Le genre du film.
Film::Genre Film::getGenre() const
{
    return genre_;
}

//! Retourner si le film est restreint par l'âge.
//! \return Le film est-il restreint par l'âge.
bool Film::estRestreintParAge() const
{
    return estRestreintParAge_;
}

//! Retourner le nom du film.
//! \return Le nom du film.
const std::string& Film::getNom() const
{
    return nom_;
}

//! Retourner l'auteur du film.
//! \return L'auteur du film.
Auteur* Film::getAuteur()
{
    return auteur_;
}