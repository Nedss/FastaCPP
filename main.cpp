#include "fasta.h"

using namespace std;

int main(int argc, char** argv){

  //Variables
  vector<Fasta> fasta_vector;
  int s;
  int choiceLecture = 0;
  int choiceSave = 0;
  string the_file;
  if (Fasta::isFasta(argv,argc)==true) {
    cout<<"ok"<<endl;
  }else{
    cout<<"nop"<<endl;

  }
  Fastm fnom;
  Fasta f2;

  myFile = fnom.nomFichier();
  if (fm.file(myFile) != true){
    return -1;
  }
  fasta_vector = f2.lecture_all(the_file);
      for (size_t i=0; i<fasta_vector.size(); i++){
        if (!NULL){
          f2.getSequence(fasta_vector[i], the_file);
          f2.display(fasta_vector[i]);
          //delete [] sequenceTab;
        }
      }
  }
  return 0;
}
