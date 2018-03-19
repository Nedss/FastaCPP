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
Fasta::Fasta(string header, string sequence, int longueur, int position){
  this->header=header;
  this->sequence=sequence;
  this->longueur=longueur;
  this->position=position;
}

/*
================================================================================
=                                 Accesseurs                                   =
================================================================================
*/
//GET
string getHeader(){
  return header;
}
string getSequence(){
  return sequence;
}
int getLongueur(){
  return longueur;
}
int getPos(){
  return position;
}
//SET
void setHeader(string header){
  this->header=header;
}
void setSequence(string sequence){
  this->sequence=sequence;
}
void setPos(int position){
  this->position=position;
}
void setLongueur(int longueur){
  this->position=position;
}

/*
================================================================================
=                                 Méthodes                                     =
================================================================================
*/

//Verifications
bool isFasta() const{}
bool isNucl(char c, bool degenerate=TRUE){}
bool isBlank(char c);

//Autres
vector<Fasta> extractionHeader(){}
vector<Fasta> extractionHeader() const{}
vector<Fasta> extractionSequence() const{}
vector<Fasta> extractionPosition() const{}
vector<Fasta> extractionLongueur() const{}
