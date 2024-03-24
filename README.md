# Trabajo Práctico Número 3 - Testing Unitario

## Enunciado
Seleccionar una biblioteca (o componente) del software a desarrollar en el TP final de la carrera de especialización / maestría y escribir un test unitario con ceedling que incluya por lo menos 5 test cases. El archivo de test debe tener por lo menos 65 líneas de extensión.

## Uso del repositorio

Este repositorio usa [pre-commit](https://pre-comit.com) para validaciones de formato, y [ceedling](https://www.throwtheswitch.org/ceedling) para la ejecución de tests.
Para trabajar con el mismo usted debería tener instalado:

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
