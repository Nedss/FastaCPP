#ifndef __fasta__
#define __fasta__

#include <iostream>


class fasta {
private:
  std::string seq;
  std::int longueur;
  std::int position;
public:
  fasta();
  fasta(std::string seq, std::int longueur, std::int position);
};

#endif
