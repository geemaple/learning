import pandas as pd
import matplotlib.pyplot as plt

# The usage of the index_col and parse_dates parameters of the read_csv function to 
# define the first (0th) column as index of the resulting DataFrame and 
# convert the dates in the column to Timestamp objects, respectively.
df = pd.read_csv('BTC-USD.csv', index_col=0, parse_dates=True)
df.columns= df.columns.str.lower()
df.sort_index()
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

plt.style.use('fivethirtyeight')
figure, axis = plt.subplots(2)
figure.canvas.manager.set_window_title('lesson 01')
figure.set_size_inches(8, 6)

# #plot up prices
k = axis[0]
k.set_title('Candle Chart')
k.bar(up.index, up.close - up.open, candle, bottom=up.open, color=up_color)
k.bar(up.index, up.high - up.close, wick, bottom=up.close, color=up_color)
k.bar(up.index, up.open - up.low, wick, bottom=up.low, color=up_color)
#plot down prices
k.bar(down.index, down.open - down.close, candle, bottom=down.close, color=down_color)
k.bar(down.index, down.high - down.open, wick, bottom=down.open, color=down_color)
k.bar(down.index, down.close - down.low, wick, bottom=down.low, color=down_color)
k.axes.get_xaxis().set_visible(False)

#plot volume
ta = axis[1]
ta.set_title('Volume')
ta.bar(up.index, up.volume, candle, bottom=0, color=up_color)
ta.bar(down.index, down.volume, candle, bottom=0, color=down_color)
#rotate x-axis tick labels
plt.xticks(rotation=45,  ha='right')
plt.subplots_adjust(bottom=0.2)
plt.show()