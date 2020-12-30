////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe Media
///\file Media.cpp
///\authors Alexis Foulon et Florence Cloutier
///
/// Ce programme contient les methodes qui ont pour but la construction de la classe 
/// Media et l'implementation des methodes de cette derniere.
///
/// Celles-ci peuvent notamment:
///-Convertir le enum Media::Genre en string
///-Convertir le enum Pays en string
///-Construire par defaut l'objet de type Media
///-Construire par parametre l'objet de type Media
///-Construire par copie un objet de type Media
///-Detruire une objet de type Media
///-Ajouter un pays a la liste des pays restreints du film
///-Supprimer les pays restreints
///-Retourner si un pays est dans la liste des pays restreints du film
///-Retourner si le film est restreint aux moins de 16 ans
///-Afficher un Media
///-Afficher un Media avec la surcharge de l'operateur <<
///-Retourner les attributs d'un objet de type Media
///-Lire un stream
///-Lire un stream avec la surcharge de l'operateur >>
///-Allouer dynamiquement une copie d'un media et retourne celle-ci
///
////////////////////////////////////////////////////////////////////////////////

#include "Media.h"

namespace
{
    //! Fonction qui convertit le enum Media::Genre en string
    //! \param genre    Le genre à convertir
    //! \return         Le string qui représente le enum
    const std::string& getGenreString(Media::Genre genre)
    {
        static const std::string NOMS_GENRES[] = {"Action",
                                                  "Aventure",
                                                  "Comedie",
                                                  "Horreur",
                                                  "Romance"};

        auto index = enum_value(genre);
        assert(valid_as_enum<Media::Genre>(index));
        return NOMS_GENRES[index];
    }

    //! Fonction qui convertit le enum Pays en string
    //! \param pays     Le pays à convertir
    //! \return         Le string qui représente le enum
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

//! Construteur de Media
Media::Media(Auteur* auteur, Media::TypeMedia typeMedia)
    : nom_("")
    , anneeDeSortie_(0)
    , estRestreintParAge_(false)
    , auteur_(auteur)
    , typeMedia_(typeMedia)
{
}

//! Constructeur par paramètre de Media
Media::Media(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur, Media::TypeMedia typeMedia)
    : nom_(nom)
    , anneeDeSortie_(anneeDeSortie)
    , genre_(genre)
    , pays_(pays)
    , estRestreintParAge_(estRestreintParAge)
    , auteur_(auteur)
    , typeMedia_(typeMedia)
{
}

//! Constructeur par copie de Media
Media::Media(const Media& serie)
{
    if (this != &serie)
    {
        nom_ = serie.nom_;
        anneeDeSortie_ = serie.anneeDeSortie_;
        genre_ = serie.genre_;
        pays_ = serie.pays_;
        estRestreintParAge_ = serie.estRestreintParAge_;
        auteur_ = serie.auteur_;
        typeMedia_ = serie.typeMedia_;

        for (const Pays& pays : serie.paysRestreints_)
            paysRestreints_.push_back(pays);
    }
}

//! Destructeur de Media
Media::~Media()
{
    auteur_->setNbMedias(auteur_->getNbMedias() - 1);
}

//! Méthode qui ajoute un pays à liste des pays restreints du film
//! \param pays Pays à ajouter à la liste
void Media::ajouterPaysRestreint(Pays pays)
{
	paysRestreints_.push_back(pays);
}

//! Méthode qui supprime les pays restreints
void Media::supprimerPaysRestreints()
{
	paysRestreints_.clear();
}

//! Méthode qui retourne si un pays est dans la liste des pays restreints du film
//! \param pays Le pays à chercher dans la liste des pays restreints
//! \return     Un bool représentant si le pays se trouve dans la liste des pays restreints
bool Media::estRestreintDansPays(Pays pays) const
{
    for (std::size_t i = 0; i < paysRestreints_.size(); i++)
    {
        if (paysRestreints_[i] == pays)
        {
            return true;
        }
    }
    return false;
}

//! Méthode qui retourne si le film est restreint aux moins de 16 ans
//! \return Un bool représentant si le film est restreint aux moins de 16 ans
bool Media::estRestreintParAge() const
{
    return estRestreintParAge_;
}

//! Affiche un Media
//! \param os Le stream dans lequel afficher le Media
//! \return Le stream dans lequel on a afficher le Media
std::ostream& Media::afficher(std::ostream& os) const
{
    os << nom_ << "\n\tDate de sortie: " << anneeDeSortie_
		<< "\n\tGenre: " << getGenreString(genre_) << "\n\tAuteur: " << auteur_->getNom()
		<< "\n\tPays: " << getPaysString(pays_)
		<< (paysRestreints_.size() == 0 ? "\n\tAucun pays restreint." : "\n\tPays restreints:");

	for (std::size_t i = 0; i < paysRestreints_.size(); i++)
	{
		os << "\n\t\t" << getPaysString(paysRestreints_[i]);
	}
	os << '\n';

	return os;
}

//! Operateur qui permet l'affichage d'un media
//! \return Le stream dans lequel afficher
std::ostream& operator<<(std::ostream& os, const Media& media)
{
    media.afficher(os);
    return os;
}

//! Getter de l'attribut genre_
//! \return le genre
Media::Genre Media::getGenre() const
{
    return genre_;
}

//! Getter pour le nom du Media
//! \return le nom du Media
const std::string& Media::getNom() const
{
    return nom_;
}

//! Getter pour le type du Media
//! \return le type du media
Media::TypeMedia Media::getTypeMedia() const
{
    return typeMedia_;
}

//! Lecture d'un stream
//! \param is Le stream duquel il faut lire
//! \return Le stream lu
std::istream& Media::lire(std::istream& is)
{
    int genre, pays;

    is >> std::quoted(nom_) >> anneeDeSortie_ >> genre >> pays >> estRestreintParAge_;
    genre_ = to_enum<Genre>(genre);
    pays_ = to_enum<Pays>(pays);

    return is;
}

//! Lecture d'un stream
//! \param is Le stream duquel il faut lire
//! \param is Le media à lire
//! \return Le stream lu
std::istream& operator>>(std::istream& is, Media& media)
{
    media.lire(is);
    return is;
}

//! Alloue dynamiquement une copie d'un media et retourne celle-ci
//! \return Un pointeur sur le nouveau media
std::unique_ptr<Media> Media::clone() const
{
    return std::make_unique<Media>(*this);
}
