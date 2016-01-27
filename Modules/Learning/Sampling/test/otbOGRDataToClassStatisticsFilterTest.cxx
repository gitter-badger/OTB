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

#include "otbOGRDataToClassStatisticsFilter.h"
#include "otbVectorImage.h"
#include "otbImage.h"

int otbOGRDataToClassStatisticsFilterNew(int itkNotUsed(argc), char* itkNotUsed(argv) [])
{
  typedef otb::VectorImage<float> InputImageType;
  typedef otb::Image<unsigned char> MaskImageType;
  typedef otb::OGRDataToClassStatisticsFilter<InputImageType,MaskImageType> FilterType;
  
  FilterType::Pointer filter = FilterType::New();
  std::cout << filter << std::endl;
  return EXIT_SUCCESS;
}
