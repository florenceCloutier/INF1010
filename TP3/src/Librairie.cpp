////////////////////////////////////////////////////////////////////////////////
/// Implementation de la classe Librairie
///\file Librairie.cpp
///\authors Alexis Foulon et Florence Cloutier
///
/// Ce programme contient les methodes qui ont pour but la construction de la classe 
/// Librairie et l'implementation des methodes de cette derniere.
///
/// Celles-ci peuvent notamment:
///-Construire par copie un objet de type Librairie
///-Copier un objet de type Librairie dans un autre objet de ce meme type avec la surcharge de 
///l'operateur =
///-Detruire une objet de type Librairie
///-Chercher un film ou une serie dans la Librairie selon un nom
///-Ajouter/retirer une saison a la Librairie
///-Ajouter/retirer un épisode a une Saison d'une Série dans la Librairie
///-Charger les series à partir d'un fichier donne 
///-Charger les restrictions des series à partir d'un fichier donne
///-Retourner les attributs de la Librairie
///-Afficher une Librairie avec la surcharge de l'operateur <<
///-Lire une librairie avec la surcharge de l'operateur >>
///-Retourner les attributs de l'objet de type Librairie
///-Trouver l'index d'un episode dont le nom est passe en parametre
///
////////////////////////////////////////////////////////////////////////////////

#include "Librairie.h"

//! Constructer par copie
//! \param librairie La librairie à copier
Librairie::Librairie(const Librairie& librairie)
{
    for (const std::unique_ptr<Media>& media : librairie.medias_)
        medias_.push_back(media->clone());
}

//! Copie d'une libraire
//! \param librairie La librairie à copier
Librairie& Librairie::operator=(const Librairie& librairie)
{
    if (this != &librairie)
    {
        for (const std::unique_ptr<Media>& media : librairie.medias_)
            medias_.push_back(media->clone());
    }
    return *this;
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
    medias_.clear();
}

//! Chercher un film selon son nom
//! \param nomFilm Le nom du film à chercher
//! \return Le film rechercher
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
    return dynamic_cast<Film*>(chercherMedia(nomFilm, Media::TypeMedia::Film));
}

//! Cherche une série dans la librairie selon son nom
//! \param nomSerie Le nom de la série à chercher
//! \return La série rechercher
Serie* Librairie::chercherSerie(const std::string& nomSerie)
{
    return dynamic_cast<Serie*>(chercherMedia(nomSerie, Media::TypeMedia::Serie));
}

