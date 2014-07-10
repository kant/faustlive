//
//  FLErrorWindow.cpp
//  
//
//  Created by Sarah Denoux on 13/05/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "FLErrorWindow.h"

//-----------------------ERRORWINDOW IMPLEMENTATION

FLErrorWindow::FLErrorWindow(){
    fErrorText = new QTextEdit(this);
}

FLErrorWindow::~FLErrorWindow(){
    delete fErrorText;
}

void FLErrorWindow::init_Window(){
    
    fWidget = new QWidget(this);
    fButton = new QPushButton(tr("OK"), this);
    connect(fButton, SIGNAL(clicked()), this, SLOT(hideWin()));
    connect(fButton, SIGNAL(clicked()), this, SLOT(redirectClose()));
    fLayout = new QVBoxLayout();
    
    QFont font;
    font.setFamily(QString::fromUtf8("Menlo"));
    font.setPointSize(12);
    fErrorText->setFont(font);
    
    fErrorText->setReadOnly(true);
    
    QSize screenSize = QApplication::desktop()->geometry().size();
    this->setGeometry(screenSize.width()*3/4 , 0,screenSize.width()/4,screenSize.height()/10);
    this->setCentralWidget(fWidget);
    
    fLayout->addWidget(fErrorText);
    fLayout->addWidget(fButton);
    
    fWidget->setLayout(fLayout);
}

void FLErrorWindow::redirectClose(){
    emit close();
}

void FLErrorWindow::closeEvent(QCloseEvent* /*event*/){
    
    this->hideWin();
    
    if(QApplication::keyboardModifiers() == Qt::AltModifier)
        emit closeAll();
}

void FLErrorWindow::hideWin(){
    fErrorText->setPlainText("");
    hide();
}

void FLErrorWindow::print_Error(const QString& text){
    
    QString inter = fErrorText->toPlainText(); 
    QString wholeText = inter +"\n" +text;
    
    fErrorText->setPlainText(wholeText);
    this->adjustSize();
    show();
    raise(); 
}
