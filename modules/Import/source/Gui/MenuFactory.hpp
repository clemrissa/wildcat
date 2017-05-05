#ifndef Geo_Import_TreeWrapperMenuFactory_hpp
#define Geo_Import_TreeWrapperMenuFactory_hpp

class QMenu;

namespace Geo {
namespace Import {
namespace  TreeWrapper {
class WellInfoBase;
}
namespace Gui {
//

class TreeWrapperMenuFactory
{
public:
  static QMenu*
  getWellInformationBaseMenu(TreeWrapper::WellInfoBase* wellInfo,
                             int                        column);
};

//
}
}
}
#endif //  Geo_Import_TreeWrapperMenuFactory_hpp
