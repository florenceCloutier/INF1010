////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe Librairie
///\file Librairie.cpp
///\authors Alexis Foulon et Florence Cloutier
///
///Ce programme contient les methodes qui ont pour but la construction de la 
///classe Librairie et l'implementation des methodes de cette derniere.
///
///Celles-ci peuvent notamment:
///-Construire par defaut un objet de type Librairie
///-Detruire un objet de type Librairie
///-Ajouter un film a la liste de films
///-Retirer un film de la liste de films
///-Chercher un film en particulier dans la liste
///-Charger les films a partir d'un fichier
///-Charger les restrictions des films a partir d'un fichier
///-Afficher la liste des films 
///-Retourner les attributs de l'objet de type Librairie
///-Supprimer les films d'un tableau de films
///-Ajouter des restrictions de films a partir d'un string
///-Ajouter un film a partir d'un string
///-Trouver l'index d'un film dans un tableau de films
///
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "debogageMemoire.h"
#include "typesafe_enum.h"
#include "Librairie.h"

namespace
{
    constexpr std::size_t CAPACITE_FILMS_INITIALE = 2;
    constexpr int FILM_INEXSISTANT = -1;
} // namespace

//! Constructeur par défault
Librairie::Librairie() : films_(new Film* [CAPACITE_FILMS_INITIALE]), nbFilms_(0), capaciteFilms_(CAPACITE_FILMS_INITIALE) {}

//! Destructeur
Librairie::~Librairie()
{
    supprimerFilms();
    delete[] films_;
    films_ = nullptr;
}

//! Méthode qui ajoute un film à la liste des films.
//! \param film Le film alloué dynamiquement à ajouter à la liste. La classe
//! devient propriétaire du film.
void Librairie::ajouterFilm(Film* film)
{
    static constexpr unsigned int AUGMENTATION_CAPACITE_FILMS = 2;

    if (film != nullptr)
    {
        if (nbFilms_ == capaciteFilms_)
        {
            capaciteFilms_ *= AUGMENTATION_CAPACITE_FILMS;
            Film** tempFilms = new Film*[capaciteFilms_];

            for (unsigned int i = 0 ; i < nbFilms_ ; i++)
                tempFilms[i] = films_[i]; 

            delete[] films_;
            films_ = tempFilms;
            tempFilms = nullptr;
        }
    
        films_[nbFilms_] = film;
        nbFilms_++;
    }
}

//! Retirer un film ayant le même nom que celui envoyé en paramètre.
//! \param nomFilm Le nom du film à retirer.
void Librairie::retirerFilm(const std::string& nomFilm)
{
    int index = trouverIndexFilm(nomFilm);

    if (index != FILM_INEXSISTANT)
    {
        delete films_[index];

        nbFilms_ --;

        films_[index] = films_[nbFilms_];
        films_[nbFilms_] = nullptr;
    }
}

//! Retourner un pointeur vers le film recherché
//! \param nomFilm  Le nom du film à rechercher.
//! \return         Un pointeur sur le film rechercher.
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
    int index = trouverIndexFilm(nomFilm);

    if (index != FILM_INEXSISTANT)
        return films_[index];
    
    return nullptr;
}

//! Méthode qui charge les films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerFilmsDepuisFichier(const std::string& nomFichier,
                                          GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        supprimerFilms();
        std::string ligne;
        
        while (std::getline(fichier, ligne))
            if (!lireLigneFilm(ligne, gestionnaireAuteurs))
                return false;
        return true;
    }   
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui charge les restrictions des films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un
//! succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (unsigned int i = 0; i < nbFilms_; i++)
            films_[i]->supprimerPaysRestreints();
        
        std::string ligne;
        
        while (std::getline(fichier, ligne))
            if (!lireLigneRestrictions(ligne))
                return false;
        
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui affiche la liste des films.
//! \param stream Le stream dans lequel afficher.
void Librairie::afficher(std::ostream& stream) const
{
    // Ne pas modifier cette méthode
    for (std::size_t i = 0; i < nbFilms_; i++)
    {
        films_[i]->afficher(stream);
        stream << '\n';
    }
}

//! Retourner le nombre de films.
//! \return Le nombre de films.
std::size_t Librairie::getNbFilms() const
{
    return nbFilms_;
}

//! Supprimer les films du tableau
void Librairie::supprimerFilms() 
{
    for (unsigned int i = 0; i < nbFilms_; i++)
    {
        delete films_[i];
        films_[i] = nullptr;
    }
    nbFilms_ = 0;
}

//! Méthode qui ajoute les restrictions d'un film avec un string.
//! \param ligne Le string comportant les restrictions du film.
//! \return      Un bool représentant si l'opération est un succès.
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    int paysValeurEnum;

    stream >> std::quoted(nomFilm);

    Film* film = chercherFilm(nomFilm);
    if (film == nullptr)
        return false;

    while (stream >> paysValeurEnum)
        film->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));

    return true;
}

//! Méthode qui ajoute un film avec un string comportant les attributs du film.
//! \param ligne                Le string comportant les attributs du film.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un auteur.
//! \return                     Un bool représentant si l'opération est un succès.
bool Librairie::lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    unsigned int anneeSortie;
    int genreValeurEnum;
    int paysValeurEnum;
    bool estRestreintParAge;
    std::string nomAuteur;

    stream  >> std::quoted(nomFilm) >> anneeSortie >> genreValeurEnum
            >> paysValeurEnum >> estRestreintParAge >> std::quoted(nomAuteur);

    Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
    if (auteur == nullptr)
        return false;
    
    Film* film = new Film(nomFilm, anneeSortie, to_enum<Film::Genre>(genreValeurEnum), to_enum<Pays>(paysValeurEnum), estRestreintParAge, auteur);

    ajouterFilm(film);

    return true;
}

//! Retourner l'indexe du film comportant le nom envoyé en paramètre.
//! \param nomFilm Nom du film dont on cherche l'index.
//! \return Index du film recherché.
int Librairie::trouverIndexFilm(const std::string& nomFilm) const
{
    for (unsigned int i = 0; i < nbFilms_; i++)
        if (films_[i]->getNom() == nomFilm)
            return i;
    
    return FILM_INEXSISTANT;
}