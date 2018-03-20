#include "fasta.h"

using namespace std;

int main(int argc, char** argv){
  if (Fasta::isFasta(argv,argc)==true) {
    cout<<"ok"<<endl;
  }else{
    cout<<"nop"<<endl;
  }

  //vector<Fasta> list_fasta;
  //Fasta::extractionFasta(argv, &list_fasta);
  // fasta monfasta.fasta

  return 0;
}
