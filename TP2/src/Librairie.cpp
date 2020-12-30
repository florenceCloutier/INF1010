////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe Librairie
///\file Librairie.cpp
///\authors Alexis Foulon et Florence Cloutier
///
/// Ce programme contient les methodes qui ont pour but la construction de la
/// classe Librairie et l'implementation des methodes de cette derniere.
///
/// Celles-ci peuvent notamment:
///-Construire par defaut un objet de type Librairie
///-Implementation d'un constructeur de copie
///-Detruire un objet de type Librairie
///-Copier une librairie dans une autre en utilisant la surcharge de l'operateur =
///-Ajouter un film a la liste de films en utilisant la surcharge de l'operateur +=
///-Retirer un film de la liste de films en utilisant la surcharge de l'operateur -=
///-Chercher un film en particulier dans la liste
///-Charger les films a partir d'un fichier
///-Charger les restrictions des films a partir d'un fichier
///-Afficher la liste des films  en utilisant la surcharge de l'operateur <<
///-Retourner les attributs de l'objet de type Librairie
///-Supprimer les films d'un vecteur de films
///-Ajouter des restrictions de films a partir d'un string
///-Ajouter un film a partir d'un string
///-Trouver l'index d'un film dans un tableau de films
///
////////////////////////////////////////////////////////////////////////////////

#include "Librairie.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "debogageMemoire.h"
#include "typesafe_enum.h"

namespace
{
    constexpr std::size_t CAPACITE_FILMS_INITIALE = 2;
    constexpr int FILM_INEXSISTANT = -1;
} // namespace

//! Constructeur de la classe Librairie
Librairie::Librairie()
{
}

//! Constructeur par copie
//! \param La librairie copiee
Librairie::Librairie(const Librairie& librairie)
{
    for (const std::unique_ptr<Film>& film : librairie.films_)
        films_.push_back(std::make_unique<Film>(*film));
}

//! Surcharge de l'operateur = pour faire une copie d'une librairie dans une autre
//! \param librairie La librairie que l'on souhaite copier dans l'autre
//! \return          Une librairie pareille a celle copiee
Librairie& Librairie::operator=(const Librairie& librairie)
{
    if (this != &librairie)
    {
        films_.clear();
        for (const std::unique_ptr<Film>& film : librairie.films_)
            films_.push_back(std::make_unique<Film>(*film));
    }
    return *this;
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
}

//! Methode qui retourne le vecteur comportant la liste de tous les films dans la librairie
//! \return Le film
const std::vector<std::unique_ptr<Film>>& Librairie::getFilms() const
{
    return films_;
}

//! Méthode qui retourne un film comportant le même nom que celui envoyé en paramètre
//! \param nomFilm Le nom du film à chercher
//! \return        Un pointeur vers le film. Nullptr si le film n'existe pas
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
    int indexFilm = trouverIndexFilm(nomFilm);
    if (indexFilm == FILM_INEXSISTANT)
    {
        return nullptr;
    }
    return films_[indexFilm].get();
}

//! Méthode qui charge les films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//! auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerFilmsDepuisFichier(const std::string& nomFichier,
                                          GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        // Supprimers les vieux films avant de lire les nouveaux
        supprimerFilms();

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneFilm(ligne, gestionnaireAuteurs) == false)
            {
                return false;
            }
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui charge les restrictions des films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (const auto& film : films_)
            film->supprimerPaysRestreints();

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneRestrictions(ligne) == false)
            {
                return false;
            }
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui retourne le nombre de films
//! \return Le nombre de films
std::size_t Librairie::getNbFilms() const
{
    return films_.size();
}

//! Surcharge de l'operateur += pour ajouter un film
//! \param film Le film à ajouter à la liste. La classe devient propriétaire du
//!             film.
//! \return La librairie contenant maintenant le film
Librairie& Librairie::operator+=(Film* film)
{
    if (film != nullptr)
    {
        films_.push_back(std::unique_ptr<Film>(film));
    }
    return *this;
}

//! Méthode qui retire un film de la liste
//! \param film Le nom du film à retirer
//! \return La librairie avec le film enlevé
Librairie& Librairie::operator-=(const std::string& film)
{
    int i = trouverIndexFilm(film);
    if (i != FILM_INEXSISTANT)
    {
        films_[i] = std::move(films_.back());
        films_.pop_back();
    }
    return *this;
}

//! Méthode qui affiche la liste des films.
//! \param stream Le stream dans lequel afficher
//! \param librairie La librairie à ajouter
//! \return Le stream dans lequel on à afficher
std::ostream& operator<<(std::ostream& stream, const Librairie& librairie)
{
    for (const std::unique_ptr<Film>& film : librairie.films_)
        stream << *film << std::endl;

    return stream;
}

//! Méthode qui supprime tous les films
void Librairie::supprimerFilms()
{
    films_.clear();
}

//! Méthode qui ajoute les restrictions d'un film avec un string
//! \param ligne Le string comportant les restrictions du film
//! \return      Un bool représentant si l'opération est un succès
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
    if (stream >> std::quoted(nomFilm))
    {
        Film* film = chercherFilm(nomFilm);
        if (film == nullptr)
        {
            // Film n'existe pas
            return false;
        }

        int paysValeurEnum;
        while (stream >> paysValeurEnum)
        {
            film->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
        }
        return true;
    }
    return false;
}

//! Méthode qui ajoute un film avec un string comportant les attributs du film
//! \param ligne                Le string comportant les attributs du film
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//!                             auteur.
//! \return                     Un bool représentant si l'opération est un succès
bool Librairie::lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    unsigned int anneeSortie;
    int genreValeurEnum;
    int paysValeurEnum;
    bool estRestreintParAge;
    std::string nomAuteur;

    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)

    if (stream >> std::quoted(nomFilm) >> anneeSortie >> genreValeurEnum >> paysValeurEnum >>
        estRestreintParAge >> std::quoted(nomAuteur))
    {
        Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
        if (auteur == nullptr)
        {
            // Auteur non existant
            return false;
        }
        auteur->setNbFilms(auteur->getNbFilms() + 1);
        Film* film = new Film(nomFilm,
                              anneeSortie,
                              to_enum<Film::Genre>(genreValeurEnum),
                              to_enum<Pays>(paysValeurEnum),
                              estRestreintParAge,
                              auteur);
        *this += film; // TODO Facon sans this?
        return true;
    }
    return false;
}

//! Méthode qui retourne l'index d'un film en cherchant son nom
//! \param nomFilm Le nom du film à trouver
//! \return        L'index du film. Retourne -1 si le film n'existe pas
int Librairie::trouverIndexFilm(const std::string& nomFilm) const
{
    for (std::size_t i = 0; i < films_.size(); i++)
        if (films_[i]->getNom() == nomFilm)
            return (int)i;

    return FILM_INEXSISTANT;
}