////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe GestionnaireAuteurs
///\file GestionnaireAuteurs.cpp
///\authors Alexis Foulon et Florence Cloutier
///
///Ce programme contient les methodes qui ont pour but la construction de la 
///classe GestionnaireAuteurs et l'implementation des methodes de cette derniere.
///
///Celles-ci peuvent notamment:
///-Construire par defaut un objet de type GestionnaireAuteurs
///-Ajouter un auteur dans la liste d'auteurs
///-Chercher un auteur en particulier
///-Charger les auteurs d'un fichier
///-Afficher la liste d'auteurs
///-Ajouter un auteur a partir d'un string
///-Retourner les attributs de l'objet de type GestionnaireAuteurs
///
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "GestionnaireAuteurs.h"

//! Constructeur par défault
GestionnaireAuteurs::GestionnaireAuteurs() : nbAuteurs_(0) {}

//! Ajouter un auteur au tableau des auteurs.
//! \param auteur L'auteur à ajouter au gestionnaire.
//! \return Si l'auteur à été ajouter.
bool GestionnaireAuteurs::ajouterAuteur(const Auteur& auteur)
{
    if (nbAuteurs_ < NB_AUTEURS_MAX)
    {
        auteurs_[nbAuteurs_] = auteur;
        nbAuteurs_ ++;
        return true;
    }
    else
        return false;
}

//! Chercher dans la liste des auteurs si un auteur comporte le nom passé en paramètre.
//! \param nomAuteur Le nom de l'auteur recherché.
//! \return Un pointeur sur l'auteur ayant le nom recherché.
Auteur* GestionnaireAuteurs::chercherAuteur(const std::string& nomAuteur)
{
    for (unsigned int i = 0; i < nbAuteurs_; i++)
        if (auteurs_[i].getNom() == nomAuteur)
            return &auteurs_[i];
    
    return nullptr;
}

//! Méthode qui prend un nom de fichier en paramètre et qui charge les auteurs.
//! \param nomFichier   Le nom du fichier à charger.
//! \return             Un bool représentant si le chargement a été un succès.
bool GestionnaireAuteurs::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        std::string ligne;

        while (std::getline(fichier, ligne))
            if (!lireLigneAuteur(ligne))
                return false;
        
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
            << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui affiche la liste des auteurs.
//! \param stream Le stream dans lequel afficher.
void GestionnaireAuteurs::afficher(std::ostream& stream) const
{
    // Ne pas modifier cette méthode
    for (std::size_t i = 0; i < nbAuteurs_; i++)
    {
        auteurs_[i].afficher(stream);
        stream << '\n';
    }
}

//! Retourne le nombre d'auteurs dans la liste.
//! \return Le nombre d'auteurs dans la liste.
std::size_t GestionnaireAuteurs::getNbAuteurs() const
{
    return nbAuteurs_;
}

//! Méthode qui ajoute un auteur avec un string.
//! \param ligne Le string qui comporte tous les attributs de l'auteur.
bool GestionnaireAuteurs::lireLigneAuteur(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nom;
    unsigned int age;

    //Extrait le nom
    stream >> std::quoted(nom);
    //Extrait l'age
    stream >> age;

    if (nom != "" && age > 0)
    {
        ajouterAuteur(Auteur(nom, age));
        return true;
    }
    else
        return false;
}