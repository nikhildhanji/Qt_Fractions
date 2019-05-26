#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_clear_button_clicked();

    void on_submit_button_clicked();

    void on_numerator_line_edit_1_editingFinished();

    void on_denominator_line_edit_1_editingFinished();

    void on_numerator_line_edit_2_editingFinished();

    void on_denominator_line_edit_2_editingFinished();

    void on_numerator_line_edit_1_selectionChanged();

    void on_denominator_line_edit_1_selectionChanged();

    void on_numerator_line_edit_2_selectionChanged();

    void on_denominator_line_edit_2_selectionChanged();

    void on_inverse_button_1_clicked();

    void on_inverse_button_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
