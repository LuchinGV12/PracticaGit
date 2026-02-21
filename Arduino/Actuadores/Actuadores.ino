//Ahora funciona correctamente

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
GPIO.setup(pulsador, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

movimientos = 0
clave = "1234"
clave_cambiada = False

try:
    print("Sistema activo")
    print("Pulsa el botón para simular movimiento\n")

    while True:
        if GPIO.input(pulsador) == GPIO.HIGH:
            movimientos += 1
            print("Movimiento número:", movimientos)
            time.sleep(0.5)  # antirrebote

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

                intento = input("Introduce la clave: ")

                if intento == clave:
                    print("ALARMA DESACTIVADA")

                    if not clave_cambiada:
                        while True:
                            nueva = input("Nueva clave (6 caracteres y un símbolo): ")

                            if len(nueva) == 6:
                                simbolo = False
                                for c in nueva:
                                    if not c.isalnum():
                                        simbolo = True

                                if simbolo:
                                    clave = nueva
                                    clave_cambiada = True
                                    print("Clave cambiada correctamente")
                                    break
                                else:
                                    print("Debe tener al menos un símbolo")
                            else:
                                print("Debe tener exactamente 6 caracteres")

                else:
                    print("AVISANDO A LA POLICÍA")

                movimientos = 0

except KeyboardInterrupt:
    print("Programa finalizado")

finally:
    GPIO.cleanup()