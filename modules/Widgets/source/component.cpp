#include "Implementation/ConnectionSettingsWidget.hpp"
#include "Implementation/KeywordWidget.hpp"

#include "Export.hpp"

#include <ComponentManager/ComponentRegistry>

extern "C" {
Widgets_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(Geo::Widgets::Implementation::KeywordWidget);
  REGISTER_TYPE(Geo::Widgets::Implementation::ConnectionSettingsWidget);
}
}
