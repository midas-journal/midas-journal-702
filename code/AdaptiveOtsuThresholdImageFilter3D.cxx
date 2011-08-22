/*=========================================================================
  Author: $Author: krm15 $  // Author of last commit
  Version: $Rev: 743 $  // Revision of last commit
  Date: $Date: 2009-10-17 18:14:28 -0400 (Sat, 17 Oct 2009) $  // Date of last commit
=========================================================================*/

/*=========================================================================
 Authors: The GoFigure Dev. Team.
 at Megason Lab, Systems biology, Harvard Medical school, 2009

 Copyright (c) 2009, President and Fellows of Harvard College.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.
 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 Neither the name of the  President and Fellows of Harvard College
 nor the names of its contributors may be used to endorse or promote
 products derived from this software without specific prior written
 permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkAdaptiveOtsuThresholdImageFilter.h"

using namespace std;

int main(int argc, char**argv)
{
  if ( argc < 7 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " InputImage OutputImage radius numOfSamples numOfLevels numOfControlPts" << std::endl;
    return EXIT_FAILURE;
    }

  double radius = atof( argv[3] );

  const unsigned int Dimension = 3;

	typedef unsigned char PixelType;
	typedef itk::Image< PixelType, Dimension > ImageType;
  typedef ImageType::SizeType SizeType;
  typedef ImageType::SpacingType SpacingType;
  typedef SizeType::SizeValueType SizeValueType;
	typedef itk::ImageFileReader< ImageType > ReaderType;
  typedef itk::AdaptiveOtsuThresholdImageFilter< ImageType, ImageType > FilterType;
	typedef itk::ImageFileWriter< ImageType > WriterType;

	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName( argv[1] );
	reader->Update();
  SpacingType spacing = reader->GetOutput()->GetSpacing();
  SizeType size = reader->GetOutput()->GetLargestPossibleRegion().GetSize();

  SizeType m_radius;
  for( unsigned int i = 0; i < Dimension; i++ )
    {
    m_radius[i] = static_cast<SizeValueType>( radius/spacing[i] );
    }

  ImageType::Pointer output;
    {
    FilterType::Pointer filter = FilterType::New();
    filter->SetInput( reader->GetOutput() );
    filter->SetInsideValue( 255 );
    filter->SetOutsideValue( 0 );
    filter->SetNumberOfHistogramBins( 256 );
    filter->SetNumberOfControlPoints( atoi( argv[6] ) );
    filter->SetNumberOfLevels( atoi( argv[5] ) );
    filter->SetNumberOfSamples( atoi( argv[4] ) );
    filter->SetRadius( m_radius );
    filter->Update();

    output = filter->GetOutput();
    output->DisconnectPipeline();
    }

  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( output );
  writer->SetFileName( argv[2] );
  writer->Update();

	return EXIT_SUCCESS;
}
