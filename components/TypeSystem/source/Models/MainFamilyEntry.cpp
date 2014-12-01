#include "MainFamilyEntry.hpp"


using Geo::TypeSystem::Models::MainFamily;


MainFamily::
MainFamily(Geo::Domain::CurveType::Shared curveType):
  TreeEntry(curveType)
{

}


MainFamily::
~MainFamily()
{

}


QVariant
MainFamily::
data(int role, int column) const 
{
//
}
