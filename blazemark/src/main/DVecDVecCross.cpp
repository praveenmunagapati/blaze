//=================================================================================================
/*!
//  \file src/blaze/DVecDVecCross.cpp
//  \brief Source file for the dense vector/dense vector cross product benchmark
//
//  Copyright (C) 2013 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <blaze/math/Functions.h>
#include <blaze/math/Infinity.h>
#include <blaze/math/StaticVector.h>
#include <blaze/util/AlignedAllocator.h>
#include <blaze/util/Random.h>
#include <blaze/util/Timing.h>
#include <blazemark/armadillo/DVecDVecCross.h>
#include <blazemark/blaze/DVecDVecCross.h>
#include <blazemark/blaze/init/StaticVector.h>
#include <blazemark/clike/DVecDVecCross.h>
#include <blazemark/eigen/DVecDVecCross.h>
#include <blazemark/system/Armadillo.h>
#include <blazemark/system/Config.h>
#include <blazemark/system/Eigen.h>
#include <blazemark/system/Types.h>
#include <blazemark/util/Benchmarks.h>
#include <blazemark/util/Parser.h>
#include <blazemark/util/StaticDenseRun.h>


//*************************************************************************************************
// Using declarations
//*************************************************************************************************

using blazemark::Benchmarks;
using blazemark::Parser;
using blazemark::StaticDenseRun;




//=================================================================================================
//
//  TYPE DEFINITIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Type of a benchmark run.
//
// This type definition specifies the type of a single benchmark run for the dense vector/dense
// vector cross product benchmark.
*/
typedef StaticDenseRun<3UL>  Run;
//*************************************************************************************************




