
/*
Esto esta guardando el numero asi:

	n = 1 2345 6789
	nodo->v = [6789,2345,1,0,0]

La idea es que solo el ultimo trozo del numero que se guardo, sea el unico que puede tener
menos de 4 digitos. Todos los demas se toman como 4 digitos.

Ejemplo:

	n = 1 0234 0056 0007		 El ultimo digito es el 1 y solo ese se toma con el tamaño que tiene
	nodo->v = [7,56,234,1,0]	 a los demás les añadimos los ceros que les faltan.

	Se puede calcular así: 7 + 56*10^4 + 234*10^8 + 1*10^12 + 0*10^16

	Igual eso creo que nunca lo vamos a calcular, porque a la hora de mostrar el numero solo le metemos 
	los ceros que le hacen falta.

*/
