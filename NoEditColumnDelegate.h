#ifndef NOEDITCOLUMNDELEGATE_H
#define NOEDITCOLUMNDELEGATE_H

#include <QStyledItemDelegate>

class NoEditColumnDelegate : public QStyledItemDelegate
{
public:
    NoEditColumnDelegate(QObject* parent = 0);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // NOEDITCOLUMNDELEGATE_H
