#include "openxlsx2_types.h"

std::string int_to_col(uint32_t cell);
uint32_t uint_col_to_int(std::string& a);
Rcpp::IntegerVector col_to_int(Rcpp::CharacterVector x);

SEXP si_to_txt(XPtrXML doc);
SEXP is_to_txt(Rcpp::CharacterVector is_vec);

std::string txt_to_is(std::string txt, bool no_escapes, bool raw);

// check if we are running in a latin1 or utf8 encoding
inline pugi::xml_encoding is_utf8(bool utf8) {
  if (utf8) {
    return(pugi::encoding_utf8);
  } else {
    return(pugi::encoding_latin1);
  }
}
