#ifndef TREEMODELCONTROL_H
#define TREEMODELCONTROL_H

#include <QAbstractItemModel>

#include "treeitemcontrol.h"

class TreeModelControl : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TreeModelControl(const QStringList &headers, const QString &data, QObject *parent = Q_NULLPTR);
    ~TreeModelControl();

    // QAbstractItemModel interface
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    void setModelData(const QStringList &data, TreeItemControl *parent);

    TreeItemControl *rootItem = Q_NULLPTR;

    TreeItemControl *getItem(const QModelIndex &index) const;
};

#endif // TREEMODELCONTROL_H
