#include "fasta.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/stat.h>

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
Fasta::~Fasta(){}

/*
================================================================================
=                                 Accesseurs                                   =
================================================================================
*/

                      /////////////////////////////////
                      //           Getters           //
                      /////////////////////////////////

string Fasta::getHeader() const{
  return header;
}

//Cas spécial : getSequence
//--------------------------
string Fasta::getSequence(const string &myFile) {
  ifstream file(myFile.c_str(), ios::in);
  char seq_buffer[1024];
  size_t charNb;
  size_t length = this->getLongueur();
  file.seekg(this->getPos());
  string seq(length, '?');
  size_t p = 0;
  size_t i = 0;

  do{
    if (i == charNb){
      i = 0;
      file.read(seq_buffer,1024);
      charNb = file.gcount();
    }

    file.read(seq_buffer, 1024);
    charNb = file.gcount();
    for(size_t i = 0; (i < charNb) && (p < length); i++){
      if(seq_buffer[i] != '\n') {
  seq[p++] = seq_buffer[i];
      }
    }
  } while(charNb);
  file.close();
  return seq;
}

/*
COMMENTAIRES :
On utilise le principe de buffer. Le principe se rapproche de la fonction extraction qui est détaillée plus bas.
On récupère donc la séqunce de notre fichier Fasta à l'aide de la position. On ne prend en paramètre qu'un lien vers notre fichier. 
________________________________________________________________________________
*/

size_t Fasta::getLongueur() const{
  return longueur;
}
size_t Fasta::getPos() const{
  return position;
}
string Fasta::getType() const{
  return type;
}

                      /////////////////////////////////
                      //            Setters          //
                      /////////////////////////////////

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

/*
--------------------------------------------------------------------------------
-                          Fichier & Verifications                             -
--------------------------------------------------------------------------------

                      /////////////////////////////////
                      //         Extension           //
                      /////////////////////////////////

Vérification avec Arguments.
-------------------------------
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
*/

//Vérification avec saisie
//-------------------------
bool Fasta::isFasta(string locaFichier){
  string ext = locaFichier.substr(locaFichier.find_last_of(".")+1);
  /*
  Debug pour avoir l'extension.
  cout <<ext<<endl;
  */
  if (ext != "fasta" && ext !="fa"){
    return false;
  }
  return true;
}

/*
COMMENTAIRES :
----------------
La version saisie a été choisie pour utiliser toutes les fonctionnalités du programme en interne.
On prend en paramètre le chemin du fichier, on récupère l'extension grâce à substr qui va prendre une sous chaîne de locaFichier, ici on récupère la sous-chaîne après le '.'.
On admet deux extensions de fasta : .fasta et .fa.
________________________________________________________________________________

                      /////////////////////////////////
                      //         Existence           //
                      /////////////////////////////////
*/
bool Fasta::fastaExist(const string& myFile) {
    struct stat file_temp;
    return (stat(myFile.c_str(), &file_temp) == 0);
}
/*
COMMENTAIRES
-------------
Pour vérifier qu'un fichier existe on utilise stat(). La fonction permet de récupérer des informations sur un fichier, ainsi, on si on retrouve le fichier, on renvoie 0 et donc fastaExist prend la valeur true.
________________________________________________________________________________

                      /////////////////////////////////
                      //         Identification      //
                      //         de Caractères       //
                      /////////////////////////////////

*/

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
/*
bool Fasta::isADN(char c){
  return ((c=='T') || (c=='T'));
}

bool Fasta::isARN(char c){
  return ((c=='U') || (c=='u'));
}

COMMENTAIRES :
--------------
Le principe ici est d'avoir des informations sur des nucléotides. isNucl nous permet de savoir si le nucléotide en paramètre est valide. On considère de base les nucléotides dégénérés dans l'appel de la fonction mais on peut changer la valeur à souhait.
isBlank prend aussi un caractère en paramètre et permet d'identifier une absence de caractère ou un "Blank". Ce peut être un retour chariot (\n), une tabulation (\t) ou même un espace (' ').
Les fonctions isADN et isARN ne sont pas encore développées et permettent de reconnaître une un nucléotide caractéristique de l'ADN ou de l'ARN.
________________________________________________________________________________

                      /////////////////////////////////
                      //            Chemin           //
                      /////////////////////////////////
*/
string Fasta::nomFichier(){
  string locaFichier;
  cout <<"Saisir l'emplacement du fichier"<<endl;
  cin >> locaFichier;
  //cout<<locaFichier <<endl;
  return locaFichier;
}
/*
COMMENTAIRES
-------------
Simple fonction qui demande la sasie du chemin du fichier fasta.
________________________________________________________________________________

                      /////////////////////////////////
                      //          Extraction         //
                      /////////////////////////////////


*/

