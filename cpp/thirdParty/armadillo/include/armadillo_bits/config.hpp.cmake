// Copyright (C) 2010 NICTA and the authors listed below
// http://nicta.com.au
// 
// Authors:
// - Conrad Sanderson (conradsand at ieee dot org)
// 
// This file is part of the Armadillo C++ library.
// It is provided without any warranty of fitness
// for any purpose. You can redistribute this file
// and/or modify it under the terms of the GNU
// Lesser General Public License (LGPL) as published
// by the Free Software Foundation, either version 3
// of the License or (at your option) any later version.
// (see http://www.opensource.org/licenses for more info)



#if !defined(ARMA_USE_LAPACK)
#cmakedefine ARMA_USE_LAPACK
#endif

#if !defined(ARMA_USE_BLAS)
#cmakedefine ARMA_USE_BLAS
#endif

#cmakedefine ARMA_USE_ATLAS
#define ARMA_ATLAS_INCLUDE_DIR ${ARMA_ATLAS_INCLUDE_DIR}/
//// If you're using ATLAS and the compiler can't find cblas.h and/or clapack.h
//// uncomment the above define and specify the appropriate include directory.
//// Make sure the directory has a trailing /

#cmakedefine ARMA_USE_BOOST
#cmakedefine ARMA_USE_BOOST_DATE

#cmakedefine ARMA_HAVE_STD_ISFINITE
#cmakedefine ARMA_HAVE_STD_ISINF
#cmakedefine ARMA_HAVE_STD_ISNAN
#cmakedefine ARMA_HAVE_STD_SNPRINTF

#cmakedefine ARMA_HAVE_LOG1P
#cmakedefine ARMA_HAVE_GETTIMEOFDAY

#cmakedefine ARMA_EXTRA_DEBUG
#cmakedefine ARMA_NO_DEBUG
