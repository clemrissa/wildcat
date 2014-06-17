#include "LogViewerWidget.hpp"

#include "RenderWidgets/BodyRenderWidget.hpp"
#include "RenderWidgets/HeaderRenderWidget.hpp"

#include "SectionControllers/MultiWellSectionController.hpp"
#include "SectionViews/MultiWellSectionView.hpp"

#include "Scalers/AxisScaler.hpp"
#include "Scalers/Scaler.hpp"

#include <QSplitter>
#include <QStatusBar>
#include <QVBoxLayout>

using Geo::LogViewer::LogViewerWidget;
using Geo::LogViewer::SectionControllers::AbstractSectionController;

struct LogViewerWidget::Private {
  RenderWidgets::HeaderRenderWidget* headerRenderWidget;
  RenderWidgets::BodyRenderWidget*   bodyRenderWidget;

  QSplitter* verticalSplitter;

  QStatusBar* statusBar;

  AbstractSectionController::Pointer rootSection;

  Scalers::Scaler::Pointer headerScaler;
  Scalers::Scaler::Pointer bodyScaler;
};

LogViewerWidget::
LogViewerWidget():
  _p(new Private)
{
  setWindowTitle("LogViewer");

  setMinimumSize(400, 400);

  _p->rootSection = SectionControllers::MultiWellSectionController::Pointer(
    new SectionControllers::MultiWellSectionController());

  double dotsPerInch = this->physicalDpiX();

  QSharedPointer<Scalers::AxisScaler> xScaler(new Scalers::AxisScaler(
                                                dotsPerInch, 0.6));

  QSharedPointer<Scalers::AxisScaler> yHeaderScaler(new Scalers::AxisScaler(
                                                      dotsPerInch, 1.0));

  QSharedPointer<Scalers::AxisScaler> yBodyScaler(new Scalers::AxisScaler(
                                                    dotsPerInch, 0.002));

  _p->headerScaler = Scalers::Scaler::Pointer(new Scalers::Scaler(xScaler,
                                                                  yHeaderScaler));
  _p->bodyScaler = Scalers::Scaler::Pointer(new Scalers::Scaler(xScaler,
                                                                yBodyScaler));
  _p->headerRenderWidget = new
                           RenderWidgets::
                           HeaderRenderWidget(_p->headerScaler, _p->rootSection);

  _p->bodyRenderWidget = new
                         RenderWidgets::
                         BodyRenderWidget(_p->bodyScaler, _p->rootSection);

  QVBoxLayout* layout = new
                        QVBoxLayout();

  layout->addWidget(_p->verticalSplitter = new QSplitter(Qt::Vertical));
  _p->verticalSplitter->addWidget(_p->headerRenderWidget);
  _p->verticalSplitter->addWidget(_p->bodyRenderWidget);
  _p->verticalSplitter->setStretchFactor(0, 1);
  _p->verticalSplitter->setStretchFactor(1, 7);

  this->setLayout(layout);

  // setStatusBar(_p->statusBar = new QStatusBar(this));
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  connect(xScaler.data(),       SIGNAL(scalerChanged()),
          _p->headerRenderWidget, SLOT(update()));
  connect(xScaler.data(),       SIGNAL(scalerChanged()),
          _p->bodyRenderWidget, SLOT(update()));

  connect(yHeaderScaler.data(), SIGNAL(scalerChanged()),
          _p->headerRenderWidget, SLOT(update()));

  connect(yBodyScaler.data(),   SIGNAL(scalerChanged()),
          _p->bodyRenderWidget, SLOT(update()));
}


LogViewerWidget::
~LogViewerWidget()
{
  delete _p;
}