vector<Fasta> Fasta::extractionFasta(string &myFile){
  ifstream file(myFile.c_str(), ios::in);

//Variables
//----------

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

  /*
  A ajouter si on veut savoir quel est le type de la séquence.
  size_t estADN = 0;
  size_t estARN = 0;
  */

  size_t OtherType = 0;

//Partie extraction
//------------------

  FileReadState state = IN_HEADER;
  do {

    if (i == charNb){
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
          } else if (buffer[i] != '\n'){
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

            /*
            A ajouter si on veut savoir quel est le type de la séquence.
            if (Fasta::isADN(buffer[i])) {
              estADN ++;
            } else if (Fasta::isARN(buffer[i])) {
              estARN ++;
            } else {
              OtherType ++;
            }
            */

          } else {
            if (Fasta::isBlank(buffer[i])) {
              num_line += (buffer[i] == '\n');
            } else {
              if ((last_c == '\n') && ((buffer[i] == '>') || (buffer[i] == ';'))) {

                /*
                A ajouter si on veut savoir quel est le type de la séquence
                f1.setType(Fasta::compteurType(estADN, estARN, OtherType));
                */

                f1.setLongueur(seqSize);
                seqSize = 0;
                state = IN_HEADER;
                listeFasta.push_back(f1);

                /*
                A ajouter si on veut savoir quel est le type de la séquence.
                estADN = 0;
                estARN = 0;
                OtherType = 0;
                */

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

  /*
  A ajouter si on veut savoir quel est le type de la séquence
  f1.setType(Fasta::compteurType(estADN, estARN, OtherType));
  */

  file.close();
  cout << "\n" << "Il y a " << fails << " erreur(s) dans le fichier" << "\n" << endl;
  listeFasta.push_back(f1);
  return listeFasta;
}
/*
COMMENTAIRES
------------
La partie de la fonction est l'utilisation d'un buffer. Cela permet de parcourir le fichier en ne sauvegardant que les données dont on a besoin. En effet le buffer ayant une taille de 1024 caractères, il est renouvellé par la suite des caractères du fichier quand il a atteint sa quantité maximale.

Il y a deux parties dans le fichier Fasta, un header et notre séquence. Une énumération a été créée afin de déterminer dans quelle partie du fichier on est.
  -STATE HEADER : On démarre notre parcours dans le header. En effet un fichier Fasta normalement créé dispose en premier lieu d'un header. Dès qu'on observe un retour chariot, on en déduit que nous sommes passé dans la séquence. On ajoute donc le header et la position de notre séquence dans notre objet. On réinitialise le header pour les prochains objets.
  -STATE SEQUENCE : On vérifie si les nucléotides qu'on parcourt sont corrects dégénérés ou pas. Si c'est le cas, on incrémente la longueur de la séquence. Si ce n'est pas le cas, on signale une erreur. On repasse ensuite dans le Header si jamais on trouve un '>' ou un ';'
A chaque fin de séquence on ajoute un l'objet créé dans une liste d'objets.
Le dernier header et la dernière séquences sont reconnus par la fin des caractères présents dans le fichier, en effet, on est obligé d'utiliser une telle méthode car on a pas de header qui suit pour lancer les fonctions de stockages.

________________________________________________________________________________

                      /////////////////////////////////
                      //        Prototypes           //
                      /////////////////////////////////

string Fasta::compteurType(size_t estADN, size_t estARN, size_t OtherType){
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
*/
