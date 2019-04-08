from ui.login_window import Ui_Dialog
from ui_logic.main_window_logic import MainWindow

from PyQt5.QtWidgets import QDialog

class LoginWindow(QDialog, Ui_Dialog):
    def __init__(self):
        super().__init__()
        super().setupUi(self)

        self.main_window = MainWindow()

    def accept(self):
        self.destroy()
        self.main_window.show()
        # TODO main window GUI 종료 후에도 프로세스가 끝나지 않음
