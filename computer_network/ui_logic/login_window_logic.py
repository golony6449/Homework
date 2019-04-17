from ui.login_window import Ui_Dialog

from PyQt5.QtWidgets import QDialog

class LoginWindow(QDialog, Ui_Dialog):
    def __init__(self):
        super().__init__()
        super().setupUi(self)

        self.Server.toggled.connect(lambda: self.mode_select(True))
        self.Client.toggled.connect(lambda: self.mode_select(False))
        self.is_server = False

    def mode_select(self, is_server):
        if is_server is True:
            self.host_edit.setText('127.0.0.1')
            self.host_edit.setEnabled(False)
            # self.username_edit.setEnabled(False)
            self.is_server = True

        else:
            self.host_edit.setText('')
            self.host_edit.setEnabled(True)
            # self.username_edit.setEnabled(True)
            self.is_server = False

    def accept(self):
        login_flag = True   # GUI 개발용 값

        # TODO 로그인 작업

        if login_flag is True:
            super().accept()
        else:
            return
