// Automatically translated using m2cpp 2.0 on 2019-05-01 21:38:38

#ifndef CALCBREN_M_HPP
#define CALCBREN_M_HPP

#include "mconvert.h"
#include <armadillo>
using namespace arma ;

struct _Handles
{
  TYPE brenDisp ;
} ;

TYPE calcbren(_Handles handles)
{
  TYPE DH, DV, FM, M, N, _aux_TYPE_1, bren, poutImage ;
  _Handles handles ;
  poutImage = imread("pout.png") ;
  _aux_TYPE_1 = double(poutImage) ;
  M = _aux_TYPE_1.n_rows;
  N = _aux_TYPE_1.n_cols;
  
  DH = arma::zeros<mat>(M, N) ;
  DV = arma::zeros<mat>(M, N) ;
  DV.rows(m2cpp::fspan(1, 1, M-2)) = poutImage.rows(m2cpp::fspan(3, 1, poutImage.n_rows))-poutImage.rows(m2cpp::fspan(1, 1, poutImage.n_rows-2)) ;
  DH.cols(m2cpp::fspan(1, 1, N-2)) = poutImage.cols(m2cpp::fspan(3, 1, poutImage.n_cols))-poutImage.cols(m2cpp::fspan(1, 1, poutImage.n_cols-2)) ;
  FM = max(DH, DV) ;
  FM = arma::square(FM) ;
  bren = mean2(FM) ;
  set(handles.brenDisp, "String", num2str(bren)) ;
  return bren ;
}
#endif