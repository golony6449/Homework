# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'main.ui'
#
# Created by: PyQt5 UI code generator 5.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1280, 720)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1280, 21))
        self.menubar.setObjectName("menubar")
        self.menutype = QtWidgets.QMenu(self.menubar)
        self.menutype.setObjectName("menutype")
        self.menucolor = QtWidgets.QMenu(self.menubar)
        self.menucolor.setObjectName("menucolor")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.actionCharactor = QtWidgets.QAction(MainWindow)
        self.actionCharactor.setCheckable(True)
        self.actionCharactor.setObjectName("actionCharactor")
        self.actionPicture = QtWidgets.QAction(MainWindow)
        self.actionPicture.setCheckable(True)
        self.actionPicture.setObjectName("actionPicture")
        self.actionDraw = QtWidgets.QAction(MainWindow)
        self.actionDraw.setCheckable(True)
        self.actionDraw.setChecked(True)
        self.actionDraw.setObjectName("actionDraw")
        self.actionRed = QtWidgets.QAction(MainWindow)
        self.actionRed.setCheckable(True)
        self.actionRed.setObjectName("actionRed")
        self.actionBlue = QtWidgets.QAction(MainWindow)
        self.actionBlue.setCheckable(True)
        self.actionBlue.setChecked(True)
        self.actionBlue.setObjectName("actionBlue")
        self.actionYellow = QtWidgets.QAction(MainWindow)
        self.actionYellow.setCheckable(True)
        self.actionYellow.setChecked(False)
        self.actionYellow.setObjectName("actionYellow")
        self.actionGreen = QtWidgets.QAction(MainWindow)
        self.actionGreen.setCheckable(True)
        self.actionGreen.setObjectName("actionGreen")
        self.actionPurple = QtWidgets.QAction(MainWindow)
        self.actionPurple.setCheckable(True)
        self.actionPurple.setObjectName("actionPurple")
        self.menutype.addAction(self.actionCharactor)
        self.menutype.addAction(self.actionPicture)
        self.menutype.addAction(self.actionDraw)
        self.menucolor.addAction(self.actionRed)
        self.menucolor.addAction(self.actionBlue)
        self.menucolor.addAction(self.actionYellow)
        self.menucolor.addAction(self.actionGreen)
        self.menucolor.addAction(self.actionPurple)
        self.menubar.addAction(self.menutype.menuAction())
        self.menubar.addAction(self.menucolor.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.menutype.setTitle(_translate("MainWindow", "type"))
        self.menucolor.setTitle(_translate("MainWindow", "color"))
        self.actionCharactor.setText(_translate("MainWindow", "Charactor"))
        self.actionPicture.setText(_translate("MainWindow", "Picture"))
        self.actionDraw.setText(_translate("MainWindow", "Draw"))
        self.actionRed.setText(_translate("MainWindow", "Red"))
        self.actionBlue.setText(_translate("MainWindow", "Blue"))
        self.actionYellow.setText(_translate("MainWindow", "Yellow"))
        self.actionGreen.setText(_translate("MainWindow", "Green"))
        self.actionPurple.setText(_translate("MainWindow", "Purple"))