//! Ajouter une saison à La librairie
//! \param nomSerie Le nom de la serie dans laquelle ajouter une saison
//! \param saison La saison à ajouter
void Librairie::ajouterSaison(const std::string& nomSerie, std::unique_ptr<Saison> saison)
{
    size_t index = trouverIndexMedia(nomSerie);
    if (index != MEDIA_INEXSISTANT)
        if (medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
            *dynamic_cast<Serie*>(medias_[index].get()) += std::move(saison);
}

//! Retirer une saison de La librairie
//! \param nomSerie Le nom de la serie dans laquelle retirer une saison
//! \param numSaison Le numero de la saison à retirer
void Librairie::retirerSaison(const std::string& nomSerie, unsigned int numSaison)
{
    size_t index = trouverIndexMedia(nomSerie);
    if (index != MEDIA_INEXSISTANT)
        if (medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
            *dynamic_cast<Serie*>(medias_[index].get()) -= numSaison;
}

//! Ajouter un épisode a une Saison d'une Série
//! \param nomSerie Le nom de la serie
//! \param numSaison Le numero de la saison
//! \param episode L'Episode à ajouter
void Librairie::ajouterEpisode(const std::string& nomSerie, unsigned int numSaison,
                               std::unique_ptr<Episode> episode)
{
    size_t index = trouverIndexMedia(nomSerie);

    if (index != MEDIA_INEXSISTANT)
        if (medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
        {
            dynamic_cast<Serie*>(medias_[index].get())
                ->ajouterEpisode(numSaison, std::move(episode));
        }
}

//! Retirer un épisode a une Saison d'une Série
//! \param nomSerie Le nom de la serie
//! \param numSaison Le numero de la saison
//! \param numEpisode Le numero de l'epise à ajouter
void Librairie::retirerEpisode(const std::string& nomSerie, unsigned int numSaison,
                               unsigned int numEpisode)
{
    size_t index = trouverIndexMedia(nomSerie);

    if (index != MEDIA_INEXSISTANT)
        if (medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
            dynamic_cast<Serie*>(medias_[index].get())->retirerEpisode(numSaison, numEpisode);
}

//! Méthode qui charge les series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un serie à un
//! auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerMediasDepuisFichier(const std::string& nomFichier,
                                           GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::fstream fichier(nomFichier);

    if (fichier)
    {
        std::string ligne;
        medias_.clear();

        while (getline(fichier, ligne))
            if (!lireLigneMedia(ligne, gestionnaireAuteurs))
                return false;

        return true;
    }

    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui charge les restrictions des series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (size_t i = 0; i < medias_.size(); i++)
            medias_[i]->supprimerPaysRestreints();

        std::string ligne;
        while (getline(fichier, ligne))
            if (!lireLigneRestrictions(ligne))
                return false;

        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Getter du nombre de Media
//! \return le nombre de Media de la librairie
size_t Librairie::getNbMedias() const
{
    return medias_.size();
}

//! Affiche une librairie
//! \param os Le stream dans lequel afficher
//! \param librairie La librairie à afficher
//! \return le stream dans lequel on a afficher
std::ostream& operator<<(std::ostream& os, const Librairie& librairie)
{
    
    for (const std::unique_ptr<Media>& media : librairie.medias_)
        os << *media;

    return os;
}

//! Trouve l'index du media dont le nom est passé en paramètre
//! \param nomMedia Le nom du media à recherché
//! \return L'index du media
size_t Librairie::trouverIndexMedia(const std::string& nomMedia) const
{
    for (unsigned int i = 0; i < medias_.size(); i++)
        if (medias_[i]->getNom() == nomMedia)
            return i;

    return MEDIA_INEXSISTANT;
}

//! Ajouter un media à la Librairie
//! \param media Le media à ajouter
//! \return la librairie dans laquelle on a ajouter un media
Librairie& Librairie::operator+=(std::unique_ptr<Media> media)
{
    if (media != nullptr)
        medias_.push_back(std::move(media));

    return *this;
}

//! Retirer un media
//! \param nomMedia Le nom du media à retirer
//! \return La librairie dans laquelle on a retirer un media
Librairie& Librairie::operator-=(const std::string& nomMedia)
{
    size_t index = trouverIndexMedia(nomMedia);
    if (index != MEDIA_INEXSISTANT)
    {
        medias_[index] = std::move(medias_.back());
        medias_.pop_back();
    }

    return *this;
}

//! Recherche un Média selon son nom et son type
//! \param nomMedia Le nom du media
//! \param typeMedia Le type du media
//! \return Le media recherché
Media* Librairie::chercherMedia(const std::string& nomMedia, Media::TypeMedia typeMedia)
{
    size_t index = trouverIndexMedia(nomMedia);

    if (index != MEDIA_INEXSISTANT)
        if (medias_[index]->getTypeMedia() == typeMedia)
            return medias_[index].get();

    return nullptr;
}

//! Lire les restrictions d'un media
//! \param ligne La ligne contenant les restrictions
//! \return Si la lecture de la ligne à été un succès
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);

    size_t typeMediaValeur;
    size_t paysRestreintValeur;
    std::string nomMedia;

    stream >> typeMediaValeur >> std::quoted(nomMedia);

    Media* media = chercherMedia(nomMedia, to_enum<Media::TypeMedia>(typeMediaValeur));

    if (media != nullptr)
    {
        while (stream >> paysRestreintValeur)
            media->ajouterPaysRestreint(to_enum<Pays>(paysRestreintValeur));

        return true;
    }
    return false;
}

//! Lire une ligne contenant les informations d'un Media
//! \param ligne La ligne à lire
//! \param gestionnaireAuteurs Le gestionnaire d'auteur
//! \return Si la lecture de la ligne à été un succès
bool Librairie::lireLigneMedia(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    lireLigneMediaFunction fonctionLireligne[] = {&Librairie::lireLigneFilm,
                                                  &Librairie::lireLigneSerie,
                                                  &Librairie::lireLigneSaison,
                                                  &Librairie::lireLigneEpisode};
    std::istringstream stream(ligne);
    int typeMediaValeurEnum;

    if (stream >> typeMediaValeurEnum)
    {
        bool success = invoke(fonctionLireligne[typeMediaValeurEnum], *this, stream, gestionnaireAuteurs);
        sort(medias_.begin(), medias_.end(), Media::SortByTypeMedia());
        return success;
    }

    return false;
}

//! Getter des Media d'une librairie
const std::vector<std::unique_ptr<Media>>& Librairie::getMedias() const
{
    return medias_;
}

//! Remplis un Media de type Episode à partir d'une ligne
//! \param is Le stream duquel il faut lire
//! \return La lecture c'est bien effectué
bool Librairie::lireLigneEpisode(std::istream& is, GestionnaireAuteurs&)
{
    std::string nomSerie;
    unsigned int numSaison;

    std::unique_ptr<Episode> episode = std::make_unique<Episode>();
    is >> *episode >> std::quoted(nomSerie) >> numSaison;
    ajouterEpisode(nomSerie, numSaison, std::move(episode));

    return true;
}

//! Remplis un Media de type Saison à partir d'une ligne
//! \param is Le stream duquel il faut lire
//! \return La lecture c'est bien effectué
bool Librairie::lireLigneSaison(std::istream& is, GestionnaireAuteurs&)
{
    std::string nomSerie;

    std::unique_ptr<Saison> saison = std::make_unique<Saison>();
    is >> *saison >> std::quoted(nomSerie);
    ajouterSaison(nomSerie, std::move(saison));

    return true;
}

//! Remplis un Media de type Serie à partir d'une ligne
//! \param is Le stream duquel il faut lire
//! \param gestionnaireAuteurs Le gestionnaire d'auteur pour trouver l'auteur du Media
//! \return La lecture c'est bien effectué
bool Librairie::lireLigneSerie(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::string nomAuteur;

    is >> std::quoted(nomAuteur);

    Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);

    if (auteur != nullptr)
    {
        std::unique_ptr<Serie> serie = std::make_unique<Serie>(auteur);
        serie->lire(is);

        *this += std::move(serie);
        auteur->setNbMedias(auteur->getNbMedias() + 1);

        return true;
    }

    return false;
}

//! Remplis un Media de type Film à partir d'une ligne
//! \param is Le stream duquel il faut lire
//! \param gestionnaireAuteurs Le gestionnaire d'auteur pour trouver l'auteur du Media
//! \return La lecture c'est bien effectué
bool Librairie::lireLigneFilm(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::string nomAuteur;

    is >> std::quoted(nomAuteur);

    Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);

    if (auteur != nullptr)
    {
        std::unique_ptr<Film> film = std::make_unique<Film>(auteur);
        film->lire(is);

        *this += std::move(film);
        auteur->setNbMedias(auteur->getNbMedias() + 1);

        return true;
    }

    return false;
}

