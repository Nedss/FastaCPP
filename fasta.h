#ifndef __fasta__
#define __fasta__

#include <iostream>
#include <vector>


class Fasta {

/*
================================================================================
=                                 Variables                                    =
================================================================================
*/

private:
  std::string header;
  std::string sequence;
  size_t longueur;
  size_t position;
  std::vector<std::string>list_sequence;
  std::vector<std::string>list_header;
  std::vector<size_t>list_longueur;
  std::vector<size_t>list_position;
public:

/*
================================================================================
=                                 Constructeurs                                =
================================================================================
*/
  fasta();
  fasta(std::string header, std::string sequence, size_t longueur, size_t position);

/*
================================================================================
=                                 Accesseurs                                   =
================================================================================
*/
  //GET
  std::string getHeader() const;
  std::string getSequence() const;
  size_t getLongueur() const;
  size_t getPos() const;
  //SET
  void setHeader(string header);
  void setSequence(string sequence);
  void setLongueur(int longueur);
  void setPos(int pos);

/*
================================================================================
=                                 Méthodes                                     =
================================================================================
*/

  //Verifications
  bool isFasta() const;
  bool isNucl(char c, bool degenerate=TRUE) const;
  bool isBlank(char c) const;

  //Autres



};

#endif
