Python 3.8.1 (tags/v3.8.1:1b293b6, Dec 18 2019, 22:39:24) [MSC v.1916 32 bit (Intel)] on win32
Type "help", "copyright", "credits" or "license" for more information.
(InteractiveConsole)
>>> from bs4 import BeautifulSoup
>>> tsoup = BeautifulSoup('<td class="align-left" data-v-45ac69d8><a href="/institution/tsinghua-university" data-v-45ac69d8>清华大学</a> <p style="display:none" data-v-45ac69d8></p></td>','html.parser')
>>> tsoup
<td class="align-left" data-v-45ac69d8=""><a data-v-45ac69d8="" href="/institution/tsinghua-university">清华大学</a> <p data-v-45ac69d8="" style="display:none"></p></td>
>>> tsoup.string
>>> tsoup.find_all('td')
[<td class="align-left" data-v-45ac69d8=""><a data-v-45ac69d8="" href="/institution/tsinghua-university">清华大学</a> <p data-v-45ac69d8="" style="display:none"></p></td>]
>>> tsoup.find_all('td')[0].string
>>> l = tsoup.find_all('a')
>>> l
[<a data-v-45ac69d8="" href="/institution/tsinghua-university">清华大学</a>]
>>> l[0].string
'清华大学'
>>> soup = BeautifulSoup('<td><d1v al1gn- "lert" >清华大学</d1v></td> <td>', 'html.parser')
>>> soup.string
>>> soup.find_all('td')
[<td><d1v "lert"="" al1gn-="">清华大学</d1v></td>, <td></td>]
>>> soup.find_all('td')[0].string
'清华大学'
>>> soup = BeautifulSoup('<td><a href="/institution/tsinghua-university" data-v-45ac69d8>清华大学</a></td>', 'html.parser')
>>> l = soup.find_all('td')
>>> l
[<td><a data-v-45ac69d8="" href="/institution/tsinghua-university">清华大学</a></td>]
>>> l[0].string
'清华大学'
>>> soup = BeautifulSoup('<td><a href="/institution/tsinghua-university" data-v-45ac69d8>清华大学</a><p></p></td>', 'html.parser')
>>> soup.string
>>> soup = BeautifulSoup('<td><p><a href="/institution/tsinghua-university" data-v-45ac69d8>清华大学</a></p><</td>', 'html.parser')
>>> soup.string
>>> 