#ifndef CAFE_RAPOR_VIEW_H
#define CAFE_RAPOR_VIEW_H

#include <QGraphicsView>
#include <QObject>

namespace Cafe {
namespace Rapor {

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View();
};

} // namespace Rapor
} // namespace Cafe

#endif // CAFE_RAPOR_VIEW_H
