//
// Created by Kolby on 6/19/2019.
//


#include <startoptionsrevealed.h>
#include <ui_startoptionsrevealed.h>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>


StartOptionsRevealed::StartOptionsRevealed(std::vector<std::string>& Words, int rows, QWidget *parent)
        : QWidget(parent), ui(new Ui::StartOptionsRevealed)
        {
    ui->setupUi(this);
    ui->seedLabel->setText(
        tr("The words below are your recovery phrase (mnemonic seed). Please "
           "write them down and/or securely save them. "
           "Once they are securely saved, click next."));

    for(int i=0; i<rows; i++){
        for(int k=0; k<6; k++){

            QLabel* label = new QLabel(this);
            label->setStyleSheet("QLabel{background-color:transparent;padding-left:8px;padding-right:8px;border-radius:0px;color:#000;border-bottom:2px solid rgb(153,50,204);}");
            label->setMinimumSize(80,36);
            label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
            label->setContentsMargins(8,12,8,12);
            label->setAlignment(Qt::AlignCenter);
            labelsList.push_back(label);
            ui->gridLayoutRevealed->addWidget(label, i, k, Qt::AlignCenter);
        }
    }
    int i = 0;
    for (QLabel* label : labelsList) {
        label->setStyleSheet("QLabel{background-color:transparent;padding-left:8px;padding-right:8px;border-radius:0px;color:#000;border-bottom:2px solid rgb(153,50,204);}");
        label->setContentsMargins(8,12,8,12);
        label->setText(QString::fromStdString(Words[i]));
        i++;
    }
}

StartOptionsRevealed::~StartOptionsRevealed() {
    delete ui;
}

