#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QTranslator>

#include "treemodelcontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addStolbBtn_clicked();

    void on_delStolbBtn_clicked();

    void on_addStrBtn_clicked();

    void on_delStrBtn_clicked();

    void on_addHeadBtn_clicked();

    void on_action_2_triggered();

    void on_action_3_triggered();

private:
    Ui::MainWindow *ui;
    //! Поле для текста с красной границей
    const QString BorderRed = QString("QTreeView {  border: 1px solid red;"
                                      "border-radius: 2px;"
                                      "margin-left: 1px;"
                                      "height:28;"
                                      "}");
    //! Поле для текста с серой границей
    const QString BorderGrey = QString("QTreeView {  border: 1px solid grey;"
                                       "border-radius: 2px;"
                                       "margin-left: 1px;"
                                       "height:28;"
                                       "}");

    TreeModelControl *modelOne = Q_NULLPTR;
    TreeModelControl *modelTwo = Q_NULLPTR;
    TreeModelControl *modelThree = Q_NULLPTR;
    TreeModelControl *modelSecondOne = Q_NULLPTR;
    TreeModelControl *modelSecondTwo = Q_NULLPTR;
    TreeModelControl *modelSecondThree = Q_NULLPTR;
    TreeModelControl *modelSecondFor = Q_NULLPTR;

    QTreeView *currenTree = Q_NULLPTR;

    QTranslator qTranslator;

    void setAllBorderGrey();

    void resizeToContent(QTreeView *treeView = Q_NULLPTR);

    bool eventFilter(QObject *watched, QEvent *event) override;

    void changeEvent(QEvent *event) override;
};
#endif // MAINWINDOW_H
