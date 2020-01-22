// TODO: Faire l'entête de fichier

// TODO: Inclure la définition de la classe appropriée

#include "Utilisateur.h"

using namespace std;

// TODO: Constructeur utilisant la liste d'initialisation

Utilisateur::Utilisateur(const std::string& nom, unsigned int age, bool estPremium, Pays pays): nom_(nom), age_(age), estPremium_(estPremium), nbFilmsVus_(0), pays_(pays){

}

//! Méthode qui retourne si le film est disponible pour un utilisateur.
//! \param film Le film à évaluer.
//! \return Un bool représentant si un film est disponible à l'utilisateur.
bool Utilisateur::filmEstDisponible(const Film& film) const
{
	// TODO
	// Vérifier que le film n'est pas restreint dans le pays de l'utilisateur
	// Vérifier que l'utilisateur a l'âge approprié pour regarder le film (s'il est est restreint
	// pour les moins de 16 ans).
    static constexpr unsigned int AGE_MINIMUM_POUR_FILMS_RESTREINTS = 16;
	if (film.estRestreintDansPays(pays_))
		return false;
	if (film.estRestreintParAge() && age_ < 16)
		return false;
	return true;
    
}

// TODO nbLimiteFilmsAtteint() const
// Retourner si l'utilisateur a atteint la limite de films qu'il peut regarder
// Si un utilisateur est premium, il n'y a pas de limite
// Si un utilisateur n'est pas premium, il peut regarder au maximum NB_FILMS_GRATUITS

bool Utilisateur::nbLimiteFilmsAtteint() const {
	if (estPremium_)
		return false;
	if (nbFilmsVus_ < NB_FILMS_GRATUITS)
		return false;
	return true;
}

bool Utilisateur::regarderFilm(const Film& film) {
	if (nbLimiteFilmsAtteint() || !filmEstDisponible(film))
		return false;
	nbFilmsVus_++;
	return true;
}
// TODO regarderFilm(const Film& film)
// Vérifier que l'utilisateur n'a pas atteint la limite de films qu'il peut regarder
// Vérifier que le film est disponnible dans le pays de l'utilisateur
// Si ces deux conditions sont remplies, incrémenter nbFilmsVus_ et retourner true
// Sinon, retourner false

// TODO getNbFilmsVus() const: Retourner le nombre de films vus

unsigned int Utilisateur::getNbFilmsVus() const {
	return nbFilmsVus_;
}