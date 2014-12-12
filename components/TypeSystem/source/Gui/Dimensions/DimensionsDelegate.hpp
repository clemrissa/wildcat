#ifndef Geo_TypeSystem_Gui_Dimensions_DimensionsDelegate_hpp
#define Geo_TypeSystem_Gui_Dimensions_DimensionsDelegate_hpp

#include <QtWidgets/QStyledItemDelegate>

#include <Domain/Dimensions>

namespace Geo {
namespace TypeSystem {
namespace Gui {
//

class DimensionsDelegate: public QWidget
{
  Q_OBJECT

public:
  DimensionsDelegate(Domain::Dimensions& dimensions,
                     QWidget*            parent = nullptr);

private:
  void
  setupUi();

private:
  Domain::Dimensions& _dimensions;
};

//
} // namespace Gui
} // namespace TypeSystem
} // namespace Geo

#endif // Geo_TypeSystem_Gui_Dimensions_DimensionsDelegate_hpp
