#include <iostream>
#include <climits> // for INT_MAX limits
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <QInputDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fraction.h"
#include "fraction_util.h"
namespace Arith{
    enum arith_op {Add = 1, Subtract, Multiply, Divide};
    static const arith_op all[] = { Add, Subtract, Multiply, Divide};
    static inline std::string get(arith_op e)
    {
        switch (e)
        {
            case Add:
                return "Add";
            case Subtract:
                return "Sub";
            case Multiply:
                return "Mul";
            default:
                return "Div";
        }
    }
}
namespace Logical{
    enum log_op {Greater = 1, Less, Equals, Not_Equals};
    static const log_op all[] = { Greater, Less, Equals, Not_Equals};

    static inline std::string get(log_op e)
    {
        switch (e)
        {
            case Greater:
                return "Greater";
            case Less:
                return "Less";
            case Equals:
                return "Equals";
            default:
                return "!Equals";
        }
    }
}
void setPlaceHolderText(Ui::MainWindow *ui){
    ui->numerator_line_edit_1->setPlaceholderText(" [0-9]*");
    ui->denominator_line_edit_1->setPlaceholderText(" [0-9]*");
    ui->numerator_line_edit_2->setPlaceholderText(" [0-9]*");
    ui->denominator_line_edit_2->setPlaceholderText(" [0-9]*");
}

