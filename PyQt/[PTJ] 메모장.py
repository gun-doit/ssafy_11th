from PySide6.QtWidgets import *
from PySide6.QtGui import *
from time import *
import subprocess

class MyApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.main()
        
    def main(self):
        self.setGeometry(100, 100, 1000, 600)
        self.setWindowTitle("Python 메모장")       
         
        mainWidget = QWidget(self)
        mainLayout = QVBoxLayout(mainWidget)
        mainLayout.setContentsMargins(0,0,0,0)
        self.Menu()
        self.BottomStatus()
        self.TextArea(mainLayout)
        
        self.setCentralWidget(mainWidget)
    
    
    def BottomStatus(self):
        self.bottombar = QStatusBar(self)
        self.setStatusBar(self.bottombar)
        self.bottombar.showMessage("Ln 1, Col 1")
        
    def BottomStatusToggle(self):
        if(self.bottombar.isHidden()):
            self.bottombar.show()
        else:
            self.bottombar.hide()
    
    
    def ShowCursorPos(self):
        ss = self.textarea.textCursor().selectionStart()
        se = self.textarea.textCursor().selectionEnd()

        selected_info = ""
        if se - ss:
            selected_info = "{0} {1}  ".format(se - ss, "char" if (se-ss) == 1 else "chars")
        self.bottombar.showMessage("Ln {0}{1}, Col{2}".format(
            selected_info,
            self.textarea.textCursor().blockNumber() + 1,
            self.textarea.textCursor().columnNumber() + 1)
        )
        
    def TextArea(self, Layout):
        self.textarea = QTextEdit()
        self.textarea.setStyleSheet("QTextEdit {border: none; background-color: white;}")
        self.textarea.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOn)
        self.textarea.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOn)
        self.textarea.cursorPositionChanged.connect(self.ShowCursorPos)
        
        
        Layout.addWidget(self.textarea)
            
    def Menu(self):
        self.menu = self.menuBar()
        self.menuFile = self.menu.addMenu("&파일(F)")
        self.menuEdit = self.menu.addMenu("&편집(E)")
        self.menuFormat = self.menu.addMenu("&서식(O)")
        self.menuView = self.menu.addMenu("&보기(V)")
        self.menuInfo = self.menu.addMenu("&도움말(H)")
        
        def customAction(name, shortcut, connect):
            action = QAction(name, self)
            if(shortcut != None): action.setShortcut(shortcut)
            if(connect != None): action.triggered.connect(connect)
            if(name == "&상태 표시줄(S)"): 
                action.setCheckable(True)
                action.setChecked(True)
            return action
        
        # 파일
        self.menuFiles = [customAction("&새로 만들기(N)", "Ctrl + N", None),
                     customAction("&새 창(W)", "Ctrl + Shift + N", lambda: subprocess.Popen(['python', 'C:\\Users\\SSAFY\\Desktop\\[PTJ]memo.py'], capture_output=True, text=True)),
                     customAction("&열기(O)...", "Ctrl + O", None),
                     customAction("&저장(S)", "Ctrl + S", None),
                     customAction("&다른 이름으로 저장(A)...", "Ctrl + Shift + S", None),
                     "Seperator",
                     customAction("&페이지 설정(U)...", "Ctrl + Shift + U", None),
                     customAction("&인쇄(P)...", "Ctrl + P", None),
                     "Seperator",
                     customAction("&끝내기(X)", "Ctrl + X", exit),]
        
        for menu in self.menuFiles:
            if(menu == "Seperator"): self.menuFile.addSeparator()
            else: self.menuFile.addAction(menu)
            
        # Edit
        self.menuEdits = [customAction("&실행 취소(U)", "Ctrl + Z", None),
                     "Seperator",
                     customAction("&잘라내기(T)", "Ctrl + X", None),
                     customAction("&복사(C)", "Ctrl + C", None),
                     customAction("&붙여넣기(P)", "Ctrl + V", None),
                     customAction("&삭제(L)", "DEL", None),
                     "Seperator",
                     customAction("&Bing으로 검색(S)...", "Ctrl + E", None),
                     customAction("&찾기(F)", "Ctrl + F", None),
                     customAction("&다음 찾기(N)", "F3", None),
                     customAction("&이전 찾기(V)", "Shift + F3", None),
                     customAction("&바꾸기(R)...", "Ctrl + H", None),
                     customAction("&이동(G)...", "Ctrl + G", None),
                     "Seperator",
                     customAction("&모두 선택(A)...", "Ctrl + A", None),
                     customAction("&시간/날짜(D)...", "F5", None)]
        
        for menu in self.menuEdits:
            if(menu == "Seperator"): self.menuEdit.addSeparator()
            else: self.menuEdit.addAction(menu)
          
          
        # Format
        self.menuFormats = [customAction("자동 줄 바꿈(W)", None, None),
                            customAction("글꼴(F)...",None, None)]
        
        for menu in self.menuFormats:
            if(menu == "Seperator"): self.menuFormat.addSeparator()
            else: self.menuFormat.addAction(menu)
            
        # View
        # self.menuViews = [customAction("&확대하기/축소하기", None, None),
        self.menuViewTips = [customAction("확대(I)", "Ctrl + 더하기", None),
                             customAction("축소(O)", "Ctrl + 빼기", None),
                             customAction("확대하기/축소하기 기본값 복원", "Ctrl +  0", None)]
        self.menuViewTip = QMenu("확대하기/축소하기")
        for menu in self.menuViewTips:
            if(menu == "Seperator"): self.menuViewTip.addSeparator()
            else: self.menuViewTip.addAction(menu)
            
        self.menuView.addMenu(self.menuViewTip)
        self.menuView.addAction(customAction("&상태 표시줄(S)", None, self.BottomStatusToggle))
            
        # Info
        self.menuInfos = [customAction("&도움말 보기(H)", None, None),
                          customAction("&피드백 보내기(F)", None, None),
                          "Seperator",
                          customAction("&메모장 정보(A)", None, None)]
        
        for menu in self.menuInfos:
            if(menu == "Seperator"): self.menuInfo.addSeparator()
            else: self.menuInfo.addAction(menu)
        
        # self.menuView.addAction(self.comboAction)
    
if __name__ == '__main__':
    app = QApplication()
    win = MyApp()
    win.show()
    app.exec()
