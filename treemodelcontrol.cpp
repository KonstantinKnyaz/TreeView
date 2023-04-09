#include "treemodelcontrol.h"


TreeModelControl::TreeModelControl(const QStringList &headers, const QString &data, QObject *parent) : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    if(headers.count() >= 2)
        rootData << headers.at(0) << headers.at(1);
    else
        rootData << "Заголовок" << "Описание";
    rootItem = new TreeItemControl(rootData);
    setModelData(data.split("\n"), rootItem);
}

TreeModelControl::~TreeModelControl()
{
    if(rootItem != Q_NULLPTR)
        delete rootItem;
}

QModelIndex TreeModelControl::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItemControl *parentItem;

    if(!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItemControl*>(parent.internalPointer());

    TreeItemControl *childeItem = parentItem->child(row);

    if(childeItem)
        return createIndex(row, column, childeItem);

    return QModelIndex();
}

QModelIndex TreeModelControl::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    TreeItemControl *childeItem = static_cast<TreeItemControl*>(child.internalPointer());
    TreeItemControl *parentItem = childeItem->parent();

    if(parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModelControl::rowCount(const QModelIndex &parent) const
{
    TreeItemControl *parentItem = getItem(parent);

    return parentItem->childCount();
}

int TreeModelControl::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return static_cast<TreeItemControl*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

QVariant TreeModelControl::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItemControl *item = static_cast<TreeItemControl*>(index.internalPointer());

    return item->data(index.column());
}

QVariant TreeModelControl::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

Qt::ItemFlags TreeModelControl::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

bool TreeModelControl::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItemControl *item = getItem(index);

    bool result = item->setData(index.column(), value);

    if (result) {
        emit dataChanged(index, index);
    }

    return result;
}

bool TreeModelControl::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result) {
        emit headerDataChanged(orientation, section, section);
    }

    return result;
}

bool TreeModelControl::insertRows(int row, int count, const QModelIndex &parent)
{
    TreeItemControl *parentItem = getItem(parent);

    bool success;

    beginInsertRows(parent, row, row + count - 1);

    success = parentItem->insertChildren(row, count, rootItem->columnCount());

    endInsertRows();

    return success;
}

bool TreeModelControl::insertColumns(int column, int count, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, column, column + count - 1);

    success = rootItem->insertColumns(column, count);

    endInsertColumns();

    return success;
}

bool TreeModelControl::removeRows(int row, int count, const QModelIndex &parent)
{
    TreeItemControl *parentItem = getItem(parent);

    bool success = true;

    beginRemoveRows(parent, row, row + count - 1);

    success = parentItem->removeChildren(row, count);

    endRemoveRows();

    return success;
}

bool TreeModelControl::removeColumns(int column, int count, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, column, column + count - 1);

    success = rootItem->removeColumns(column, count);

    endRemoveColumns();

    if (rootItem->columnCount() == 0) removeRows(0, rowCount());
        return success;
}

void TreeModelControl::setModelData(const QStringList &data, TreeItemControl *parent)
{
    QList<TreeItemControl*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;
    int number = 0;

    while (number < data.count()) {
        int position = 0;
        while (position < data[number].length()) {
            if (data[number].at(position) != ' ')
                break;
            position++;
        }

        QString lineData = data[number].mid(position).trimmed();
        if (!lineData.isEmpty()) {

            QStringList columnStrings = lineData.split(QLatin1Char('\t'), QString::SkipEmptyParts);

            QVector <QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            parents.last()->addChild(new TreeItemControl(columnData, parents.last()));
        }
        ++number;
    }
}

TreeItemControl *TreeModelControl::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItemControl *item = static_cast<TreeItemControl*>(index.internalPointer());
        if (item) return item;
    }

    return rootItem;
}
