/// Definition et implementation des foncteurs
/// author Florence Cloutier, Alexis Foulon
///  date 2020-04-17

#ifndef FONCTEUR_H
#define FONCTEUR_H

#include <memory>
#include <utility>
#include <string>
#include <LigneLog.h>



/// @brief Définition du foncteur prédicat unaire servant à déterminer si un film est sorti entre   ///        deux annees
/// Constructeur par parametres de la classe:
///  @param anneeInferieure, borne inferieure de l'intervalle de dates
///  @param anneeSuperieure, borne superieure de l'intervalle de dates
/// operator():
///  @param film de type reference constante a un pointeur unique de Film
///  @return bool qui confirme si le film passe en param est dans l'intervalle de dates de la classe
/// Attributs:
///  anneeInferieure_ : Borne inferieure de l'intervalle de dates
///  anneeSuperieure_ : Borne superieure de l'intervalle de dates
class EstDansIntervalleDatesFilm
{
public:
    EstDansIntervalleDatesFilm(int anneeInferieure, int anneeSuperieure) 
        : anneeInferieure_(anneeInferieure), 
        anneeSuperieure_(anneeSuperieure) 
        {
        }
    bool operator()(const std::unique_ptr<Film>& film) const 
    {
        return (film->annee >= anneeInferieure_ && film->annee <= anneeSuperieure_);
    }
private:
    int anneeInferieure_, anneeSuperieure_;
};

/// @brief Définition du foncteur prédicat binaire servant à comparer les dates des lignes de log   ///       pour indiquer si elles sont en ordre chronologique
/// operator():
///  @param ligneLog1, log inferieur de type reference constante a LigneLog
///  @param ligneLog2, log superieur de type reference constante a LigneLog                         /// @return bool qui confirme si les lignes de log sont en ordre chronologique
class ComparateurLog
{
public:
    bool operator()(const LigneLog& ligneLog1, const LigneLog& ligneLog2) const
    {
        return ligneLog1.timestamp < ligneLog2.timestamp;
    }
};

/// @brief Définition du template de foncteur prédicat binaire servant à comparer les seconds       ///        elements de paires pour determiner si elles sont en ordre
/// operator():
///  @param paire1, paire inferieure de type reference constante a une paire constituee de T1, T2
///  @param paire2, paire superieur de type reference constante a une paire constituee de T1, T2
///  @return bool qui confirme si les paires sont en ordre
template <class T1, class T2>
class ComparateurSecondElementPaire
{
public:
    bool operator()(const std::pair<T1, T2>& paire1, const std::pair<T1, T2>& paire2)
    {
        return paire1.second < paire2.second;
    }
};

#endif