#ifndef NOTE_H
#define NOTE_H
#include <QFileDialog>
#include <QMainWindow>
#include<QtCore>
#include<QtGui>
namespace Ui {
class note;
}

class note : public QMainWindow
{
    Q_OBJECT

public:
    explicit note(QWidget *parent = nullptr);
    ~note();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionSave_As_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

private:
    Ui::note *ui;
    QString file_path_;
};

#endif // NOTE_H
