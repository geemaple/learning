import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def calculate_ema(prices, days, smoothing=2):
    ema = [np.nan for i in range(days - 1)]
    sma = sum(prices[:days]) / days
    ema.append(sma)
    for price in prices[days:]:
        ema.append((price * (smoothing / (1 + days))) + ema[-1] * (1 - (smoothing / (1 + days))))
    return pd.Series(ema, index=prices.index)

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
figure.canvas.manager.set_window_title('lesson 04')
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

# MACD
fast = 12
slow = 26
smooth = 9
window = max([fast, slow]) + smooth
close_prices = df['close']

ema_fast = close_prices.tail(365 + window).ewm(span=fast,min_periods=fast,adjust=False,ignore_na=False).mean()
ema_slow = close_prices.tail(365 + window).ewm(span=slow,min_periods=slow,adjust=False,ignore_na=False).mean()
macd_line = ema_fast - ema_slow
macd_signal = macd_line.ewm(span=smooth, min_periods=smooth, adjust=False, ignore_na=False).mean()
macd_histogram = macd_line - macd_signal

k.plot(ema_fast.tail(365), color='darkorange', linewidth=1, label='12 EMA')
k.plot(ema_slow.tail(365), color='royalblue', linewidth=1, label='26 EMA')
k.legend(loc='upper right')

#plot MACD
ta = axis[1]
ta.set_title('Moving Average Convergence Divergence')
ta.plot(macd_line.tail(365), color='darkorange', linewidth=1, label='MACD')
ta.plot(macd_signal.tail(365), color='royalblue', linewidth=1, label='Signal')

histogram = macd_histogram.tail(365)
for i in range(len(histogram)):
    if histogram[i] >= 0:
        ta.bar(histogram.index[i], histogram[i], color=up_color)
    else:
        ta.bar(histogram.index[i], histogram[i], color=down_color)

ta.legend(loc='lower right')

plt.xticks(rotation=45,  ha='right')
plt.subplots_adjust(bottom=0.2)
plt.show()