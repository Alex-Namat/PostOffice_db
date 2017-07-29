#ifndef IDATTACHMENTDELEGAT_H
#define IDATTACHMENTDELEGAT_H

#include <QStyledItemDelegate>

class IdAttachmentDelegat : public QStyledItemDelegate
{
public:
    explicit IdAttachmentDelegat(QObject* parent = 0);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // IDATTACHMENTDELEGAT_H
