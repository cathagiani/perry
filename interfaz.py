import subprocess
import tkinter as tk
from tkinter import scrolledtext
import threading

def enviar_comando(event=None):
    comando = entrada_texto.get()
    if comando:
        try:
            if proceso and proceso.poll() is None:  # El proceso está en ejecución
                proceso.stdin.write(comando + '\n')
                proceso.stdin.flush()
            else:
                salida_texto.config(state=tk.NORMAL)
                salida_texto.insert(tk.END, "El juego no está en ejecución.\n")
                salida_texto.config(state=tk.DISABLED)
        except BrokenPipeError:
            salida_texto.config(state=tk.NORMAL)
            salida_texto.insert(tk.END, "Error: Pipe roto. El juego puede haber terminado.\n")
            salida_texto.config(state=tk.DISABLED)
        entrada_texto.delete(0, tk.END)

def ejecutar_juego():
    global proceso
    try:
        # Ejecutar el juego y capturar la salida
        proceso = subprocess.Popen(
            ['./juego'],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        
        # Ocultar el botón después de iniciar el juego
        btn_ejecutar.pack_forget()
        
        # Leer la salida en tiempo real y actualizar el área de texto
        def leer_salida():
            for linea in iter(proceso.stdout.readline, ''):
                salida_texto.config(state=tk.NORMAL)
                salida_texto.insert(tk.END, linea)
                salida_texto.yview(tk.END)  # Auto-scroll
                salida_texto.config(state=tk.DISABLED)
            proceso.stdout.close()

        def leer_errores():
            errores = proceso.stderr.read()
            if errores:
                salida_texto.config(state=tk.NORMAL)
                salida_texto.insert(tk.END, f"Errores:\n{errores}\n")
                salida_texto.config(state=tk.DISABLED)

        # Leer la salida y errores en hilos separados
        threading.Thread(target=leer_salida, daemon=True).start()
        threading.Thread(target=leer_errores, daemon=True).start()
    
    except Exception as e:
        salida_texto.config(state=tk.NORMAL)
        salida_texto.insert(tk.END, f"No se pudo ejecutar el juego: {e}\n")
        salida_texto.config(state=tk.DISABLED)

# Configuración de la ventana principal
ventana = tk.Tk()
ventana.title("Interfaz del Juego")
ventana.geometry("800x600")  # Tamaño de la ventana principal

# Configuración del área de texto para mensajes
salida_texto = scrolledtext.ScrolledText(ventana, width=80, height=30, state=tk.DISABLED, font=("Courier", 12))
salida_texto.pack(padx=10, pady=10, fill=tk.BOTH, expand=True)

# Configuración del área de entrada para comandos
entrada_texto = tk.Entry(ventana, width=80, font=("Courier", 12))
entrada_texto.pack(padx=10, pady=5)

# Bind de la tecla Enter a la función enviar_comando
entrada_texto.bind('<Return>', enviar_comando)

# Botón para enviar comandos
btn_enviar = tk.Button(ventana, text="Enviar Comando", command=enviar_comando, font=("Courier", 12))
btn_enviar.pack(pady=5)

# Botón para ejecutar el juego
btn_ejecutar = tk.Button(ventana, text="Ejecutar Juego", command=ejecutar_juego, font=("Courier", 12))
btn_ejecutar.pack(pady=10)

# Inicializar la variable del proceso
proceso = None

ventana.mainloop()