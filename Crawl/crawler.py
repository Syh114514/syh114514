# coding=gbk
import os
import re
import json
import time
import requests
from tkinter import *
from tkinter.ttk import *
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.common.by import By


class WinGUI(Tk):
    def __init__(self):
        super().__init__()
        self.__win()
        self.tk_select_box_lmkfrwxg = self.__tk_select_box_lmkfrwxg(self)
        self.tk_text_lmkftbq7 = self.__tk_text_lmkftbq7(self)
        self.tk_label_lmkg0xn5 = self.__tk_label_lmkg0xn5(self)
        self.tk_label_lmkgack7 = self.__tk_label_lmkgack7(self)
        self.tk_table_lmkgn0s2 = self.__tk_table_lmkgn0s2(self)
        self.tk_button_lmkgvakd = self.__tk_button_lmkgvakd(self)
        self.tk_button_lmkh01qz = self.__tk_button_lmkh01qz(self)

    def __win(self):
        self.title("洛谷爬虫")
        width = 639
        height = 358
        screenwidth = self.winfo_screenwidth()
        screenheight = self.winfo_screenheight()
        geometry = '%dx%d+%d+%d' % (width, height, (screenwidth - width) / 2, (screenheight - height) / 2)
        self.geometry(geometry)
        self.resizable(width=False, height=False)

    def scrollbar_autohide(self, bar, widget):
        self.__scrollbar_hide(bar, widget)
        widget.bind("<Enter>", lambda e: self.__scrollbar_show(bar, widget))
        bar.bind("<Enter>", lambda e: self.__scrollbar_show(bar, widget))
        widget.bind("<Leave>", lambda e: self.__scrollbar_hide(bar, widget))
        bar.bind("<Leave>", lambda e: self.__scrollbar_hide(bar, widget))

    def __scrollbar_show(self, bar, widget):
        bar.lift(widget)

    def __scrollbar_hide(self, bar, widget):
        bar.lower(widget)

    def vbar(self, ele, x, y, w, h, parent):
        sw = 15
        x = x + w - sw
        vbar = Scrollbar(parent)
        ele.configure(yscrollcommand=vbar.set)
        vbar.config(command=ele.yview)
        vbar.place(x=x, y=y, width=sw, height=h)
        self.scrollbar_autohide(vbar, ele)

    def __tk_select_box_lmkfrwxg(self, parent):
        cb = Combobox(parent, state="readonly", )
        cb['values'] = ("入门", "普及", "普及/提高-", "普及+/提高", "提高+/省选-", "省选/NOI-", "NOI/NOI+/CTSC")
        cb.place(x=120, y=180, width=140, height=30)
        return cb

    def __tk_text_lmkftbq7(self, parent):
        text = Text(parent)
        text.place(x=120, y=110, width=140, height=30)
        self.vbar(text, 120, 110, 140, 30, parent)
        return text

    def __tk_label_lmkg0xn5(self, parent):
        label = Label(parent, text="题目难度", anchor="center", )
        label.place(x=40, y=180, width=60, height=30)
        return label

    def __tk_label_lmkgack7(self, parent):
        label = Label(parent, text="关键词", anchor="center", )
        label.place(x=40, y=110, width=60, height=30)
        return label

    def __tk_table_lmkgn0s2(self, parent):
        # 表头字段 表头宽度
        columns = {"算法标签": 63, "难度": 63, "标题": 191}
        tk_table = Treeview(parent, show="headings", columns=list(columns), )
        for text, width in columns.items():  # 批量设置列属性
            tk_table.heading(text, text=text, anchor='center')
            tk_table.column(text, anchor='center', width=width, stretch=False)  # stretch 不自动拉伸

        tk_table.place(x=300, y=40, width=320, height=220)
        self.vbar(tk_table, 300, 40, 320, 220, parent)
        return tk_table

    def __tk_button_lmkgvakd(self, parent):
        btn = Button(parent, text="开始爬虫", takefocus=False, )
        btn.place(x=150, y=280, width=101, height=40)
        return btn

    def __tk_button_lmkh01qz(self, parent):
        btn = Button(parent, text="打开文件夹", takefocus=False, )
        btn.place(x=390, y=280, width=101, height=40)
        return btn


class Win(WinGUI):
    def __init__(self):
        super().__init__()
        self.__event_bind()

    def __event_bind(self):
        pass


prob_url = "https://www.luogu.com.cn/problem/"