//=================================================================================================
//
//  UTILITY FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Estimating the necessary number of steps for each benchmark.
//
// \param run The parameters for the benchmark run.
// \return void
//
// This function estimates the necessary number of steps for the given benchmark based on the
// performance of the Blaze library.
*/
void estimateSteps( Run& run )
{
   using blazemark::element_t;
   using blaze::columnVector;

   typedef blaze::StaticVector<element_t,3UL,columnVector>  VectorType;
   typedef blaze::AlignedAllocator<VectorType>              AllocatorType;

   blaze::setSeed( blazemark::seed );

   const size_t N( run.getSize() );

   std::vector< VectorType, AllocatorType > a( N ), b( N ), c( N );
   blaze::timing::WcTimer timer;
   double wct( 0.0 );
   size_t steps( 1UL );

   blazemark::blaze::init( a );
   blazemark::blaze::init( b );

   while( true ) {
      timer.start();
      for( size_t step=0UL, i=0UL; step<steps; ++step, ++i ) {
         if( i == N ) i = 0UL;
         c[i] = a[i] % b[i];
      }
      timer.end();
      wct = timer.last();
      if( wct >= 0.2 ) break;
      steps *= 2UL;
   }

   for( size_t i=0UL; i<N; ++i )
      if( c[i].size() != 3UL )
         std::cerr << " Line " << __LINE__ << ": ERROR detected!!!\n";

   run.setSteps( blaze::max( 1UL, ( blazemark::runtime * steps ) / timer.last() ) );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Estimating the necessary number of floating point operations.
//
// \param run The parameters for the benchmark run.
// \return void
//
// This function estimates the number of floating point operations required for a single
// computation of the (composite) arithmetic operation.
*/
void estimateFlops( Run& run )
{
   run.setFlops( 9UL );
}
//*************************************************************************************************




//=================================================================================================
//
//  BENCHMARK FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Dense vector/dense vector cross product benchmark function.
//
// \param runs The specified benchmark runs.
// \param benchmarks The selection of benchmarks.
// \return void
*/
void dvecdveccross( std::vector<Run>& runs, Benchmarks benchmarks )
{
   std::cout << std::left;

   std::sort( runs.begin(), runs.end() );

   size_t slowSize( blaze::inf );
   for( std::vector<Run>::iterator run=runs.begin(); run!=runs.end(); ++run )
   {
      estimateFlops( *run );

      if( run->getSteps() == 0UL ) {
         if( run->getSize() < slowSize ) {
            estimateSteps( *run );
            if( run->getSteps() == 1UL )
               slowSize = run->getSize();
         }
         else run->setSteps( 1UL );
      }
   }

   if( benchmarks.runClike ) {
      std::cout << "   C-like implementation [MFlop/s]:\n";
      for( std::vector<Run>::iterator run=runs.begin(); run!=runs.end(); ++run ) {
         const size_t N    ( run->getNumber() );
         const size_t steps( run->getSteps()  );
         run->setClikeResult( blazemark::clike::dvecdveccross( N, steps ) );
         const double mflops( run->getFlops() * steps / run->getClikeResult() / 1E6 );
         std::cout << "     " << std::setw(12) << N << mflops << std::endl;
      }
   }

   if( benchmarks.runBlaze ) {
      std::cout << "   Blaze [MFlop/s]:\n";
      for( std::vector<Run>::iterator run=runs.begin(); run!=runs.end(); ++run ) {
         const size_t N    ( run->getNumber() );
         const size_t steps( run->getSteps()  );
         run->setBlazeResult( blazemark::blaze::dvecdveccross( N, steps ) );
         const double mflops( run->getFlops() * steps / run->getBlazeResult() / 1E6 );
         std::cout << "     " << std::setw(12) << N << mflops << std::endl;
      }
   }

#if BLAZEMARK_ARMADILLO_MODE
   if( benchmarks.runArmadillo ) {
      std::cout << "   Armadillo [MFlop/s]:\n";
      for( std::vector<Run>::iterator run=runs.begin(); run!=runs.end(); ++run ) {
         const size_t N    ( run->getNumber() );
         const size_t steps( run->getSteps()  );
         run->setArmadilloResult( blazemark::armadillo::dvecdveccross( N, steps ) );
         const double mflops( run->getFlops() * steps / run->getArmadilloResult() / 1E6 );
         std::cout << "     " << std::setw(12) << N << mflops << std::endl;
      }
   }
#endif

#if BLAZEMARK_EIGEN_MODE
   if( benchmarks.runEigen ) {
      std::cout << "   Eigen [MFlop/s]:\n";
      for( std::vector<Run>::iterator run=runs.begin(); run!=runs.end(); ++run ) {
         const size_t N    ( run->getNumber() );
         const size_t steps( run->getSteps()  );
         run->setEigenResult( blazemark::eigen::dvecdveccross( N, steps ) );
         const double mflops( run->getFlops() * steps / run->getEigenResult() / 1E6 );
         std::cout << "     " << std::setw(12) << N << mflops << std::endl;
      }
   }
#endif

   for( std::vector<Run>::iterator run=runs.begin(); run!=runs.end(); ++run ) {
      std::cout << *run;
   }
}
//*************************************************************************************************




//=================================================================================================
//
//  MAIN FUNCTION
//
//=================================================================================================

//*************************************************************************************************
/*!\brief The main function for the dense vector/dense vector cross product benchmark.
//
// \param argc The total number of command line arguments.
// \param argv The array of command line arguments.
// \return void
*/
int main( int argc, char** argv )
{
   std::cout << "\n Dense Vector/Dense Vector Cross Product:\n";

   Benchmarks benchmarks;

   try {
      parseCommandLineArguments( argc, argv, benchmarks );
   }
   catch( std::exception& ex ) {
      std::cerr << "   " << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   const std::string installPath( INSTALL_PATH );
   const std::string parameterFile( installPath + "/params/dvecdveccross.prm" );
   Parser<Run> parser;
   std::vector<Run> runs;

   try {
      parser.parse( parameterFile.c_str(), runs );
   }
   catch( std::exception& ex ) {
      std::cerr << "   Error during parameter extraction: " << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   try {
      dvecdveccross( runs, benchmarks );
   }
   catch( std::exception& ex ) {
      std::cerr << "   Error during benchmark execution: " << ex.what() << "\n";
      return EXIT_FAILURE;
   }
}
//*************************************************************************************************
