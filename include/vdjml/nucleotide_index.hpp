/** @file "/vdjml/include/vdjml/nucleotide_index.hpp"
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013-4 @author Mikhail K Levin
*******************************************************************************/
#ifndef NUCLEOTIDE_INDEX_HPP_
#define NUCLEOTIDE_INDEX_HPP_
#include "boost/assert.hpp"
#include "vdj_pipe/exception.hpp"

namespace vdj_pipe{

enum Nucleotide {
   Adenine = 0, Cytosine = 1, Guanine = 2, Thymine = 3,
   Any = 4,
   Uracil = 5,    ///< U
   Purine = 6,    ///< R : A, G
   Pyrimidine = 7,///< Y : C, T, U
   Ketone = 8,    ///< K : G, T, U
   Amine = 9,     ///< M : A, C
   Strong = 10,   ///< S : C, G
   Weak = 11,     ///< W : A, T, U
   not_A,         ///< B : C G T
   not_C,         ///< D : A G T
   not_G,         ///< H : A C T
   not_T,         ///< V : A C G
   Unknown = (unsigned)-1
};

/**@brief 
*******************************************************************************/
inline Nucleotide nucleotide_index(const char c) {
   switch (c) {
   case 'A':
   case 'a':
      return Adenine;
   case 'C':
   case 'c':
      return Cytosine;
   case 'G':
   case 'g':
      return Guanine;
   case 'T':
   case 't':
      return Thymine;
   case 'U':
   case 'u':
      return Uracil;
   case 'R':
   case 'r':
      return Purine;
   case 'Y':
   case 'y':
      return Pyrimidine;
   case 'K':
   case 'k':
      return Ketone;
   case 'M':
   case 'm':
      return Amine;
   case 'S':
   case 's':
      return Strong;
   case 'W':
   case 'w':
      return Weak;
   case 'B':
   case 'b':
      return not_A;
   case 'D':
   case 'd':
      return not_C;
   case 'H':
   case 'h':
      return not_G;
   case 'V':
   case 'v':
      return not_T;
   case 'N':
   case 'n':
      return Any;
   default:
      BOOST_ASSERT( ! "invalid character");
      return Unknown;
   }
}

/**@brief
*******************************************************************************/
inline bool is_ambiguous(const char c) {
   switch (c) {
   case 'A':
   case 'a':
   case 'C':
   case 'c':
   case 'G':
   case 'g':
   case 'T':
   case 't':
      return false;
   default:
      return true;
   }
}

/**@brief
*******************************************************************************/
inline Nucleotide complement(const Nucleotide n) {
   switch (n) {
   case Adenine: return Thymine;
   case Cytosine: return Guanine;
   case Guanine: return Cytosine;
   case Thymine: return Adenine;
   case Uracil: return Adenine;
   case Purine: return Pyrimidine;
   case Pyrimidine: return Purine;
   case Ketone: return Amine;
   case Amine: return Ketone;
   case Strong: return Weak;
   case Weak: return Strong;
   case not_A: return not_T;
   case not_C: return not_G;
   case not_G: return not_C;
   case not_T: return not_A;
   case Any: return Any;
   case Unknown: return Unknown;
   }
}

/**@brief
*******************************************************************************/
inline char to_capital(const Nucleotide n) {
   switch (n) {
   case Adenine: return 'A';
   case Cytosine: return 'C';
   case Guanine: return 'G';
   case Thymine: return 'T';
   case Uracil: return 'U';
   case Purine: return 'R';
   case Pyrimidine: return 'Y';
   case Ketone: return 'K';
   case Amine: return 'M';
   case Strong: return 'S';
   case Weak: return 'W';
   case not_A: return 'B';
   case not_C: return 'D';
   case not_G: return 'H';
   case not_T: return 'V';
   case Any: return 'N';
   default:
      break;
   }
   return 'X';
}

/**@brief
*******************************************************************************/
inline char to_small(const Nucleotide n) {
   switch (n) {
   case Adenine: return 'a';
   case Cytosine: return 'c';
   case Guanine: return 'g';
   case Thymine: return 't';
   case Uracil: return 'u';
   case Purine: return 'r';
   case Pyrimidine: return 'y';
   case Ketone: return 'k';
   case Amine: return 'm';
   case Strong: return 's';
   case Weak: return 'w';
   case not_A: return 'b';
   case not_C: return 'd';
   case not_G: return 'h';
   case not_T: return 'v';
   case Any: return 'n';
   case Unknown: return 'x';
   }
}

/**@return
    2 for definite match, e.g., A and A
    1 for approximate match, e.g., M and A
    0 for undetermined, e.g., N and anything else, K and S
   -2 for mismatch e.g., A and G, or R and C, or M and K
*******************************************************************************/
inline int identity(const Nucleotide n1, const Nucleotide n2) {
   switch(n1) {
   case Adenine:
      switch(n2) {
      case Adenine:
         return 2;
      case Purine:
      case Amine:
      case Weak:
         return 1;
      case Any:
         return 0;
      case Cytosine:
      case Guanine:
      case Thymine:
      case Uracil:
      case Pyrimidine:
      case Ketone:
      case Strong:
         return-2;
      default:
         break;
      }
      break;
   case Cytosine:
      switch(n2) {
      case Cytosine:
         return 2;
      case Pyrimidine:
      case Amine:
      case Strong:
         return 1;
      case Any:
         return 0;
      case Adenine:
      case Guanine:
      case Thymine:
      case Uracil:
      case Ketone:
      case Purine:
      case Weak:
         return-2;
      default:
         break;
      }
      break;
   case Guanine:
      switch(n2) {
      case Guanine:
         return 2;
      case Purine:
      case Ketone:
      case Strong:
         return 1;
      case Any:
         return 0;
      case Adenine:
      case Cytosine:
      case Thymine:
      case Uracil:
      case Amine:
      case Pyrimidine:
      case Weak:
         return-2;
      default:
         break;
      }
      break;
   case Thymine:
      switch(n2) {
      case Thymine:
         return 2;
      case Pyrimidine:
      case Ketone:
      case Weak:
         return 1;
      case Any:
         return 0;
      case Adenine:
      case Cytosine:
      case Guanine:
      case Uracil:
      case Amine:
      case Purine:
      case Strong:
         return-2;
      default:
         break;
      }
      break;
   case Uracil:
      switch(n2) {
      case Uracil:
         return 2;
      case Pyrimidine:
      case Ketone:
      case Weak:
         return 1;
      case Any:
         return 0;
      case Adenine:
      case Cytosine:
      case Guanine:
      case Thymine:
      case Amine:
      case Purine:
      case Strong:
         return-2;
      default:
         break;
      }
      break;
   case Purine:
      switch(n2) {
      case Purine:
      case Adenine:
      case Guanine:
         return 1;
      case Any:
      case Ketone:
      case Weak:
      case Amine:
      case Strong:
         return 0;
      case Cytosine:
      case Thymine:
      case Uracil:
      case Pyrimidine:
         return-2;
      default:
         break;
      }
      break;
   case Pyrimidine:
      switch(n2) {
      case Pyrimidine:
      case Cytosine:
      case Thymine:
      case Uracil:
         return 1;
      case Any:
      case Ketone:
      case Weak:
      case Amine:
      case Strong:
         return 0;
      case Adenine:
      case Guanine:
      case Purine:
         return-2;
      default:
         break;
      }
      break;
   case Ketone:
      switch(n2) {
      case Ketone:
      case Guanine:
      case Thymine:
      case Uracil:
         return 1;
      case Pyrimidine:
      case Any:
      case Weak:
      case Strong:
      case Purine:
         return 0;
      case Adenine:
      case Cytosine:
      case Amine:
         return-2;
      default:
         break;
      }
      break;
   case Amine:
      switch(n2) {
      case Adenine:
      case Cytosine:
      case Amine:
         return 1;
      case Pyrimidine:
      case Any:
      case Weak:
      case Strong:
      case Purine:
         return 0;
      case Guanine:
      case Thymine:
      case Uracil:
      case Ketone:
         return-2;
      default:
         break;
      }
      break;
   case Strong:
      switch(n2) {
      case Cytosine:
      case Guanine:
      case Strong:
         return 1;
      case Any:
      case Pyrimidine:
      case Amine:
      case Purine:
      case Ketone:
         return 0;
      case Adenine:
      case Thymine:
      case Uracil:
      case Weak:
         return-2;
      default:
         break;
      }
      break;
   case Weak:
      switch(n2) {
      case Adenine:
      case Thymine:
      case Uracil:
      case Weak:
         return 1;
      case Any:
      case Pyrimidine:
      case Amine:
      case Purine:
      case Ketone:
         return 0;
      case Cytosine:
      case Guanine:
      case Strong:
         return-2;
      default:
         break;
      }
      break;
   default:
         break;
   }
   BOOST_ASSERT(false);
   return 0;
}

}//namespace vdj_pipe
#endif /* NUCLEOTIDE_INDEX_HPP_ */
