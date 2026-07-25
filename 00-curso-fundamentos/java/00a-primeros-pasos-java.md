# Lección 0.1 – 0.6 — Primeros pasos en Java

> Módulo 0 — Fundamentos absolutos de Java. No se asume nada previo, aunque
> ya conoces C — usaremos esa base para comparar y que se te fije más rápido
> lo que es distinto de verdad.

## 0.1 — Qué es la JVM y por qué Java "compila distinto"

En C, el compilador (`clang`) traduce tu código directamente a instrucciones
binarias específicas de tu ordenador (Mac Intel, en tu caso). Ese binario
**solo funciona en máquinas compatibles** con esa arquitectura.

Java hace algo distinto en dos pasos:

```
HolaMundo.java  →  [ javac ]  →  HolaMundo.class  →  [ java (JVM) ]  →  se ejecuta
 (código fuente)    (compilador)   (bytecode)          (máquina virtual)
```

1. `javac` (el compilador de Java) traduce tu código a **bytecode**: un
   formato intermedio, no directamente binario de tu máquina.
2. La **JVM** (*Java Virtual Machine*) es un programa que sabe leer ese
   bytecode y ejecutarlo, traduciéndolo sobre la marcha a las instrucciones
   reales de la máquina donde corre.

Esto es lo que hace que Java sea "portable": el mismo `.class` compilado una
vez corre igual en Windows, Linux o Mac, siempre que cada sistema tenga
instalada una JVM (que es justo lo que comprobaste al principio del
proyecto con `java -version` — la versión 21 de Temurin que tienes
instalada).

## 0.2 — Primer programa: compilar y ejecutar

```java
public class HolaMundo {
    public static void main(String[] args) {
        System.out.println("Hola, mundo");
    }
}
```

Comparado con el `main` de C, hay diferencias importantes que conviene fijar
ya:

- **En Java, todo código vive dentro de una clase.** No existen funciones
  "sueltas" como en C — por eso `main` está dentro de `public class
  HolaMundo`. Y una regla estricta: **el nombre del fichero tiene que
  coincidir exactamente con el nombre de la clase pública** (`HolaMundo.java`
  para `public class HolaMundo`).
- **`public static void main(String[] args)`** es la firma exacta que
  siempre debe llevar el punto de entrada — no puedes cambiarla. `static`
  significa que este método pertenece a la clase en sí, no a un objeto
  concreto de esa clase (lo veremos en 0.5). `void` significa que no
  devuelve nada (a diferencia del `int main` de C).
- **`System.out.println(...)`** es el equivalente a `printf` de C, aunque
  aquí se accede a través de `System.out` (un objeto que representa "la
  salida estándar") y su método `println` (*print line*, que además añade
  el salto de línea automáticamente — no hace falta un `\n` explícito como
  en C).

### Compilar y ejecutar

```bash
javac HolaMundo.java   # genera HolaMundo.class (el bytecode)
java HolaMundo          # ejecuta ese bytecode (SIN la extensión .class)
```

## 0.3 — Variables, tipos primitivos vs objetos, `String`

Java distingue dos categorías de tipos, y esta distinción es más importante
de lo que parece a primera vista:

**Tipos primitivos** — parecidos a los de C, valores simples:

```java
int edad = 25;
double saldo = 1500.75;
boolean activo = true;     // en C no existe boolean nativo, usabas int (0/1)
char letra = 'A';
```

**Objetos** — todo lo demás, incluyendo algo tan básico como el texto:

```java
String nombre = "Hector";   // OJO: con mayúscula, String es una CLASE, no
                              // un tipo primitivo — es un objeto
```

Esto es una diferencia real con C: en C, una cadena era "un array de `char`
terminado en `\0`" y tú gestionabas su memoria a mano. En Java, `String` es
un objeto que gestiona su propia memoria por ti — no hay `malloc`/`free`
para cadenas en Java. De hecho, no hay `malloc`/`free` para casi nada: Java
tiene un **recolector de basura** (*garbage collector*) que libera memoria
automáticamente cuando detecta que ya nadie usa un objeto. Esto es una de
las diferencias más grandes con C, y la retomaremos cuando toque diseñar
`java-service` (menos control manual, pero también muchos menos bugs de
memoria posibles).

## 0.4 — Operadores y control de flujo

Prácticamente idéntico a C en sintaxis:

```java
if (edad >= 18) {
    System.out.println("Mayor de edad");
} else {
    System.out.println("Menor de edad");
}

for (int i = 0; i < 5; i++) {
    System.out.println(i);
}

while (edad < 30) {
    edad++;
}
```

