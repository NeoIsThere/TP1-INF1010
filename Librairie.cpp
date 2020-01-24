// TODO: Faire l'entête de fichier

// TODO: Inclure la définition de la classe appropriée
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
}

// TODO: Constructeur par défault en utilisant la liste d'initialisation
Librairie::Librairie(): films_(new Film* [CAPACITE_FILMS_INITIALE]), nbFilms_(0), capaciteFilms_(CAPACITE_FILMS_INITIALE)

{
}
// Utiliser CAPACITE_FILMS_INITIALE pour la taille initiale de films_ (allocation dynamique!)


// TODO: Destructeur
// Faire appel à la fonction supprimerFilms()
// Ne pas oublier de désallouer le tableau ET les films
Librairie::~Librairie() {
	supprimerFilms();
	delete[] films_;
	
	
}

//! Méthode qui ajoute un film à la liste des films.
//! \param film Le film alloué dynamiquement à ajouter à la liste. La classe devient propriétaire du
//!             film.
void Librairie::ajouterFilm(Film* film)
{
	//std::cout << film->getNom() << std::endl;
	static constexpr unsigned int AUGMENTATION_CAPACITE_FILMS = 2;

	// TODO
	// Verifier si assez de mémoire est allouée
	// Si pas assez de mémoire, doubler la taille du tableau (AUGMENTATION_CAPACITE_FILMS)
	// Ajouter le film au tableau seulement si film n'est pas un nullptr

	if (nbFilms_ == capaciteFilms_) {
		Film** listeAggrandie = new Film * [capaciteFilms_ * AUGMENTATION_CAPACITE_FILMS];
		for (int i = 0; i < nbFilms_; i++)
			listeAggrandie[i] = films_[i];
		films_ = listeAggrandie;
		capaciteFilms_ = capaciteFilms_ * AUGMENTATION_CAPACITE_FILMS;
		
		
	}
	if (film) {
		films_[nbFilms_++] = film;
	}
}

// TODO: retirerFilm(const std::string& nomFilm)
void Librairie::retirerFilm(const std::string& nomFilm) {
	int index = trouverIndexFilm(nomFilm);
	//std::cout << index << " nb films-1:  " << nbFilms_-1 << " ";
	


	if (index >= 0) {
		delete films_[index];
		films_[index] = nullptr;
		for (int i = index; i < nbFilms_ -1; i++) {
			films_[i] = films_[i + 1];
		}
		
		//delete films_[nbFilms_ - 1];
		films_[nbFilms_-1] = nullptr;
		nbFilms_ -= 1;

		
		}
	}

// Retirer un film ayant le même nom que celui envoyé en paramètre
// Si le film n'existe pas, ne rien faire
// Faire appel à la fonction trouverIndexFilm

// TODO chercherFilm(const std::string& nomFilm)
Film* Librairie::chercherFilm(const std::string& nomFilm) {
	int index = trouverIndexFilm(nomFilm);
	if (index >= 0)
		return films_[index];
	return nullptr;

}


// Retourner un pointeur vers le film recherché
// Si le film n'existe pas, retourner nullptr
// Utiliser la fonction trouverIndexFilm

//! Méthode qui charge les films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//!                             auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerFilmsDepuisFichier(const std::string& nomFichier,
	GestionnaireAuteurs& gestionnaireAuteurs)
{
	supprimerFilms();

	std::ifstream fichier(nomFichier);
	if (fichier.is_open())
	{
		std::string ligne;

		while (getline(fichier,ligne)) 
			lireLigneFilm(ligne, gestionnaireAuteurs);
		return true;
		
	}
	std::cerr << "Le fichier " << nomFichier
			<< " n'existe pas. Assurez-vous de le mettre au bon endroit.\n";
	return false;
	
}

//! Méthode qui charge les restrictions des films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
	if (nbFilms_ > 0)
		for (int i = 0; i < nbFilms_; i++)
			films_[i]->supprimerPaysRestreints();
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
		std::string ligne;
		while (getline(fichier, ligne)) {
			lireLigneRestrictions(ligne);
		}
		return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez-vous de le mettre au bon endroit.\n";
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

// TODO getNbFilms() const: Retourner le nombre de films

size_t Librairie::getNbFilms() const {
	return nbFilms_;
}

// TODO supprimerFilms()

void Librairie::supprimerFilms() {
	for (int i = 0; i < nbFilms_; i++) {
			//std::cout << films_[9]->getNom()<< std::endl;
		
			films_[i]->getAuteur()->setNbFilms(0);
		
		
			delete films_[i];

			films_[i] = nullptr;
	}

	nbFilms_ = 0;

}
// Supprimer les films du tableau (delete)

//! Méthode qui ajoute les restrictions d'un film avec un string.
//! \param ligne Le string comportant les restrictions du film.
//! \return      Un bool représentant si l'opération est un succès.
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
	int filmValeurEnum;
	stream >> std::quoted(nomFilm);
	//for (int i = 0; i < nbFilms_; i++)
		//std::cout << films_[i]->getNom() << std::endl;
	Film* adresseFilm = chercherFilm(nomFilm);
	if (adresseFilm) {
		while (stream >> filmValeurEnum) {
			//std::cout << filmValeurEnum;
			adresseFilm->ajouterPaysRestreint(to_enum<Pays>(filmValeurEnum));
		}

		//std::cout << "AAAAA"<< std::endl;
			return true;
	}
	return false;
			

    // TODO
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
    // Utiliser l'opérateur d'extraction (>>) pour retrouver le nom du film
    // Trouver le film qui comporte le nom
    // Si le film n'existe pas, retourner false
    // Faire une boucle while (stream >> int), puis utiliser ce int pour appeler la fonction
    // film->ajouterPaysRestreint
}

//! Méthode qui ajoute un film avec un string comportant les attributs du film.
//! \param ligne                Le string comportant les attributs du film.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//!                             auteur.
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

	stream >> std::quoted(nomFilm) >> anneeSortie >> genreValeurEnum >> paysValeurEnum >> estRestreintParAge >> std::quoted(nomAuteur);
	//std::cout << " " << anneeSortie << " " << genreValeurEnum << " " << paysValeurEnum << " " << estRestreintParAge << " "<<nomAuteur << std::endl;
	Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
	//std::cout << nomAuteur << std::endl;
	if (auteur) {
		//std::cout << "trouve" << std::endl;
		//std::cout << " " << anneeSortie << " " << genreValeurEnum << " " << paysValeurEnum << " " << estRestreintParAge << nomAuteur << "AAAA"<< std::endl;
		Film* film = new Film(nomFilm, anneeSortie, to_enum<Film::Genre>(genreValeurEnum), to_enum<Pays>(paysValeurEnum), estRestreintParAge, auteur);
		ajouterFilm(film);
		film->getAuteur()->setNbFilms(film->getAuteur()->getNbFilms() + 1);
		//std::cout << nbFilms_ <<" "<< nomFilm << std::endl;
		return true;
		
	}
	return false;
	
	

    // TODO
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
    // Utiliser l'opérateur d'extraction (>>) pour retrouver les attributs du films
    // Si l'auteur n'existe pas, retourner false
    // Utiliser la fonction ajouter film
}

int Librairie::trouverIndexFilm(const std::string& nomFilm) const {
	for (int i = 0; i < nbFilms_; i++) {
		if (films_[i]->getNom() == nomFilm)
			return i;
	}
	return -1;
}
// TODO: trouverIndexFilm(const std::string& nomFilm) const
// Retourner l'indexe du film comportant le nom envoyé en paramètre
// Si le film n'existe pas, retourner -1 (FILM_INEXSISTANT)