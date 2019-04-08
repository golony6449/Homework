from ui_logic.login_window_logic import LoginWindow

import sys
from PyQt5.QtWidgets import QApplication

if __name__ == '__main__':
    app = QApplication(sys.argv)
    login_window = LoginWindow()
    login_window.show()
    # app.exec_() # GUI 만 종료되고, 프로세스는 계속 실행중인 문제 발생
    # https://stackoverflow.com/questions/22291434/pyqt-application-closes-successfully-but-process-is-not-killed
    sys.exit(app.exec_())
