#include "fasta.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


/*
================================================================================
=                                 Constructeurs                                =
================================================================================
*/
  Fasta::Fasta(){}
  Fasta::Fasta(string header, string sequence, size_t longueur, size_t position){
    setHeader(header);
    setSequence(sequence);
    setLongueur(longueur);
    setPosition(position);
}

/*
================================================================================
=                                 Accesseurs                                   =
================================================================================
*/
//GET
  string Fasta::getHeader() const{
    return header;
  }
  string Fasta::getSequence() const{
    return sequence;
  }
  size_t Fasta::getLongueur() const{
    return longueur;
  }
  size_t Fasta::getPos() const{
    return position;
  }
  //SET
  void Fasta::setHeader(string header){
    this->header=header;
  }
  void Fasta::setSequence(string sequence){
    this->sequence=sequence;
  }
  void Fasta::setPosition(size_t position){
    this->position=position;
  }
  void Fasta::setLongueur(size_t longueur){
    this->longueur=longueur;
  }

/*
================================================================================
=                                 Méthodes                                     =
================================================================================
*/

//Verifications
  bool Fasta::isFasta(char** argv, int argc){
    string ext = strrchr(argv[1], '.');
    if (argc != 2){
      return false;
    }
    //Verifications fichier Fasta
      //Verification extension
    cout<<ext<<endl;
    if (ext != ".fasta" && ext != ".fa"){
        return false;
      }
      // Vérification existence fichier
      //if (argv[1]){
      //}
    return true;
  }

  bool Fasta::isNucl(char c, bool degenerate=true) const{}
  bool Fasta::isBlank(char c) const{}

//Autres
/*  void extractionFasta(char *argv[],vector<Fasta> list_fasta){
    size_t compteur =0;
    string contenu = NULL;
    ifstream fichier(argv[1], ios::in);
    if (fichier){
      while (getline(fichier, contenu)){
        this->f_tmp();
        if (contenu[0] ==">"){

          // Ajouter ici la partie du brouillon sur l'itération de classe
        }
      }
    }
  }
*/
/*
vector<Fasta> extractionHeader(){}
vector<Fasta> extractionHeader() const{}
vector<Fasta> extractionSequence() const{}
vector<Fasta> extractionPosition() const{}
vector<Fasta> extractionLongueur() const{}
*/
