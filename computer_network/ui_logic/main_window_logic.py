from ui.main_window import Ui_MainWindow
from PyQt5.QtWidgets import QMainWindow, QLabel
from PyQt5.QtGui import QPainter, QColor, QFont, QPen, QPixmap, QImage
from PyQt5.QtCore import Qt, QRect, QPoint

from ui_logic.login_window_logic import LoginWindow
from ui_logic.file_select_window_logic import FileSelectWindow
from ui_logic.char_input_window_logic import CharInputWindow
from module.const_value import *

from copy import copy


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        super().setupUi(self)

        self.setMouseTracking(True)
        self.centralwidget.setMouseTracking(True)

        # 이벤트 관리용 리스트 작성
        self.action_list = [self.actionCharactor, self.actionPicture,
                            self.actionLineDraw, self.actionElipseDraw, self.actionRectDraw,
                            self.actionRed, self.actionBlue, self.actionYellow, self.actionGreen,
                            self.actionPurple]
        self.mode = DRAW_LINE
        self.color = BLUE_SELECTED

        self.event_init()

        self.from_x = self.from_y = self.to_x = self.to_y = self.from_pos = self.to_pos = None
        self.object_list = []
        self.registered_user_list = ['kang', 'kim', 'lee' 'park', 'song']
        self.current_user_list = list()

    def event_init(self):
        # for i, action in enumerate(self.action_list):
        #     action.toggled.connect(lambda : self.triggerEvent(i))

        self.actionCharactor.triggered.connect(lambda: self.triggerEvent(CHAR_SELECTED))
        self.actionPicture.triggered.connect(lambda: self.triggerEvent(PICTURE_SELECTED))
        self.actionDrawLine.triggered.connect(lambda: self.triggerEvent(DRAW_LINE))
        self.actionDrawElipse.triggered.connect(lambda: self.triggerEvent(DRAW_ELIPSE))
        self.actionDrawRect.triggered.connect(lambda: self.triggerEvent(DRAW_RECT))
        self.actionRed.triggered.connect(lambda: self.triggerEvent(RED_SELECTED))
        self.actionBlue.triggered.connect(lambda: self.triggerEvent(BLUE_SELECTED))
        self.actionYellow.triggered.connect(lambda: self.triggerEvent(YELLOW_SELECTED))
        self.actionGreen.triggered.connect(lambda: self.triggerEvent(GREEN_SELECTED))
        self.actionPurple.triggered.connect(lambda: self.triggerEvent(PURPLE_SELECTED))

    def triggerEvent(self, event):
        # TODO: 이벤트 구분은 정상, But UI 상에 Check가 이상하게 찍힘, Status도 이상한 것을 보아 구현 자체를 엎어야 할듯
        # 이벤트 유형 구분
        if CHAR_SELECTED <= event <= DRAW_RECT:
            self.mode = event
        else:
            self.color = event
        # print('mode: ', self.mode, 'color: ', self.color)
        for i, action in enumerate(self.action_list):
            # print(i, "는 ", action.isChecked(), end=" | ")
            if i != self.mode and i != self.color:
                action.setChecked(False)
            else:
                action.setChecked(True)
        print()

    def createNewWindow(self, x, y):
        if self.mode == PICTURE_SELECTED:
            new_window = FileSelectWindow()
        elif self.mode == CHAR_SELECTED:
            new_window = CharInputWindow()
        else:
            return

        if new_window.exec_():
            if self.mode == PICTURE_SELECTED:
                self.user_input = new_window.filePath.toPlainText()
            elif self.mode == CHAR_SELECTED:
                self.user_input = new_window.inputText.toPlainText()

    def mousePressEvent(self, event):
        self.from_x = event.x()
        self.from_y = event.y()
        self.from_pos = event.pos()

        is_Right = self.mouseButtonKind(event.button())

        if not is_Right:
            self.createNewWindow(self.from_x, self.from_y)  # 필요시 새 윈도우 생성

        # (모드, 위치, 텍스트, 색상)
        if self.mode == CHAR_SELECTED and not is_Right:
            self.object_list.append((self.mode, event.pos(), self.user_input, self.extractRGB()))
            self.user_input = None
        elif self.mode == PICTURE_SELECTED and not is_Right:
            self.object_list.append((self.mode, event.pos(), self.user_input, QImage(self.user_input)))
            self.user_input = None

        if is_Right:
            temp = copy(self.object_list)
            for i, obj in enumerate(temp):
                if obj[0] == CHAR_SELECTED:
                    x = obj[1].x()
                    y = obj[1].y()
                    if x - 5 < event.x() < x + (13 * len(obj[2])):
                        if y - 25 < event.y() < y + 5:
                            self.object_list.remove(obj)
                            break

                elif obj[0] == PICTURE_SELECTED:
                    x = obj[1].x()
                    y = obj[1].y()
                    if x - 5 < event.x() < x + obj[4].size().width() + 5:
                        if y - 5 < event.y() < y + obj[4].size().height() + 5:
                            self.object_list.remove(obj)
                            break

                elif obj[0] == DRAW_LINE:
                    # TODO: 급한 경사인 경우 삭제가 어려운 문제점 존재
                    if obj[1].x() < obj[2].x():
                        left_x = obj[1].x()
                        right_x = obj[2].x()
                        left_y = obj[1].y()
                        right_y = obj[2].y()
                    else:
                        left_x = obj[2].x()
                        right_x = obj[1].x()
                        left_y = obj[2].y()
                        right_y = obj[1].y()

                    slope = (right_y - left_y) / (right_x - left_x)
                    y_intercept = left_y - (slope * left_x)
                    func = lambda t: slope * t + y_intercept

                    print('slope: ', slope, 'y_intercept: ', y_intercept,
                        'func(x): ', func(event.x()), 'mouse x: ', event.x(), 'mouse y: ', event.y())

                    if left_x - 5 < event.x() < right_x + 5:
                        if func(event.x()) - 10 < event.y() < func(event.x()) + 10:
                            self.object_list.remove(obj)
                            break

                elif obj[0] == DRAW_ELIPSE:
                    if obj[1].x() < obj[2].x():
                        left_x = obj[1].x()
                        right_x = obj[2].x()
                        left_y = obj[1].y()
                        right_y = obj[2].y()
                    else:
                        left_x = obj[2].x()
                        right_x = obj[1].x()
                        left_y = obj[2].y()
                        right_y = obj[1].y()

                    # TODO: 타원방정식 구현
                    # import math
                    # a = None
                    # b = abs(left_y - right_y) / 2
                    # c = math.sqrt(a*a - b*b)
                    if left_x < event.x() < right_x:
                        if left_y < event.y() < right_y or right_y < event.y() < left_y:
                            self.object_list.remove(obj)
                            break

                elif obj[0] == DRAW_RECT:
                    from_x = obj[1].x()
                    from_y = obj[1].y()
                    to_x = obj[2].x()
                    to_y = obj[2].y()
                    # print('from_x: ', from_x, 'from_y: ', from_y, 'to_x: ', to_x, 'to_y: ', to_y,
                    #       "mouse x: ", event.x(), "mouse y: ", event.y())
                    if from_x - 10 < event.x() < from_x + 10 or to_x - 10 < event.x() < to_x + 10:
                        if from_y - 10 < event.y() < to_y + 10:
                            self.object_list.remove(obj)
                            break

                    if from_y - 10 < event.y() < from_y + 10 or to_y - 10 < event.y() < to_y + 10:
                        if from_x - 10 < event.x() < to_x + 10:
                            self.object_list.remove(obj)
                            break

    def extractRGB(self):
        if self.color == RED_SELECTED:
            color = RED
        elif self.color == BLUE_SELECTED:
            color = BLUE
        elif self.color == YELLOW_SELECTED:
            color = YELLOW
        elif self.color == GREEN_SELECTED:
            color = GREEN
        elif self.color == PURPLE_SELECTED:
            color = PURPLE
        else:
            color = (0, 0, 0)
        return color

    def mouseReleaseEvent(self, event):
        self.to_x = event.x()
        self.to_y = event.y()
        self.to_pos = event.pos()
        
        is_Right = self.mouseButtonKind(event.button())

        if self.mode == DRAW_LINE and not is_Right:
            # (유형, 시점, 종점, 색상)
            self.object_list.append((self.mode, self.from_pos, event.pos(), self.extractRGB()))
            # 테스트 용
            # print("라인 추가", self.mode, self.from_pos, event.pos(), self.extractRGB())

        elif self.mode == DRAW_ELIPSE and not is_Right:
            # (유형, 시점, 종점, 색상)
            self.object_list.append((self.mode, self.from_pos, event.pos(), self.extractRGB()))

        elif self.mode == DRAW_RECT and not is_Right:
            # (유형, 시점, 종점, 색상)
            self.object_list.append((self.mode, self.from_pos, event.pos(), self.extractRGB()))

        self.from_x = self.from_y = self.to_x = self.to_y = None
        self.update()

    def paintEvent(self, event):
        # print("윈도우 다시 그리기! 수행")
        painter = QPainter()
        pen = QPen(Qt.SolidLine)
        pen.setWidth(2)

        # TODO: 각각의 객체(QLine, QPoint 등)을 이용하도록 리팩토링
        painter.begin(self)
        for obj in self.object_list:
            if obj[0] == CHAR_SELECTED:
                painter.setPen(QColor(obj[3][0], obj[3][1], obj[3][2]))
                painter.setFont(QFont('Decorative', 15))
                painter.drawText(obj[1], obj[2])
            elif obj[0] == PICTURE_SELECTED:
                # label = QLabel(self.centralwidget)
                # print(obj[2])
                # pixmap = QPixmap('images.jpg')
                # label.setGeometry(QRect(obj[1], pixmap.size()))
                # # label.setPixmap(pixmap)
                # label.setText("test")

                img = QImage(obj[2])
                painter.drawImage(obj[1], img)
                pass

            elif obj[0] == DRAW_LINE:
                pen.setColor(QColor(obj[3][0], obj[3][1], obj[3][2]))
                painter.setPen(pen)
                painter.drawLine(obj[1], obj[2])
            elif obj[0] == DRAW_ELIPSE:
                pen.setColor(QColor(obj[3][0], obj[3][1], obj[3][2]))
                painter.setPen(pen)
                painter.drawEllipse(QRect(obj[1], obj[2]))
            elif obj[0] == DRAW_RECT:
                pen.setColor(QColor(obj[3][0], obj[3][1], obj[3][2]))
                painter.setPen(pen)
                painter.drawRect(QRect(obj[1], obj[2]))

        painter.end()

    def mouseButtonKind(self, buttons):
        # Reference: https://freeprog.tistory.com/330
        if buttons == Qt.LeftButton:
            print('LEFT')
            return False
        if buttons == Qt.MidButton:
            print('MIDDLE')
        if buttons == Qt.RightButton:
            print('RIGHT')
            return True

    def try_login(self):
        # https://www.reddit.com/r/learnpython/comments/7w9pt9/pyqt5_passing_variable_from_one_window_to_another/
        login = LoginWindow()

        if login.exec_():
            self.username = login.username_edit.toPlainText()
            self.host = login.host_edit.toPlainText()
            self.is_server = login.is_server
            return False
        return True