//! Donne le nombre de film de la librairie
//! \return le nombre de films
size_t Librairie::getNbFilms() const
{
    size_t nFilms = 0;
    for (const std::unique_ptr<Media>& media : medias_)
        if (media->getTypeMedia() == Media::TypeMedia::Film)
            nFilms += 1;

    return nFilms;
}

//! Donne le nombre de Séries de la librairie
//! \return Le nombre de série
size_t Librairie::getNbSeries() const
{
    size_t nSeries = 0;
    for (const std::unique_ptr<Media>& media : medias_)
        if (media->getTypeMedia() == Media::TypeMedia::Serie)
            nSeries += 1;

    return nSeries;
}

//! Donne le nomrbe de saisons dans la série
//! \param nomSerie Le nom de la série
//! \return le nombre de saisons de la série
size_t Librairie::getNbSaisons(const std::string& nomSerie) const
{
    size_t index = trouverIndexMedia(nomSerie);

    if (index != MEDIA_INEXSISTANT)
        return dynamic_cast<Serie*>(medias_[index].get())->getNbSaisons();

    return 0;
}

//! Donne le nombre d'épisode dans la série
//! \param nomSerie Le nom de la série
//! \param numSaison le numero de la saison dont on veut le nombre d'épisode
//! \return Le nombre d'épisode
size_t Librairie::getNbEpisodes(const std::string& nomSerie, const unsigned int numSaison) const
{
    size_t index = trouverIndexMedia(nomSerie);

    if (index != MEDIA_INEXSISTANT)
        return dynamic_cast<Serie*>(medias_[index].get())->getSaison(numSaison)->getNbEpisodes();

    return 0;
}
