////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe Saison
///\file Saison.cpp
///\authors Alexis Foulon et Florence Cloutier
///
/// Ce programme contient les methodes qui ont pour but la construction de la classe 
/// Saison et l'implementation des methodes de cette derniere.
///
/// Celles-ci peuvent notamment:
///-Construire par defaut l'objet de type Saison
///-Construire avec parametre l'objet de type Saison
///-Construire par copie un objet de type Saison
///-Detruire une objet de type Saison
///-Ajouter/retirer un episode de la Saison avec l'operateur += et -=
///-Verifier si deux Saisons sont la meme selon le numSaison avec la surcharge de l'operateur ==
///-Afficher la Saison avec la surcharge de l'operateur <<
///-Lire la Saison avec la surcharge de l'operateur >>
///
////////////////////////////////////////////////////////////////////////////////

#include "Saison.h"
#include <iostream>
#include <memory>
#include <string>

//! Constructeur sans parametre de la classe Saison
Saison::Saison()
    : numSaison_(0)
    , nbEpisodesmax_(0)
{
}

//! Constructeur avec parametres de la classe Saison
Saison::Saison(unsigned int numSaison, unsigned int nbEpisodemax)
    : numSaison_(numSaison)
    , nbEpisodesmax_(nbEpisodemax)
{
}

//! Constructeur par copie
Saison::Saison(const Saison& saison)
{
    if (this != &saison)
    {
        numSaison_ = saison.numSaison_;
        nbEpisodesmax_ = saison.nbEpisodesmax_;

        for (const std::unique_ptr<Episode>& episode : saison.episodes_)
            episodes_.push_back(std::make_unique<Episode>(*episode));
    }
}

//! Destructeur de la classe Saison
Saison::~Saison()
{
    episodes_.clear();
}

//! Surcharge de l'operateur +=
//! \param episode Episode que l'on souhaite ajouter 
//! \return La reference a la saison dans laquelle l'episode a ete ajoute
Saison& Saison::operator+=(std::unique_ptr<Episode> episode)
{
    size_t index = trouverIndexEpisode(episode->getNumEpisode());
    if (index != EPISODE_INEXSISTANTE)
    {
        episodes_[index] = std::move(episodes_.back());
        episodes_.pop_back();
    }

    episodes_.push_back(std::move(episode));

    sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());

    return *this;
}

//! Surcharge de l'operateur -=
//! \param numEpisode Le numero de l'episode que l'on souhaite retirer
//! \return La reference a la saison dans laquelle l'episode a ete retire
Saison& Saison::operator-=(unsigned int numEpisode)
{
    size_t index = trouverIndexEpisode(numEpisode);
    if (index != EPISODE_INEXSISTANTE)
    {
        episodes_[index] = std::move(episodes_.back());
        episodes_.pop_back();
    }
    sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());

    return *this;
}

//! Surcharge de l'operateur ==
//! \param numSaison Le numero de la saison que l'on souhaite comparer
//! \return bool si le numero de la saison est le meme ou non
bool Saison::operator==(unsigned int numSaison)
{
    if (numSaison_ == numSaison)
        return true;
    return false;
}

//! Surcharge de l'operateur << pour l'affichage
//! \param os Le stream dans lequel il faut afficher
//! \param saison La saison dont il faut afficher l'information
//! \return Le stream, dans lequel il faut afficher
std::ostream& operator<<(std::ostream& os, const Saison& saison)
{
    std::string enCours;
    if (saison.episodes_.size() < saison.nbEpisodesmax_)
        enCours = "(En cours)";
    else
        enCours = "(Terminée)";

    os << std::string(8, ' ') << "Saison " << std::setfill('0') << std::setw(2) << saison.numSaison_
       << ": " << saison.episodes_.size() << "/" << saison.nbEpisodesmax_ << enCours << std::endl;

    for (const std::unique_ptr<Episode>& episode : saison.episodes_)
        os << *episode;

    return os;
}

//! Surcharge de l'operateur >>
//! \param is Le stream dans lequel lire les informations
//! \param saison La saison à remplir avec l'information lu
//! \return Le stream dans lequel on a lu l'information
std::istream& operator>>(std::istream& is, Saison& saison)
{
    is >> saison.numSaison_ >> saison.nbEpisodesmax_;
    return is;
}

//! Methode qui donne le numero de la saison
//! \return la numero de la saison
unsigned int Saison::getNumSaison() const
{
    return numSaison_;
}

//! Methode qui donne le nombre d'episode courant de la saison
//! \return Le nombre d'episode
size_t Saison::getNbEpisodes() const
{
    return episodes_.size();
}

//! Methode qui trouve l'index d'un episode dans le vecteur d'episodes
//! \param numEpisode Le numero de l'episode dont on cherche l'index
//! \return L'index de l'episode rechercher
size_t Saison::trouverIndexEpisode(unsigned int numEpisode)
{
    for (size_t index = 0; index < episodes_.size(); index++)
    {
        if (*episodes_[index] == numEpisode)
            return index;
    }
    return EPISODE_INEXSISTANTE;
}