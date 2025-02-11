a = float(input("Введите сумму покупки "))
if a >= 1000:
	print(f"К оплате {a - a * 0.1}")
else:
	print(f"К оплате {a}")
