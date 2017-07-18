#include "NoEditColumnDelegate.h"

NoEditColumnDelegate::NoEditColumnDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

QWidget *NoEditColumnDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(parent)
    Q_UNUSED(option)
    Q_UNUSED(index)

    return 0;
}
