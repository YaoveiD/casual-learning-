import requests
import re
import time
import os

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

html = gethtml('https://www.vmgirls.com/13344.html', kv)

dir_name = re.findall('<h1 class="post-title h1">(.*?)</h1>', html)[-1]
if not os.path.exists(dir_name):
	os.mkdir(dir_name)

urls = re.findall('<a href="(.*?)" alt="少女情怀总是诗".*?</a>', html)
counter = 1
for url in urls:
#	time.sleep(1)
	file_name = url.split('/')[-1]
	response = requests.get('https:' + url, headers = kv)
	with open(dir_name + '/' + file_name, 'wb') as f:
		f.write(response.content)
	print("crawling %d" % counter)
	counter += 1

print('ok')