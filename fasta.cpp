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
Fasta::Fasta(string header, string sequence, size_t longueur, size_t position, string type){
  setHeader(header);
  setSequence(sequence);
  setLongueur(longueur);
  setPosition(position);
  setType(type);
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
string Fasta::getType() const{
  return type;
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
void Fasta::setType(string type){
  this->type=type;
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

bool Fasta::isNucl(char c, bool degenerated = true){
  return ((c == 'A') || (c == 'a')
  || (c == 'C') || (c == 'c')
  || (c == 'G') || (c == 'g')
  || (c == 'T') || (c == 't')
  || (c == 'U') || (c == 'u')
  || (degenerated
    && ((c == 'N') || (c == 'n')
    || (c == 'R') || (c == 'r')
    || (c == 'Y') || (c == 'y')
    || (c == 'S') || (c == 's')
    || (c == 'W') || (c == 'w')
    || (c == 'K') || (c == 'k')
    || (c == 'M') || (c == 'm')
    || (c == 'B') || (c == 'b')
    || (c == 'D') || (c == 'd')
    || (c == 'H') || (c == 'h')
    || (c == 'V') || (c == 'v'))));
}

bool Fasta::isBlank(char c){
  return ((c == ' ') || (c == '\t') || (c == '\n'));
}

static string nomFichier(){
  string locaFichier;
  cout <<"Saisir l'emplacement du fichier"<<endl;
  cerr<<locaFichier <<endl;
  return locaFichier;
}

string compteurType(size_t estADN, size_t estARN, size_t OtherType){
  string type = NULL;
  if(estADN >= estARN && estADN >= OtherType){
    if(estADN == estARN || estADN == OtherType){
      type="Autre_type";
      return type;
    }
    else{
      type="ADN";
      return type;
    }
  }
  else if(estARN >= estADN && estARN >= OtherType){
    if(estARN == estADN || estARN == OtherType){
      type="Autre_Type";
      return type;
    }
    else{
      type="ARN";
      return type;
    }
  }
  else {
    type="Autre_Type";
    return type;
  }
}

vector<Fasta> Fasta::extractionFasta(string &myFile){
  ifstream file(myFile.c_str(), ios::in);

  // Variables extraction
  vector<Fasta> listeFasta;
  Fasta f1;
  string header;
  char last_c = '\n';
  size_t debut = 0;
  size_t seqSize = 0;
  size_t i = 0;
  size_t charNb = 0;
  size_t num_line = 1;
  size_t fails = 0;
  char buffer[1024];
  size_t estADN = 0;
  size_t estARN = 0;
  size_t OtherType = 0;

  // Partie extraction
  FileReadState state = IN_HEADER;
  do {

    if (i == charNb){
      //On supprime ce qui existe déjà
      i = 0;
      debut = file.tellg();
      file.read(buffer,1024);
      charNb = file.gcount();
    }
    while (i < charNb) {
      switch (state) {
        case IN_HEADER: {
          if (buffer[i] == '\n' && buffer[i+1] != ';' && buffer[i+1] != '>') {
            ++num_line;
            f1.setHeader(header);
            header.clear();
            state = IN_SEQUENCE;
            f1.setPosition(debut+i);
          } else if (buffer[i] != '\n'){ // Regroupe header sur une seule ligne
            header += buffer[i];
          }

          break;
        }
        case IN_SEQUENCE: {
          if (Fasta::isNucl(buffer[i])) {
            ++seqSize;
            if (!Fasta::isNucl(buffer[i], false)) {
              cerr << myFile << ": Ligne " << num_line << ": " << "Nucléotide inconnu " << endl;
              fails++;
            }
            if (Fasta::isADN(buffer[i])) {
              estADN ++;
            } else if (Fasta::isARN(buffer[i])) {
              estARN ++;
            } else {
              OtherType ++;
            }
          } else {
            if (Fasta::isBlank(buffer[i])) {
              num_line += (buffer[i] == '\n');
            } else {
              if ((last_c == '\n') && ((buffer[i] == '>') || (buffer[i] == ';'))) {
                f1.setType(Fasta::compteurType(estADN, estARN, OtherType));
                f1.setLongueur(seqSize);
                seqSize = 0;
                state = IN_HEADER;
                listeFasta.push_back(f1);
                estADN = 0;
                estARN = 0;
                OtherType = 0;
                header += buffer[i];
              } else {
                cerr << myFile << ": Ligne " << num_line << ": " << "Nucléotide dégénéré" << endl;
                fails++;
              }
            }
          }
          break;
        }
      }
      last_c = buffer[i++];
    }
  } while (charNb);

  if (!header.empty()) {
    f1.setHeader(header);
    header.clear();
  }
  f1.setLongueur(seqSize);
  f1.setType(Fasta::compteurType(estADN, estARN, OtherType));
  file.close();
  cout << "\n" << "Il y a " << fails << " erreur(s) dans le fichier" << "\n" << endl;
  listeFasta.push_back(f1);
  return listeFasta;
}

/*
vector<Fasta> extractionHeader(){}
vector<Fasta> extractionHeader() const{}
vector<Fasta> extractionSequence() const{}
vector<Fasta> extractionPosition() const{}
vector<Fasta> extractionLongueur() const{}
*/
