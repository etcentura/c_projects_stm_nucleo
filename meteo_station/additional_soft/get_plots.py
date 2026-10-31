import serial
import re
import time
from collections import deque
from datetime import datetime

import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.ticker import FuncFormatter

# ---------------- НАСТРОЙКИ ----------------
COM_PORT = "COM4"        # <-- замените на ваш порт
BAUD_RATE = 9600
MAX_POINTS = 20          # сколько отсчётов показывать на графике

# ---------------- ДАННЫЕ ----------------
# deque с maxlen=20: при добавлении 21-го элемента первый автоматически удаляется
times   = deque(maxlen=MAX_POINTS)   # datetime объектов
lux     = deque(maxlen=MAX_POINTS)
temp    = deque(maxlen=MAX_POINTS)
hum     = deque(maxlen=MAX_POINTS)
pres    = deque(maxlen=MAX_POINTS)
# volt    = deque(maxlen=MAX_POINTS)
air     = deque(maxlen=MAX_POINTS)

# ---------------- ПАРСИНГ ----------------
# Ожидаем блоки вида:
# LUX\n85\nTEMP\n31.71\nHUM\n49.95\nPRES\n1024.10\nVOLT\n0.43\n\n
LABELS = ("LUX", "TEMP", "HUM", "PRES", "VOLT")

def parse_block(lines):
    """
    lines — список строк (без \r\n), например:
    ['LUX','85','TEMP','31.71','HUM','49.95','PRES','1024.10','VOLT','0.43']
    Возвращает dict или None, если блок неполный/битый.
    """
    if len(lines) < 10:
        return None
    data = {}
    i = 0
    while i < len(lines) - 1:
        key = lines[i].strip().upper()
        val = lines[i + 1].strip()
        if key in LABELS:
            try:
                data[key] = float(val)
            except ValueError:
                return None
            i += 2
        else:
            # пропускаем мусорные строки
            i += 1
    if all(k in data for k in LABELS):
        return data
    return None


def read_serial_loop(ser, on_block):
    """
    Читает порт построчно, накапливает буфер и при обнаружении
    полного блока из 5 пар (10 строк) вызывает on_block(dict).
    """
    buf = []
    while True:
        try:
            raw = ser.readline()
        except serial.SerialException:
            print("Порт закрыт")
            return
        if not raw:
            continue
        line = raw.decode("ascii", errors="ignore").strip()
        if line == "":
            # пустая строка — разделитель блоков
            block = parse_block(buf)
            if block is not None:
                on_block(block)
            buf = []
        else:
            buf.append(line)
            # защита от переполнения, если разделитель не пришёл
            if len(buf) > 30:
                buf = buf[-30:]


# ---------------- ГРАФИКИ ----------------
fig, axes = plt.subplots(5, 1, figsize=(10, 9), sharex=True)
fig.subplots_adjust(hspace=0.5)

plots = []
titles = ["Lux", "Temperature (°C)", "Humidity (%)", "Pressure (kPa)", "Air"]
colors = ["gold", "red", "blue", "green", "purple"]
data_queues = [lux, temp, hum, pres, air]

for ax, title, color in zip(axes, titles, colors):
    line, = ax.plot([], [], marker="o", color=color, linewidth=1.5)
    ax.set_title(title, fontsize=10, loc="left")
    ax.grid(True, linestyle=":", alpha=0.6)
    plots.append(line)

axes[-1].set_xlabel("Время")

def format_time(x, pos=None):
    # x — это timestamp (секунды), преобразуем в ЧЧ:ММ:СС
    try:
        return datetime.fromtimestamp(x).strftime("%H:%M:%S")
    except Exception:
        return ""

axes[-1].xaxis.set_major_formatter(FuncFormatter(format_time))
axes[-1].tick_params(axis="x", rotation=30)


def update_plot(frame):
    # Если данных ещё нет — ничего не рисуем
    if len(times) == 0:
        return plots

    xs = [t.timestamp() for t in times]

    for line, q in zip(plots, data_queues):
        ys = list(q)
        line.set_data(xs, ys)
        ax = line.axes
        ax.relim()
        ax.autoscale_view()

    # Ось X: показываем только последние 20 отсчётов
    if len(xs) >= 2:
        axes[-1].set_xlim(xs[0], xs[-1] + 0.5)
    return plots


# ---------------- MAIN ----------------
def main():
    ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
    print(f"Открыт {COM_PORT} на {BAUD_RATE} бод. Ждём данные...")

    current_time = str(datetime.now())
    current_time = current_time.replace(' ', '_')
    current_time = current_time.replace(':', '_')
    filename = "meteostation_{}.log".format(current_time)
    with open(filename, "w") as file:
        file.write("*"*50)
        file.write("\n")
        file.write("Log start at {}\n".format(str(datetime.now())))
        file.write("*"*50)
        file.write("\n")
    
    def on_block(data):
        now = datetime.now()
        times.append(now)
        lux.append(data["LUX"])
        temp.append(data["TEMP"])
        hum.append(data["HUM"])
        pres.append(data["PRES"])
        air_val = (data["VOLT"] / 4.0) * 100.0
        air.append(air_val)
        string_to_write = (f"{now.strftime('%H:%M:%S')}  "
            f"LUX={data['LUX']:.0f}  T={data['TEMP']:.2f}  "
            f"H={data['HUM']:.2f}  P={data['PRES']:.2f}  AIR={air_val:.2f}")
        print(string_to_write)
        with open(filename, "a") as file:
            file.write(string_to_write+'\n')

    # Запускаем чтение порта в фоновом потоке, чтобы не блокировать анимацию
    import threading
    t = threading.Thread(target=read_serial_loop, args=(ser, on_block), daemon=True)
    t.start()

    ani = animation.FuncAnimation(
        fig, update_plot, interval=500, blit=False, cache_frame_data=False
    )

    try:
        plt.show()
    finally:
        ser.close()
        print("Порт закрыт.")


if __name__ == "__main__":
    main()