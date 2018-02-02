# Bitácora de la Práctica 1

*Esta es una recopilación de los problemas con los que me encontré al
realizar esta práctica y los conceptos más importantes a la hora de
resolverlos. Este proyecto de bitácora cayó en desuso en las
siguientes prácticas.*

El primer problema surgió con la librería `libglew-dev`, al intentar
compilar la aplicación devolvía un error en el archivo cabecera
`glwidget.h`, donde el include de `<GL/glew.h>` producía un error que
indicaba que faltaba dicha librería.

Una vez solucionado este error ya se puede compilar la aplicación, y
vemos la ventana resultante, el único cambio extra ha sido modificar
la ventana para que en ella aparezca nuestro nombre en lugar de el
nombre por defecto.

Añadimos unas modificaciones extra al archivo `esqueleto_qt.pro` para
poder modularizar el proyecto. Estas modificaciones han sido, tras
haber añadido un árbol de directorios, indicar en qué directorio se
encontraba cada archivo que se usa en el proyecto.

En dicho archivo, si intentamos añadir manualmente algún archivo al
proyecto tenemos que añadir “include” o “src” al principio de cada
nombre, según corresponda, y un “ \” al final de cada archivo para que
pueda leer los posteriores ficheros.


A continuación procederemos a generar nuestras estructuras de datos.

En primer lugar haremos la clase “Punto”, que será la que almacene en
un vector los vértices (_vertex3f, pues es una 3-upla de reales que
permite almacenar las coordenadas de cada vértice, accedibles a cada
dato miembro que almacenan mediante x,y,z o sus correspondientes
similares como _0, _1, _2) de nuestro modelo. Además tendrá el método
“DrawPoints()”, que será el encargado de pintar los puntos del vector.

De esta clase heredará la clase “Triangulo”, que tendrá un vector de
triángulos, estos vendrán determinado por elementos de tipo _vertex3i,
donde cada entero representa índice de cada vértice que conforma el
triángulo. Así pues tendrá un método para dibujar los aristas y otro
para pintar interior del triángulo. Además le añadiremos un método
para pintar en modo ajedrez. A la hora de dibujar los aristas
tendremos que usar  `glPolygonMode(GL_FRONT_AND_BACK, GL_LINES)` para
que se pinten exclusivamente las líneas de los triángulos. Mientras
que para pintar el interior hay que usar
`glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);`. Para el ajedrez basta
usar el método anterior pero alternando en dos bucles que dibujen en
distinto color, seleccionado con `glColor3f(<red>,<green>,<blue>)`
tomando un valor `double` entre 0 y 1 cada argumento.
