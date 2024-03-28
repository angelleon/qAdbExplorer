#ifndef QADBEXPLORER_LISTVIEW_H
#define QADBEXPLORER_LISTVIEW_H

#include <QListView>
#include <QObject>

namespace qAdbExplorer {

class ListView : public QListView
{
    Q_OBJECT
public:
    ListView();
};

} // namespace qAdbExplorer

#endif // QADBEXPLORER_LISTVIEW_H
