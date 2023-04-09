#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Главное окно");
    QString programmPath = qApp->applicationDirPath();

    programmPath.append("/QtLanguage_en.qm");

    qDebug() << programmPath;
    qTranslator.load(programmPath);
    qApp->installTranslator(&qTranslator);

    setAllBorderGrey();

    QString data = "";

    QFile file("E:/Documents/build-TreeViewTest-Desktop_Qt_5_14_2_MinGW_64_bit-Debug/debug/default.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        data = file.readAll();
        file.close();
    }

    QStringList headers;
    headers << tr("Заголовок") << tr("Описание");

    modelOne = new TreeModelControl(headers, data, this);
    modelTwo = new TreeModelControl(headers, data, this);
    modelThree = new TreeModelControl(headers, data, this);
    modelSecondOne = new TreeModelControl(headers, data, this);
    modelSecondTwo = new TreeModelControl(headers, data, this);
    modelSecondThree = new TreeModelControl(headers, data, this);
    modelSecondFor = new TreeModelControl(headers, data, this);

    ui->treeFOne->setModel(modelOne);
    ui->treeFTwo->setModel(modelTwo);
    ui->treeViewFThree->setModel(modelThree);
    ui->treeFTOne->setModel(modelSecondOne);
    ui->treeFTTwo->setModel(modelSecondTwo);
    ui->treeFTThree->setModel(modelSecondThree);
    ui->treeFTFor->setModel(modelSecondFor);

    QList<QTreeView*> treeList;

    treeList << ui->treeFOne << ui->treeFTwo << ui->treeViewFThree << ui->treeFTOne << ui->treeFTTwo << ui->treeFTThree << ui->treeFTFor;

    for(int i = 0; i < treeList.count(); i++) {
        resizeToContent(treeList.at(i));
        treeList.at(i)->viewport()->setMouseTracking(true);
        treeList.at(i)->viewport()->installEventFilter(this);
        treeList.at(i)->setToolTip("Нажмите левую кнопку мыши для возможности редактирования");
        treeList.at(i)->setSelectionMode(QAbstractItemView::MultiSelection);
    }
}

MainWindow::~MainWindow()
{
    if(modelOne != Q_NULLPTR) {
        delete modelOne;
    }
    if(modelTwo != Q_NULLPTR) {
        delete modelTwo;
    }
    if(modelThree != Q_NULLPTR) {
        delete modelThree;
    }
    if(modelSecondOne != Q_NULLPTR) {
        delete modelSecondOne;
    }
    if(modelSecondTwo != Q_NULLPTR) {
        delete modelSecondTwo;
    }
    if(modelSecondThree != Q_NULLPTR) {
        delete modelSecondThree;
    }
    if(modelSecondFor != Q_NULLPTR) {
        delete modelSecondFor;
    }
    delete ui;
}

void MainWindow::setAllBorderGrey()
{
    ui->treeFOne->setStyleSheet(BorderGrey);
    ui->treeFTwo->setStyleSheet(BorderGrey);
    ui->treeViewFThree->setStyleSheet(BorderGrey);
    ui->treeFTOne->setStyleSheet(BorderGrey);
    ui->treeFTTwo->setStyleSheet(BorderGrey);
    ui->treeFTThree->setStyleSheet(BorderGrey);
    ui->treeFTFor->setStyleSheet(BorderGrey);
}

