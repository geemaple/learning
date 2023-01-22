import datetime
import pandas as pd
import matplotlib.dates as mdates
import matplotlib.pyplot as plt

# The usage of the index_col and parse_dates parameters of the read_csv function to 
# define the first (0th) column as index of the resulting DataFrame and 
# convert the dates in the column to Timestamp objects, respectively.
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

plt.style.use('fivethirtyeight')
figure, axis = plt.subplots(2)
figure.canvas.manager.set_window_title('lesson 02')
figure.set_size_inches(8, 6)

#plot up prices
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

# RSI
days = 14
# calculate U and D
change = df.tail(365 + days)['close'].diff()

ups = change.copy()
downs = change.copy()

ups[ups < 0] = 0
downs[downs > 0] = 0

# calculate RS
sma_up = ups.rolling(days).mean().tail(365)
sma_down = downs.rolling(days).mean().abs().tail(365)

# scale rs to range [1, 100]
rsi = 100 * sma_up / (sma_up + sma_down)
print(rsi)

#plot rsi
ta = axis[1]
ta.set_title('Relative Strength Index')
ta.plot(rsi, color='orange', linewidth=1)

# Oversold
ta.axhline(30, linestyle='--', linewidth=1.5, color='green')
ta.axhline(70, linestyle='--', linewidth=1.5, color='red')

plt.xticks(rotation=45,  ha='right')
plt.subplots_adjust(bottom=0.2)
plt.show()