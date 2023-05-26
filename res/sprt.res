SPRITE main_sprt "sprt/zeraready.bmp" 2 4 NONE 5 CIRCLE
SPRITE elli_sprt "sprt/ojo.bmp" 4 4 NONE 5 BOX
//SPRITE elli_sprt "sprt/elliready.bmp" 4 4 NONE 5 BOX

// SPRITE nombre_variable "recurso.png" tiles_ancho tiles_alto FAST veloc_ani
// nombre variable: variable que usaremos en el main.c
// recurso.png: el nombre del archivo (opcional: poner la ruta si está en subcarpetas)
// tiles_ancho y tiles_alto: indicaremos aquí cuantos tiles mide el sprite.
// FAST: tipo de compresión, lo dejamos así de momento
// veloc_ani: tiempo entre cada frame del sprite
// Si el sprite son p.e. 32×16 pixeles, en [tiles_ancho] y [tiles_alto] pondremos 4 y 2 respectivamente ( 32/8 = 4  ,   16/8 = 2).