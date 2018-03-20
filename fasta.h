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
  std::vector<Fasta> listFasta;
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
  Fasta();
  Fasta(std::string header, std::string sequence, size_t longueur, size_t position);

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
  void setHeader(std::string header);
  void setSequence(std::string sequence);
  void setLongueur(size_t longueur);
  void setPosition(size_t pos);

/*
================================================================================
=                                 Méthodes                                     =
================================================================================
*/

  //Verifications
  static bool isFasta(char** argv, int argc);
  bool isNucl(char c, bool degenerate) const;
  bool isBlank(char c) const;

  //Autres
  void extractionFasta(char *argv[]);
  /*
  std::vector<Fasta> extractionHeader() const;
  std::vector<Fasta> extractionSequence() const;
  std::vector<Fasta> extractionPosition() const;
  std:: vector<Fasta> extractionLongueur() const;
  */
};

#endif
