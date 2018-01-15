/**
 * @file /src/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QApplication>
#include "../include/rosgui/ros/qnode.hpp"
//#include "../include/rosgui/qt/main_window.hpp"
#include "../include/rosgui/qt/t3_af_welcome.hpp"
/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv) {

    /*********************
    ** Qt
    **********************/
    QApplication app(argc, argv);
//    rosgui::MainWindow w(argc,argv);
//    w.show();
    //----------------jason code
    rosgui::QNode *qnode = rosgui::QNode::getInstance();
    qnode->init(argc, argv);
    //----------------jason end
    T3_AF_welcome welcome_;
    welcome_.show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    int result = app.exec();

	return result;
}
