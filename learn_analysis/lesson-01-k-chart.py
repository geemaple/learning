import datetime
import pandas as pd
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

#plot up prices
plt.bar(up.index, up.close-up.open, candle, bottom=up.open, color=up_color)
plt.bar(up.index, up.high-up.close, wick, bottom=up.close, color=up_color)
plt.bar(up.index, up.low-up.open, wick, bottom=up.open, color=up_color)

#plot down prices
plt.bar(down.index, down.close-down.open, candle, bottom=down.open, color=down_color)
plt.bar(down.index, down.high-down.open, wick, bottom=down.open, color=down_color)
plt.bar(down.index, down.low-down.close, wick, bottom=down.close, color=down_color)

#rotate x-axis tick labels
plt.xticks(rotation=45,  ha='right')

plt.show()