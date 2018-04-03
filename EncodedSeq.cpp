#include "EncodedSeq.h"
#include <cstdlib>
#include <cstring>


using namespace std;

const size_t _mask = (sizeof(EncodedSeq::word_t) << 2) - 1;
const size_t _shift = (sizeof(EncodedSeq::word_t) + 1);

EncodedSeq::word_t encode(char c, EncodedSeq::DNA_generator_t gen = EncodedSeq::genA) {
  if (!EncodedSeq::isNucleotide(c, true)) {
    cerr << "Erreur: le nucleotide '" << c << "' n'existe pas" << endl;
    exit(1);
  }
  if (!EncodedSeq::isNucleotide(c, false)) {
    cerr << "Avertissement: nous ne pouvons pas nous permettre d'encoder le nucleotide dégénéré '" << c << "'. ";
    c = gen();
    cerr << "Nous le remplaçons par '" << c << "'. Tant pis pour vous!!!" << endl;
  }
  return (((c == 'A') || (c == 'a'))
	  ? 0
	  : (((c == 'C') || (c == 'c'))
	     ? 1
	     : (((c == 'G') || (c == 'g'))
		? 2
		: 3)));
}

char decode(EncodedSeq::word_t v) {
  if (v > (EncodedSeq::word_t) 3) {
    cerr << "Erreur: la valeur encodée n'existe pas!!!" << endl;
    exit(1);
  }
  return ((v == 0)
	  ? 'A'
	  : ((v == 1)
	     ? 'C'
	     : ((v == 2)
		? 'G'
		: 'T')));
}

bool EncodedSeq::isNucleotide(char c, bool allow_degenerated) {
  return (((c == 'A') || (c == 'a') ||
	   (c == 'C') || (c == 'c') ||
	   (c == 'G') || (c == 'g') ||
	   (c == 'T') || (c == 't'))
	  || (allow_degenerated &&
	      ((c == 'N') || (c == 'n')
	       )));
}

char EncodedSeq::genA() {
  return 'A';
}

char EncodedSeq::genRnd() {
  int x = rand() & 3;
  return ((x == 0)
	  ? 'A'
	  :((x == 1)
	    ? 'C'
	    :((x == 2)
	      ? 'G'
	      : 'T')));
}

// Nucléotide +1
size_t EncodedSeq::getWord(size_t i) const {
  return i >> _shift;
}


size_t EncodedSeq::getPosInWord(size_t i) const {
  return (~i) & _mask;
}

EncodedSeq::EncodedSeq(const char *s):
  n(s ? strlen(s) : 0),
  nbWords(n ? getWord(n - 1) + 1 : 0),
  t(nbWords ? new word_t[nbWords] : NULL)
{
  for (size_t i = 0; i < n; i++) {
    setLetter(i, s[i]);
  }
}

EncodedSeq::EncodedSeq(size_t n, EncodedSeq::DNA_generator_t gen):
  n(n),
  nbWords(n ? getWord(n - 1) + 1 : 0),
  t(nbWords ? new word_t[nbWords] : NULL)
{
  for (size_t i = 0; i < n; ++i) {
    setLetter(i, gen());
  }
}

// Constructeur par copie
EncodedSeq::EncodedSeq(const EncodedSeq &e):
  n(e.n),
  nbWords(e.nbWords),
  t(nbWords ? new word_t[nbWords] : NULL)
{
  for (size_t i = 0; i < nbWords; ++i) {
    t[i] = e.t[i];
  }
}

EncodedSeq::~EncodedSeq() {
  clear();
}

EncodedSeq &EncodedSeq::operator=(const EncodedSeq &e) {
  if (this != &e) {
    resize(e.n);
    for (size_t i = 0; i < nbWords; ++i) {
      t[i] = e.t[i];
    }
  }
  return *this;
}

size_t EncodedSeq::size() const {
  return n;
}

void EncodedSeq::toStream(ostream &os) const {
  for (size_t i = 0; i < n; ++i) {
    os << operator[](i);
  }
}

void EncodedSeq::clear() {
  resize(0);
}

void EncodedSeq::resize(size_t n, EncodedSeq::DNA_generator_t gen) {
  size_t new_nbWords = n ? getWord(n - 1) + 1 : 0;
  if (new_nbWords != nbWords) {
    word_t * new_t = new_nbWords ? new word_t[new_nbWords] : NULL;
    size_t min_nbWords = nbWords > new_nbWords ? new_nbWords : nbWords;
    for (size_t i = 0; i < min_nbWords; ++i) {
      new_t[i] = t[i];
    }
    delete [] t;
    t = new_t;
    nbWords = new_nbWords;
  }
  for (size_t i = this->n; i < n; ++i) {
    setLetter(i, gen());
  }
  this->n = n;
}

void EncodedSeq::setLetter(size_t i, char c) {
  if (i >= n) {
    cerr << "Erreur: La séquence est de taille " << n
	 << " et vous voulez changer le nucléotide à la position " << (i + 1)
	 << endl;
    exit(1);
  }
  size_t p = getWord(i);
  size_t q = getPosInWord(i);

  t[p] = t[p] & ~(word_t(3) << (q << 1)); //Libération de deux case mémoires
  t[p] = t[p] | (encode(c) << (q << 1)); // Ajout d'une nouvelle lettre
}
char EncodedSeq::operator[](size_t i) const {
  if (i >= n) {
    cerr << "Erreur: La séquence est de taille " << n
	 << " et vous voulez accéder au nucléotide à la position " << (i + 1)
	 << endl;
    exit(1);
  }
  size_t p = getWord(i);
  size_t q = getPosInWord(i);
  return decode((t[p] >> (q << 1)) & word_t(3));
}

EncodedSeq EncodedSeq::operator()(size_t i, size_t j) const {
  if (i >= n) {
    cerr << "Erreur: La séquence est de taille " << n
	 << " et vous voulez extraire le facteur qui commence à la position " << (i + 1)
	 << endl;
    exit(1);
  }
  if (j > n) {
    j = n - 1;
  }
  if (j < i) {
    j = i;
  }
  EncodedSeq e(j - i + 1);
  for (size_t p = i; p <= j; ++p) {
    e.setLetter(p - i, operator[](p));
  }
  return e;
}

ostream &operator<<(ostream &os, const EncodedSeq &e) {
  e.toStream(os);
  return os;
}
