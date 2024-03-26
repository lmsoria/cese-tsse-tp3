# Trabajo Práctico Número 3 - Testing Unitario

## Enunciado
Seleccionar una biblioteca (o componente) del software a desarrollar en el TP final de la carrera de especialización / maestría y escribir un test unitario con ceedling que incluya por lo menos 5 test cases. El archivo de test debe tener por lo menos 65 líneas de extensión.

## Descripción del componente a testear
Según [`RMC-DA-001`](https://drive.google.com/file/d/17ik5rbIs7S9iKl0JNVmAKJW53fEcZvwu) (el documento de arquitectura del proyecto final), se agregará un mecanismo de *buffering* en las etapas transmisoras. De esta manera se encolarán los distintos mensajes MIDI previos a ser enviados por la UART correspondiente.

Para lograr este fin se optó por utilizar un Buffer Circular (o *Ring Buffer*), una estructura común para estos casos.

Dentro del directorio `utils` se encuentra la biblioteca para el manejo de ring buffers desarrollada, siguiendo el patrón de encapsulamiento por *opaque pointer* aprendido en Ingeniería de Software.

### API provista
* `ring_buffer_init`: Inicializa un ring buffer del tamaño especificado. Es responsabilidad del usuario proveer un buffer de tamaño adecuado como contenedor de la estructura.
* `ring_buffer_deinit`: Libera la memoria alocada por el ring buffer. Es responsabilidad del usuario liberar la memoria del buffer pasado durante `ring_buffer_init`.
* `ring_buffer_reset`: Limpia el ring buffer, dejándolo vacío. Los datos no son limpiados, solo los índices internos.
* `ring_buffer_size`: Retorna el número de elementos almacenados en el ring buffer.
* `ring_buffer_capacity`: Retorna la capacidad máxima de elementos que se pueden almacenar en el buffer.
* `ring_buffer_is_empty`: Consulta si el buffer se encuentra vacío.
* `ring_buffer_is_full`: Consulta si el buffer se encuentra lleno.
* `ring_buffer_write_byte`: Inserta un byte en el buffer. Si el buffer se encuentra lleno, sobrescribirá los datos más viejos.
* `ring_buffer_read_byte`: Lee un byte del buffer, liberando en 1 su tamaño.

### Tests realizados:
1. Inicializar un buffer de tamaño `BUFFER_SIZE`. Verificar que se genere un puntero válido, que la capacidad del buffer sea `BUFFER_SIZE` y que el tamaño sea cero.
2. Inicializar un buffer de tamaño `BUFFER_SIZE`. Sin agregar datos, verificar que `ring_buffer_is_empty()` retorne `true` y que `ring_buffer_is_full()` retorne `false`.
3. Inicializar un buffer de tamaño `BUFFER_SIZE` y llenarlo de `BUFFER_SIZE` datos. Verificar que `ring_buffer_is_empty()` retorne `false`, que `ring_buffer_is_full()` retorne `true` y que `ring_buffer_size()` retorne `BUFFER_SIZE`.
4. Inicializar un buffer de tamaño `BUFFER_SIZE`. Sin agregar datos, intentar leer de el usando `ring_buffer_read_byte()`. Verificar que dicha función retorne `-1`.
5. Inicializar un buffer de tamaño `BUFFER_SIZE`. Llenarlo de `BUFFER_SIZE` datos. Verificar que se `ring_buffer_is_full()` retorne `true`. Luego resetear el buffer llamando a `ring_buffer_reset()`. Verificar que ahora `ring_buffer_is_true()` retorne `false` y `ring_buffer_is_empty()` retorne `true`, ademas de que `ring_buffer_size()` retorne `0`.
6. Inicializar un buffer de tamaño `BUFFER_SIZE`. Llenarlo de `BUFFER_SIZE` datos. Luego llamar a `ring_buffer_deinit()` y verificar que el ring buffer sea `NULL`, mientras que el contenedor del buffer no.
7. Inicializar un buffer de tamaño `BUFFER_SIZE`. Escribir el caracter `a` en él. Verificar que `ring_buffer_size()` retorne `1`, y que tanto `ring_buffer_is_empty()` como `ring_buffer_is_full()` retornen `false`. Luego leer el buffer. Verificar que `ring_buffer_read_byte()` retorne `0` y que el dato retornado sea `a`. Verificar que `ring_buffer_read_byte()` retorne `true` y `ring_buffer_is_full()` retorne `false`.
8. Inicializar un buffer de tamaño `BUFFER_SIZE`. Escribirle tres elementos `A`, `B` y `C`. Verificar que luego de estas escrituras `ring_buffer_size()` retorne `3`. Luego ralizar tres operaciones de lectura. Verificar que en las tres la función `ring_buffer_read_byte()` retorne `0`, y verificar que el primer elemento leído sea `A`, el segundo sea `B` y el tercero sea `C` (comportamiento FIFO). Finalmente verificar que `ring_buffer_is_empty()` retorne `true` despues de las tres lecturas.
9. Inicializar un buffer de tamaño `BUFFER_SIZE`. Llenarlo de `BUFFER_SIZE - 1` datos. Verificar que `ring_buffer_size()` retorne `BUFFER_SIZE - 1` y que `ring_buffer_is_full()` retorne `false`. Insertar el elemento `A`. Verificar que `ring_buffer_size()` retorne `BUFFER_SIZE` y que `ring_buffer_is_full()` retorne `true` esta vez. Ahora agregar el elemento `B`, para probar la sobrescritura de datos. Verificar que nuevamente `ring_buffer_size()` retorne `BUFFER_SIZE` y `ring_buffer_is_full()` retorne `true`. Ahora realizar una operación de lectura. Verificar que `ring_buffer_read_byte()` retorne `0`, y que el valor leido no sea el escrito originalmente (`0`), si no el siguiente `1`. Ludgo de leer verificar que `ring_buffer_size()` retorne `BUFFER_SIZE - 1` y que `ring_buffer_is_full()` retorne `false`.
## Uso del repositorio

Este repositorio usa [pre-commit](https://pre-comit.com) para validaciones de formato, y [ceedling](https://www.throwtheswitch.org/ceedling) para la ejecución de tests.
Para trabajar con el mismo usted debería seguir los siguientes pasos:

1. Instrucciones para instalar [`pre-commit`](https://pre-commit.com/#install)
2. Para instalar `ceedling`:
```
sudo apt install ruby
sudo gem install ceedling
```
3. Después de clonar el repositorio ejecutar el siguiente comando:
```
pre-commit install
```
4. Para compilar el código y correr los tests:
```
ceedling
```
5. Para correr reporte de coverage:
```
ceedling clobber gcov:all utils:gcov
```
