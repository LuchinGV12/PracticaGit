//En este codigo no funciona el pulsador


import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

ledamarillo = 17
ledrojo = 27
zumbador = 22
pulsador = 23

GPIO.setup(ledamarillo, GPIO.OUT)
GPIO.setup(ledrojo, GPIO.OUT)
GPIO.setup(zumbador, GPIO.OUT)
GPIO.setup(pulsador, GPIO.IN)   # ERROR: falta pull_up_down

movimientos = 0

print("Sistema activo")
print("Pulsa el botón para simular movimiento\n")

try:
    while True:
        if GPIO.input(pulsador) == GPIO.HIGH:
            movimientos += 1
            print("Movimiento número:", movimientos)
            time.sleep(0.5)

            if movimientos == 1:
                GPIO.output(ledamarillo, True)

            elif movimientos == 2:
                GPIO.output(ledamarillo, False)
                GPIO.output(ledrojo, True)

            elif movimientos == 3:
                GPIO.output(ledrojo, False)
                GPIO.output(zumbador, True)
                time.sleep(5)
                GPIO.output(zumbador, False)
                movimientos = 0

except KeyboardInterrupt:
    GPIO.cleanup()