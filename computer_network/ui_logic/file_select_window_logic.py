from ui.file_select_window import Ui_Dialog
from PyQt5.QtWidgets import QDialog

class FileSelectWindow(QDialog, Ui_Dialog):
    def __init__(self):
        super().setupUi()