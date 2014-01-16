/** @file "/vdjml/include/vdjml/aa_index.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef AA_INDEX_HPP_
#define AA_INDEX_HPP_
#include "vdjml/exception.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
enum Aminoacid {
   Ala,   ///< Alanine, A
   Cys,   ///< Cysteine, C
   Asp,   ///< Aspartic Acid, D
   Glu,   ///< Glutamic Acid, E
   Phe,   ///< Phenylalanine, F
   Gly,   ///< Glycine, G
   His,   ///< Histidine, H
   Ile,   ///< Isoleucine, I
   Lys,   ///< Lysine, K
   Leu,   ///< Leucine, L
   Met,   ///< Methionine, M
   Asn,   ///< Asparagine, N
   Pro,   ///< Proline, P
   Gln,   ///< Glutamine, Q
   Arg,   ///< Arginine, R
   Ser,   ///< Serine, S
   Thr,   ///< Threonine, T
   Val,   ///< Valine, V
   Trp,   ///< Tryptophan, W
   Tyr,   ///< Tyrosine, Y
   Stop   ///< Stop codon, *
};

/**@brief
*******************************************************************************/
inline Aminoacid aminoacid_index(const char c) {
   switch(c) {
   case 'A':
   case 'a':
      return Ala;
   case 'C':
   case 'c':
      return Cys;
   case 'D':
   case 'd':
      return Asp;
   case 'E':
   case 'e':
      return Glu;
   case 'F':
   case 'f':
      return Phe;
   case 'G':
   case 'g':
      return Gly;
   case 'H':
   case 'h':
      return His;
   case 'I':
   case 'i':
      return Ile;
   case 'K':
   case 'k':
      return Lys;
   case 'L':
   case 'l':
      return Leu;
   case 'M':
   case 'm':
      return Met;
   case 'N':
   case 'n':
      return Asn;
   case 'P':
   case 'p':
      return Pro;
   case 'Q':
   case 'q':
      return Gln;
   case 'R':
   case 'r':
      return Arg;
   case 'S':
   case 's':
      return Ser;
   case 'T':
   case 't':
      return Thr;
   case 'V':
   case 'v':
      return Val;
   case 'W':
   case 'w':
      return Trp;
   case 'Y':
   case 'y':
      return Tyr;
   case '*':
      return Stop;
   default: {
      std::string s("invalid amino acid code \"");
      s += c;
      s += '"';
      BOOST_THROW_EXCEPTION(
               base_exception()
               << base_exception::msg_t(s)
      );
   }
   }
}

/**@brief
*******************************************************************************/
inline char to_capital(const Aminoacid n) {
   switch(n) {
   case Ala: return 'A';
   case Cys: return 'C';
   case Asp: return 'D';
   case Glu: return 'E';
   case Phe: return 'F';
   case Gly: return 'G';
   case His: return 'H';
   case Ile: return 'I';
   case Lys: return 'K';
   case Leu: return 'L';
   case Met: return 'M';
   case Asn: return 'N';
   case Pro: return 'P';
   case Gln: return 'Q';
   case Arg: return 'R';
   case Ser: return 'S';
   case Thr: return 'T';
   case Val: return 'V';
   case Trp: return 'W';
   case Tyr: return 'Y';
   case Stop: return '*';
   }
}

/**@brief
*******************************************************************************/
inline char to_small(const Aminoacid n) {
   switch(n) {
   case Ala: return 'a';
   case Cys: return 'c';
   case Asp: return 'd';
   case Glu: return 'e';
   case Phe: return 'f';
   case Gly: return 'g';
   case His: return 'h';
   case Ile: return 'i';
   case Lys: return 'k';
   case Leu: return 'l';
   case Met: return 'm';
   case Asn: return 'n';
   case Pro: return 'p';
   case Gln: return 'q';
   case Arg: return 'r';
   case Ser: return 's';
   case Thr: return 't';
   case Val: return 'v';
   case Trp: return 'w';
   case Tyr: return 'y';
   case Stop: return '*';
   }
}

}//namespace vdjml
#endif /* AA_INDEX_HPP_ */
