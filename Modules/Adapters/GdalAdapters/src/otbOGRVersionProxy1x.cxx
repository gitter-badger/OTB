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
#include "otbOGRVersionProxy.h"

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include "ogrsf_frmts.h"
#pragma GCC diagnostic pop
#else
#include "ogrsf_frmts.h"
#endif

namespace otb
{
namespace ogr
{
namespace version_proxy
{

GDALDatasetType * Open(const char * filename, bool readOnly)
{
  return OGRSFDriverRegistrar::Open(filename,!readOnly);
}

void Close(GDALDatasetType * dataset)
{
  OGRDataSource::DestroyDataSource(dataset);
}
  
GDALDatasetType * Create(GDALDriverType * driver, const char * name)
{
  GDALDatasetType * ds = driver->CreateDataSource(name);

  if(ds)  
    ds->SetDriver(driver);
  
  return ds;
}

bool Delete(GDALDriverType * driver, const char * name)
{
  OGRErr ret = driver->DeleteDataSource(name);

  return (ret == OGRERR_NONE);
}

GDALDriverType *  GetDriverByName(const char * name)
{
  return OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(name);
}

bool TestCapability(const GDALDriverType * driver, const GDALDatasetType *, const char * capability)
{
  // Class OGRDataSource is not const correct
  return const_cast<GDALDriverType * >(driver)->TestCapability(capability);
}

std::string GetDatasetClassName()
{
  return std::string("OGRDataSource");
}

std::string GetDriverClassName()
{
  return std::string("OGRSFDriver");
}

std::vector<std::string> GetFileListAsStringVector(GDALDatasetType * dataset)
{
  std::vector<std::string> ret;

  ret.push_back(std::string(dataset->GetName()));
  
  return ret;
}

bool SyncToDisk(GDALDatasetType * dataset)
{
  const OGRErr res= dataset->SyncToDisk();

  return (res == OGRERR_NONE);
}

std::vector<std::string> GetAvailableDriversAsStringVector()
{
  std::vector<std::string> ret;
  
  int nbDrivers = OGRSFDriverRegistrar::GetRegistrar()->GetDriverCount();
  
  for(int i = 0; i < nbDrivers;++i)
    {
    ret.push_back(OGRSFDriverRegistrar::GetRegistrar()->GetDriver(i)->GetName());
    }

  return ret;
}

}
}
} // end namespace
