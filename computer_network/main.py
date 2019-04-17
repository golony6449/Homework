from ui_logic.main_window_logic import MainWindow

import sys
from PyQt5.QtWidgets import QApplication

if __name__ == '__main__':
    app = QApplication(sys.argv)

    main_window = MainWindow()
    while main_window.try_login():
        print('login fail')
    main_window.show()

    # 그냥 python 소켓을 사용할지 고민중
    # https://eli.thegreenplace.net/2011/05/26/code-sample-socket-client-based-on-twisted-with-pyqt
    import qt5reactor
    qt5reactor.install()

    from twisted.internet import reactor
    reactor.run()

    # app.exec_() # GUI 만 종료되고, 프로세스는 계속 실행중인 문제 발생
    # https://stackoverflow.com/questions/22291434/pyqt-application-closes-successfully-but-process-is-not-killed
    sys.exit(app.exec_())
