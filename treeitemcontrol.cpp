#include "treeitemcontrol.h"

TreeItemControl::TreeItemControl(const QVector<QVariant> &data, TreeItemControl *parent)
    : itemData(data),
      parentItem(parent)
{

}

TreeItemControl::~TreeItemControl()
{
    if(!childItems.isEmpty())
        qDeleteAll(childItems);
}

void TreeItemControl::addChild(TreeItemControl *child)
{
    childItems.append(child);
}

bool TreeItemControl::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size()) return false;
    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        TreeItemControl *item = new TreeItemControl(data, this);
        childItems.insert(position, item);
    }
    return true;
}

bool TreeItemControl::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.count())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach (TreeItemControl *child, childItems) child->insertColumns(position, columns);

    return true;
}

bool TreeItemControl::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.count())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}

bool TreeItemControl::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.removeAt(position);

    foreach (TreeItemControl *child, childItems)
        child->removeColumns(position, columns);

    return true;
}

bool TreeItemControl::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}

int TreeItemControl::columnCount() const
{
    return itemData.count();
}

int TreeItemControl::childCount() const
{
    return childItems.count();
}

int TreeItemControl::row() const
{
    if(parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItemControl*>(this));
    return 0;
}

QVariant TreeItemControl::data(int column) const
{
    if(column < 0 || column >= itemData.size())
        return QVariant();
    return itemData.at(column);
}

TreeItemControl *TreeItemControl::parent()
{
    return parentItem;
}

TreeItemControl *TreeItemControl::child(int row)
{
    if(row < 0 || row >= childItems.count())
        return Q_NULLPTR;
    return childItems.at(row);
}
