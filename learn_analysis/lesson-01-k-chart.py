import datetime
import pandas as pd
import matplotlib.dates as mdates
import matplotlib.pyplot as plt

df = pd.read_csv('BTC-USD.csv', index_col=0, parse_dates=True)
df.columns= df.columns.str.lower()

#latest 1 year data
prices = df.tail(365)

#define candle of candlestick elements
candle = 0.8
wick = 0.2

#define up and down prices
up = prices[prices.close>=prices.open]
down = prices[prices.close<prices.open]

#define colors to use
up_color = 'green'
down_color = 'red'

figure, axis = plt.subplots(2)
figure.canvas.manager.set_window_title('lesson 01')
figure.suptitle('k-chart')
figure.set_size_inches(8, 6)

# #plot up prices
k = axis[0]
k.bar(up.index, up.close - up.open, candle, bottom=up.open, color=up_color)
k.bar(up.index, up.high - up.close, wick, bottom=up.close, color=up_color)
k.bar(up.index, up.open - up.low, wick, bottom=up.low, color=up_color)
#plot down prices
k.bar(down.index, down.open - down.close, candle, bottom=down.close, color=down_color)
k.bar(down.index, down.high - down.open, wick, bottom=down.open, color=down_color)
k.bar(down.index, down.close - down.low, wick, bottom=down.low, color=down_color)

#plot volume
v = axis[1]
v.bar(up.index, up.volume, candle, bottom=0, color=up_color)
v.bar(down.index, down.volume, candle, bottom=0, color=down_color)
#rotate x-axis tick labels
plt.xticks(rotation=45,  ha='right')
plt.subplots_adjust(bottom=0.2)
plt.show()