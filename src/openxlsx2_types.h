/******************************************************************************
 *                                                                            *
 * This file defines typedefs. R expects it to be called <pkgname>_types.h    *
 *                                                                            *
 ******************************************************************************/

/* create custom Rcpp::wrap function to be used with std::vector<xml_col> */
#include <RcppCommon.h>

typedef struct {
  std::string row_r ;
  std::string c_r;
  std::string c_s;
  std::string c_t;
  std::string v;
  std::string f;
  std::string f_t;
  std::string f_ref;
  std::string f_ca;
  std::string f_si;
  std::string is;
} xml_col;


typedef struct {
  std::string v;
  std::string c_s;
  std::string c_t;
  std::string is;
  std::string f;
  std::string typ;
  std::string r;
} celltyp;

enum celltype {
  short_date = 0,
  long_date  = 1,
  numeric    = 2,
  boolean    = 3,
  character  = 4,
  formula    = 5,
  accounting = 6,
  percentage = 7,
  scientific = 8,
  comma      = 9,
  hyperlink  = 10
};

#include <Rcpp.h>

// custom wrap function
// Converts the imported values from c++ std::vector<xml_col> to an R dataframe.
// Whenever new fields are spotted they have to be added here
namespace Rcpp {
template <>
inline SEXP wrap(const std::vector<xml_col> &x) {

  size_t n = x.size();

  // Vector structure identical to xml_col from openxlsx2_types.h
  Rcpp::CharacterVector row_r(no_init(n));     // row name: 1, 2, ..., 9999

  Rcpp::CharacterVector c_r(no_init(n));       // col name: A, B, ..., ZZ
  Rcpp::CharacterVector c_s(no_init(n));       // cell style
  Rcpp::CharacterVector c_t(no_init(n));       // cell type

  Rcpp::CharacterVector v(no_init(n));         // <v> tag
  Rcpp::CharacterVector f(no_init(n));         // <f> tag
  Rcpp::CharacterVector f_t(no_init(n));       // <f t=""> attribute most likely shared
  Rcpp::CharacterVector f_ref(no_init(n));     // <f ref=""> attribute most likely reference
  Rcpp::CharacterVector f_ca(no_init(n));      // <f ca=""> attribute most likely conditional formatting
  Rcpp::CharacterVector f_si(no_init(n));      // <f si=""> attribute most likely sharedString
  Rcpp::CharacterVector is(no_init(n));        // <is> tag

  // struct to vector
  for (size_t i = 0; i < n; ++i) {
    row_r[i] = x[i].row_r;
    c_r[i]   = x[i].c_r;
    c_s[i]   = x[i].c_s;
    c_t[i]   = x[i].c_t;
    v[i]     = x[i].v;
    f[i]     = x[i].f;
    f_t[i]   = x[i].f_t;
    f_ref[i] = x[i].f_ref;
    f_ca[i]  = x[i].f_ca;
    f_si[i]  = x[i].f_si;
    is[i]     = x[i].is;
  }

  // Assign and return a dataframe
  return Rcpp::wrap(Rcpp::DataFrame::create(
      Rcpp::Named("row_r") = row_r,
      Rcpp::Named("c_r")   = c_r,
      Rcpp::Named("c_s")   = c_s,
      Rcpp::Named("c_t")   = c_t,
      Rcpp::Named("v")     = v,
      Rcpp::Named("f")     = f,
      Rcpp::Named("f_t")   = f_t,
      Rcpp::Named("f_ref") = f_ref,
      Rcpp::Named("f_ca")  = f_ca,
      Rcpp::Named("f_si")  = f_si,
      Rcpp::Named("is")    = is
  )
  );
}
}

// pugixml defines. This creates the xmlptr
#include "pugixml.hpp"

typedef pugi::xml_document xmldoc;
typedef Rcpp::XPtr<xmldoc> XPtrXML;
