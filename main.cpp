#include "fasta.h"

using namespace std;

int main(int argc, char** argv){

/*
================================================================================
=                                Variables                                     =
================================================================================
*/
  vector<Fasta> fasta_vector;
  size_t position;
  char choixSeq;
  bool checkChoix=false;
  bool checkExt=false;
  bool checkPos=false;
  bool checkListe=false;
  string myFile=Fasta::nomFichier();
  Fasta f1;


    /*

================================================================================
=                                 Exécution                                    =
================================================================================
    //Pour lancer la vérification avec Argument.
    if (Fasta::isFasta(argv,argc)==true) {
      cout<<"ok"<<endl;
    }else{
      cout<<"nop"<<endl;

    }
    */

  while(checkExt==false){
    if (Fasta::isFasta(myFile)==false){
      cerr<<"Veuillez saisir un fichier qui a la bonne extension."<<endl;
      string myFile=Fasta::nomFichier();
    }
    else{
      checkExt=true;
    }
  }
  if (Fasta::fastaExist(myFile) != true){
    cerr<<"Le fichier n'existe pas, fermeture du programme"<<endl;
    return -1;
  }

  fasta_vector = f1.extractionFasta(myFile);
  cout<<"\t\t Bienvenue dans le projet FASTA \n Le fichier a bien été traité, quelle est la position qui vous intéresse ?" <<endl;
  cin >> position;
  while(checkChoix==false){
    cout<< "Le header sera affiché par défaut, voulez-vous extraire la séquence ? (O,o/N,n)"<<endl;
    cin >> choixSeq;
    if (choixSeq =='O' || choixSeq=='o' || choixSeq=='N' || choixSeq=='n'){
      checkChoix=true;
    }
  }
  while(checkPos==false){
    for (size_t i=0; i<fasta_vector.size(); i++){
      if (!NULL){
        if(fasta_vector[i].getPos() == position){
          checkPos=true;
          cout<<fasta_vector[i].getHeader()<<endl;
          if (choixSeq == 'O' || choixSeq =='o'){
            cout<<fasta_vector[i].getSequence(myFile)<<endl;
          }
        }
        //cerr<<fasta_vector[i].getSequence(myFile)<<endl;
        //f1.display(fasta_vector[i]);
        //delete [] sequenceTab;
      }
    }
    if(checkPos==false){
      cerr<<"La position désirée n'existe pas, veuillez en saisir une correcte"<<endl;
      cout<<"Affichage des positions pour sélectionner la bonne"<<endl;
      for (size_t i=0; i<fasta_vector.size(); i++){
        cout<<fasta_vector[i].getPos()<<endl;
      }
      cout<<"Saisir la nouvelle position :"<<endl;
      cin>>position;
    }
  }
  return 0;
}

/*
COMMENTAIRES :
On récupère le chemin du fichier. On boucle la saisie tant qu'on a pas un fichier valable. On vérifie ensuite si le fichier existe avant de lancer l'extraction. On décide alors si on veut afficher la séquence de notre Fasta.
________________________________________________________________________________
*/
