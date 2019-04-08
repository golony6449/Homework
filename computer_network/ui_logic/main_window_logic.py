from ui.main_window import Ui_MainWindow
from PyQt5.QtWidgets import QMainWindow

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        super().setupUi(self)

        self.setMouseTracking(True)
        self.centralwidget.setMouseTracking(True)

    def mousePressEvent(self, event):
        pass

    def mouseReleaseEvent(self, event):
        pass

    def mouseMoveEvent(self, event):
        print('x: ', event.x(), 'y: ', event.y())