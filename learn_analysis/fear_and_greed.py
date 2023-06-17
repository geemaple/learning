import requests
from datetime import datetime

r = requests.get('https://api.alternative.me/fng/?limit=730').json()

bear_days = 0
bull_days = 0
max_bear_days = 0
max_bull_days = 0

data = r.get('data', [])

for indicator in data[::-1]:
  date = datetime.fromtimestamp(int(indicator["timestamp"]))

  if int(indicator['value']) > 54:
    if bear_days > 0:
      print('熊结束:{} 连续天数 = {}'.format(date, bear_days))
      max_bear_days = max(bear_days, max_bear_days)
      bear_days = 0
  else:
    if bear_days == 0:
      print('熊开始:{}'.format(date))
    bear_days += 1

print('最长熊 = {}'.format(max_bear_days))