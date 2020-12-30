////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe Episode
///\file Episode.cpp
///\authors Alexis Foulon et Florence Cloutier
///
/// Ce programme contient les methodes qui ont pour but la construction de la classe Episode et
/// l'implementation des methodes de cette derniere.
///
/// Celles-ci peuvent notamment:
///-Construire par defaut un objet de type Episode
///-Construire par parametre un objet de type Auteur
///-Comparer l'attribut "numEpisode" d'un objet de type Episode avec une surcharge de l'operateur ==
///-Afficher un objet de type Episode avec une surcharge de l'operateur <<
///-Lire un objet de type Episode avec une surcharge de l'operateur >>
///-Retourner les attributs de l'objet de type Auteur
///
////////////////////////////////////////////////////////////////////////////////

#include "Episode.h"

//! Constructeur par défaut
Episode::Episode()
    : nom_("")
    , duree_("")
    , numEpisode_(0)
{
}

//! Constructeur par paramètre
//! \param numEpisode Le numero de l'épisode
//! \param nom Le nom de l'épisode
//! \param duree La duree de l'épisode
Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree)
    : nom_(nom)
    , duree_(duree)
    , numEpisode_(numEpisode)
{
}

//! Surcharge de l'operateur ==
//! \param numEpisode Le numero de l'episode à comparer
//! \return Le résultat de la comparaison
bool Episode::operator==(unsigned int numEpisode)
{
    return numEpisode_ == numEpisode;
}

//! Surchage de l'operateur << pour l'affichage
//! \param os Le stream de sortie
//! \param episode L'objet à afficher
//! \return Le stream dans lequel afficher
std::ostream& operator<<(std::ostream& os, const Episode& episode)
{
    os << std::string(16, ' ') << "Episode " << std::setfill('0') << std::setw(2)
       << episode.numEpisode_ << ": " << episode.nom_ << " | Durée: " << episode.duree_
       << std::endl;
    return os;
}

//! Surcharge de l'operateur >> pour la lecture
//! \param is Le stream d'entrée
//! \param episode L'objet à modifier
//! \return Le stream d'entrée
std::istream& operator>>(std::istream& is, Episode& episode)
{
    is >> episode.numEpisode_ >> std::quoted(episode.nom_) >> std::quoted(episode.duree_);
    return is;
}

//! Getter pour le nombre numero de l'épisode
//! \return numero de l'épisode
unsigned int Episode::getNumEpisode() const
{
    return numEpisode_;
}