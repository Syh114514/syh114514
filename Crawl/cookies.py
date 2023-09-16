from selenium import webdriver
from selenium.webdriver.common.by import By
import time
import json

options = webdriver.ChromeOptions()
options.add_argument(
    "--user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.159 Safari/537.36")
#
# 创建 Chrome WebDriver 对象
driver = webdriver.Chrome(options=options)
driver.get("https://www.luogu.com.cn/auth/login")
time.sleep(15)
with open('cookies.txt', 'w') as f:
    f.write(json.dumps(driver.get_cookies()))

driver.quit()