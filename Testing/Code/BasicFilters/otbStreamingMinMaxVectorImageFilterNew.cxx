/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "itkExceptionObject.h"

#include "otbStreamingMinMaxVectorImageFilter.h"
#include "otbVectorImage.h"

int otbStreamingMinMaxVectorImageFilterNew(int argc, char * argv[])
{
  const unsigned int Dimension = 2;
  typedef unsigned char PixelType;

  typedef otb::VectorImage<PixelType, Dimension>               ImageType;
  typedef otb::StreamingMinMaxVectorImageFilter<ImageType> StreamingMinMaxVectorImageFilterType;

  // Instantiating object
  StreamingMinMaxVectorImageFilterType::Pointer object = StreamingMinMaxVectorImageFilterType::New();

  return EXIT_SUCCESS;
}
