#include "ConnectionSettingsWidget.hpp"
#include "KeywordWidget.hpp"

#include "WidgetsExport.hpp"

#include <ComponentManager/ComponentRegistry>

extern "C" {
Widgets_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(Geo::Widgets::KeywordWidget);
  REGISTER_TYPE(Geo::Widgets::ConnectionSettingsWidget);
}
}