Los operadores (`+ - * / % == != < > && || !`) se comportan igual que en C.
La diferencia real está en las condiciones: en Java, **la condición de un
`if` tiene que ser obligatoriamente un `boolean`**, no puede ser un `int`
como en C.

```java
int x = 5;
if (x) { ... }        // ERROR de compilación en Java — no compila
if (x != 0) { ... }   // así sí, porque esto SÍ es un boolean
```

Este detalle, de hecho, habría evitado por completo el bug del checkpoint
0.1 de C (`if (x = 0)`) — en Java ni siquiera compilaría, porque `x = 0` es
un `int`, no un `boolean`. Es un ejemplo real de cómo el diseño del lenguaje
puede prevenir una categoría entera de errores.

## 0.5 — Clase vs objeto: la diferencia real

Una **clase** es un molde, una plantilla. Un **objeto** es algo concreto
construido a partir de ese molde.

```java
public class Movimiento {
    String fecha;
    double importe;
    String tipo;

    // constructor: cómo se construye un objeto de esta clase
    public Movimiento(String fecha, double importe, String tipo) {
        this.fecha = fecha;
        this.importe = importe;
        this.tipo = tipo;
    }
}
```

```java
Movimiento mov1 = new Movimiento("2025-01-05", 1200.00, "ingreso");
Movimiento mov2 = new Movimiento("2025-01-06", 350.00, "gasto");
```

`Movimiento` es la clase (el molde: dice "todo movimiento tiene fecha,
importe y tipo"). `mov1` y `mov2` son objetos (instancias concretas de ese
molde, cada uno con sus propios valores). `new` es la palabra clave que
crea un objeto nuevo en memoria (aproximadamente equivalente, en espíritu,
a cuando en C hacías `malloc(sizeof(t_movimiento))` — reservar memoria para
algo nuevo —, aunque en Java no gestionas tú esa memoria después).

`this.fecha = fecha;` dentro del constructor: `this` se refiere "a este
objeto que se está construyendo ahora mismo" — distingue el parámetro
`fecha` (la variable local que llega al constructor) del campo `this.fecha`
(el que pertenece al objeto).

Esto es directamente el equivalente conceptual de tu `t_movimiento` de C,
pero con una diferencia de fondo: en C, un struct es solo datos agrupados.
En Java, una clase puede agrupar datos **y también comportamiento**
(métodos) en el mismo sitio — lo verás en la siguiente lección.

## 0.6 — Métodos: `static` vs no `static`

```java
public class Movimiento {
    String tipo;
    double importe;

    // método de INSTANCIA: opera sobre un objeto concreto (usa 'this'
    // implícitamente)
    public boolean esIngreso() {
        return tipo.equals("ingreso");
    }

    // método ESTÁTICO: pertenece a la clase, no a ningún objeto concreto
    public static double sumarImportes(Movimiento a, Movimiento b) {
        return a.importe + b.importe;
    }
}
```

```java
Movimiento mov = new Movimiento(...);
mov.esIngreso();                          // se llama SOBRE un objeto

Movimiento.sumarImportes(mov1, mov2);     // se llama SOBRE la clase
```

`main` es `static` porque, cuando el programa arranca, todavía no existe
ningún objeto creado — tiene que poder ejecutarse sin depender de una
instancia concreta.

Un detalle de sintaxis importante: `tipo.equals("ingreso")`, no `tipo ==
"ingreso"`. Con objetos (incluido `String`), `==` compara si son **el mismo
objeto en memoria**, no si su contenido es igual — esto es distinto a C,
donde `strcmp` era la única forma de comparar contenido de cadenas, y aquí
Java tiene la trampa inversa: parece que `==` debería funcionar para
strings, y a veces "funciona por casualidad", pero no es fiable. Siempre
`.equals()` para comparar contenido de objetos.

## Checkpoint 0.1 – 0.6

1. ¿Por qué `if (x)` con `x` de tipo `int` no compila en Java, mientras que
   en C sí era válido? ¿Qué tenías que hacer en C para evitar el bug del
   checkpoint anterior, y por qué Java te obliga a hacerlo siempre?
2. Escribe una clase `Persona` con dos campos (`nombre` de tipo `String`,
   `edad` de tipo `int`), un constructor que los reciba, y un método de
   instancia `esMayorDeEdad()` que devuelva `boolean`.
3. En tu propio código, ¿dónde usarías `==` y dónde `.equals()`? Pon un
   ejemplo de cada uno con los tipos que ya conoces (`int`, `String`).

Contesta estas tres y seguimos, cuando cierre el siguiente módulo de C, con
la Lección 0.7 en adelante de Java (colecciones, excepciones, Maven).
