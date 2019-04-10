from ui.main_window import Ui_MainWindow
from PyQt5.QtWidgets import QMainWindow

from ui_logic.login_window_logic import LoginWindow
from ui_logic.file_select_window_logic import FileSelectWindow
from ui_logic.char_input_window_logic import CharInputWindow
from module.const_value import *

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        super().setupUi(self)

        self.setMouseTracking(True)
        self.centralwidget.setMouseTracking(True)

        # 이벤트 관리용 리스트 작성
        self.action_list = [self.actionCharactor, self.actionPicture, self.actionDraw,
                            self.actionRed, self.actionBlue, self.actionYellow, self.actionGreen,
                            self.actionPurple]
        self.mode = DRAW_SELECTED
        self.color = BLUE_SELECTED

        self.event_init()

    def event_init(self):
        # for i, action in enumerate(self.action_list):
        #     action.toggled.connect(lambda : self.triggerEvent(i))

        self.actionCharactor.triggered.connect(lambda : self.triggerEvent(CHAR_SELECTED))
        self.actionPicture.triggered.connect(lambda : self.triggerEvent(PICTURE_SELECTED))
        self.actionDraw.triggered.connect(lambda : self.triggerEvent(DRAW_SELECTED))
        self.actionRed.triggered.connect(lambda : self.triggerEvent(RED_SELECTED))
        self.actionBlue.triggered.connect(lambda : self.triggerEvent(BLUE_SELECTED))
        self.actionYellow.triggered.connect(lambda : self.triggerEvent(YELLOW_SELECTED))
        self.actionGreen.triggered.connect(lambda : self.triggerEvent(GREEN_SELECTED))
        self.actionPurple.triggered.connect(lambda : self.triggerEvent(PURPLE_SELECTED))

    def triggerEvent(self, event):
        print('Event: ', event, " value: ", self.actionCharactor.isChecked())

        # 이벤트 유형 구분
        if CHAR_SELECTED <= event <= DRAW_SELECTED:
            self.mode = event
        else:
            self.color = event

        for i, action in enumerate(self.action_list):
            if i != self.mode and i != self.color:
                action.setChecked(False)
            else:
                action.setChecked(True)
            # else:
            #     print(action, "is Checked")
            #     action.setChecked(True)

    def createNewWindow(self):
        if self.mode == PICTURE_SELECTED:
            new_window = FileSelectWindow()
        elif self.mode == CHAR_SELECTED:
            new_window = CharInputWindow()
        else:
            return

        if new_window.exec_():
            pass

    def mousePressEvent(self, event):
        self.createNewWindow()

    def mouseReleaseEvent(self, event):
        pass

    def mouseMoveEvent(self, event):
        # print('x: ', event.x(), 'y: ', event.y())
        pass

    def login(self):
        # https://www.reddit.com/r/learnpython/comments/7w9pt9/pyqt5_passing_variable_from_one_window_to_another/
        login = LoginWindow()

        if login.exec_():
            return False
        return True
