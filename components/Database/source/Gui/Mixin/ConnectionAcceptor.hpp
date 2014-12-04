#ifndef Geo_Database_Mixin_ConnectionAcceptor_hpp
#define Geo_Database_Mixin_ConnectionAcceptor_hpp

#include <Connections/Connection.hpp>
#include <QWidget>

namespace Geo {
namespace Database {
namespace Gui {
namespace Mixin {
//

// some widget which takes Connection to process
class ConnectionAcceptor
{
public:
  virtual
  ~ConnectionAcceptor()
  {
  }

public slots:
  virtual void
  setConnection(Connections::Connection::Shared connection) = 0;
};

//
}
}
}
}

#endif // Geo_Database_Mixin_ConnectionAcceptor_hpp
