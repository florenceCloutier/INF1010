////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe GestionnaireAuteurs
///\file GestionnaireAuteurs.cpp
///\authors Alexis Foulon et Florence Cloutier
///
/// Ce programme contient les methodes qui ont pour but la construction de la
/// classe GestionnaireAuteurs et l'implementation des methodes de cette derniere.
///
/// Celles-ci peuvent notamment:
///-Construire par defaut un objet de type GestionnaireAuteurs
///-Ajouter un auteur dans la liste d'auteurs en utilisant la surcharge de l'operateur +=
///-Chercher un auteur en particulier
///-Charger les auteurs d'un fichier
///-Afficher la liste d'auteurs en utilisant la surcharge de l'operateur <<
///-Ajouter un auteur a partir d'un string
///-Retourner les attributs de l'objet de type GestionnaireAuteurs
///
////////////////////////////////////////////////////////////////////////////////

#include "GestionnaireAuteurs.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

//! Constructeur de la classe GestionnaireAuteurs
GestionnaireAuteurs::GestionnaireAuteurs()
    : auteurs_(std::vector<Auteur>(
          NB_AUTEURS_MAX)) // ne pas changer. le vecteur doit etre initialiser a 16 ici
{
}

//! Méthode qui ajoute un auteur à la liste des auteurs
//! \param auteur L'auteur à ajouter
//! \return       Un bool représentant si l'opération a ete reussi ou non
bool GestionnaireAuteurs::operator+=(const Auteur& auteur)
{
    if (auteurs_.size() >= NB_AUTEURS_MAX)
        return false;

    auteurs_.push_back(auteur);
    return true;
}

//! Méhode qui cherche un auteur par son nom complet
//! \param nomAuteur Le nom de l'auteur à trouver
//! \return          Un pointeur vers l'auteur. Le pointeur est nullptr si l'auteur n'existe pas.
Auteur* GestionnaireAuteurs::chercherAuteur(const std::string& nomAuteur)
{
    for (auto& auteur : auteurs_)
    {
        if (auteur == nomAuteur)
            return &auteur;
    }
    return nullptr;
}

//! Méthode qui prend un nom de fichier en paramètre et qui charge les auteurs
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool représentant si le chargement a été un succès
bool GestionnaireAuteurs::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        auteurs_.clear();
        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneAuteur(ligne) == false)
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

//! Méthode qui affiche la liste des auteurs
//! \param o            Le stream dans lequel afficher
//! \param gestionnaire Le gestionnaire d'auteurs que l'on veut afficher
//! \return             Le stream dans lequel le gestionnaire d'auteurs est affiché
std::ostream& operator<<(std::ostream& o, GestionnaireAuteurs& gestionnaire)
{
    for (auto const& auteur : gestionnaire.auteurs_)
    {
        o << auteur;
        o << '\n';
    }
    return o;
}

//! Méthode qui retourne le nombre d'auteurs
//! \return Le nombre d'auteurs
std::size_t GestionnaireAuteurs::getNbAuteurs() const
{
    return auteurs_.size();
}

//! Méthode qui ajoute un auteur avec un string
//! \param ligne Le string qui comporte tous les attributs de l'auteur
//! \return      Un bool représentant si la ligne a ete lue avec succes ou non
bool GestionnaireAuteurs::lireLigneAuteur(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomAuteur;
    unsigned int age;

    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)

    if (stream >> std::quoted(nomAuteur) >> age)
    {
        bool succes = (*this += Auteur(nomAuteur, age));
        return succes;
    }
    return false;
}