// TODO: Faire l'entête de fichier

// TODO: Inclure la définition de la classe appropriée
#include <iostream>
#include "Auteur.h"

using namespace std;
// TODO: Constructeur par paramètre en utilisant la liste d'initialisation
Auteur::Auteur(const std::string& nom, unsigned int anneeDeNaissance) : nom_(nom), anneeDeNaissance_(anneeDeNaissance), nbFilms_(0) {
}

//! Méthode qui affiche un auteur.
//! \param stream Le stream dans lequel afficher.
void Auteur::afficher(std::ostream& stream) const
{
    // Ne modifiez pas cette fonction
    stream << "Nom: " << nom_ << " | Date de naissance: " << anneeDeNaissance_
           << " | Nombre de films: " << nbFilms_;
}

// TODO getNom() const: Retourner le nom
const string& Auteur::getNom() const {

	return nom_;
}

// TODO getAnneeDeNaissance() const: Retourner l'annee de naissance
unsigned int Auteur::getAnneeDeNaissance() const {

	return anneeDeNaissance_;
}
// TODO getNbFilms() const: Retourner le nombre de films de l'auteur
unsigned int Auteur::getNbFilms() const {

	return nbFilms_;
}

// TODO setNbFilms(unsigned int nbFilms): Set le nombre de films de l'auteur

void Auteur::setNbFilms(unsigned int nbFilms) {

	nbFilms_ = nbFilms;
}

