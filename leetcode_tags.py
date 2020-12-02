import requests
import re
import time
import os
from bs4 import BeautifulSoup

kv = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:76.0) Gecko/20100101 Firefox/76.0'}
def gethtml(url, headers, code = 'utf-8'):
	try:
		response = requests.get(url, headers = headers)
		response.raise_for_status()
		#code = r.apparent_encoding
		#r.encoding = code
		return response.text
	except Exception as e:
		raise e


html = gethtml('https://leetcode-cn.com/problemset/all/', kv)
soup = BeautifulSoup(html, 'html.parser')
taglst = soup.find('div', class_= "tags tags-fade")
#似乎题目是代码生成的，所以只会定向爬取标签的
#采用requests + bs 路线
for tag in taglst.find_all('a'):
	title = tag['title'] + '\n'
	url = 'url: ' + 'https://leetcode-cn.com' + tag['href'] + '\n'
	with open('leetcode_tags_urls.txt', 'a+') as f:
		f.write(title)
		f.write(url)
print('ok')
