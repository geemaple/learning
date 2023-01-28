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
figure.canvas.manager.set_window_title('lesson 05')
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

# Stoch
days = 14
smooth = 3
prices = df.tail(365 + days)['close']
# find High and Low
high = prices.rolling(days).max()
low = prices.rolling(days).min()

percentage_k = 100 * (prices - low) / (high - low)
percentage_d = percentage_k.rolling(smooth).mean()

#plot rsi
ta = axis[1]
ta.set_title('Stochastic Oscillator')
ta.plot(percentage_k.tail(365), color='darkorange', linewidth=1, label='%K')
ta.plot(percentage_d.tail(365), color='royalblue', linewidth=1, label='%D')

# Oversold
ta.axhline(20, linestyle='--', linewidth=1.5, color='green')
ta.axhline(80, linestyle='--', linewidth=1.5, color='red')
ta.legend(loc='lower right')

plt.xticks(rotation=45,  ha='right')
plt.subplots_adjust(bottom=0.2)
plt.show()