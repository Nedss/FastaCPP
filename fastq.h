#ifndef __fastq__
#define __fastq__

#include <iostream>
#include <vector>


class Fastq {

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
  std::string description;
  std::string score;
  std::vector<Fastq> listFastq;

public:
  enum FileReadState{IN_HEADER, IN_SEQUENCE, IN_DESCRIPTION, IN_SCORE};
/*
================================================================================
=                                 Constructeurs                                =
================================================================================
*/
  Fastq();
  Fastq(std::string header, std::string sequence, size_t longueur, size_t position, std::string description, std::string score);
  ~Fastq();

/*
================================================================================
=                                 Accesseurs                                   =
================================================================================
*/
  //GET
  std::string getHeader() const;
  std::string getSequence(const std::string &myFile);
  size_t getLongueur() const;
  size_t getPos() const;
  std::string getDescription() const;
  std::string getScore() const;
  //SET
  void setHeader(std::string header);
  void setSequence(std::string sequence);
  void setLongueur(size_t longueur);
  void setPosition(size_t pos);
  void setDescription(std::string description);
  void setScore(std::string score);

/*
================================================================================
=                                 Méthodes                                     =
================================================================================
*/

  //Verifications
  /*
  Vérification du fichier avec arguments.
  static bool isFasta(char** argv, int argc);
  */

  static bool isFastq(std::string locaFichier);
  static bool fastqExist(const std::string& myFile);
  static bool isNucl(char c, bool degenerated);
  static bool isBlank(char c);

  //Autres
  static std::vector<Fastq> extractionFastq(std::string &myFile);
  static std::string nomFichier();


  /*A développer si temps
  static bool isADN(char c);
  static bool isARN(char c);
  static std::string compteurType(size_t estADN, size_t estARN, size_t OtherType);
*/

/*
================================================================================
=                                 Encoded                                      =
================================================================================



Fasta(const std::string &header, const EncodedSeq &sequence);
std::string EncodedSeq getSequence () const;
void setSequence(const EncodedSeq &sequence);
std::string EncodedSeq inverseAdn();
std::string EncodedSeq inverseArn();
std::string EncodedSeq reverse();
*/

};

#endif
