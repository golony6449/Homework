from ui.char_input_window import Ui_Dialog
from PyQt5.QtWidgets import QDialog

class CharInputWindow(QDialog, Ui_Dialog):
    def __init__(self):
        super().__init__()
        super().setupUi(self)