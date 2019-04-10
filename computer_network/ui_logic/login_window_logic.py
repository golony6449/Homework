from ui.login_window import Ui_Dialog

from PyQt5.QtWidgets import QDialog

class LoginWindow(QDialog, Ui_Dialog):
    def __init__(self):
        super().__init__()
        super().setupUi(self)

    def accept(self):
        login_flag = True   # GUI 개발용 값

        # TODO 로그인 작업

        if login_flag is True:
            super().accept()
        else:
            return

# TODO main window GUI 종료 후에도 프로세스가 끝나지 않음
