import bs4
from bs4 import BeautifulSoup
import requests
import re

class UniverseList(object):
	"""docstring for UniverseList"""
	def __init__(self, url):
		super(UniverseList, self).__init__()
		self.url = url
	def printUnivList(self, num):
		def getHTMLText(url):
			try:
				r = requests.get(url, timeout = 30)
				r.raise_for_status()
				r.encoding = r.apparent_encoding
				return r.text
			except :
				return ''
		def fillUnivList(html):
			ulist = list()
			soup = BeautifulSoup(html, 'html.parser')
			for tr in soup.find('tbody').children:
				if isinstance(tr, bs4.element.Tag):
					tds = tr.find_all('td')
					ulist.append([tds[0].string, tds[1].find('a').string, tds[2].string])
					#刚开始tds[1].string，发现不行，后来改成这样就可以了
					'''	tds[1] html:
						<td class="align-left" data-v-45ac69d8><a href="/institution/tsinghua-university" data-v-45ac69d8>清华大学</a>
					   	<p style="display:none" data-v-45ac69d8></p></td>
					'''
			return ulist
		print('{:^10}\t{:^6}\t{:^10}'.format('排名', '学校名称', '省份'))
		ulist = fillUnivList(getHTMLText(self.url))
		#print(ulist)
		for i in range(num):
			u = ulist[i]
			print('{:^10}\t{:^6}\t{:^10}'.format(u[0], u[1], u[2]))

if __name__ == '__main__':
	url = 'https://www.shanghairanking.cn/rankings/bcur/2020'
	#r = requests.get('http://www.baidu.com/s', params = {'wd': 'helloworld'})
	#print(soup.prettify)
	'''
	for link in soup.find_all('a'):
		print(link.get('href'))
	'''
	uni = UniverseList(url)
	uni.printUnivList(20)