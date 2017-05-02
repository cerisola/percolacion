# Informe
En la carpeta "informe" se encuentra una copia del informe.

# Programas
En la carpeta "percolation" se ecuentran los programas utilizados para las simulaciones y hay un Makefile para compilarlos. En total hay tres programas distintos:

## percolation_critical_point_bisection_search
Este programa realiza un búsqueda por bisección del punto crítico por el método de bisección. El programa se ejecuta de la forma:

    ./percolation_critical_point_bisection_search L N precision (seed)

donde *L* es el tamaño de la red, *N* es número de realizaciones y *precision* es la precisión con la que se estima cada probabilidad crítica. Finalmente optativamente se puede pasar un último parámetro *seed* que fija la semilla del generador de números aleatorios.

En la carpeta también hay un script the Python critical_point_bisection_search.py que contiene los parámetros utilizados para las simulaciones usadas para el informe.

## percolation_probability_sweep
Este programa hace un barrido en la probabilidad de ocupación y para cada valor genera estima la probabilidad de percolación la precisión deseada. Además, para cada probabilidad también genera y guarda la estadística de los tamaños de clusters.
El programa se ejecuta de la forma:

    ./percolation_probability_sweep L ngrid pcenter decay rounding mintrials error ci maxtime (seed)
    
donde *L* es el tamaño de la red, *ngrid* es el número de puntos entre 0 y 1 a tomar, *pcenter* y *decay* fijan el centro y el coeficiente de la grilla exponencial simétrica en la cuál se divide el intervalo 0, 1 (en los headers apropiados está explicada la fórmula utilizada para la grilla). *rounding* es el número de cifras a redondear de los puntos de la grilla. *mintrials* es número mínimo de realizaciones para cada probabilidad mientras que *error* y *ci* fijan el error de la probabilidad de percolación a estimar. Finalmente *maxtime* es una cota de tiempo para seguir en caso de que alcanzar la precisión deseada tarde demasiado y *seed*, como antes, es opcional y especifica la semilla del generador de números aleatorios.

En la carpeta también hay un script the Python probability_sweep.py que contiene los parámetros utilizados para las simulaciones usadas para el informe.

## percolation_windows_mass
Este programa genera una red de un dado tamaño y luego calcula la masa del cluster percolante para ventanas de distinto tamaño. El programa se ejecuta de la forma:

    ./percolation_windows_mass L N (seed)
   
donde *L* es el tamaño de la red y *N* es el número de repeticiones sobre el cual promediar.

# Funciones con la signatura solicitada
Las funciones con la signatura y nombres solicitados (llenar, imprimir, hoshen, etc.) se encuentran definidas en los archivos
**bindings.h,c**, que luego llaman a las funciones utilizadas en el resto del programa (originalmente la había puesto otros nombres).

# Análisis de datos
Para el análisis de datos se utilizaron scripts en Python que se encuentran en la carpeta "analysis".
