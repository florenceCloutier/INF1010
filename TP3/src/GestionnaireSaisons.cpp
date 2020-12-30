////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe GestionnaireSaisons
///\file GestionnaireSaisons.cpp
///\authors Alexis Foulon et Florence Cloutier
///
/// Ce programme contient les methodes qui ont pour but la construction de la classe 
/// GestionnaireSaisons et l'implementation des methodes de cette derniere.
///
/// Celles-ci peuvent notamment:
///-Detruire un objet de type GestionnaireSaisons
///-Ajouter une saison a la liste de saisons avec la surcharge de l'operateur +=
///-Retirer une saison a la liste de saisons avec la surcharge de l'operateur -=
///-Ajouter un episode a la saison
///-Retirer un episode a la saison
///-Trouver l'index d'une saison selon son numero
///-Retourner les attributs d'un objet de type GestionnaireSaisons 
///
////////////////////////////////////////////////////////////////////////////////

#include "GestionnaireSaisons.h"

//! Destructeur
GestionnaireSaisons::~GestionnaireSaisons()
{
    saisons_.clear();
}

//! Surcharge de l'operateur += pour l'ajout d'une saison
//! \param saison Un pointeur sur la saison à ajouter
//! \return Une référence sur le GestionnaireSaison
GestionnaireSaisons& GestionnaireSaisons::operator+=(std::unique_ptr<Saison> saison)
{
    const size_t index = trouverIndexSaison(saison->getNumSaison());
    if (index != SAISON_INEXSISTANTE)
        saisons_[index] = std::move(saison);
    else
        saisons_.push_back(std::move(saison));

    sort(saisons_.begin(), saisons_.end(), Saison::SortByNumSaison());

    return *this;
}

//! Surcharge de l'operateur -= pour enlever une saison
//! \param numSaison le numero de la saison à enlever
//! \return Une référence sur le GestionnaireSaison
GestionnaireSaisons& GestionnaireSaisons::operator-=(const unsigned int numSaison)
{
    const size_t index = trouverIndexSaison(numSaison);

    if (index != SAISON_INEXSISTANTE)
    {
        saisons_[index] = std::move(saisons_.back());
        saisons_.pop_back();
    }

    sort(saisons_.begin(), saisons_.end(), Saison::SortByNumSaison());

    return *this;
}

//! Ajouter un épisode à la saison
//! \param numSaison Le numero de la saison dans laquelle ajouter l'épisode
//! \param episode Un pointeur sur l'épisode à ajouter
void GestionnaireSaisons::ajouterEpisode(const unsigned int numSaison,
                                         std::unique_ptr<Episode> episode)
{
    const size_t index = trouverIndexSaison(numSaison);
    if (index != SAISON_INEXSISTANTE)
        *saisons_[index] += std::move(episode);
}

//! Retirer un épisode à la saison
//! \param numSaison Le numero de la saison dans laquelle ajouter l'épisode
//! \param numEpisode Le numero de l'episode à retirer
void GestionnaireSaisons::retirerEpisode(const unsigned int numSaison,
                                         const unsigned int numEpisode)
{
    const size_t index = trouverIndexSaison(numSaison);
    if (index != SAISON_INEXSISTANTE)
        *saisons_[index] -= numEpisode;
}

//! Trouve l'index d'une Saison selon son numéro
//! \param numSaison Le numero de la saison à trouver
//! \return L'index de la saison
size_t GestionnaireSaisons::trouverIndexSaison(const unsigned int numSaison) const
{
    for (size_t i = 0; i < saisons_.size(); i++)
        if (*saisons_[i] == numSaison)
            return i;
    
    return SAISON_INEXSISTANTE;
}

//! Getter pour une saison selon son numero
//! \return Un pointeur sur une saison
Saison* GestionnaireSaisons::getSaison(const unsigned int numSaison) const
{
    const size_t index = trouverIndexSaison(numSaison);
    if (index != SAISON_INEXSISTANTE)
        return saisons_[index].get();
    
    return nullptr;
}

//! Getter pour le nombre de saison
//! \return Le nombre de saison
size_t GestionnaireSaisons::getNbSaisons() const
{
    return saisons_.size();
}
