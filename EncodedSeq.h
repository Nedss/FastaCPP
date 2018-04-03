#ifndef __ENCODED_SEQUENCE__
#define __ENCODED_SEQUENCE__

#include <sys/types.h>
#include <stdint.h>
#include <iostream>

class EncodedSeq {
 public:
  typedef uint32_t word_t;
  typedef char(*DNA_generator_t)();

protected:
  size_t n;
  word_t nbWords;
  word_t *t;
  size_t getWord(size_t i) const;
  size_t getPosInWord(size_t i) const;
  size_t getNbWords(size_t i) const;

 public:
  EncodedSeq(const char *s = NULL);
  EncodedSeq(size_t n, DNA_generator_t gen = genA);
  EncodedSeq(const EncodedSeq &e);
  ~EncodedSeq();
  EncodedSeq &operator=(const EncodedSeq &e);

  size_t size() const;
  void toStream(std::ostream &os = std::cout) const;
  void clear();
  void resize(size_t n, DNA_generator_t gen = genA);
  void setLetter(size_t i, char c);
  char operator[](size_t i) const;
  EncodedSeq operator()(size_t i, size_t j = (size_t) -1) const;

  static bool isNucleotide(char c, bool allow_degenerated = false);
  static char genA();
  static char genRnd();
};

std::ostream &operator<<(std::ostream &os, const EncodedSeq &e);

#endif