void MainWindow::resizeToContent(QTreeView *treeView)
{
    QTreeView *tree = treeView;
    if(tree == Q_NULLPTR)
        tree = currenTree;

    for(int col = 0; col < tree->model()->columnCount(); col++)
        tree->resizeColumnToContents(col);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->treeFOne->viewport()) {
        if(event->type() == QEvent::MouseButtonPress) {
            setAllBorderGrey();
            ui->treeFOne->setStyleSheet(BorderRed);
            currenTree = ui->treeFOne;
        }
    }

    if(watched == ui->treeFTwo->viewport()) {
        if(event->type() == QEvent::MouseButtonPress) {
            setAllBorderGrey();
            ui->treeFTwo->setStyleSheet(BorderRed);
            currenTree = ui->treeFTwo;
        }
    }

    if(watched == ui->treeViewFThree->viewport()) {
        if(event->type() == QEvent::MouseButtonPress) {
            setAllBorderGrey();
            ui->treeViewFThree->setStyleSheet(BorderRed);
            currenTree = ui->treeViewFThree;
        }
    }

    if(watched == ui->treeFTOne->viewport()) {
        if(event->type() == QEvent::MouseButtonPress) {
            setAllBorderGrey();
            ui->treeFTOne->setStyleSheet(BorderRed);
            currenTree = ui->treeFTOne;
        }
    }

    if(watched == ui->treeFTTwo->viewport()) {
        if(event->type() == QEvent::MouseButtonPress) {
            setAllBorderGrey();
            ui->treeFTTwo->setStyleSheet(BorderRed);
            currenTree = ui->treeFTTwo;
        }
    }

    if(watched == ui->treeFTThree->viewport()) {
        if(event->type() == QEvent::MouseButtonPress) {
            setAllBorderGrey();
            ui->treeFTThree->setStyleSheet(BorderRed);
            currenTree = ui->treeFTThree;
        }
    }

    if(watched == ui->treeFTFor->viewport()) {
        if(event->type() == QEvent::MouseButtonPress) {
            setAllBorderGrey();
            ui->treeFTFor->setStyleSheet(BorderRed);
            currenTree = ui->treeFTFor;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

void MainWindow::on_addStolbBtn_clicked()
{
    if(currenTree == Q_NULLPTR)
        return;

    QString elemCount = ui->elementCountLine->text();
    int colEl = 1;
    if(elemCount.toInt() != 0)
        colEl = elemCount.toInt();

    for(int i = 0; i < colEl; i++) {

        QAbstractItemModel *treeModel = currenTree->model();
        int column = currenTree->selectionModel()->currentIndex().column();
        int colCount = treeModel->columnCount();
        int rowCount = treeModel->rowCount();
        bool changed = treeModel->insertColumn(column + 1);
        if (changed)
            treeModel->setHeaderData(column + 1, Qt::Horizontal, QVariant(QString("Col%1 Row%2").arg(colCount+1).arg(rowCount)), Qt::EditRole);
    }
    resizeToContent();
}

void MainWindow::on_delStolbBtn_clicked()
{
    if(currenTree == Q_NULLPTR)
        return;

    QAbstractItemModel *treeModel = currenTree->model();
    int column = currenTree->selectionModel()->currentIndex().column();
    treeModel->removeColumn(column);

    resizeToContent();
}

void MainWindow::on_addStrBtn_clicked()
{
    if(currenTree == Q_NULLPTR)
        return;

    QModelIndex index = currenTree->selectionModel()->currentIndex();
    QAbstractItemModel *treeModel = currenTree->model();

    QString elemCount = ui->elementCountLine->text();
    int colEl = 1;
    if(elemCount.toInt() != 0)
        colEl = elemCount.toInt();

    for(int i = 0; i < colEl; i++) {
        if (!treeModel->insertRow(index.row()+1, index.parent()))
            return;

        int colCount = treeModel->columnCount();
        int rowCount = treeModel->rowCount();

        for (int column = 0; column < treeModel->columnCount(index.parent()); ++column) {
            QModelIndex child = treeModel->index(index.row()+1, column, index.parent());
            treeModel->setData(child, QVariant(QString("Col%1 Row%2").arg(colCount).arg(rowCount+1)), Qt::EditRole);
        }
    }
    resizeToContent();
}

void MainWindow::on_delStrBtn_clicked()
{
    if(currenTree == Q_NULLPTR)
        return;

    QModelIndexList modelList = currenTree->selectionModel()->selectedIndexes();
    QAbstractItemModel *treeModel = currenTree->model();
    for(int i = modelList.count(); i > 0; i--) {
        QModelIndex index = modelList.at(i-1);
        treeModel->removeRow(index.row(), index.parent());
    }

    resizeToContent();
}

void MainWindow::on_addHeadBtn_clicked()
{
    if(currenTree == Q_NULLPTR)
        return;

    QModelIndex index = currenTree->selectionModel()->currentIndex();

    if(!index.isValid())
        return;

    QAbstractItemModel *treeModel = currenTree->model();

    if(treeModel->columnCount(index) == 0) {
        if(!treeModel->insertColumn(0, index))
            return;
    }

    if(!treeModel->insertRow(0, index))
        return;

    for(int col = 0; col < treeModel->columnCount(); col++) {
        QModelIndex childIndex = treeModel->index(0, col, index);
        treeModel->setData(childIndex, QVariant("Подзаголовок"), Qt::EditRole);

        if(!treeModel->headerData(col, Qt::Horizontal).isValid())
            treeModel->setHeaderData(col, Qt::Horizontal, QVariant("Подзаголовок"), Qt::EditRole);
    }

    currenTree->selectionModel()->setCurrentIndex(treeModel->index(0, 0, index), QItemSelectionModel::ClearAndSelect);

    resizeToContent();
}

void MainWindow::on_action_2_triggered()
{
    qTranslator.load(QString("QtLanguage_") + QString("ru"));
    qApp->installTranslator(&qTranslator);
}

void MainWindow::on_action_3_triggered()
{
    QString programmPath = qApp->applicationDirPath();

    programmPath.append("/QtLanguage_en.qm");
    qTranslator.load(programmPath);
    qApp->installTranslator(&qTranslator);
}
