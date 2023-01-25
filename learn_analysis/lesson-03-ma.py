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
figure, axis = plt.subplots(1)
figure.canvas.manager.set_window_title('lesson 02')
figure.set_size_inches(8, 6)

#plot up prices
k = axis
k.set_title('Candle Chart')
k.bar(up.index, up.close - up.open, candle, bottom=up.open, color=up_color)
k.bar(up.index, up.high - up.close, wick, bottom=up.close, color=up_color)
k.bar(up.index, up.open - up.low, wick, bottom=up.low, color=up_color)
#plot down prices
k.bar(down.index, down.open - down.close, candle, bottom=down.close, color=down_color)
k.bar(down.index, down.high - down.open, wick, bottom=down.open, color=down_color)
k.bar(down.index, down.close - down.low, wick, bottom=down.low, color=down_color)
k.axes.get_xaxis().set_visible(False)

# MA
days = 14
close_prices = df.tail(365 * 2)['close']

# SMA
sma = close_prices.tail(365 + days).rolling(days).mean().tail(365)

# WMA
weights = np.array([i for i in range(14, 0, -1)])
sum_wights = np.sum(weights)
wma = close_prices.tail(365 + days).rolling(days).apply(lambda x: np.sum(x * weights) / sum_wights).tail(365)

# EMA
ema_1 = close_prices.tail(365 + days).ewm(span=days,min_periods=days,adjust=False,ignore_na=False).mean()
ema_2 = ema_1.ewm(span=days,min_periods=days,adjust=False,ignore_na=False).mean()
ema_3 = ema_2.ewm(span=days,min_periods=days,adjust=False,ignore_na=False).mean()
ema = ema_1.tail(365)

# Double EMA
double_ema = (2 * ema_1 - ema_2).tail(365)

triple_ema = ((3 * ema_1 - 3 * ema_2) + ema_3).tail(365)
# Tripple EMA

# 200SMA
sma200 = close_prices.tail(365 + 200).rolling(200).mean().tail(365)

k.plot(sma, color='gold', linewidth=1, label='14 SMA')
k.plot(wma, color='darkorange', linewidth=1, label='14 WMA')
k.plot(ema, color='royalblue', linewidth=1, label='14 EMA')
k.plot(double_ema, color='blueviolet', linewidth=1, label='14 Double EMA')
k.plot(triple_ema, color='darkcyan', linewidth=1, label='14 Triple EMA')
k.plot(sma200, color='black', linewidth=1, label='200 SMA')
plt.legend(loc='upper right')
plt.xticks(rotation=45,  ha='right')
plt.show()