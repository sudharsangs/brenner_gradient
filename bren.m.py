# Automatically translated using m2cpp 2.0 on 2019-05-01 21:38:38
#
# encoding: utf-8
#
# Supplement file
#
# Valid inputs:
#
# uword   int     float   double cx_double
# uvec    ivec    fvec    vec    cx_vec
# urowvec irowvec frowvec rowvec cx_rowvec
# umat    imat    fmat    mat    cx_mat
# ucube   icube   fcube   cube   cx_cube
#
# char    string  struct  structs func_lambda

functions = {
  "calcbren" : {
             "DH" : "", # mat
             "DV" : "", # mat
             "FM" : "",
              "M" : "", # int
              "N" : "", # int
           "bren" : "",
        "handles" : "struct",
      "poutImage" : "",
  },
}
structs = {
  "handles" : {
    "brenDisp" : "",
  },
}
includes = [
  '#include "mconvert.h"',
  '#include <armadillo>',
  'using namespace arma ;',
]