bool lineEditsEmpty(Ui::MainWindow *ui){
 return !(ui->numerator_line_edit_1->text().isEmpty()) &&
            !(ui->denominator_line_edit_1->text().isEmpty()) &&
                !(ui->numerator_line_edit_2->text().isEmpty()) &&
                    !(ui->denominator_line_edit_2->text().isEmpty()) ;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setFixedSize(403,300);

    QPixmap pic("./printable-fraction-bar-strips_60030.jpg");
    ui->pic_label->setPixmap(pic);
    ui->pic_label->setScaledContents(true);
    ui->arith_op_combo_box->addItem("      ");
    for(auto e: Arith::all)
       ui->arith_op_combo_box->addItem(QString::fromStdString(Arith::get(e)));

    ui->log_op_combo_box->addItem("   ");
    for(auto e: Logical::all)
       ui->log_op_combo_box->addItem(QString::fromStdString(Logical::get(e)));

    ui->submit_button->setEnabled(false);
    setPlaceHolderText(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clear_button_clicked()
{
    ui->numerator_line_edit_1->clear();
    ui->denominator_line_edit_1->clear();
    ui->numerator_line_edit_2->clear();
    ui->denominator_line_edit_2->clear();
    ui->text_edit->clear();
    ui->arith_op_combo_box->setCurrentIndex(0);
    ui->log_op_combo_box->setCurrentIndex(0);
    ui->submit_button->setEnabled(false);
    setPlaceHolderText(ui);
}

Fraction getFractionFromUI(QLineEdit* ptr_1,QLineEdit* ptr_2 )throw (std::invalid_argument){
    std::string str_num =  ptr_1->text().toStdString();
    std::string str_den = ptr_2->text().toStdString();
    int n = 0;
    int d = 1;
    try{
        n =  std::stoi( str_num );
    }
    catch(const std::invalid_argument& ia){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","Invalid argument for numerator or denomiator!");
        ptr_1->clear();
        throw ia;
    }
    try{
        d =  std::stoi( str_den );
    }
    catch(const std::invalid_argument& ia){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","Invalid argument for numerator or denomiator!");
        ptr_2->clear();
        throw ia;
    }
    try{
        Fraction f{n,d};
        return f;
    }
    catch(const std::invalid_argument& ia){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error",ia.what());
        ptr_2->clear();
        throw ia;
    }
}

void MainWindow::on_submit_button_clicked()
{

    try{
         Fraction f1 = getFractionFromUI(ui->numerator_line_edit_1,ui->denominator_line_edit_1);
         Fraction f2 = getFractionFromUI(ui->numerator_line_edit_2,ui->denominator_line_edit_2);
         ui->text_edit->clear();

         std::string str_f1 = "Fraction#1: ";
         str_f1.append(to_string(f1));
         std::string str_red_f1 = "Fraction#1 (reduced form): ";
         str_red_f1.append(stringify(f1));


         ui->text_edit->append(QString::fromStdString(str_f1));
         ui->text_edit->append(QString::fromStdString(str_red_f1));


         std::string str_f2 = "Fraction#2: ";
         str_f2.append(to_string(f2));
         std::string str_red_f2 = "Fraction#2 (reduced form): ";
         str_red_f2.append(stringify(f2));

         ui->text_edit->append(QString::fromStdString(str_f2));
         ui->text_edit->append(QString::fromStdString(str_red_f2));

         int arith_op_idx = ui->arith_op_combo_box->currentIndex();
         if(arith_op_idx!=0){
            ui->text_edit->append( "Arithmetic :");

            std::string str_arith_op = Arith::get(static_cast<Arith::arith_op>(arith_op_idx));
            if(str_arith_op=="Add"){
                std::string f1_plus_f2 = to_string(f1).append(" + ").append(to_string(f2)).append(" = ").append(stringify(f1+f2));
                ui->text_edit->append(QString::fromStdString(f1_plus_f2));
            }else if(str_arith_op=="Sub"){
                std::string f1_minus_f2 = to_string(f1).append(" - ").append(to_string(f2)).append(" = ").append(stringify(f1-f2));
                ui->text_edit->append(QString::fromStdString(f1_minus_f2));
            }else if(str_arith_op=="Mul"){
                std::string f1_times_f2 = to_string(f1).append(" x ").append(to_string(f2)).append(" = ").append(stringify(f1*f2));
                ui->text_edit->append(QString::fromStdString(f1_times_f2));
            }else if(str_arith_op=="Div"){
                std::string f1_divide_f2 = to_string(f1).append(" ÷ ").append(to_string(f2)).append(" = ").append(stringify(f1/f2));
                ui->text_edit->append(QString::fromStdString(f1_divide_f2));
            }
         }
         int log_op_idx = ui->log_op_combo_box->currentIndex();
         if(log_op_idx!=0){
           ui->text_edit->append("Logical :");

           std::string str_log_op = Logical::get(static_cast<Logical::log_op>(log_op_idx));
           if(str_log_op=="Greater"){
               std::string f1_greater_than_f2 = to_string(f1).append(" > ").append(to_string(f2)).append(" = ").append(f1>f2?"True":"False");
               ui->text_edit->append(QString::fromStdString(f1_greater_than_f2));
           }else if(str_log_op=="Less"){
               std::string f1_less_than_f2 = to_string(f1).append(" < ").append(to_string(f2)).append(" = ").append(f1<f2?"True":"False");
               ui->text_edit->append(QString::fromStdString(f1_less_than_f2));
           }else if(str_log_op=="Equals"){
               std::string f1_eqauls_f2 = to_string(f1).append(" == ").append(to_string(f2)).append(" = ").append(f1==f2?"True":"False");
               ui->text_edit->append(QString::fromStdString(f1_eqauls_f2));
           }else if(str_log_op=="!Equals"){
               std::string f1_not_equals_f2 = to_string(f1).append(" != ").append(to_string(f2)).append(" = ").append(f1!=f2?"True":"False");
               ui->text_edit->append(QString::fromStdString(f1_not_equals_f2));
           }
         }
    }
    catch(const std::invalid_argument& ia){
        std::cout<<ia.what()<<std::endl;
    }
}

void MainWindow::on_numerator_line_edit_1_editingFinished()
{
    ui->submit_button->setEnabled(lineEditsEmpty(ui));
}

void MainWindow::on_denominator_line_edit_1_editingFinished()
{
    ui->submit_button->setEnabled(lineEditsEmpty(ui));
}

void MainWindow::on_numerator_line_edit_2_editingFinished()
{
    ui->submit_button->setEnabled(lineEditsEmpty(ui));
}

void MainWindow::on_denominator_line_edit_2_editingFinished()
{
    ui->submit_button->setEnabled(lineEditsEmpty(ui));
}

void MainWindow::on_numerator_line_edit_1_selectionChanged()
{
    ui->submit_button->setEnabled(lineEditsEmpty(ui));
}

void MainWindow::on_denominator_line_edit_1_selectionChanged()
{
    ui->submit_button->setEnabled(lineEditsEmpty(ui));
}

void MainWindow::on_numerator_line_edit_2_selectionChanged()
{
    ui->submit_button->setEnabled(lineEditsEmpty(ui));
}

void MainWindow::on_denominator_line_edit_2_selectionChanged()
{
    ui->submit_button->setEnabled(lineEditsEmpty(ui));
}

void MainWindow::on_inverse_button_1_clicked()
{
  if(!(ui->numerator_line_edit_1->text().isEmpty()) &&
       !(ui->denominator_line_edit_1->text().isEmpty())){
      QString s1 = ui->numerator_line_edit_1->text();
      ui->numerator_line_edit_1->setText(ui->denominator_line_edit_1->text());
      ui->denominator_line_edit_1->setText(s1);
  }
}

void MainWindow::on_inverse_button_2_clicked()
{
    if(!(ui->numerator_line_edit_2->text().isEmpty()) &&
         !(ui->denominator_line_edit_2->text().isEmpty())){
        QString s1 = ui->numerator_line_edit_2->text();
        ui->numerator_line_edit_2->setText(ui->denominator_line_edit_2->text());
        ui->denominator_line_edit_2->setText(s1);
    }

}