def get_html(url):
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
                      "AppleWebKit/537.36 (KHTML, like Gecko) "
                      "Chrome/95.0.4638.54 Safari/537.36",
    }
    response = requests.get(url, headers=headers)
    html = response.content.decode("utf-8")
    if response.ok:
        return html
    else:
        print("Error!")


def crawl():
    option = webdriver.ChromeOptions()
    option.add_argument("--user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.54 Safari/537.36")
    browser = webdriver.Chrome(options=option)
    browser.maximize_window()
    browser.get('https://www.luogu.com.cn/problem/list')
    browser.delete_all_cookies()
    with open('cookies.txt', 'r') as cks:
        cookies_list = json.load(cks)
        for ck in cookies_list:
            browser.add_cookie(ck)
    browser.refresh()
    click = browser.find_element(By.LINK_TEXT, "显示算法")
    click.click()
    rows = browser.find_elements(By.CLASS_NAME, "row")
    cnt = 0
    for row in rows:
        if cnt < 10:
            pid = str("P100" + str(cnt))
        else:
            pid = str("P10" + str(cnt))
        title = row.find_element(By.CLASS_NAME, "title").text
        difficulty = row.find_element(By.CLASS_NAME, "difficulty").text
        difficulty = re.sub('/', 'or', difficulty)
        tags = row.find_element(By.CLASS_NAME, "tags").text
        tag_cnt = 1
        for t in tags:
            if t == '\n':
                tags = re.sub('\n', '-', tags)
                tag_cnt += 1
        prob = str(prob_url + pid)
        save(pid, title, difficulty, tags, prob, "p")
        save(pid, title, difficulty, tags, prob, "s")
        time.sleep(7)
        cnt += 1
    time.sleep(2)
    browser.quit()


def save(pid, tit, dif, tag, url, pors):
    time.sleep(3)
    soup = BeautifulSoup(get_html(url), 'lxml')
    if pors == "p":
        if "{dif}-{tag}".format(dif=dif, tag=tag) not in os.listdir():
            os.mkdir("{dif}-{tag}".format(dif=dif, tag=tag))
        if "{dif}-{tag}/{pid}-{tit}".format(dif=dif, tag=tag, pid=pid, tit=tit) not in os.listdir():
            os.mkdir("{dif}-{tag}/{pid}-{tit}".format(dif=dif, tag=tag, pid=pid, tit=tit))
        art_usl = soup.select('article')
        art = str(art_usl)
        with open(r"{dif}-{tag}/{pid}-{tit}/{pid}-{tit}.md".format(dif=dif, tag=tag, pid=pid, tit=tit), 'w', encoding='utf8') as md_file:
            art = re.sub("<h1>", "# ", art)
            art = re.sub("<h2>", "## ", art)
            art = re.sub("<h3>", "#### ", art)
            art = re.sub("</?[a-zA-Z]+[^<>]*>", "", art)
            md_file.write(art)
            print("markdown问题文件保存成功！")
    elif pors == "s":
        option = webdriver.ChromeOptions()
        option.add_argument("--user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.54 Safari/537.36")
        browser = webdriver.Chrome(options=option)
        browser.maximize_window()
        browser.get(url)
        time.sleep(3)
        browser.implicitly_wait(10)
        browser.delete_all_cookies()
        with open('cookies.txt', 'r') as cks:
            cookies_list = json.load(cks)
            for ck in cookies_list:
                browser.add_cookie(ck)
        browser.refresh()
        sol_url = browser.find_element(By.XPATH, "//*[@id='app']/div[2]/main/div/section[1]/div[1]/a[2]").get_attribute('href')
        browser.get(sol_url)
        time.sleep(3)
        browser.implicitly_wait(10)
        sol = browser.find_element(By.XPATH, "/html/body/div/div[2]/main/div/section[2]/div/div[1]/b")
        if sol.text[0] != '0':
            art = browser.find_element(By.XPATH, "/html/body/div/div[2]/main/div/section[2]/div/div[2]"
                                                 "/div/div[1]/div/div[1]/div/div[2]/div[1]/div/div").get_attribute("innerHTML")
            with open(r"{dif}-{tag}/{pid}-{tit}/{pid}-{tit}-题解.md".format(dif=dif, tag=tag, pid=pid, tit=tit), 'w', encoding='utf8') as md_file:
                md_file.write(art)
                print("markdown题解文件保存成功！")
        browser.quit()


if __name__ == "__main__":
    win = Win()
    win.mainloop()
    crawl()
