#ifndef TREEITEMCONTROL_H
#define TREEITEMCONTROL_H

#include <QVariant>

class TreeItemControl
{
public:
    explicit TreeItemControl(const QVector<QVariant> &data, TreeItemControl *parent = Q_NULLPTR);
    ~TreeItemControl();

    /*!
     * \brief addChild добавляет дочерний элемент
     * \param child дочерний элемент
     */
    void addChild(TreeItemControl *child);

    /*!
     * \brief insertChildren вставляет потомков
     * \param position
     * \param count
     * \param columns
     * \return
     */
    bool insertChildren(int position, int count, int columns);

    /*!
     * \brief insertColumns вставляет столбцы
     * \param position
     * \param columns
     * \return
     */
    bool insertColumns(int position, int columns);

    /*!
     * \brief removeChildren удаляет потомков
     * \param position
     * \param count
     * \return
     */
    bool removeChildren(int position, int count);

    /*!
     * \brief removeColumns удаляет столбцы
     * \param position
     * \param columns
     * \return
     */
    bool removeColumns(int position, int columns);

    /*!
     * \brief setData устанавливает данные
     * \param column
     * \param value
     * \return
     */
    bool setData(int column, const QVariant &value);

    /*!
     * \brief columnCount возвращает количество столбцов
     * \return количество
     */
    int columnCount() const;

    /*!
     * \brief childCount возвращает количество дочерних элементов
     * \return количество
     */
    int childCount() const;

    /*!
     * \brief row возвращает расположение элемента
     * \return строку элемента
     */
    int row() const;

    /*!
     * \brief data возвращает номер стоки эдемента
     * \param column столбец
     * \return данные
     */
    QVariant data(int column) const;

    /*!
     * \brief parent возвращает родительский элемент
     * \return элемент (если элемент корневой, то вернёт 0)
     */
    TreeItemControl *parent();

    /*!
     * \brief child возвращает дочерний элемент по номеру строки
     * \param row номер строки
     * \return дочернйи элемент
     */
    TreeItemControl *child(int row);

private:
    QList<TreeItemControl*> childItems;
    QVector<QVariant> itemData;
    TreeItemControl *parentItem = Q_NULLPTR;
};

#endif // TREEITEMCONTROL_H
