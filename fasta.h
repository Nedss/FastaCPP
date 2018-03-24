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
  std::string type;
  std::vector<Fasta> listFasta;

public:
  enum FileReadState{IN_HEADER, IN_SEQUENCE};
/*
================================================================================
=                                 Constructeurs                                =
================================================================================
*/
  Fasta();
  Fasta(std::string header, std::string sequence, size_t longueur, size_t position, std::string type);
  ~Fasta();

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
  std::string getType() const;
  //SET
  void setHeader(std::string header);
  void setSequence(std::string sequence);
  void setLongueur(size_t longueur);
  void setPosition(size_t pos);
  void setType(std::string type);

/*
================================================================================
=                                 Méthodes                                     =
================================================================================
*/

  //Verifications
  static bool isFasta(char** argv, int argc);
  static bool isNucl(char c, bool degenerate);
  static bool isBlank(char c);
  static bool isADN(char c);
  static bool isARN(char c);

  //Autres
  static std::vector<Fasta> extractionFasta(std::string &the_file);
  static std::string nomFichier();
  static std::string compteurType(size_t estADN, size_t estARN, size_t OtherType);


};

#endif
/*
Notes utiles :
HERITAGES :
virtual
virtual =0
*/
