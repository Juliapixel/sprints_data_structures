import subprocess
import random

p = subprocess.Popen("sprint3.exe", stdin=subprocess.PIPE, stdout=subprocess.PIPE)
alphabet = "abcdefghijklmnopqrstuvwxyz"
stdin = bytes()

# simular grande quantidade de valores entrados no programa
for i in range(500):
    name = ""
    for j in range(5):
        name += random.choice(alphabet)
    stdin += f"1\n{name}\n{random.randint(1,3)}\n{random.random() * 100}\n".encode("utf-8")

# simular consumo, com 0 kWh de energia disponível e sair do programa em seguida
stdin += "3\n0\n4\n".encode("utf-8")

# passar entrada de usuário simulada para o subprocesso
print(p.communicate(stdin)[0].decode("utf-8"))
