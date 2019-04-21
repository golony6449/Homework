from ui.login_window import Ui_Dialog

from PyQt5.QtWidgets import QDialog, QErrorMessage

from module.socket import *
import module.const_value as values
from time import sleep


class LoginWindow(QDialog, Ui_Dialog):
    def __init__(self, caller):
        super().__init__()
        super().setupUi(self)

        self.Server.toggled.connect(lambda: self.mode_select(True))
        self.Client.toggled.connect(lambda: self.mode_select(False))
        self.is_server = False
        self.caller = caller

    def mode_select(self, is_server):
        if is_server is True:
            self.host_edit.setText('127.0.0.1')
            self.host_edit.setEnabled(False)
            # self.username_edit.setEnabled(False)
            self.is_server = True

        else:
            self.host_edit.setText('127.0.0.1')
            self.host_edit.setEnabled(True)
            # self.username_edit.setEnabled(True)
            self.is_server = False

    def accept(self):
        # login_flag = True   # GUI 개발용 값
        login_flag = None

        # TODO 로그인 작업
        login_flag = self.connection_establish()
        sleep(1)
        if not self.is_server:
            login_flag = self.login()

        if login_flag is True:
            super().accept()
        else:
            return

    def connection_establish(self):
        if self.is_server is True:
            self.caller.serverThread = ServerThread(window=self.caller)
            self.caller.serverThread.start()
            return True

        else:
            try:
                host = self.host_edit.toPlainText()
                self.caller.clientThread = ClientThread(host, self.caller)
                self.caller.clientThread.start()
                return True

            except ConnectionRefusedError:
                print('대상 컴퓨터에서 연결을 거부했으므로 연결하지 못했습니다')
                return False

            # except ConnectionResetError:
            #     print('현재 연결은 원격 호스트에 의해 강제로 끊겼습니다')
            #     login_flag = False

    def login(self):
        # TODO: 유저 이름 확인, 매칭 실패시 접속 해제
        flag = self.caller.clientThread.login(self.username_edit.toPlainText())
        return flag
