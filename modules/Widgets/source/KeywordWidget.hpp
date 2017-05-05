#ifndef Geo_Widgets_KeywordWidget_hpp
#define Geo_Widgets_KeywordWidget_hpp

#include <QtCore/QStringList>
#include <QtWidgets/QWidget>

class QLineEdit;

namespace Geo {
namespace Widgets {
//

class KeywordWidget: public QWidget
{
  //Q_OBJECT
public:
  virtual
  ~KeywordWidget() {}

  virtual void
  setKeywords(QStringList keywordList) = 0;

  virtual QStringList
  keywords() const = 0;

signals:
  virtual void
  keywordAdded() = 0;

private slots:
  virtual void
  onTextChanged(QString const& text) =  0;
};

//
}
}
#endif //  Geo_Widgets_KeywordWidget_hpp
